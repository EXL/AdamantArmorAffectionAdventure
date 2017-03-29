#ifndef VARS_H
#define VARS_H

#include "zctables.h"
#include "ztypes.h"

#include <math.h>
#include <stdio.h>

extern u8 zcoreenabled;

extern u32 count, levelframes, frametime;

extern s16 axis[4], mouseaxis[2], holdmouseaxis[2];
extern u16 button[16], mousebutton[4], buttonstate, mousetap;

extern u8 bgm, gamemode, newgamemode, playmode;
extern s8 gameswitchdelay, soundbanks;

extern u8 configdata[32];

extern s32 fps, tickcount;

extern u8 secretskin;
#define MESH_CNT 16384

#ifdef ANDROID_NDK
    // EXL: For replacing main() to SDL_main() need include SDL.h in main.c
    #include <SDL.h>
    #include <android/log.h>
    #define PATH_M 256

    #define LOG_TAG "AAAA_jni"
    #define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
    #define TO_DEBUG_LOG(...) LOGI(__VA_ARGS__)

    // EXL: Touch Joystick
    extern u8 tjoy_b[8];

    extern u16 accelScale;

    enum TJButtons {
        TJ_UP,
        TJ_LEFT,
        TJ_DOWN,
        TJ_RIGHT,
        TJ_UPRIGHT,
        TJ_UPLEFT,
        TJ_DOWNRIGHT,
        TJ_DOWNLEFT
    };

    extern char *obbMountedPath;
#else
    #define TO_DEBUG_LOG(...) fprintf(stderr, __VA_ARGS__)
    #define PATH_M 128
#endif

#ifdef PC_GL
    #include <GL/gl.h>
    extern GLfloat mesh[MESH_CNT * 3];
    extern GLfloat mesht[MESH_CNT * 2];
#endif

#if defined(GP2X) || defined(PC_GLES) || defined(ANDROID_NDK)
    #if defined(GP2XCAANOO) || defined(PC_GLES) || defined(ANDROID_NDK)
        #include <GLES/gl.h>
    #endif
    #ifdef GP2XWIZ
        #include <OpenGLES/gl.h>
    #endif
    extern GLfixed mesh[MESH_CNT * 3];
    extern GLfixed mesht[MESH_CNT * 2];
#endif
extern GLubyte meshc[MESH_CNT * 4];

extern GLushort indices[18];

extern s32 fog_end;
extern GLuint zc_texture[128];

extern u8 meshtid[MESH_CNT];

extern u8 textureheader[256][4], texturereload[256];
extern u16 texturedata[1048576 * 5 / 2];
extern u32 texturepointer[256];

extern u16 meshcount;

extern s32 camera[6], tcamera[6], vcamera[3][4], camerasync;

extern u16 screenwidth, screenheight;

#define MAPSIZEH 128
#define MAPSIZEY 64

extern u8 level, lastlevel;

extern s32 rmapmaxh, rmapmaxy, truemaxmaph, truemaxmapx;
extern u16 mapmaxh, mapmaxy;

extern u8 mp1mode;

extern u8 mpheader[64];
extern u8 mp[MAPSIZEH][MAPSIZEH][MAPSIZEY][2];
extern u8 mpb[MAPSIZEH][MAPSIZEH][MAPSIZEY];
extern u8 mpc[MAPSIZEH + 1][MAPSIZEH + 1][MAPSIZEY + 1];
extern u8 intrestingvertex[MAPSIZEH + 1][MAPSIZEH + 1][MAPSIZEY + 1];
extern u8 intrestingmp[MAPSIZEH][MAPSIZEH][MAPSIZEY];
extern s32 mcube[MAPSIZEH + 1][MAPSIZEH + 1][MAPSIZEY + 1][3];

extern u8 terrtexx[40][4];
extern u8 lightg[9];
extern s32 lightgv[3];

extern s32 mob[65][64];

extern char s_text[64];
extern u8 l_text;

extern s32 pr[129][16];

extern u8 mobcontrol;
extern s32 tpscam[16];

extern s32 sprite[33][8], bullet[33][16];
extern s32 tension[8];

extern u8 playeraim, portraitmode, fpsdisplay, frameskip, thisframenice;

extern s32 vibro, gsensor[6];

extern s32 lcuber[3], lflare[8];

extern s32 i_probe[6];

extern u8 mobsonic[19][16];

extern s32 contblock[16];

extern s8 firstperson;

extern s32 consoleturn[2];

extern s32 narration, narationticks, narrationstate, startnarationtick, wantnarration, levelnarration[2],
       checkpointnotify, loserwantexit, endlevel, narrationlength, firstnightrule;

extern s32 autismdelay, autismstuff;

extern s32 debugprobe[3], levelstarttick, ltime[2], currenttick;

extern u8 ai_attack_disable_cheat;

#endif // VARS_H
