#include "vars.h"

#ifdef ANDROID_NDK
#include "../../SDL2-2.0.5/src/core/android/SDL_android.h" // For G-Sensor
#include "zlext/android_extras.h" // For Vibration

float accelValue[3];

u16 accelScale = 1000;

// Vibration Haptics

void zlProcVibe()
{
    int vibr = vibro / 3;
    if (vibr > 10) {
        // TO_DEBUG_LOG("Vibro = %d\n", vibro / 2);
        doVibrateFromJNI(vibr);
    }
}

// G-Sensor

void zlProcGSensor()
{
    Android_JNI_GetAccelerometerValues(accelValue);
    // TO_DEBUG_LOG("X = %f, Y = %f, Z = %f\n", accelValue[0], accelValue[1], accelValue[2]);

    int x, y, z, ix, iy, iz;

    x = accelValue[0] * accelScale;
    y = accelValue[1] * accelScale;
    z = accelValue[2] * accelScale;

    // TO_DEBUG_LOG("X = %d, Y = %d, Z = %d\n", x, y, z);

    ix = x - gsensor[0];
    iy = y - gsensor[1];
    iz = z - gsensor[2];

    gsensor[0] = x;
    gsensor[1] = y;
    gsensor[2] = z;

    int gsensor_filter = 40;

    if (abs(ix) < gsensor_filter) {
        ix = 0;
    }

    if (abs(iy) < gsensor_filter) {
        iy = 0;
    }

    if (abs(iz) < gsensor_filter) {
        iz = 0;
    }

    gsensor[3] = gsensor[3] + (ix - gsensor[3]) / 4;
    gsensor[4] = gsensor[4] + (iy - gsensor[4]) / 4;
    gsensor[5] = gsensor[5] + (iz - gsensor[5]) / 4;

    int gsensor_filter0 = 5;

    if (abs(gsensor[3]) < gsensor_filter0) {
        gsensor[3] = 0;
    }

    if (abs(gsensor[4]) < gsensor_filter0) {
        gsensor[4] = 0;
    }

    if (abs(gsensor[5]) < gsensor_filter0) {
        gsensor[5] = 0;
    }
}
#endif

#ifdef GP2XCAANOO

// Vibration

#include "zlext/simple_isa1200if.h"

#include <fcntl.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define DEVICE_FILENAME "/dev/isa1200"

int fd;

void zlInitVibe(void)
{
    fd = open(DEVICE_FILENAME, O_RDWR | O_NDELAY);
    ioctl(fd, IOCTL_MOTOR_DRV_ENABLE);
    // ioctl(fd, IOCTL_SET_VIB_LEVEL, VIB_LEVEL_MAX);
}

pattern_data_t vibedata = {.act_number = 4, .vib_act_array = { { 0, 126 }, { 10, 126 }, { 20, 126 }, { 30, -126 } } };

void zlProcVibe(void)
{
    if (vibro > -64) {
        vibedata.vib_act_array[0].vib_strength = vibro;
        vibedata.vib_act_array[1].vib_strength = vibro;
        vibedata.vib_act_array[2].vib_strength = vibro;
        ioctl(fd, IOCTL_PLAY_PATTERN, &(vibedata));
    }
}

void zlShutDownVibe(void)
{
    ioctl(fd, IOCTL_MOTOR_DRV_DISABLE);
    close(fd);
}

// G-SENSOR

#include "zlext/te9_tf9_hybrid_driver.h"
// #include "zlext/te9_tf9_main.h"
#include "zlext/te9_tf9_regs.h"

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>

#include <errno.h>
#include <signal.h>
#include <sys/poll.h>
#include <sys/wait.h>

int accel_fd;
struct sigaction sigact, oldact;
int exitIrqChecker = 0;

static void irqChecker_sigHandler(int signo)
{
    switch (signo) {
        case SIGIO:
            KIONIX_ACCEL_service_interrupt();
            break;

        case SIGINT:
        case SIGQUIT:
            exitIrqChecker = 1;
            break;
    }

    return;
}

void zlInitGSensor()
{
    accel_fd = open("/dev/accel", O_RDWR);
    int oflag;
    /*
    sigact.sa_handler = irqChecker_sigHandler;
    sigemptyset(&sigact.sa_mask);
    sigact.sa_flags=SA_INTERRUPT;
    sigaction(SIGIO,&sigact,&oldact);
    */
    fcntl(accel_fd, F_SETOWN, getpid());
    oflag = fcntl(accel_fd, F_GETFL);
    fcntl(accel_fd, F_SETFL, oflag | FASYNC);

    KIONIX_ACCEL_init();
}

