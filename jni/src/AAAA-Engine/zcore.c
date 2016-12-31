#ifndef SDL2_PORT
#include "SDL/SDL.h"
#ifndef NO_SDL_MIXER
#include "SDL/SDL_mixer.h"
#endif
#else
#ifndef ANDROID_NDK
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif
#ifndef NO_SDL_MIXER
#ifndef ANDROID_NDK
#include <SDL2/SDL_mixer.h>
#else
#include <SDL_mixer.h>
#endif
#endif
#endif

#ifdef PC32

#include <GL/gl.h>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
SDL_Surface* screen = NULL;
#endif

#ifdef GP2XWIZ
#include "Panel/fake_os.h"
#endif

#if defined(GP2X) || defined(PC_GLES) || defined(ANDROID_NDK)
#if defined(PC_GLES) || defined(ANDROID_NDK)
// EXL: Drop X11
//#include <X11/Xlib.h>
#include "GLES/gl.h"
#include "GLES/glext.h"
#ifndef ANDROID_NDK
#include "GLES/egl.h"
// EXL: Drop EGL in Android
//#else
//#include <EGL/egl.h>
#endif
#ifndef SDL2_PORT
#include <SDL/SDL_syswm.h>
#else
#ifndef ANDROID_NDK
#include <SDL2/SDL_syswm.h>
// EXL: Drop SDL2 => EGL bindings...
//#else
//#include <SDL_syswm.h>
#endif
#endif
#endif

//Display *g_x11Display = NULL;
#endif
#ifdef GP2XCAANOO
#include "GLES/egl.h"
#include "GLES/gl.h"
#include "GLES/glext.h"
#endif
#ifdef GP2XWIZ
#include "OpenGLES/egl.h"
#include "OpenGLES/gl.h"
#include "OpenGLES/glext.h"
#endif

#ifndef ANDROID_NDK
// EXL: Drop EGL
EGLDisplay glDisplay;
EGLConfig glConfig;
EGLContext glContext;
EGLSurface glSurface;
NativeWindowType hNativeWnd = 0;
const char *gl_vendor, *gl_renderer, *gl_version, *gl_extensions;

#if defined(PC_GLES)
EGLint attrib_list_fsaa[]= {
    EGL_RED_SIZE,		5,
    EGL_GREEN_SIZE,		6,
    EGL_BLUE_SIZE,		5,
    EGL_DEPTH_SIZE,		16,
    EGL_SURFACE_TYPE,	EGL_WINDOW_BIT,
    EGL_RENDERABLE_TYPE,	EGL_OPENGL_ES_BIT,
    EGL_SAMPLE_BUFFERS,	1,
    EGL_SAMPLES,		1,
    EGL_NONE
};

EGLint attrib_list[]= {
    EGL_RED_SIZE,		5,
    EGL_GREEN_SIZE,		6,
    EGL_BLUE_SIZE,		5,
    EGL_DEPTH_SIZE,		16,
    EGL_SURFACE_TYPE,	EGL_WINDOW_BIT,
    EGL_RENDERABLE_TYPE,	EGL_OPENGL_ES_BIT,
    EGL_SAMPLE_BUFFERS,	1,
    EGL_SAMPLES,		4,
    EGL_NONE
};
#else
EGLint attrib_list_fsaa[] = { EGL_SURFACE_TYPE, EGL_WINDOW_BIT, EGL_BUFFER_SIZE, 16, EGL_DEPTH_SIZE, 16, EGL_SAMPLE_BUFFERS, 1, EGL_SAMPLES, 4, EGL_NONE };
EGLint attrib_list[] = { EGL_SURFACE_TYPE, EGL_WINDOW_BIT, EGL_BUFFER_SIZE, 16, EGL_DEPTH_SIZE, 16, EGL_NONE };
#endif
#endif

#ifndef SDL2_PORT
SDL_Surface* screen = NULL;
#else
SDL_Window *globalWindow = NULL;
SDL_GLContext *glContext_SDL = NULL;
#endif

SDL_Joystick* gamepad = NULL;

