#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"

#ifdef PC32

#include <GL/gl.h>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
SDL_Surface *screen = NULL;
#endif


#ifdef GP2XWIZ
#include "Panel/fake_os.h"
#endif

#ifdef GP2X
#ifdef GP2XCAANOO
#include "GLES/gl.h"
#include "GLES/egl.h"
#include "GLES/glext.h"
#endif
#ifdef GP2XWIZ
#include "OpenGLES/gl.h"
#include "OpenGLES/egl.h"
#include "OpenGLES/glext.h"
#endif

EGLDisplay glDisplay;
EGLConfig glConfig;
EGLContext glContext;
EGLSurface glSurface;
NativeWindowType hNativeWnd=0;
const char *gl_vendor,*gl_renderer,*gl_version,*gl_extensions;
EGLint attrib_list_fsaa[]={EGL_SURFACE_TYPE,EGL_WINDOW_BIT,EGL_BUFFER_SIZE,16,EGL_DEPTH_SIZE,16,EGL_SAMPLE_BUFFERS,1,EGL_SAMPLES,4,EGL_NONE};
EGLint attrib_list[]={EGL_SURFACE_TYPE,EGL_WINDOW_BIT,EGL_BUFFER_SIZE,16,EGL_DEPTH_SIZE,16,EGL_NONE};

SDL_Surface *screen = NULL;
#endif

SDL_Joystick *gamepad=NULL;

int audio_channels=2,audio_rate=22050,audio_buffers=1024;
Uint16 audio_format= AUDIO_S16;

#include "vars.h"
#include "zresm.h"
#include "render.h"
#include "zcsound.h"

char spath[256];

// Video SubSystem Begin

GLushort texturedata_0[65536];

u8 filtertag[256]=
{
0,0,0,0,1,0,0,1, 0,0,1,0,0,0,0,0,
1,1,1,1,1,1,1,1, 0,0,0,1,1,1,1,1,
1,0,0,0,0,0,0,0, 0,0,0,1,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,1,1,0,0,

0,0,0,0,0,0,0,0, 0,0,1,1,1,1,1,1,
1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
1,1,1,1,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,//last one is noicemap

0,0,1,1,1,1,1,1, 1,1,1,1,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0
};

void corereloadtexture(unsigned char index)
{
u32 ii,i;
u16 x,y;
i=0;
ii=texturepointer[index];
for (y=0;y<textureheader[index][2];y++){for (x=0;x<textureheader[index][1];x++)texturedata_0[i++]=texturedata[ii++];}

glBindTexture(GL_TEXTURE_2D,zc_texture[index]);
glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

//if (index<24 | index>31)
{
//if ((textureheader[index][2]==16)|(index==8)|(index>=100))
if (filtertag[index]==0)
{
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
}
else
{
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
}
}
glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,textureheader[index][1],textureheader[index][2],0,GL_RGBA,GL_UNSIGNED_SHORT_4_4_4_4,texturedata_0);
}

void coreupdatetextures(void)
{
u16 i;
for (i=0;i<256;i++)if (texturereload[i]){texturereload[i]=0;if (textureheader[i][0]) corereloadtexture(i);}
}

void zcore_video_init(void)
{
screenwidth=800;screenheight=480;
SDL_InitSubSystem(SDL_INIT_VIDEO);
SDL_ShowCursor(0);
SDL_ShowCursor(0);
#ifdef PC32
//screenwidth=800;
//screenheight=600;
SDL_GL_SetAttribute(SDL_GL_RED_SIZE,5);
SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,5);
SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,5);
SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,16);
SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
//screen=SDL_SetVideoMode(screenwidth,screenheight,32, SDL_OPENGL | SDL_FULLSCREEN);
screen=SDL_SetVideoMode(screenwidth,screenheight,32, SDL_OPENGL);

glVertexPointer(3,GL_FLOAT,0,mesh);
glTexCoordPointer(2,GL_FLOAT,0,mesht);
glFogi(GL_FOG_MODE,GL_LINEAR);

glFogf(GL_FOG_START,5.0f);
glFogf(GL_FOG_END,7.0f);


glAlphaFunc(GL_GREATER,0.5);
glClear(GL_ACCUM_BUFFER_BIT);
//glHint (GL_FOG_HINT, GL_NICEST);
#endif
#ifdef GP2X
screen=SDL_SetVideoMode(320,240,16, SDL_OPENGL);
EGLint numConfigs,majorVersion,minorVersion;

hNativeWnd=OS_CreateWindow();