void zlProcGSensor()
{
    static ACCEL_XYZ accel_val;

    KIONIX_ACCEL_enable_outputs();
    /*
    KIONIX_ACCEL_read_LPF_cnt(&accel_val.x, &accel_val.y, &accel_val.z);
    debug_v[0]=accel_val.x;
    debug_v[1]=accel_val.y;
    debug_v[2]=accel_val.z;
    */
    int x, y, z, ix, iy, iz;

    KIONIX_ACCEL_read_LPF_g(&x, &y, &z);

    ix = x - gsensor[0];
    iy = y - gsensor[1];
    iz = z - gsensor[2];

    gsensor[0] = x;
    gsensor[1] = y;
    gsensor[2] = z;

    int gsensor_filter = 40;

    if (abs(ix) < gsensor_filter) {
        ix = 0;
    }

    if (abs(iy) < gsensor_filter) {
        iy = 0;
    }

    if (abs(iz) < gsensor_filter) {
        iz = 0;
    }

    gsensor[3] = gsensor[3] + (ix - gsensor[3]) / 4;
    gsensor[4] = gsensor[4] + (iy - gsensor[4]) / 4;
    gsensor[5] = gsensor[5] + (iz - gsensor[5]) / 4;

    int gsensor_filter0 = 5;

    if (abs(gsensor[3]) < gsensor_filter0) {
        gsensor[3] = 0;
    }

    if (abs(gsensor[4]) < gsensor_filter0) {
        gsensor[4] = 0;
    }

    if (abs(gsensor[5]) < gsensor_filter0) {
        gsensor[5] = 0;
    }
}

void zlShutDownGSensor()
{
    KIONIX_ACCEL_deinit();
    close(accel_fd);
}

void caanoohack(void)
{
    volatile unsigned short *mregs;
    int mdev, i, prm, myram[8] = { 3, 8, 4, 1, 1, 1, 1, 1 };

    mdev = open("/dev/mem", O_RDWR);
    mregs = mmap(0, 0x20000, PROT_READ | PROT_WRITE, MAP_SHARED, mdev, 0xc0000000);
    // myram

    prm = mregs[0x14802 >> 1] & 0x0f00;
    prm = prm | (myram[4] << 12) | (myram[5] << 4) | myram[6];
    mregs[0x14802 >> 1] = prm;
    prm = mregs[0x14804 >> 1] & 0x4000;
    prm = prm | (myram[0] << 12) | (myram[1] << 8) | (myram[2] << 4) | myram[3];
    prm = prm | 0x8000;
    mregs[0x14804 >> 1] = prm;

    for (i = 0; i < 0x100000 && (mregs[0x14804 >> 1] & 0x8000); i++) { }

    // myram
    munmap((void *) mregs, 0x20000);
    close(mdev);
}
#endif

#ifdef GP2XWIZ
void wizhack(void)
{
    volatile unsigned short *mregs;
    int mdev, i, prm, myram[8] = { 3, 9, 4, 1, 1, 1, 1, 1 };
    mdev = open("/dev/mem", O_RDWR);
    mregs = mmap(0, 0x20000, PROT_READ | PROT_WRITE, MAP_SHARED, mdev, 0xc0000000);
    // myram
    prm = mregs[0x14802 >> 1] & 0x0f00;
    prm = prm | (myram[4] << 12) | (myram[5] << 4) | myram[6];
    mregs[0x14802 >> 1] = prm;
    prm = mregs[0x14804 >> 1] & 0x4000;
    prm = prm | (myram[0] << 12) | (myram[1] << 8) | (myram[2] << 4) | myram[3];
    prm = prm | 0x8000;
    mregs[0x14804 >> 1] = prm;

    for (i = 0; i < 0x100000 && (mregs[0x14804 >> 1] & 0x8000); i++) { }

    // myram

    /*
    int mhz=700;
    int mdiv,pdiv,sdiv=0;
    int v;
    pdiv=9;
    mdiv=(mhz*pdiv)/27;
    v=(pdiv<<18)|(mdiv<<8)|sdiv;
    mregs[0xf004>>2]=v;
    mregs[0xf07c>>2]|=0x8000;
    for (i=0;(mregs[0xf07c>>2]&0x8000)&&i<0x100000;i++);
    */

    munmap((void *) mregs, 0x20000);
    close(mdev);
}
#endif

void zlextinit(void)
{
#ifdef GP2XCAANOO
    zlInitVibe();
    zlInitGSensor();

    caanoohack();
#endif
#ifdef GP2XWIZ
    wizhack();
#endif
}
void zlextframe(void)
{
    if (vibro > -64) {
        vibro -= 20;
    }

#if defined(GP2XCAANOO) || defined(ANDROID_NDK)

    if (configdata[11]) {
        zlProcGSensor();
        consoleturn[1] += ((-gsensor[0] - consoleturn[1]) >> 4);
        consoleturn[0] += (((1024 - gsensor[1]) - consoleturn[0]) >> 4);
    } else {
        gsensor[0] = 0;
        gsensor[1] = 0;
        gsensor[2] = 0;
        gsensor[3] = 0;
        gsensor[4] = 0;
        gsensor[5] = 0;
        consoleturn[0] = 0;
        consoleturn[1] = 0;
    }

    if (configdata[10]) {
        zlProcVibe();
    } else {
        vibro = -80;
    }

#endif
}

void zlextshutdown(void)
{
#ifdef GP2XCAANOO
    zlShutDownVibe();
    zlShutDownGSensor();
#endif
}