int audio_channels = 2, audio_rate = 22050, audio_buffers = 1024;
Uint16 audio_format = AUDIO_S16;

#include "render.h"
#include "vars.h"
#include "zcsound.h"
#include "zresm.h"

char spath[256];

// Video SubSystem Begin

GLushort texturedata_0[65536];

u8 filtertag[256] = {
    0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0,
    1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0,

    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //last one is noicemap

    0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

void corereloadtexture(unsigned char index)
{
    u32 ii, i;
    u16 x, y;
    i = 0;
    ii = texturepointer[index];
    for (y = 0; y < textureheader[index][2]; y++) {
        for (x = 0; x < textureheader[index][1]; x++)
            texturedata_0[i++] = texturedata[ii++];
    }

    glBindTexture(GL_TEXTURE_2D, zc_texture[index]);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    //if (index<24 | index>31)
    {
        //if ((textureheader[index][2]==16)|(index==8)|(index>=100))
        if (filtertag[index] == 0) {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        } else {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        }
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureheader[index][1], textureheader[index][2], 0, GL_RGBA, GL_UNSIGNED_SHORT_4_4_4_4, texturedata_0);
}

void coreupdatetextures(void)
{
    u16 i;
    for (i = 0; i < 256; i++)
        if (texturereload[i]) {
            texturereload[i] = 0;
            if (textureheader[i][0])
                corereloadtexture(i);
        }
}

void zcore_video_init(void)
{
    screenwidth = 800;
    screenheight = 480;
    SDL_InitSubSystem(SDL_INIT_VIDEO);
    SDL_ShowCursor(0);

#ifdef ANDROID_NDK
    // EXL: Android OpenGLES 1.1 via SDL2 initialization
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,24);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE,0);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE,0);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE,0);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE,0);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE,0);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1); // TODO: Check this.
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);

    globalWindow = SDL_CreateWindow("AAAA", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                    screenwidth, screenheight, SDL_WINDOW_OPENGL);

    TO_DEBUG_LOG("Init SDL window: %dx%d\n", screenwidth, screenheight);
    SDL_SetWindowFullscreen(globalWindow, SDL_TRUE);

    // Update Size
    SDL_GetWindowSize(globalWindow, &screenwidth, &screenheight);
    TO_DEBUG_LOG("Resize SDL window: %dx%d\n", screenwidth, screenheight);

    glContext_SDL = SDL_GL_CreateContext(globalWindow);

    glVertexPointer(3,GL_FIXED,0,mesh);
    glTexCoordPointer(2,GL_FIXED,0,mesht);
    glFogf(GL_FOG_MODE,GL_LINEAR);
    glAlphaFuncx(GL_GREATER,65536/2);
#endif

#ifdef PC_GLES
    // const char* output;
    // EGLBoolean result;
    EGLint egl_config_attr[] = {
        EGL_BUFFER_SIZE,   16,
        EGL_DEPTH_SIZE,    16,
        EGL_STENCIL_SIZE,  0,
        EGL_SURFACE_TYPE,
        EGL_WINDOW_BIT,
        EGL_NONE
    };
    //screenwidth=800;
    //screenheight=480;
    EGLint numConfigs,majorVersion,minorVersion;
    int screenbpp=16;
    globalWindow = SDL_CreateWindow("AAAA", 0, 0,
                                    screenwidth, screenheight,0?(SDL_WINDOW_OPENGL|SDL_WINDOW_FULLSCREEN):SDL_WINDOW_OPENGL);
    //screen=SDL_SetVideoMode(screenwidth,screenheight,screenbpp, SDL_SWSURFACE); // | SDL_FULLSCREEN);
    //g_x11Display = XOpenDisplay(NULL);
    glDisplay=eglGetDisplay(EGL_DEFAULT_DISPLAY);

    //#define _EGL_DSP (EGLNativeDisplayType)g_x11Display
    //glDisplay=eglGetDisplay(_EGL_DSP);
    eglInitialize(glDisplay, &majorVersion, &minorVersion );
    eglChooseConfig(glDisplay, egl_config_attr, &glConfig, 1, &numConfigs);
    SDL_SysWMinfo sysInfo;
    SDL_VERSION(&sysInfo.version); //Set SDL version
    SDL_GetWindowWMInfo(globalWindow, &sysInfo);
    glContext = eglCreateContext(glDisplay, glConfig, EGL_NO_CONTEXT, NULL);
    // Test This 0 on Android??
    glSurface=eglCreateWindowSurface(glDisplay,glConfig,(EGLNativeWindowType)sysInfo.info.x11.window,0);
    eglMakeCurrent(glDisplay, glSurface, glSurface, glContext);
    eglSwapInterval(glDisplay, 1);      // VSYNC
    glVertexPointer(3,GL_FIXED,0,mesh);
    glTexCoordPointer(2,GL_FIXED,0,mesht);
    glFogf(GL_FOG_MODE,GL_LINEAR);
    glAlphaFuncx(GL_GREATER,65536/2);
