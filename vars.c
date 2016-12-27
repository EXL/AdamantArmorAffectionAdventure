#include "ztypes.h"

u8 zcoreenabled;

u32 count,levelframes,frametime;

s16 axis[4],mouseaxis[2],holdmouseaxis[2];
u16 button[16],mousebutton[4],buttonstate,mousetap;

u8 bgm,gamemode,newgamemode,playmode;
s8 gameswitchdelay=0,soundbanks=46;//-1

u8 configdata[32]=
{1,0,0,0, 0,0,1,1, 128,48, 1,1, 2,1,0,0,
99,59, 199,59, 199,59, 199,59, 199,59, 199,59, 199,59, 199,59
};//0-7 mainmenu, 8-soundvolume, 9 -music volume, 10vibro, 11gsensor, 12turbohack, 13noise 14,15hz 16-23 levels

s32 fps=0,tickcount=0;

u8 secretskin=0;

#define MESH_CNT 16384

#ifdef PC32
#include "GL/gl.h"
GLfloat mesh[MESH_CNT*3];
GLfloat mesht[MESH_CNT*2];
#endif

#ifdef GP2X
#ifdef GP2XCAANOO
#include "GLES/gl.h"
#endif
#ifdef GP2XWIZ
#include "OpenGLES/gl.h"
#endif
GLfixed mesh[MESH_CNT*3];
GLfixed mesht[MESH_CNT*2];
#endif

GLubyte meshc[MESH_CNT*4];

GLushort indices[18];
s32 fog_end;
GLuint zc_texture[256];

u8 meshtid[MESH_CNT];

u8 textureheader[256][4],texturereload[256];
u16 texturedata[1048576*5/2];
u32 texturepointer[128];

u16 meshcount;

s32 camera[6],tcamera[6],vcamera[3][4],camerasync;
u16 screenwidth,screenheight;

#define MAPSIZEH 128
#define MAPSIZEY 64

u8 level=128,lastlevel=254;

s32 rmapmaxh=(MAPSIZEH)*65536,rmapmaxy=(MAPSIZEY)*65536;
u16 mapmaxh=MAPSIZEH,mapmaxy=MAPSIZEY;
s32 truemaxmaph,truemaxmapx;


u8 mp1mode;

u8 mpheader[64];
u8 mp[MAPSIZEH][MAPSIZEH][MAPSIZEY][2];
u8 mpb[MAPSIZEH][MAPSIZEH][MAPSIZEY];

u8 mpc[MAPSIZEH+1][MAPSIZEH+1][MAPSIZEY+1];
u8 intrestingvertex[MAPSIZEH+1][MAPSIZEH+1][MAPSIZEY+1];
u8 intrestingmp[MAPSIZEH][MAPSIZEH][MAPSIZEY];
u8 terrtexx[40][4];

s32 mcube[MAPSIZEH+1][MAPSIZEH+1][MAPSIZEY+1][3];


u8 lightg[9];
s32 lightgv[3];

s32 mob[65][64];

char s_text[64];
u8 l_text;

s32 pr[129][16];

u8 mobcontrol;
s32 tpscam[16];

s32 sprite[33][8],bullet[33][16];
s32 tension[8]={255,255,255,16,0,0,255,255};

u8 playeraim=0,portraitmode=0,fpsdisplay=0,frameskip=1,thisframenice=1;

s32 vibro=127,gsensor[6]={0,0,0, 0,0,0};

s32 lcuber[3],lflare[8];

s32 i_probe[6];

u8 mobsonic[19][16];

s32 contblock[16];

s8 firstperson;

s32 consoleturn[2];

s32 narration,narationticks,narrationstate,startnarationtick,wantnarration,levelnarration[2],checkpointnotify,loserwantexit,endlevel,narrationlength,firstnightrule;

s32 autismdelay=0,autismstuff=0;

s32 debugprobe[3],levelstarttick,ltime[2],currenttick;