glDisplay=eglGetDisplay((NativeDisplayType)0);
eglInitialize(glDisplay,&majorVersion,&minorVersion);
eglChooseConfig(glDisplay,attrib_list,&glConfig,1,&numConfigs);
glSurface=eglCreateWindowSurface(glDisplay,glConfig,hNativeWnd,attrib_list);
glContext=eglCreateContext(glDisplay,glConfig,EGL_NO_CONTEXT,attrib_list);
eglMakeCurrent(glDisplay,glSurface,glSurface,glContext);

SDL_ShowCursor(SDL_DISABLE);
glVertexPointer(3,GL_FIXED,0,mesh);
glTexCoordPointer(2,GL_FIXED,0,mesht);
glFogf(GL_FOG_MODE,GL_LINEAR);
glAlphaFuncx(GL_GREATER,65536/2);
#endif

glGenTextures(256,zc_texture);
glColorPointer(4,GL_UNSIGNED_BYTE,0,meshc);
glEnableClientState(GL_VERTEX_ARRAY);
glEnableClientState(GL_COLOR_ARRAY);
glEnableClientState(GL_TEXTURE_COORD_ARRAY);
glBlendFunc (GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

//glLoadIdentity();
coreupdatetextures();
}

void zcore_video_frame(void)
{
if (thisframenice)
{
coreupdatetextures();
corerenderrender();

#ifdef PC32
/*
glAccum(GL_MULT,0.5);
glAccum(GL_ACCUM,0.5);
glAccum(GL_RETURN,1.0);
*/

SDL_GL_SwapBuffers();
#endif

#ifdef GP2X
eglSwapBuffers(glDisplay, glSurface);
#endif
}
}

void zcore_video_down(void)
{
glDeleteTextures(256,zc_texture);
#ifdef GP2X
eglDestroySurface(glDisplay,glSurface);
eglDestroyContext(glDisplay,glContext);
eglTerminate(glDisplay);
free(hNativeWnd);
#endif
}

// Video SubSystem End
// Sound SubSystem Begin

void zcore_sound_init(void)
{
SDL_InitSubSystem(SDL_INIT_AUDIO);

Mix_OpenAudio(audio_rate,audio_format,audio_channels,audio_buffers);
Mix_QuerySpec(&audio_rate,&audio_format,&audio_channels);

zcinitsound();
}

void zcore_sound_frame(void)
{
zcsoundstep();
}

void zcore_sound_down(void)
{

Mix_CloseAudio();
}

// Sound SubSystem End
// Input SubSystem Begin

#ifdef PC32
int i_keyb[20];
static const SDLKey code_keyb[20]=
{
SDLK_LCTRL,SDLK_SPACE,SDLK_LALT,SDLK_z,SDLK_LSHIFT,SDLK_x,SDLK_7,SDLK_8,
SDLK_ESCAPE,SDLK_c,SDLK_q,SDLK_w,SDLK_e,SDLK_r,SDLK_t,SDLK_BACKSPACE,
SDLK_UP,SDLK_RIGHT,SDLK_DOWN,SDLK_LEFT
};
s8 jkey_map[16]={0,1,2,3,4,5,6,7,8,9,-1,-1,-1,-1,-1,-1};
#endif

#ifdef GP2XWIZ
s8 jkey_map[16]={12,14,13,15,10,11,17,16,8,9,-1,-1,-1,-1,-1,-1};
#endif

#ifdef GP2XCAANOO
s8 jkey_map[16]={ 0, 1, 2, 3, 4, 5, 0, 0,6,8,-1,-1,-1,-1,-1,-1};
#endif

u16 s_mbutton;

s32 mousetapfade;

void zcore_input_init(void)
{
u8 i;

SDL_InitSubSystem(SDL_INIT_JOYSTICK);
for (i=0;i<16;i++) button[i]=0;
if (SDL_NumJoysticks()>0) { gamepad=SDL_JoystickOpen(0);}
}

u16 s_button[16];