#endif

#ifdef PC32
    //screenwidth=800;
    //screenheight=600;
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    //screen=SDL_SetVideoMode(screenwidth,screenheight,32, SDL_OPENGL | SDL_FULLSCREEN);
    screen = SDL_SetVideoMode(screenwidth, screenheight, 32, SDL_OPENGL);

    glVertexPointer(3, GL_FLOAT, 0, mesh);
    glTexCoordPointer(2, GL_FLOAT, 0, mesht);
    glFogi(GL_FOG_MODE, GL_LINEAR);

    glFogf(GL_FOG_START, 5.0f);
    glFogf(GL_FOG_END, 7.0f);

    glAlphaFunc(GL_GREATER, 0.5);
    glClear(GL_ACCUM_BUFFER_BIT);
//glHint (GL_FOG_HINT, GL_NICEST);
#endif

#ifdef GP2X
    screen = SDL_SetVideoMode(320, 240, 16, SDL_OPENGL);
    EGLint numConfigs, majorVersion, minorVersion;

    hNativeWnd = OS_CreateWindow();

    glDisplay = eglGetDisplay((NativeDisplayType)0);
    eglInitialize(glDisplay, &majorVersion, &minorVersion);
    eglChooseConfig(glDisplay, attrib_list, &glConfig, 1, &numConfigs);
    glSurface = eglCreateWindowSurface(glDisplay, glConfig, hNativeWnd, attrib_list);
    glContext = eglCreateContext(glDisplay, glConfig, EGL_NO_CONTEXT, attrib_list);
    eglMakeCurrent(glDisplay, glSurface, glSurface, glContext);

    SDL_ShowCursor(SDL_DISABLE);
    glVertexPointer(3, GL_FIXED, 0, mesh);
    glTexCoordPointer(2, GL_FIXED, 0, mesht);
    glFogf(GL_FOG_MODE, GL_LINEAR);
    glAlphaFuncx(GL_GREATER, 65536 / 2);
#endif

    glGenTextures(256, zc_texture);
    glColorPointer(4, GL_UNSIGNED_BYTE, 0, meshc);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glLoadIdentity();
    coreupdatetextures();
}

void zcore_video_frame(void)
{
    if (thisframenice) {
        coreupdatetextures();
        corerenderrender();

#if defined(PC32) || defined(ANDROID_NDK)
        /*
glAccum(GL_MULT,0.5);
glAccum(GL_ACCUM,0.5);
glAccum(GL_RETURN,1.0);
*/
#ifndef SDL2_PORT
        SDL_GL_SwapBuffers();
#else
        SDL_GL_SwapWindow(globalWindow);
#endif
#endif

#if defined(GP2X) || defined (PC_GLES)
        eglSwapBuffers(glDisplay, glSurface);
#endif
    }
}

void zcore_video_down(void)
{
    glDeleteTextures(256, zc_texture);
#if defined(GP2X) || defined(PC_GLES)
    eglDestroySurface(glDisplay, glSurface);
    eglDestroyContext(glDisplay, glContext);
    eglTerminate(glDisplay);
    free(hNativeWnd);
#endif
#ifdef SDL2_PORT
    SDL_GL_DeleteContext(glContext_SDL);
    glContext_SDL = NULL;
    SDL_DestroyWindow(globalWindow);
    globalWindow = NULL;
#endif
}

