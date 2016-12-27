#include "vars.h"

#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"

Mix_Chunk *zc_sdn[64];
Mix_Music *m_music=NULL;

u8 last_bgm=255,bgm_vol=0;

char spath[128];

u8 idchannel=0;

void zcinitsound(void)
{
u8 i;

for (i=0;i<soundbanks;i++)
{
zc_sdn[i]=NULL;
sprintf(spath,"sfx/%i%i.wav",i/10,i%10);
zc_sdn[i]=Mix_LoadWAV(spath);
}
}

void zcplaysound(unsigned char index)
{
s32 r,l;
if (configdata[8]>0)
if (index>0)
if (index<soundbanks)
{
r=configdata[8];l=configdata[8];
Mix_SetPanning(idchannel,r,l);
Mix_PlayChannel(idchannel,zc_sdn[index],0);
idchannel=((idchannel+1)&3);
}
}

void zcsoundstep(void)
{
if (bgm_vol!=configdata[9]) {bgm_vol=configdata[9];Mix_VolumeMusic(bgm_vol);}
if (bgm!=last_bgm)
if (configdata[9]>0)
{
sprintf(spath,"bgm/%i%i.ogg",bgm/10,bgm%10);
m_music=Mix_LoadMUS(spath);
if (bgm>=50) Mix_PlayMusic(m_music,0);
else
Mix_PlayMusic(m_music,-1);
//Mix_SetMusicPosition(10.0);//Waiting new firmware
last_bgm=bgm;
}
}
#define FPML(x,y) ((((x)>>7)*((y)>>7))>>2)

void zcplaysound3d(unsigned char index,unsigned char ssize,signed long xx,signed long yy,signed long zz)
{
s32 vx,vy,vz,ss,r,l,v,v1,range;
float f_range;

if (configdata[8])
if (index>0)
if (index<soundbanks)
{
ss=ssize*65536;v=127;r=127;l=127;
vz=10000+(FPML(xx-camera[0],vcamera[2][0])+FPML(zz-camera[1],vcamera[2][1])+FPML(yy-camera[2],vcamera[2][2]));
vy=(FPML(xx-camera[0],vcamera[1][0])+FPML(zz-camera[1],vcamera[1][1])+FPML(yy-camera[2],vcamera[1][2]));
vx=(FPML(xx-camera[0],vcamera[0][0])+FPML(zz-camera[1],vcamera[0][1])+FPML(yy-camera[2],vcamera[0][2]));

if (vx>ss) v=0; else if (vx<-ss) v=0; else
if (vy>ss) v=0; else if (vy<-ss) v=0; else
if (vz>ss) v=0; else if (vz<-ss) v=0;

if (v>0)
{
if (vx>0) l=127-(127*vx)/ss; else r=127-(127*(-vx))/ss;
range=FPML(vx,vx)+FPML(vy,vy)+FPML(vz,vz);

f_range=range/65536.0;
f_range=sqrt(f_range);
range=(f_range*65536.0);
v=128-(128*range)/ss;

if (v>0)
{

r=(r*v)*configdata[8];l=(l*v)*configdata[8];
r=((r)>>14);l=((l)>>14);
if (r>127) r=127;
if (l>127) l=127;


//Mix_PlayChannel(idchannel,zc_sdn[index],0);
idchannel=Mix_PlayChannel(-1,zc_sdn[index],0);
Mix_Volume(idchannel,127);
Mix_SetPanning(idchannel,l,r);

//printf("channel %i sound id:%i v:%i l:%i r:%i range:%i pos: x%i y%i z%i\n",idchannel,index,v,l,r,range,vx,vy,vz);

//idchannel=((idchannel+1)&3);
}
}
}
}