void zcore_input_frame(void)
{
u8 i,k;
for (i=0;i<2;i++) axis[i]=0;

if (SDL_NumJoysticks()>0)
{ SDL_JoystickUpdate();for (k=0;k<16;k++) if (jkey_map[k]>=0) {if (SDL_JoystickGetButton(gamepad,jkey_map[k])>0) s_button[k]++; else s_button[k]=0;}
axis[0]=SDL_JoystickGetAxis(gamepad,0);
axis[1]=SDL_JoystickGetAxis(gamepad,1);

axis[0]=axis[0]/256;
axis[1]=axis[1]/256;
#ifdef GP2XWIZ
if (SDL_JoystickGetButton(gamepad,0)>0) axis[1]=-128;else
if (SDL_JoystickGetButton(gamepad,1)>0) {axis[1]=-128;axis[0]=-128;}else
if (SDL_JoystickGetButton(gamepad,2)>0) {axis[1]=0;axis[0]=-128;}else
if (SDL_JoystickGetButton(gamepad,3)>0) {axis[1]=128;axis[0]=-128;}else
if (SDL_JoystickGetButton(gamepad,4)>0) {axis[1]=128;axis[0]=0;}else
if (SDL_JoystickGetButton(gamepad,5)>0) {axis[1]=128;axis[0]=128;}else
if (SDL_JoystickGetButton(gamepad,6)>0) {axis[1]=0;axis[0]=128;}else
if (SDL_JoystickGetButton(gamepad,7)>0) {axis[1]=-128;axis[0]=128;}
#endif
}
else for (i=0;i<16;i++) s_button[i]=0;

SDL_Event event;
while (SDL_PollEvent (&event))
switch (event.type)
{
#ifdef PC32
case SDL_KEYDOWN:
for (i=0;i<20;i++) if (event.key.keysym.sym==code_keyb[i]) i_keyb[i]=1; break;
case SDL_KEYUP: for (i=0;i<20;i++) if (event.key.keysym.sym==code_keyb[i]) i_keyb[i]=0; break;
#endif
case SDL_QUIT:zcoreenabled=0;break;
}

#ifdef PC32
for (k=0;k<16;k++) {if (i_keyb[k]>0) s_button[k]++;}
if (i_keyb[16]>0) axis[1]=-128;
if (i_keyb[17]>0) axis[0]=128;
if (i_keyb[18]>0) axis[1]=128;
if (i_keyb[19]>0) axis[0]=-128;
#endif

for (i=0;i<16;i++)
if (s_button[i]) button[i]++; else button[i]=0;

//TouchMouse
if (SDL_GetMouseState(&mouseaxis[0],&mouseaxis[1])) s_mbutton++; else s_mbutton=0;

if (s_mbutton==1) {holdmouseaxis[0]=mouseaxis[0];holdmouseaxis[1]=mouseaxis[1];}

mousetap=0;
if (s_mbutton>0 & mousebutton[0]==0 & mousetapfade>0) mousetap=1;

mousebutton[0]=s_mbutton;

if (mousebutton[0]==1) mousetapfade=32; else if (mousetapfade>0) mousetapfade--;

#ifdef GP2XWIZ
if (button[6]) {if (configdata[8]>0) configdata[8]--;if (configdata[9]>0) configdata[9]--;}
if (button[7]) {if (configdata[8]<128) configdata[8]++;if (configdata[9]<128) configdata[9]++;}

#endif

}

void zcore_input_down(void)
{
}

// Input SubSystem End
s32 fpsdone,tickcount2=0,tickcount3=0,fstick1,fstick0;
void calcfps(void)
{
tickcount3=tickcount;
tickcount=SDL_GetTicks();frametime=tickcount-tickcount3;
if (tickcount-tickcount2>=1000)
{fps=fpsdone;fpsdone++;tickcount2=tickcount;fpsdone=0;}
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
frameskip=configdata[12];
//if (frameskip) thisframenice=((count+1) & 1); else thisframenice=1;
if (frameskip) thisframenice=((count) % (frameskip+1))==0; else thisframenice=1;
if (gamemode==ZGM_MENU | gamemode==ZGM_CONFIG | gamemode==ZGM_SELECTOR) thisframenice=1;

zcore_input_frame();
fstick0=fstick1;
corerenderreset();
zresmstep();
zcore_video_frame();
zcore_sound_frame();
zlextframe();
count++;
fstick1=SDL_GetTicks();
currenttick=fstick1;
if (thisframenice) calcfps();

if ((gamemode!=ZGM_MENU) & (gamemode!=ZGM_CONFIG) & (gamemode!=ZGM_SELECTOR))
if (thisframenice)
while (fstick1-fstick0<20) 
{
fstick1=SDL_GetTicks();
usleep(100);//usleep is of linux
}

}

void zcoreloop(void)
{
count=0;
zcoreenabled=1;
while (zcoreenabled!=0) { zcorestep();} // Embrace thy hopeless destiny loop
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
execl("/usr/gp2x/gp2xmenu","/usr/gp2x/gp2xmenu",NULL);
#endif
}