// Video SubSystem End
// Sound SubSystem Begin

void zcore_sound_init(void)
{
    SDL_InitSubSystem(SDL_INIT_AUDIO);

#ifndef NO_SDL_MIXER
    Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers);
    Mix_QuerySpec(&audio_rate, &audio_format, &audio_channels);
#endif

    zcinitsound();
}

void zcore_sound_frame(void)
{
    zcsoundstep();
}

void zcore_sound_down(void)
{
#ifndef NO_SDL_MIXER
    Mix_CloseAudio();
#endif
}

// Sound SubSystem End
// Input SubSystem Begin

#ifdef ANDROID_NDK
int i_keyb[20];
static const SDL_Keycode code_keyb[20] = {
    // EXL: Motorola Photon Q and Motorola Droid 4 hardware keyboard mapping
    SDLK_BACKSPACE, SDLK_SPACE, SDLK_RETURN, SDLK_z, SDLK_LSHIFT, SDLK_x, SDLK_b, SDLK_n,
    SDLK_AC_BACK, SDLK_c, SDLK_f, SDLK_g, SDLK_h, SDLK_j, SDLK_k, SDLK_0,
    SDLK_w, SDLK_d, SDLK_s, SDLK_a
};
s8 jkey_map[16] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, -1, -1, -1, -1, -1, -1 };
#endif

#if defined(PC32) || defined(PC_GLES)
int i_keyb[20];
static const SDL_Keycode code_keyb[20] = {
    SDLK_LCTRL, SDLK_SPACE, SDLK_LALT, SDLK_z, SDLK_LSHIFT, SDLK_x, SDLK_7, SDLK_8,
    SDLK_ESCAPE, SDLK_c, SDLK_q, SDLK_w, SDLK_e, SDLK_r, SDLK_t, SDLK_BACKSPACE,
    SDLK_UP, SDLK_RIGHT, SDLK_DOWN, SDLK_LEFT
};
s8 jkey_map[16] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, -1, -1, -1, -1, -1, -1 };
#endif

#ifdef GP2XWIZ
s8 jkey_map[16] = { 12, 14, 13, 15, 10, 11, 17, 16, 8, 9, -1, -1, -1, -1, -1, -1 };
#endif

#ifdef GP2XCAANOO
s8 jkey_map[16] = { 0, 1, 2, 3, 4, 5, 0, 0, 6, 8, -1, -1, -1, -1, -1, -1 };
#endif

u16 s_mbutton;

s32 mousetapfade;

void zcore_input_init(void)
{
    u8 i;

    SDL_InitSubSystem(SDL_INIT_JOYSTICK);
    for (i = 0; i < 16; i++)
        button[i] = 0;
    if (SDL_NumJoysticks() > 0) {
        gamepad = SDL_JoystickOpen(0);
    }
#ifdef ANDROID_NDK
    for (i = 0; i < SDL_NumJoysticks(); ++i) {
        TO_DEBUG_LOG("SDL Joystick %d: %s\n", i, SDL_JoystickNameForIndex(i));
    }
#endif
}

u16 s_button[16];

void zcore_input_frame(void)
{
    u8 i, k;
    for (i = 0; i < 2; i++)
        axis[i] = 0;

    if (SDL_NumJoysticks() > 0) {
        SDL_JoystickUpdate();
        for (k = 0; k < 16; k++)
            if (jkey_map[k] >= 0) {
                if (SDL_JoystickGetButton(gamepad, jkey_map[k]) > 0) {
//                    TO_DEBUG_LOG("JP %d, k: %d", jkey_map[k], k);
                    s_button[k]++;
                }
                else
                    s_button[k] = 0;
            }
        axis[0] = SDL_JoystickGetAxis(gamepad, 0);
        axis[1] = SDL_JoystickGetAxis(gamepad, 1);

        axis[0] = axis[0] / 256;
        axis[1] = axis[1] / 256;

#ifdef GP2XWIZ
        if (SDL_JoystickGetButton(gamepad, 0) > 0)
            axis[1] = -128;
        else if (SDL_JoystickGetButton(gamepad, 1) > 0) {
            axis[1] = -128;
            axis[0] = -128;
        } else if (SDL_JoystickGetButton(gamepad, 2) > 0) {
            axis[1] = 0;
            axis[0] = -128;
        } else if (SDL_JoystickGetButton(gamepad, 3) > 0) {
            axis[1] = 128;
            axis[0] = -128;
        } else if (SDL_JoystickGetButton(gamepad, 4) > 0) {
            axis[1] = 128;
            axis[0] = 0;
        } else if (SDL_JoystickGetButton(gamepad, 5) > 0) {
            axis[1] = 128;
            axis[0] = 128;
        } else if (SDL_JoystickGetButton(gamepad, 6) > 0) {
            axis[1] = 0;
            axis[0] = 128;
        } else if (SDL_JoystickGetButton(gamepad, 7) > 0) {
            axis[1] = -128;
            axis[0] = 128;
        }
#elif ANDROID_NDK
        // EXL: Since SDL2 2.0.5 DPAD connected as Joystick
        // Checking diagonales first
        // Support for Touch Joystick
        // test_jkeys();
        if (SDL_JoystickGetButton(gamepad, 11)
                && SDL_JoystickGetButton(gamepad, 14)) { // DPAD UPRIGHT
            axis[1] = -128;
            axis[0] = 128 / 3;
        } else if (SDL_JoystickGetButton(gamepad, 11)
                && SDL_JoystickGetButton(gamepad, 13)) { // DPAD UPLEFT
            axis[1] = -128;
            axis[0] = -128 / 3;
        } else if (SDL_JoystickGetButton(gamepad, 12)
                && SDL_JoystickGetButton(gamepad, 14)) { // DPAD DOWNRIGHT
            axis[1] = 128;
            axis[0] = -128 / 3;
        } else if (SDL_JoystickGetButton(gamepad, 12)
                && SDL_JoystickGetButton(gamepad, 13)) { // DPAD DOWNLEFT
            axis[1] = 128;
            axis[0] = 128 / 3;
        } else if (SDL_JoystickGetButton(gamepad, 11)) { // DPAD UP
            axis[1] = -128;
        } else if (SDL_JoystickGetButton(gamepad, 13)) { // DPAD LEFT
            axis[1] = 0;
            axis[0] = -128 / 2;
        } else if (SDL_JoystickGetButton(gamepad, 12)) { // DPAD DOWN
            axis[1] = 128;
            axis[0] = 0;
        } else if (SDL_JoystickGetButton(gamepad, 14)) { // DPAD RIGHT
            axis[1] = 0;
            axis[0] = 128 / 2;
        } else if (SDL_JoystickGetButton(gamepad, 19)) { // DPAD OK
            s_button[0]++; // 0 - is index for firekey
        }
#endif
    } else
        for (i = 0; i < 16; i++)
            s_button[i] = 0;

    SDL_Event event;
    while (SDL_PollEvent(&event))
        switch (event.type) {
#if defined(PC32) || defined(PC_GLES) || defined(ANDROID_NDK)
        case SDL_KEYDOWN:
            for (i = 0; i < 20; i++)
                if (event.key.keysym.sym == code_keyb[i])
                    i_keyb[i] = 1;
            break;
        case SDL_KEYUP:
            for (i = 0; i < 20; i++)
                if (event.key.keysym.sym == code_keyb[i])
                    i_keyb[i] = 0;
            break;
#endif
        case SDL_QUIT:
            zcoreenabled = 0;
            break;
        }

#if defined(PC32) || defined(PC_GLES) || defined(ANDROID_NDK)
    for (k = 0; k < 16; k++) {
        if (i_keyb[k] > 0)
            s_button[k]++;
    }
    if (i_keyb[16] > 0)
        axis[1] = -128;
    if (i_keyb[17] > 0)
        axis[0] = 128;
    if (i_keyb[18] > 0)
        axis[1] = 128;
    if (i_keyb[19] > 0)
        axis[0] = -128;
#endif

    for (i = 0; i < 16; i++)
        if (s_button[i])
            button[i]++;
        else
            button[i] = 0;

#ifndef ANDROID_NDK
    //TouchMouse
    if (SDL_GetMouseState(&mouseaxis[0], &mouseaxis[1]))
        s_mbutton++;
    else
        s_mbutton = 0;

    if (s_mbutton == 1) {
        holdmouseaxis[0] = mouseaxis[0];
        holdmouseaxis[1] = mouseaxis[1];
    }

    mousetap = 0;
    if (s_mbutton > 0 & mousebutton[0] == 0 & mousetapfade > 0)
        mousetap = 1;

    mousebutton[0] = s_mbutton;

    if (mousebutton[0] == 1)
        mousetapfade = 32;
    else if (mousetapfade > 0)
        mousetapfade--;
#endif
#ifdef GP2XWIZ
    if (button[6]) {
        if (configdata[8] > 0)
            configdata[8]--;
        if (configdata[9] > 0)
            configdata[9]--;
    }
    if (button[7]) {
        if (configdata[8] < 128)
            configdata[8]++;
        if (configdata[9] < 128)
            configdata[9]++;
    }

#endif
}

#ifdef ANDROID_NDK
void test_jkeys(void)
{
    int i, c = SDL_JoystickNumButtons(gamepad);
    char string[100] = { 0 };
    for (i = 0; i < c; ++i) {
        sprintf(string + strlen(string), "%d ", SDL_JoystickGetButton(gamepad, i));
    }
    TO_DEBUG_LOG("JButtons count: %d; Keys: %s\n", c, string);
}
#endif

void zcore_input_down(void)
{
}

// Input SubSystem End
s32 fpsdone, tickcount2 = 0, tickcount3 = 0, fstick1, fstick0;
void calcfps(void)
{
    tickcount3 = tickcount;
    tickcount = SDL_GetTicks();
    frametime = tickcount - tickcount3;
    if (tickcount - tickcount2 >= 1000) {
        fps = fpsdone;
        fpsdone++;
        tickcount2 = tickcount;
        fpsdone = 0;
    }
    fpsdone++;
}

void zcoreinit(void)
{
    zcore_sound_init();
    zcore_video_init();
    zcore_input_init();
    zlextinit();
}

void zcorestep(void)
{
    frameskip = configdata[12];
    //if (frameskip) thisframenice=((count+1) & 1); else thisframenice=1;
    if (frameskip)
        thisframenice = ((count) % (frameskip + 1)) == 0;
    else
        thisframenice = 1;
    if (gamemode == ZGM_MENU | gamemode == ZGM_CONFIG | gamemode == ZGM_SELECTOR)
        thisframenice = 1;

    zcore_input_frame();
    fstick0 = fstick1;
    corerenderreset();
    zresmstep();
    zcore_video_frame();
    zcore_sound_frame();
    zlextframe();
    count++;
    fstick1 = SDL_GetTicks();
    currenttick = fstick1;
    if (thisframenice)
        calcfps();

    if ((gamemode != ZGM_MENU) & (gamemode != ZGM_CONFIG) & (gamemode != ZGM_SELECTOR))
        if (thisframenice)
            while (fstick1 - fstick0 < 20) {
                fstick1 = SDL_GetTicks();
                usleep(100); //usleep is of linux
            }
}

void zcoreloop(void)
{
    count = 0;
    zcoreenabled = 1;
    while (zcoreenabled != 0) {
        zcorestep();
    } // Embrace thy hopeless destiny loop
}

void zcoredown(void)
{
    zcore_input_down();
    zcore_video_down();
    zcore_sound_down();
    zlextshutdown();
    SDL_Quit();

#ifdef GP2X
    chdir("/usr/gp2x");
    execl("/usr/gp2x/gp2xmenu", "/usr/gp2x/gp2xmenu", NULL);
#endif
}
