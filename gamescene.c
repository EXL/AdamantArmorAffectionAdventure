#include "vars.h"
#include "render.h"
#include "particles.h"
#include "sprites.h"
#include "veryblend.h"
#include "bullets.h"
#include "narrator.h"

#include "zgui.h"
#include "wlight.h"
#include "mobs.h"


#include "zlmath.h"


#define RENDERCUBEW 10
#define RENDERCUBEY 9

#define RRCUBEW 20
#define RRCUBEY 18

#define FPML(x,y) ((((x)>>7)*((y)>>7))>>2)
#define FPDV(x,y)	((((x)<<6)/((y)>>6))<<4)

s32 premesh[RENDERCUBEW*2+1][RENDERCUBEW*2+1][RENDERCUBEY*2+1][3];
u8 precol[RENDERCUBEW*2+1][RENDERCUBEW*2+1][RENDERCUBEY*2+1][5];
u8 prec[RENDERCUBEW*2+1][RENDERCUBEW*2+1][RENDERCUBEY*2+1];
u8 cert[RENDERCUBEW*2][RENDERCUBEW*2][RENDERCUBEY*2];
u8 scert[RENDERCUBEW*2+1][RENDERCUBEW*2+1][RENDERCUBEY*2+1];

//u8 iseethat[RENDERCUBEW*2+1][RENDERCUBEW*2+1][RENDERCUBEY*2+1];

u8 emittick,emittick2,prevtext;
void setmp1light(u8 x,u8 y,u8 z)
{
s32 r,g,b;

r=lightg[3];
g=lightg[4];
b=lightg[5];
lcuberead(((x)<<16)+32768,((y)<<16)+32768,((z)<<16)+32768);
r+=lcuber[0];
g+=lcuber[1];
b+=lcuber[2];
if (r>255)r=255;
if (g>255)g=255;
if (b>255)b=255;

zlColor4x(r,g,b,255);
}

s32 mvx,mvy,mvz;

void predrawmp1(void)
{
s32 cx,cy,cz,cx0,cx1,cy0,cy1,cz0,cz1,x,y,z; u8 l;

cx=((camera[0])>>16);cy=((camera[2])>>16);cz=((camera)[1]>>16);
cx0=cx-RENDERCUBEW;cy0=cy-RENDERCUBEW;cz0=cz-RENDERCUBEY;
cx1=cx+RENDERCUBEW;cy1=cy+RENDERCUBEW;cz1=cz+RENDERCUBEY;

if (cx0<0) cx0=0;
if (cy0<0) cy0=0;
if (cz0<0) cz0=0;

if (cx1>mpheader[8]) cx1=mpheader[8];
if (cy1>mpheader[8]) cy1=mpheader[8];
if (cz1>mpheader[9]) cz1=mpheader[9];
for (z=cz0;z<cz1;z++)
for (y=cy0;y<cy1;y++)
for (x=cx0;x<cx1;x++)
if (mp[x][y][z][1]>0)
switch (mp[x][y][z][1])
{
case 8:newlight((x<<16)+32768,(y<<16)+32768,(z<<16)+32768,(255)+(255<<8)+(255<<16)+(2<<24));break;//white light
case 9:newlight((x<<16)+32768,(y<<16)+32768,(z<<16)+32768,(255)+(0<<8)+(0<<16)+(2<<24));break;// light
case 10:newlight((x<<16)+32768,(y<<16)+32768,(z<<16)+32768,(0)+(255<<8)+(0<<16)+(2<<24));break;// light
case 11:newlight((x<<16)+32768,(y<<16)+32768,(z<<16)+32768,(0)+(0<<8)+(255<<16)+(2<<24));break;// light
case 12:newlight((x<<16)+32768,(y<<16)+32768,(z<<16)+32768,(255)+(255<<8)+(0<<16)+(2<<24));break;// light
case 13:newlight((x<<16)+32768,(y<<16)+32768,(z<<16)+32768,(0)+(255<<8)+(255<<16)+(2<<24));break;// light
case 14:newlight((x<<16)+32768,(y<<16)+32768,(z<<16)+32768,(255)+(0<<8)+(255<<16)+(2<<24));break;// light
case 15:
l=128+f_sin[count*5]>>18;
newlight((x<<16)+32768,(y<<16)+32768,(z<<16)+32768,(l)+(l<<8)+(l<<16)+(3<<24));break;//strange light
}
}

void procmp1(u8 x,u8 y,u8 z)
{
s32 x0,y0,z0,sizex,sizey,wtx,wty,wz[4],howfar,r,g,b,ir,ig,ib,wtune;
wtx=(f_cos[(count*3)&4095])>>1;
wty=(f_sin[(count*4)&4095])>>1;
x0=((x)<<16)+32728;
y0=((y)<<16)+32728;
z0=((z)<<16)+32728;
//wtx=0;
//wty=0;wtune=0;
//if (count/16%2==0) wtx+=32768;
//if (count/16%4>1) wty+=32768;


howfar=-(FPML(x0-camera[0],vcamera[2][0])+FPML(z0-camera[1],vcamera[2][1])+FPML(y0-camera[2],vcamera[2][2]));
if (howfar>0)
switch (mp[x][y][z][1])
{
case 6://abyss;
zlColor4x(0,0,0,255);
zlBindTexture(181);
zlBeginQuads();
zlVertex3x(((x+0)<<16),((z)<<16),((y+0)<<16));
zlVertex3x(((x+1)<<16),((z)<<16),((y+0)<<16));
zlVertex3x(((x+1)<<16),((z)<<16),((y+1)<<16));
zlVertex3x(((x+0)<<16),((z)<<16),((y+1)<<16));
zlEndQuads();
break;
case 7://water;
wz[0]=16192+((f_sin[((count*16+x*475+y*531)&4095)])>>4);
wz[1]=16192+((f_sin[((count*16+(x+1)*475+y*531)&4095)])>>4);
wz[2]=16192+((f_sin[((count*16+(x+1)*475+(y+1)*531)&4095)])>>4);
wz[3]=16192+((f_sin[((count*16+x*475+(y+1)*531)&4095)])>>4);

zlBindTexture(29+((count/20)%4));
zlBeginQuads();
//zlColor4x(255,255,255,255);
if (mpc[x][y][z]) {r=lightg[3];g=lightg[4];b=lightg[5];} else {r=lightg[0];g=lightg[1];b=lightg[2];}
lcuberead(x0,y0,z0);ir=lcuber[0];ig=lcuber[1];ib=lcuber[2];
r+=ir;g+=ig;b+=ib;
if (r>255)r=255;if (g>255)g=255;if (b>255)b=255;
zlColor4x(r,g,b,255);
zlTexCoord2x(wtx+ 0,wty+65535);zlVertex3x(((x+0)<<16),((z+0)<<16)+wz[0],((y+0)<<16));
if (mpc[x+1][y][z]) {r=lightg[3];g=lightg[4];b=lightg[5];} else {r=lightg[0];g=lightg[1];b=lightg[2];}
lcuberead(x0+65536,y0,z0);ir=lcuber[0];ig=lcuber[1];ib=lcuber[2];
r+=ir;g+=ig;b+=ib;
if (r>255)r=255;if (g>255)g=255;if (b>255)b=255;
zlColor4x(r,g,b,255);
zlTexCoord2x(wtx+65535,wty+65535);zlVertex3x(((x+1)<<16),((z+0)<<16)+wz[1],((y+0)<<16));
if (mpc[x+1][y+1][z]) {r=lightg[3];g=lightg[4];b=lightg[5];} else {r=lightg[0];g=lightg[1];b=lightg[2];}
lcuberead(x0+65536,y0+65536,z0);ir=lcuber[0];ig=lcuber[1];ib=lcuber[2];
r+=ir;g+=ig;b+=ib;
if (r>255)r=255;if (g>255)g=255;if (b>255)b=255;
zlColor4x(r,g,b,255);
zlTexCoord2x(wtx+65536,wty+ 0);zlVertex3x(((x+1)<<16),((z+0)<<16)+wz[2],((y+1)<<16));
if (mpc[x][y+1][z]) {r=lightg[3];g=lightg[4];b=lightg[5];} else {r=lightg[0];g=lightg[1];b=lightg[2];}
lcuberead(x0,y0+65536,z0);ir=lcuber[0];ig=lcuber[1];ib=lcuber[2];
r+=ir;g+=ig;b+=ib;
if (r>255)r=255;if (g>255)g=255;if (b>255)b=255;
zlColor4x(r,g,b,255);
zlTexCoord2x(wtx,wty);zlVertex3x(((x+0)<<16),((z+0)<<16)+wz[3],((y+1)<<16));
zlEndQuads();
break;

case 16://red particle
if (emittick)
{
pr[128][0]=256+zlrand();

pr[128][1]=128+(zlrand()>>1);
pr[128][2]=0;
pr[128][3]=0;

pr[128][4]=x*65536+32768;
pr[128][5]=z*65536+32768;
pr[128][6]=y*65536+32768;

pr[128][10]=0;
pr[128][12]=0;
pr[128][13]=0;

pr[128][14]=0;
pr[128][15]=0;

genpartdir(128);

newparticle();
}
break;
case 17://yellow particle
if (emittick)
{
pr[128][0]=256+zlrand();
r=128+(zlrand()>>1);
pr[128][1]=r;
pr[128][2]=r;
pr[128][3]=0;

pr[128][4]=x*65536+32768;
pr[128][5]=z*65536+32768;
pr[128][6]=y*65536+32768;

pr[128][10]=0;
pr[128][12]=0;
pr[128][13]=0;

pr[128][14]=0;
pr[128][15]=0;

genpartdir(128);

newparticle();
}
break;
case 18://green particle
if (emittick)
{
pr[128][0]=256+zlrand();
r=128+(zlrand()>>1);
pr[128][1]=0;
pr[128][2]=r;
pr[128][3]=0;

pr[128][4]=x*65536+32768;
pr[128][5]=z*65536+32768;
pr[128][6]=y*65536+32768;

pr[128][10]=0;
pr[128][12]=0;
pr[128][13]=0;

pr[128][14]=0;
pr[128][15]=0;

genpartdir(128);

newparticle();
}
break;
case 19://cyan particle
if (emittick)
{
pr[128][0]=256+zlrand();
r=128+(zlrand()>>1);
pr[128][1]=0;
pr[128][2]=r;
pr[128][3]=r;

pr[128][4]=x*65536+32768;
pr[128][5]=z*65536+32768;
pr[128][6]=y*65536+32768;

pr[128][10]=0;
pr[128][12]=0;
pr[128][13]=0;

pr[128][14]=0;
pr[128][15]=0;

genpartdir(128);

newparticle();
}
break;
case 20://blue particle
if (emittick)
{
pr[128][0]=256+zlrand();
r=128+(zlrand()>>1);
pr[128][1]=0;
pr[128][2]=0;
pr[128][3]=r;

pr[128][4]=x*65536+32768;
pr[128][5]=z*65536+32768;
pr[128][6]=y*65536+32768;

pr[128][10]=0;
pr[128][12]=0;
pr[128][13]=0;

pr[128][14]=0;
pr[128][15]=0;

genpartdir(128);

newparticle();
}
break;
case 21://pink particle
if (emittick)
{
pr[128][0]=256+zlrand();
r=128+(zlrand()>>1);
pr[128][1]=r;
pr[128][2]=0;
pr[128][3]=r;

pr[128][4]=x*65536+32768;
pr[128][5]=z*65536+32768;
pr[128][6]=y*65536+32768;

pr[128][10]=0;
pr[128][12]=0;
pr[128][13]=0;

pr[128][14]=0;
pr[128][15]=0;

genpartdir(128);

newparticle();
}
break;
case 22://white particle
if (emittick)
{
pr[128][0]=256+zlrand();
r=128+64+(zlrand()>>2);
pr[128][1]=r;
pr[128][2]=r;
pr[128][3]=r;

pr[128][4]=x*65536+32768;
pr[128][5]=z*65536+32768;
pr[128][6]=y*65536+32768;

pr[128][10]=0;
pr[128][12]=0;
pr[128][13]=0;

pr[128][14]=0;
pr[128][15]=0;

genpartdir(128);

newparticle();
}
break;


case 23://fog cloud
if (emittick2)
{
pr[128][0]=512;
pr[128][1]=255;
pr[128][2]=255;
pr[128][3]=255;

pr[128][4]=x*65536+32768;
pr[128][5]=z*65536+32768;
pr[128][6]=y*65536+32768;

pr[128][10]=0;
pr[128][12]=0;
pr[128][13]=0;

pr[128][14]=0;
pr[128][15]=1;

genpartdir(128);

newparticle();
}
break;


case 24://little stone
sizex=5;sizey=5;

x0=x*65536+32768;y0=z*65536-1000;z0=y*65536+32768;

setmp1light(x,y,z);zlBindTexture(44);
zlBeginQuads();
zlTexCoord2x(    0,65536);zlVertex3x(x0-sizex*mvx,y0+  0,z0-sizex*mvz);
zlTexCoord2x(65536,65536);zlVertex3x(x0+sizex*mvx,y0+  0,z0+sizex*mvz);
zlTexCoord2x(65536,    0);zlVertex3x(x0+sizex*mvx,y0+mvy*sizey,z0+sizex*mvz);
zlTexCoord2x(    0,    0);zlVertex3x(x0-sizex*mvx,y0+mvy*sizey,z0-sizex*mvz);
zlEndQuads();
break;

case 25://little grass
sizex=5;sizey=10;

x0=x*65536+32768;y0=z*65536-3000;z0=y*65536+32768;

setmp1light(x,y,z);zlBindTexture(45);
zlBeginQuads();
zlTexCoord2x(    0,65536);zlVertex3x(x0-sizex*mvx,y0+  0,z0-sizex*mvz);
zlTexCoord2x(65536,65536);zlVertex3x(x0+sizex*mvx,y0+  0,z0+sizex*mvz);
zlTexCoord2x(65536,    0);zlVertex3x(x0+sizex*mvx,y0+mvy*sizey,z0+sizex*mvz);
zlTexCoord2x(    0,    0);zlVertex3x(x0-sizex*mvx,y0+mvy*sizey,z0-sizex*mvz);
zlEndQuads();
break;

case 26://heap of grass
sizex=8;sizey=6;

x0=x*65536+32768;y0=z*65536-2000;z0=y*65536+32768;

setmp1light(x,y,z);zlBindTexture(46);
zlBeginQuads();
zlTexCoord2x(    0,65536);zlVertex3x(x0-sizex*mvx,y0+  0,z0-sizex*mvz);
zlTexCoord2x(65536,65536);zlVertex3x(x0+sizex*mvx,y0+  0,z0+sizex*mvz);
zlTexCoord2x(65536,    0);zlVertex3x(x0+sizex*mvx,y0+mvy*sizey,z0+sizex*mvz);
zlTexCoord2x(    0,    0);zlVertex3x(x0-sizex*mvx,y0+mvy*sizey,z0-sizex*mvz);
zlEndQuads();
break;
case 27://big stone
sizex=8;sizey=16;

x0=x*65536+32768;y0=z*65536-1000;z0=y*65536+32768;
setmp1light(x,y,z);zlBindTexture(47);
zlBeginQuads();
zlTexCoord2x(    0,65536);zlVertex3x(x0-sizex*mvx,y0+  0,z0-sizex*mvz);
zlTexCoord2x(65536,65536);zlVertex3x(x0+sizex*mvx,y0+  0,z0+sizex*mvz);
zlTexCoord2x(65536,    0);zlVertex3x(x0+sizex*mvx,y0+mvy*sizey,z0+sizex*mvz);
zlTexCoord2x(    0,    0);zlVertex3x(x0-sizex*mvx,y0+mvy*sizey,z0-sizex*mvz);
zlEndQuads();
break;

case 28://tree1
sizex=16;sizey=32;

x0=x*65536+32768;y0=z*65536-4000;z0=y*65536+32768;

setmp1light(x,y,z);zlBindTexture(48);
//if (howfar>65536) zlTextureFilter(0); else zlTextureFilter(1); for better times
zlBeginQuads();
zlTexCoord2x(    0,65536);zlVertex3x(x0-sizex*mvx,y0+  0,z0-sizex*mvz);
zlTexCoord2x(65536,65536);zlVertex3x(x0+sizex*mvx,y0+  0,z0+sizex*mvz);
zlTexCoord2x(65536,    0);zlVertex3x(x0+sizex*mvx,y0+mvy*sizey,z0+sizex*mvz);
zlTexCoord2x(    0,    0);zlVertex3x(x0-sizex*mvx,y0+mvy*sizey,z0-sizex*mvz);
zlEndQuads();
break;

case 29://tree2
sizex=36;sizey=64;

x0=x*65536+32768;y0=z*65536-4000;z0=y*65536+32768;

setmp1light(x,y,z);zlBindTexture(49);
zlBeginQuads();
zlTexCoord2x(    0,65536);zlVertex3x(x0-sizex*mvx,y0+  0,z0-sizex*mvz);
zlTexCoord2x(65536,65536);zlVertex3x(x0+sizex*mvx,y0+  0,z0+sizex*mvz);
zlTexCoord2x(65536,    0);zlVertex3x(x0+sizex*mvx,y0+mvy*sizey,z0+sizex*mvz);
zlTexCoord2x(    0,    0);zlVertex3x(x0-sizex*mvx,y0+mvy*sizey,z0-sizex*mvz);
zlEndQuads();
break;

case 30://power antenna
sizex=14;sizey=52;

x0=x*65536+32768;y0=z*65536-4000;z0=y*65536+32768;

setmp1light(x,y,z);zlBindTexture(50);
zlBeginQuads();
zlTexCoord2x(    0,65536);zlVertex3x(x0-sizex*mvx,y0+  0,z0-sizex*mvz);
zlTexCoord2x(65536,65536);zlVertex3x(x0+sizex*mvx,y0+  0,z0+sizex*mvz);
zlTexCoord2x(65536,    0);zlVertex3x(x0+sizex*mvx,y0+mvy*sizey,z0+sizex*mvz);
zlTexCoord2x(    0,    0);zlVertex3x(x0-sizex*mvx,y0+mvy*sizey,z0-sizex*mvz);
zlEndQuads();
break;

case 31://explosion
sizex=16;sizey=32;

x0=x*65536+32768;y0=z*65536-1000;z0=y*65536+32768;
setmp1light(x,y,z);zlBindTexture(166+count/10%4);
zlBeginQuads();
zlTexCoord2x(    0,65536);zlVertex3x(x0-sizex*mvx,y0+  0,z0-sizex*mvz);
zlTexCoord2x(65536,65536);zlVertex3x(x0+sizex*mvx,y0+  0,z0+sizex*mvz);
zlTexCoord2x(65536,    0);zlVertex3x(x0+sizex*mvx,y0+mvy*sizey,z0+sizex*mvz);
zlTexCoord2x(    0,    0);zlVertex3x(x0-sizex*mvx,y0+mvy*sizey,z0-sizex*mvz);
zlEndQuads();
break;

case 32://zvr
sizex=8;sizey=16;
x0=x*65536+32768;y0=z*65536-1000;z0=y*65536+32768;
setmp1light(x,y,z);zlBindTexture(170);
zlBeginQuads();
zlTexCoord2x(    0,65536);zlVertex3x(x0-sizex*mvx,y0+  0,z0-sizex*mvz);
zlTexCoord2x(65536,65536);zlVertex3x(x0+sizex*mvx,y0+  0,z0+sizex*mvz);
zlTexCoord2x(65536,    0);zlVertex3x(x0+sizex*mvx,y0+mvy*sizey,z0+sizex*mvz);
zlTexCoord2x(    0,    0);zlVertex3x(x0-sizex*mvx,y0+mvy*sizey,z0-sizex*mvz);
zlEndQuads();
break;
case 33://zvr
sizex=8;sizey=16;
x0=x*65536+32768;y0=z*65536-1000;z0=y*65536+32768;
setmp1light(x,y,z);zlBindTexture(171);
zlBeginQuads();
zlTexCoord2x(    0,65536);zlVertex3x(x0-sizex*mvx,y0+  0,z0-sizex*mvz);
zlTexCoord2x(65536,65536);zlVertex3x(x0+sizex*mvx,y0+  0,z0+sizex*mvz);
zlTexCoord2x(65536,    0);zlVertex3x(x0+sizex*mvx,y0+mvy*sizey,z0+sizex*mvz);
zlTexCoord2x(    0,    0);zlVertex3x(x0-sizex*mvx,y0+mvy*sizey,z0-sizex*mvz);
zlEndQuads();
break;
case 34://zvr
sizex=8;sizey=16;
x0=x*65536+32768;y0=z*65536-1000;z0=y*65536+32768;
setmp1light(x,y,z);zlBindTexture(172);
zlBeginQuads();
zlTexCoord2x(    0,65536);zlVertex3x(x0-sizex*mvx,y0+  0,z0-sizex*mvz);
zlTexCoord2x(65536,65536);zlVertex3x(x0+sizex*mvx,y0+  0,z0+sizex*mvz);
zlTexCoord2x(65536,    0);zlVertex3x(x0+sizex*mvx,y0+mvy*sizey,z0+sizex*mvz);
zlTexCoord2x(    0,    0);zlVertex3x(x0-sizex*mvx,y0+mvy*sizey,z0-sizex*mvz);
zlEndQuads();
break;
case 35://zvr
sizex=24;sizey=48;
x0=x*65536+32768;y0=z*65536-1000;z0=y*65536+32768;
setmp1light(x,y,z);zlBindTexture(173);
zlBeginQuads();
zlTexCoord2x(    0,65536);zlVertex3x(x0-sizex*mvx,y0+  0,z0-sizex*mvz);
zlTexCoord2x(65536,65536);zlVertex3x(x0+sizex*mvx,y0+  0,z0+sizex*mvz);
zlTexCoord2x(65536,    0);zlVertex3x(x0+sizex*mvx,y0+mvy*sizey,z0+sizex*mvz);
zlTexCoord2x(    0,    0);zlVertex3x(x0-sizex*mvx,y0+mvy*sizey,z0-sizex*mvz);
zlEndQuads();
break;
case 36://zvr
sizex=8;sizey=16;
x0=x*65536+32768;y0=z*65536-1000;z0=y*65536+32768;
setmp1light(x,y,z);zlBindTexture(174);
zlBeginQuads();
zlTexCoord2x(    0,65536);zlVertex3x(x0-sizex*mvx,y0+  0,z0-sizex*mvz);
zlTexCoord2x(65536,65536);zlVertex3x(x0+sizex*mvx,y0+  0,z0+sizex*mvz);
zlTexCoord2x(65536,    0);zlVertex3x(x0+sizex*mvx,y0+mvy*sizey,z0+sizex*mvz);
zlTexCoord2x(    0,    0);zlVertex3x(x0-sizex*mvx,y0+mvy*sizey,z0-sizex*mvz);
zlEndQuads();
break;
case 37://zvr
sizex=8;sizey=16;
x0=x*65536+32768;y0=z*65536-1000;z0=y*65536+32768;
setmp1light(x,y,z);zlBindTexture(175);
zlBeginQuads();
zlTexCoord2x(    0,65536);zlVertex3x(x0-sizex*mvx,y0+  0,z0-sizex*mvz);
zlTexCoord2x(65536,65536);zlVertex3x(x0+sizex*mvx,y0+  0,z0+sizex*mvz);
zlTexCoord2x(65536,    0);zlVertex3x(x0+sizex*mvx,y0+mvy*sizey,z0+sizex*mvz);
zlTexCoord2x(    0,    0);zlVertex3x(x0-sizex*mvx,y0+mvy*sizey,z0-sizex*mvz);
zlEndQuads();
break;




//ACHIEVMENTS
case 40://achievemnt1
sizex=6;sizey=12;

x0=x*65536+32768;y0=z*65536+32768+f_sin[((count*14)&4095)]/8;z0=y*65536+32768;

setmp1light(x,y,z);zlBindTexture(17);
zlBeginQuads();
zlTexCoord2x(    0,65536);zlVertex3x(x0-sizex*mvx,y0+  0,z0-sizex*mvz);
zlTexCoord2x(65536,65536);zlVertex3x(x0+sizex*mvx,y0+  0,z0+sizex*mvz);
zlTexCoord2x(65536,    0);zlVertex3x(x0+sizex*mvx,y0+mvy*sizey,z0+sizex*mvz);
zlTexCoord2x(    0,    0);zlVertex3x(x0-sizex*mvx,y0+mvy*sizey,z0-sizex*mvz);
zlEndQuads();
break;
case 41://achievemnt1
sizex=6;sizey=12;

x0=x*65536+32768;y0=z*65536+32768+f_sin[((count*14+900)&4095)]/8;z0=y*65536+32768;

setmp1light(x,y,z);zlBindTexture(18);
zlBeginQuads();
zlTexCoord2x(    0,65536);zlVertex3x(x0-sizex*mvx,y0+  0,z0-sizex*mvz);
zlTexCoord2x(65536,65536);zlVertex3x(x0+sizex*mvx,y0+  0,z0+sizex*mvz);
zlTexCoord2x(65536,    0);zlVertex3x(x0+sizex*mvx,y0+mvy*sizey,z0+sizex*mvz);
zlTexCoord2x(    0,    0);zlVertex3x(x0-sizex*mvx,y0+mvy*sizey,z0-sizex*mvz);
zlEndQuads();
break;
case 42://achievemnt1
sizex=6;sizey=12;

x0=x*65536+32768;y0=z*65536+32768+f_sin[((count*14+2000)&4095)]/8;z0=y*65536+32768;

setmp1light(x,y,z);zlBindTexture(19);
zlBeginQuads();
zlTexCoord2x(    0,65536);zlVertex3x(x0-sizex*mvx,y0+  0,z0-sizex*mvz);
zlTexCoord2x(65536,65536);zlVertex3x(x0+sizex*mvx,y0+  0,z0+sizex*mvz);
zlTexCoord2x(65536,    0);zlVertex3x(x0+sizex*mvx,y0+mvy*sizey,z0+sizex*mvz);
zlTexCoord2x(    0,    0);zlVertex3x(x0-sizex*mvx,y0+mvy*sizey,z0-sizex*mvz);
zlEndQuads();
break;
case 43://achievemnt1
sizex=6;sizey=12;

x0=x*65536+32768;y0=z*65536+32768+f_sin[((count*14+3000)&4095)]/8;z0=y*65536+32768;

setmp1light(x,y,z);zlBindTexture(20);
zlBeginQuads();
zlTexCoord2x(    0,65536);zlVertex3x(x0-sizex*mvx,y0+  0,z0-sizex*mvz);
zlTexCoord2x(65536,65536);zlVertex3x(x0+sizex*mvx,y0+  0,z0+sizex*mvz);
zlTexCoord2x(65536,    0);zlVertex3x(x0+sizex*mvx,y0+mvy*sizey,z0+sizex*mvz);
zlTexCoord2x(    0,    0);zlVertex3x(x0-sizex*mvx,y0+mvy*sizey,z0-sizex*mvz);
zlEndQuads();
break;
case 44://achievemnt1
sizex=6;sizey=12;

x0=x*65536+32768;y0=z*65536+32768+f_sin[((count*14+1024)&4095)]/8;z0=y*65536+32768;

setmp1light(x,y,z);zlBindTexture(21);
zlBeginQuads();
zlTexCoord2x(    0,65536);zlVertex3x(x0-sizex*mvx,y0+  0,z0-sizex*mvz);
zlTexCoord2x(65536,65536);zlVertex3x(x0+sizex*mvx,y0+  0,z0+sizex*mvz);
zlTexCoord2x(65536,    0);zlVertex3x(x0+sizex*mvx,y0+mvy*sizey,z0+sizex*mvz);
zlTexCoord2x(    0,    0);zlVertex3x(x0-sizex*mvx,y0+mvy*sizey,z0-sizex*mvz);
zlEndQuads();
break;

}


}

//contblock {0r 1g 2b}

s32 mapframecount=0,maptick=0,lcx,lcy,lcz,rdata[3];
void RenderMap(void)
{
u8 cmapmaxh,cmapmaxy;

s16 x,y,z;
s32 ii_0,ii_m,ii_c,ii_t,ii_ti,r,g,b;

ii_m=0;ii_c=0,ii_ti=0,ii_t=0;

ii_m=meshcount*3;
ii_c=meshcount*4;
ii_t=meshcount*2;
ii_ti=meshcount/3;

ii_0=ii_m;

cmapmaxh=mpheader[8];
cmapmaxy=mpheader[9];

emittick=0;
emittick2=0;
if ((count % 48)==0) emittick=1;
if ((count % 240)==0) emittick2=1;

s32 cx,cy,cz,cx0,cx1,cy0,cy1,cz0,cz1,ix,iy,iz,xx,yy,zz,dd,ddx,ddy;

lcx=cx;
lcy=cy;
lcz=cz;


cx=((camera[0])>>16);cy=((camera[2])>>16);cz=((camera)[1]>>16);

cx0=cx-RENDERCUBEW;cy0=cy-RENDERCUBEW;cz0=cz-RENDERCUBEY;

cx1=cx+RENDERCUBEW;cy1=cy+RENDERCUBEW;cz1=cz+RENDERCUBEY;

if (cx0<0) cx0=0;
if (cy0<0) cy0=0;
if (cz0<0) cz0=0;

if (cx1>cmapmaxh) cx1=cmapmaxh;
if (cy1>cmapmaxh) cy1=cmapmaxh;
if (cz1>cmapmaxy) cz1=cmapmaxy;

s32 fog_end2=fog_end+65536;
u8 vis;
u32 verts=0,sverts=0,verts0=0;

u8 isee;
s32 sx,sy,sz,iisx,iisy,iisz,iseesteps,t,scx,scy,scz;

scx=camera[0];
scy=camera[2];
scz=camera[1];

sx=RENDERCUBEW*2;
sz=RENDERCUBEY*2;

contblock[0]=0;
contblock[1]=0;
contblock[2]=0;
s32 fog_eeend2=fog_end2+75536,dst;
u8 screenflag;
mapframecount++;
maptick=1;

if (maptick==1)
{
debugprobe[0]=SDL_GetTicks();

for (iz=0;iz<RENDERCUBEY*2+1;iz++)
for (iy=0;iy<RENDERCUBEW*2+1;iy++)
for (ix=0;ix<RENDERCUBEW*2+1;ix++)
{
prec[ix][iy][iz]=0;
scert[ix][iy][iz]=0;
}
for (iz=0;iz<RENDERCUBEY*2;iz++)
for (iy=0;iy<RENDERCUBEW*2;iy++)
for (ix=0;ix<RENDERCUBEW*2;ix++)
cert[ix][iy][iz]=0;

for (z=cz0;z<=cz1;z++)
for (y=cy0;y<=cy1;y++)
for (x=cx0;x<=cx1;x++)
{
if (intrestingvertex[x][y][z])
{
ix=x-cx0;iy=y-cy0;iz=z-cz0;

xx=x<<16;yy=z<<16;zz=y<<16;
screenflag=0;
verts0++;

dd=-(FPML(xx-camera[0],vcamera[2][0])+FPML(yy-camera[1],vcamera[2][1])+FPML(zz-camera[2],vcamera[2][2]));
premesh[ix][iy][iz][0]=xx;
premesh[ix][iy][iz][1]=yy;
premesh[ix][iy][iz][2]=zz;

precol[ix][iy][iz][0]=0;
precol[ix][iy][iz][1]=0;
precol[ix][iy][iz][2]=0;


if ((dd>-55000)&(dd<fog_eeend2))
{
//onscreen
ddx=(FPML(xx-camera[0],vcamera[0][0])+FPML(yy-camera[1],vcamera[0][1])+FPML(zz-camera[2],vcamera[0][2]));
dst=dd+6553;
if (dst>100)
{
//ddx=FPDV(FPML(ddx,65536+6553),dst);
if (ddx>-dst)
if (ddx<dst)
{
//ddy=(FPML(xx-camera[0],vcamera[1][0])+FPML(yy-camera[1],vcamera[1][1])+FPML(zz-camera[2],vcamera[1][2]));
//ddy=FPDV(FPML(ddy,65536+6553),dst);
//dst=dst*2;
//dst=dst>>1;
//if (ddy>-dst)
//if (ddy<dst)

sverts++;screenflag=1;

}
}
//onscreen

if (screenflag) scert[ix][iy][iz]=1;

prec[ix][iy][iz]=1;

if (mpc[x][y][z]==1) {r=lightg[3];g=lightg[4];b=lightg[5];}else
if (mpc[x][y][z]==0) {r=lightg[0];g=lightg[1];b=lightg[2];}else
{r=lightg[6];g=lightg[7];b=lightg[8];}

r+=mcube[x][y][z][0];if (r>255) r=255;
g+=mcube[x][y][z][1];if (g>255) g=255;
b+=mcube[x][y][z][2];if (b>255) b=255;

precol[ix][iy][iz][0]=r;
precol[ix][iy][iz][1]=g;
precol[ix][iy][iz][2]=b;

contblock[0]+=r;
contblock[1]+=g;
contblock[2]+=b;

precol[ix][iy][iz][3]=255;
verts++;

//if (iy>0)
if (ix<RRCUBEW)
//if (iy>0)
if (iy<RRCUBEW)
//if (iz>0)
if (iz<RRCUBEY)
cert[ix][iy][iz]=1;



}

}
}
}/*
}
}
}
*/
u8 renderit,texture;
texture=6;
u16 cubes=0,sides=0;

u8 mpid;

//zlPush();
//zlTranslate(cx*65536,(cz0-1)*65536,cy*65536);
//zlForceBindTexture(64);


prevtext=0;

if (maptick)
{
for (z=cz0;z<cz1;z++)
{
//zlTranslate(0,65536,0);
for (y=cy0;y<cy1;y++)
for (x=cx0;x<cx1;x++)
if (intrestingmp[x][y][z])
{
ix=x-cx0;
iy=y-cy0;
iz=z-cz0;

sx=x-cx+10;
sy=y-cy+10;
//sz=z-cz;

if (cert[ix][iy][iz])
{
mpid=mp[x][y][z][0];

cubes++;

texture=terrtexx[mpid][0];

renderit=1;//TOP
if (z==cmapmaxy-1) renderit=0;
else
if (z-cz>=0) renderit=0;
else
if (mp[x][y][z+1][0]>0) renderit=0;
else
if (mp[x][y][z+1][1]==7) renderit=0;
else
if (scert[ix][iy][iz+1]==0 && scert[ix+1][iy][iz+1]==0 && scert[ix][iy+1][iz+1]==0 && scert[ix+1][iy+1][iz+1]==0) renderit=0;else
/*
if (prec[ix][iy][iz+1]==0) renderit=0;else
if (prec[ix+1][iy][iz+1]==0) renderit=0;else
if (prec[ix][iy+1][iz+1]==0) renderit=0;else
if (prec[ix+1][iy+1][iz+1]==0) renderit=0;
*/
if (renderit)
{
sides++;
//if (texture!=prevtext){zlForceBindTexture(texture);prevtext=texture;}
//zlForceRender(16384+(sx+sy*22)*36,6);


//zlDrawFromIndice(6);


mesh[ii_m]=premesh[ix][iy][iz+1][0];mesh[ii_m+1]=premesh[ix][iy][iz+1][1];mesh[ii_m+2]=premesh[ix][iy][iz+1][2];
meshc[ii_c]=precol[ix][iy][iz+1][0];meshc[ii_c+1]=precol[ix][iy][iz+1][1];meshc[ii_c+2]=precol[ix][iy][iz+1][2];meshc[ii_c+3]=255;
mesht[ii_t]=0;ii_t++;
mesht[ii_t]=0;ii_t++;

mesh[ii_m+3]=premesh[ix+1][iy][iz+1][0];mesh[ii_m+4]=premesh[ix+1][iy][iz+1][1];mesh[ii_m+5]=premesh[ix+1][iy][iz+1][2];
meshc[ii_c+4]=precol[ix+1][iy][iz+1][0];meshc[ii_c+5]=precol[ix+1][iy][iz+1][1];meshc[ii_c+6]=precol[ix+1][iy][iz+1][2];meshc[ii_c+7]=255;
mesht[ii_t]=65536;ii_t++;
mesht[ii_t]=0;ii_t++;

mesh[ii_m+6]=premesh[ix][iy+1][iz+1][0];mesh[ii_m+7]=premesh[ix][iy+1][iz+1][1];mesh[ii_m+8]=premesh[ix][iy+1][iz+1][2];
meshc[ii_c+8]=precol[ix][iy+1][iz+1][0];meshc[ii_c+9]=precol[ix][iy+1][iz+1][1];meshc[ii_c+10]=precol[ix][iy+1][iz+1][2];meshc[ii_c+11]=255;
mesht[ii_t]=0;ii_t++;
mesht[ii_t]=65536;ii_t++;

mesh[ii_m+9]=mesh[ii_m+6];mesh[ii_m+10]=mesh[ii_m+7];mesh[ii_m+11]=mesh[ii_m+8];
mesh[ii_m+12]=mesh[ii_m+3];mesh[ii_m+13]=mesh[ii_m+4];mesh[ii_m+14]=mesh[ii_m+5];

meshc[ii_c+12]=meshc[ii_c+8];meshc[ii_c+13]=meshc[ii_c+9];meshc[ii_c+14]=meshc[ii_c+10];meshc[ii_c+15]=meshc[ii_c+11];
meshc[ii_c+16]=meshc[ii_c+4];meshc[ii_c+17]=meshc[ii_c+5];meshc[ii_c+18]=meshc[ii_c+6];meshc[ii_c+19]=meshc[ii_c+7];

mesht[ii_t]=mesht[ii_t-2];ii_t++;
mesht[ii_t]=mesht[ii_t-2];ii_t++;
mesht[ii_t]=mesht[ii_t-6];ii_t++;
mesht[ii_t]=mesht[ii_t-6];ii_t++;

mesh[ii_m+15]=premesh[ix+1][iy+1][iz+1][0];mesh[ii_m+16]=premesh[ix+1][iy+1][iz+1][1];mesh[ii_m+17]=premesh[ix+1][iy+1][iz+1][2];
meshc[ii_c+20]=precol[ix+1][iy+1][iz+1][0];meshc[ii_c+21]=precol[ix+1][iy+1][iz+1][1];meshc[ii_c+22]=precol[ix+1][iy+1][iz+1][2];meshc[ii_c+23]=255;
mesht[ii_t]=65536;ii_t++;
mesht[ii_t]=65536;ii_t++;

ii_m+=18;ii_c+=24;
meshtid[ii_ti]=texture;ii_ti++;
meshtid[ii_ti]=texture;ii_ti++;

}//End TOP

texture=terrtexx[mpid][2];

renderit=1;//BOTTOM
if (z<1) renderit=0;
else
if (z-cz<=0) renderit=0;
else
if (mp[x][y][z-1][0]>0) renderit=0;
else
if (scert[ix][iy][iz]==0 && scert[ix+1][iy][iz]==0 && scert[ix][iy+1][iz]==0 && scert[ix+1][iy+1][iz]==0) renderit=0;else
/*
if (prec[ix][iy][iz]==0) renderit=0;else
if (prec[ix+1][iy][iz]==0) renderit=0;else
if (prec[ix][iy+1][iz]==0) renderit=0;else
if (prec[ix+1][iy+1][iz]==0) renderit=0;
*/
if (renderit)
{
sides++;

mesh[ii_m]=premesh[ix][iy][iz][0];ii_m++;
mesh[ii_m]=premesh[ix][iy][iz][1];ii_m++;
mesh[ii_m]=premesh[ix][iy][iz][2];ii_m++;
meshc[ii_c]=precol[ix][iy][iz][0];ii_c++;
meshc[ii_c]=precol[ix][iy][iz][1];ii_c++;
meshc[ii_c]=precol[ix][iy][iz][2];ii_c++;
meshc[ii_c]=255;ii_c++;
mesht[ii_t]=0;ii_t++;
mesht[ii_t]=0;ii_t++;

mesh[ii_m]=premesh[ix+1][iy][iz][0];ii_m++;
mesh[ii_m]=premesh[ix+1][iy][iz][1];ii_m++;
mesh[ii_m]=premesh[ix+1][iy][iz][2];ii_m++;

meshc[ii_c]=precol[ix+1][iy][iz][0];ii_c++;
meshc[ii_c]=precol[ix+1][iy][iz][1];ii_c++;
meshc[ii_c]=precol[ix+1][iy][iz][2];ii_c++;
meshc[ii_c]=255;ii_c++;
mesht[ii_t]=65536;ii_t++;
mesht[ii_t]=0;ii_t++;

mesh[ii_m++]=premesh[ix][iy+1][iz][0];
mesh[ii_m++]=premesh[ix][iy+1][iz][1];
mesh[ii_m++]=premesh[ix][iy+1][iz][2];
meshc[ii_c++]=precol[ix][iy+1][iz][0];
meshc[ii_c++]=precol[ix][iy+1][iz][1];
meshc[ii_c++]=precol[ix][iy+1][iz][2];
meshc[ii_c++]=255;
mesht[ii_t++]=0;
mesht[ii_t++]=65536;

mesh[ii_m]=mesh[ii_m-3];
ii_m++;
mesh[ii_m]=mesh[ii_m-3];
ii_m++;
mesh[ii_m]=mesh[ii_m-3];
ii_m++;
mesh[ii_m]=mesh[ii_m-9];
ii_m++;
mesh[ii_m]=mesh[ii_m-9];
ii_m++;
mesh[ii_m]=mesh[ii_m-9];
ii_m++;

meshc[ii_c]=meshc[ii_c-4];
ii_c++;
meshc[ii_c]=meshc[ii_c-4];
ii_c++;
meshc[ii_c]=meshc[ii_c-4];
ii_c++;
meshc[ii_c]=meshc[ii_c-4];
ii_c++;
meshc[ii_c]=meshc[ii_c-12];
ii_c++;
meshc[ii_c]=meshc[ii_c-12];
ii_c++;
meshc[ii_c]=meshc[ii_c-12];
ii_c++;
meshc[ii_c]=meshc[ii_c-12];
ii_c++;

mesht[ii_t]=mesht[ii_t-2];
ii_t++;
mesht[ii_t]=mesht[ii_t-2];
ii_t++;
mesht[ii_t]=mesht[ii_t-6];
ii_t++;
mesht[ii_t]=mesht[ii_t-6];
ii_t++;

mesh[ii_m++]=premesh[ix+1][iy+1][iz][0];
mesh[ii_m++]=premesh[ix+1][iy+1][iz][1];
mesh[ii_m++]=premesh[ix+1][iy+1][iz][2];
meshc[ii_c++]=precol[ix+1][iy+1][iz][0];
meshc[ii_c++]=precol[ix+1][iy+1][iz][1];
meshc[ii_c++]=precol[ix+1][iy+1][iz][2];
meshc[ii_c++]=255;
mesht[ii_t++]=65536;
mesht[ii_t++]=65536;

meshtid[ii_ti++]=texture;meshtid[ii_ti++]=texture;

}//End BOTTOM

texture=terrtexx[mpid][1];

renderit=1;//FRONT
if (y==cmapmaxh-1) renderit=0;
else
if (y-cy>=0) renderit=0;
else
if (mp[x][y+1][z][0]>0) renderit=0;
else
if (scert[ix][iy+1][iz]==0 && scert[ix+1][iy+1][iz]==0 && scert[ix+1][iy+1][iz+1]==0 && scert[ix][iy+1][iz+1]==0) renderit=0;else
/*
if (prec[ix][iy+1][iz]==0) renderit=0;else
if (prec[ix+1][iy+1][iz]==0) renderit=0;else
if (prec[ix][iy+1][iz+1]==0) renderit=0;else
if (prec[ix+1][iy+1][iz+1]==0) renderit=0;
*/
if (renderit)
{
sides++;

mesh[ii_m++]=premesh[ix][iy+1][iz][0];mesh[ii_m++]=premesh[ix][iy+1][iz][1];mesh[ii_m++]=premesh[ix][iy+1][iz][2];
meshc[ii_c++]=precol[ix][iy+1][iz][0];meshc[ii_c++]=precol[ix][iy+1][iz][1];meshc[ii_c++]=precol[ix][iy+1][iz][2];meshc[ii_c++]=255;
mesht[ii_t++]=0;mesht[ii_t++]=65536;

mesh[ii_m++]=premesh[ix+1][iy+1][iz][0];mesh[ii_m++]=premesh[ix+1][iy+1][iz][1];mesh[ii_m++]=premesh[ix+1][iy+1][iz][2];
meshc[ii_c++]=precol[ix+1][iy+1][iz][0];meshc[ii_c++]=precol[ix+1][iy+1][iz][1];meshc[ii_c++]=precol[ix+1][iy+1][iz][2];meshc[ii_c++]=255;
mesht[ii_t++]=65536;mesht[ii_t++]=65536;

mesh[ii_m++]=premesh[ix][iy+1][iz+1][0];mesh[ii_m++]=premesh[ix][iy+1][iz+1][1];mesh[ii_m++]=premesh[ix][iy+1][iz+1][2];
meshc[ii_c++]=precol[ix][iy+1][iz+1][0];meshc[ii_c++]=precol[ix][iy+1][iz+1][1];meshc[ii_c++]=precol[ix][iy+1][iz+1][2];meshc[ii_c++]=255;
mesht[ii_t++]=0;mesht[ii_t++]=0;

mesh[ii_m]=mesh[ii_m-3];
ii_m++;
mesh[ii_m]=mesh[ii_m-3];
ii_m++;
mesh[ii_m]=mesh[ii_m-3];
ii_m++;
mesh[ii_m]=mesh[ii_m-9];
ii_m++;
mesh[ii_m]=mesh[ii_m-9];
ii_m++;
mesh[ii_m]=mesh[ii_m-9];
ii_m++;

meshc[ii_c]=meshc[ii_c-4];
ii_c++;
meshc[ii_c]=meshc[ii_c-4];
ii_c++;
meshc[ii_c]=meshc[ii_c-4];
ii_c++;
meshc[ii_c]=meshc[ii_c-4];
ii_c++;
meshc[ii_c]=meshc[ii_c-12];
ii_c++;
meshc[ii_c]=meshc[ii_c-12];
ii_c++;
meshc[ii_c]=meshc[ii_c-12];
ii_c++;
meshc[ii_c]=meshc[ii_c-12];
ii_c++;

mesht[ii_t]=mesht[ii_t-2];
ii_t++;
mesht[ii_t]=mesht[ii_t-2];
ii_t++;
mesht[ii_t]=mesht[ii_t-6];
ii_t++;
mesht[ii_t]=mesht[ii_t-6];
ii_t++;

mesh[ii_m++]=premesh[ix+1][iy+1][iz+1][0];mesh[ii_m++]=premesh[ix+1][iy+1][iz+1][1];mesh[ii_m++]=premesh[ix+1][iy+1][iz+1][2];
meshc[ii_c++]=precol[ix+1][iy+1][iz+1][0];meshc[ii_c++]=precol[ix+1][iy+1][iz+1][1];meshc[ii_c++]=precol[ix+1][iy+1][iz+1][2];meshc[ii_c++]=255;
mesht[ii_t++]=65536;mesht[ii_t++]=0;

meshtid[ii_ti++]=texture;meshtid[ii_ti++]=texture;

}//End FRONT

renderit=1;//BACK
if (y<1) renderit=0;
else
if (y-cy<=0) renderit=0;
else
if (mp[x][y-1][z][0]>0) renderit=0;
else
if (scert[ix][iy][iz]==0 && scert[ix+1][iy][iz]==0 && scert[ix+1][iy][iz+1]==0 && scert[ix][iy][iz+1]==0) renderit=0;else
/*
if (prec[ix][iy][iz]==0) renderit=0;else
if (prec[ix+1][iy][iz]==0) renderit=0;else
if (prec[ix][iy][iz+1]==0) renderit=0;else
if (prec[ix+1][iy][iz+1]==0) renderit=0;
*/
if (renderit)
{
sides++;

mesh[ii_m++]=premesh[ix][iy][iz][0];mesh[ii_m++]=premesh[ix][iy][iz][1];mesh[ii_m++]=premesh[ix][iy][iz][2];
meshc[ii_c++]=precol[ix][iy][iz][0];meshc[ii_c++]=precol[ix][iy][iz][1];meshc[ii_c++]=precol[ix][iy][iz][2];meshc[ii_c++]=255;
mesht[ii_t++]=65536;mesht[ii_t++]=65536;

mesh[ii_m++]=premesh[ix+1][iy][iz][0];mesh[ii_m++]=premesh[ix+1][iy][iz][1];mesh[ii_m++]=premesh[ix+1][iy][iz][2];
meshc[ii_c++]=precol[ix+1][iy][iz][0];meshc[ii_c++]=precol[ix+1][iy][iz][1];meshc[ii_c++]=precol[ix+1][iy][iz][2];meshc[ii_c++]=255;
mesht[ii_t++]=0;mesht[ii_t++]=65536;

mesh[ii_m++]=premesh[ix][iy][iz+1][0];mesh[ii_m++]=premesh[ix][iy][iz+1][1];mesh[ii_m++]=premesh[ix][iy][iz+1][2];
meshc[ii_c++]=precol[ix][iy][iz+1][0];meshc[ii_c++]=precol[ix][iy][iz+1][1];meshc[ii_c++]=precol[ix][iy][iz+1][2];meshc[ii_c++]=255;
mesht[ii_t++]=65536;mesht[ii_t++]=0;

mesh[ii_m]=mesh[ii_m-3];
ii_m++;
mesh[ii_m]=mesh[ii_m-3];
ii_m++;
mesh[ii_m]=mesh[ii_m-3];
ii_m++;
mesh[ii_m]=mesh[ii_m-9];
ii_m++;
mesh[ii_m]=mesh[ii_m-9];
ii_m++;
mesh[ii_m]=mesh[ii_m-9];
ii_m++;

meshc[ii_c]=meshc[ii_c-4];
ii_c++;
meshc[ii_c]=meshc[ii_c-4];
ii_c++;
meshc[ii_c]=meshc[ii_c-4];
ii_c++;
meshc[ii_c]=meshc[ii_c-4];
ii_c++;
meshc[ii_c]=meshc[ii_c-12];
ii_c++;
meshc[ii_c]=meshc[ii_c-12];
ii_c++;
meshc[ii_c]=meshc[ii_c-12];
ii_c++;
meshc[ii_c]=meshc[ii_c-12];
ii_c++;

mesht[ii_t]=mesht[ii_t-2];
ii_t++;
mesht[ii_t]=mesht[ii_t-2];
ii_t++;
mesht[ii_t]=mesht[ii_t-6];
ii_t++;
mesht[ii_t]=mesht[ii_t-6];
ii_t++;

mesh[ii_m++]=premesh[ix+1][iy][iz+1][0];mesh[ii_m++]=premesh[ix+1][iy][iz+1][1];mesh[ii_m++]=premesh[ix+1][iy][iz+1][2];
meshc[ii_c++]=precol[ix+1][iy][iz+1][0];meshc[ii_c++]=precol[ix+1][iy][iz+1][1];meshc[ii_c++]=precol[ix+1][iy][iz+1][2];meshc[ii_c++]=255;
mesht[ii_t++]=0;mesht[ii_t++]=0;

meshtid[ii_ti++]=texture;meshtid[ii_ti++]=texture;

}//End BACK

renderit=1;//LEFT
if (x<1) renderit=0;
else
if (x-cx<=0) renderit=0;
else
if (mp[x-1][y][z][0]>0) renderit=0;
else
if (scert[ix][iy][iz]==0 && scert[ix][iy+1][iz]==0 && scert[ix][iy+1][iz+1]==0 && scert[ix][iy][iz+1]==0) renderit=0;else
/*
if (prec[ix][iy+1][iz]==0) renderit=0;else
if (prec[ix][iy][iz]==0) renderit=0;else
if (prec[ix][iy][iz+1]==0) renderit=0;else
if (prec[ix][iy+1][iz+1]==0) renderit=0;
*/
if (renderit)
{
sides++;

mesh[ii_m++]=premesh[ix][iy][iz][0];mesh[ii_m++]=premesh[ix][iy][iz][1];mesh[ii_m++]=premesh[ix][iy][iz][2];
meshc[ii_c++]=precol[ix][iy][iz][0];meshc[ii_c++]=precol[ix][iy][iz][1];meshc[ii_c++]=precol[ix][iy][iz][2];meshc[ii_c++]=255;
mesht[ii_t++]=0;mesht[ii_t++]=65536;

mesh[ii_m++]=premesh[ix][iy+1][iz][0];mesh[ii_m++]=premesh[ix][iy+1][iz][1];mesh[ii_m++]=premesh[ix][iy+1][iz][2];
meshc[ii_c++]=precol[ix][iy+1][iz][0];meshc[ii_c++]=precol[ix][iy+1][iz][1];meshc[ii_c++]=precol[ix][iy+1][iz][2];meshc[ii_c++]=255;
mesht[ii_t++]=65536;mesht[ii_t++]=65536;

mesh[ii_m++]=premesh[ix][iy][iz+1][0];mesh[ii_m++]=premesh[ix][iy][iz+1][1];mesh[ii_m++]=premesh[ix][iy][iz+1][2];
meshc[ii_c++]=precol[ix][iy][iz+1][0];meshc[ii_c++]=precol[ix][iy][iz+1][1];meshc[ii_c++]=precol[ix][iy][iz+1][2];meshc[ii_c++]=255;
mesht[ii_t++]=0;mesht[ii_t++]=0;

mesh[ii_m]=mesh[ii_m-3];ii_m++;
mesh[ii_m]=mesh[ii_m-3];ii_m++;
mesh[ii_m]=mesh[ii_m-3];ii_m++;
mesh[ii_m]=mesh[ii_m-9];ii_m++;
mesh[ii_m]=mesh[ii_m-9];ii_m++;
mesh[ii_m]=mesh[ii_m-9];ii_m++;

meshc[ii_c]=meshc[ii_c-4];ii_c++;
meshc[ii_c]=meshc[ii_c-4];ii_c++;
meshc[ii_c]=meshc[ii_c-4];ii_c++;
meshc[ii_c]=meshc[ii_c-4];ii_c++;
meshc[ii_c]=meshc[ii_c-12];ii_c++;
meshc[ii_c]=meshc[ii_c-12];ii_c++;
meshc[ii_c]=meshc[ii_c-12];ii_c++;
meshc[ii_c]=meshc[ii_c-12];ii_c++;

mesht[ii_t]=mesht[ii_t-2];ii_t++;
mesht[ii_t]=mesht[ii_t-2];ii_t++;
mesht[ii_t]=mesht[ii_t-6];ii_t++;
mesht[ii_t]=mesht[ii_t-6];ii_t++;

mesh[ii_m++]=premesh[ix][iy+1][iz+1][0];mesh[ii_m++]=premesh[ix][iy+1][iz+1][1];mesh[ii_m++]=premesh[ix][iy+1][iz+1][2];
meshc[ii_c++]=precol[ix][iy+1][iz+1][0];meshc[ii_c++]=precol[ix][iy+1][iz+1][1];meshc[ii_c++]=precol[ix][iy+1][iz+1][2];meshc[ii_c++]=255;
mesht[ii_t++]=65536;mesht[ii_t++]=0;

meshtid[ii_ti++]=texture;meshtid[ii_ti++]=texture;

}//End LEFT

renderit=1;//RIGHT
if (x==cmapmaxh-1) renderit=0;
else
if (x-cx>=0) renderit=0;
else
if (mp[x+1][y][z][0]>0) renderit=0;
else
if (scert[ix+1][iy][iz]==0 && scert[ix+1][iy+1][iz]==0 && scert[ix+1][iy+1][iz+1]==0 && scert[ix+1][iy][iz+1]==0) renderit=0;else
/*
if (prec[ix+1][iy][iz]==0) renderit=0;else
if (prec[ix+1][iy+1][iz]==0) renderit=0;else
if (prec[ix+1][iy][iz+1]==0) renderit=0;else
if (prec[ix+1][iy+1][iz+1]==0) renderit=0;
*/
if (renderit)
{
sides++;

mesh[ii_m++]=premesh[ix+1][iy][iz][0];mesh[ii_m++]=premesh[ix+1][iy][iz][1];mesh[ii_m++]=premesh[ix+1][iy][iz][2];
meshc[ii_c++]=precol[ix+1][iy][iz][0];meshc[ii_c++]=precol[ix+1][iy][iz][1];meshc[ii_c++]=precol[ix+1][iy][iz][2];meshc[ii_c++]=255;
mesht[ii_t++]=65536;mesht[ii_t++]=65536;

mesh[ii_m++]=premesh[ix+1][iy+1][iz][0];mesh[ii_m++]=premesh[ix+1][iy+1][iz][1];mesh[ii_m++]=premesh[ix+1][iy+1][iz][2];
meshc[ii_c++]=precol[ix+1][iy+1][iz][0];meshc[ii_c++]=precol[ix+1][iy+1][iz][1];meshc[ii_c++]=precol[ix+1][iy+1][iz][2];meshc[ii_c++]=255;
mesht[ii_t++]=0;mesht[ii_t++]=65536;

mesh[ii_m++]=premesh[ix+1][iy][iz+1][0];mesh[ii_m++]=premesh[ix+1][iy][iz+1][1];mesh[ii_m++]=premesh[ix+1][iy][iz+1][2];
meshc[ii_c++]=precol[ix+1][iy][iz+1][0];meshc[ii_c++]=precol[ix+1][iy][iz+1][1];meshc[ii_c++]=precol[ix+1][iy][iz+1][2];meshc[ii_c++]=255;
mesht[ii_t++]=65536;mesht[ii_t++]=0;

mesh[ii_m]=mesh[ii_m-3];ii_m++;
mesh[ii_m]=mesh[ii_m-3];ii_m++;
mesh[ii_m]=mesh[ii_m-3];ii_m++;
mesh[ii_m]=mesh[ii_m-9];ii_m++;
mesh[ii_m]=mesh[ii_m-9];ii_m++;
mesh[ii_m]=mesh[ii_m-9];ii_m++;

meshc[ii_c]=meshc[ii_c-4];ii_c++;
meshc[ii_c]=meshc[ii_c-4];ii_c++;
meshc[ii_c]=meshc[ii_c-4];ii_c++;
meshc[ii_c]=meshc[ii_c-4];ii_c++;
meshc[ii_c]=meshc[ii_c-12];ii_c++;
meshc[ii_c]=meshc[ii_c-12];ii_c++;
meshc[ii_c]=meshc[ii_c-12];ii_c++;
meshc[ii_c]=meshc[ii_c-12];ii_c++;

mesht[ii_t]=mesht[ii_t-2];ii_t++;
mesht[ii_t]=mesht[ii_t-2];ii_t++;
mesht[ii_t]=mesht[ii_t-6];ii_t++;
mesht[ii_t]=mesht[ii_t-6];ii_t++;


mesh[ii_m++]=premesh[ix+1][iy+1][iz+1][0];mesh[ii_m++]=premesh[ix+1][iy+1][iz+1][1];mesh[ii_m++]=premesh[ix+1][iy+1][iz+1][2];
meshc[ii_c++]=precol[ix+1][iy+1][iz+1][0];meshc[ii_c++]=precol[ix+1][iy+1][iz+1][1];meshc[ii_c++]=precol[ix+1][iy+1][iz+1][2];meshc[ii_c++]=255;
mesht[ii_t++]=0;mesht[ii_t++]=0;

meshtid[ii_ti++]=texture;meshtid[ii_ti++]=texture;

}//End RIGHT
} // :3
}
}
}
s32 dx,dy,id;
if (maptick==1)
{
debugprobe[2]=SDL_GetTicks()-debugprobe[0];

rdata[0]=ii_0/3;
rdata[1]=(ii_m-ii_0)/3;
rdata[2]=ii_m;
}
//zlTranslate(-cx*65536,-cz*65536,-cy*65536);
//zlPop();
//
zlRender(rdata[0],rdata[1]);
meshcount=rdata[2]/3;
//
//zlVertexArrayID(0);

if (mp1mode)
{
zlBindTexture(2);zlColor4x(255,255,255,255);
zlBeginQuads();
for (z=cz0;z<cz1;z++)
for (y=cy0;y<cy1;y++)
for (x=cx0;x<cx1;x++)
if (mp[x][y][z][1]>0)
{
id=mp[x][y][z][1];;
dx=id%8;
dy=id/8;

zlTexCoord2x((dx+0)*8192,(dy+0)*8192);zlVertex3x((x+0)*65536,(z+0)*65536+8192,(y+0)*65536);
zlTexCoord2x((dx+1)*8192,(dy+0)*8192);zlVertex3x((x+1)*65536,(z+0)*65536+8192,(y+0)*65536);
zlTexCoord2x((dx+1)*8192,(dy+1)*8192);zlVertex3x((x+1)*65536,(z+0)*65536+8192,(y+1)*65536);
zlTexCoord2x((dx+0)*8192,(dy+1)*8192);zlVertex3x((x+0)*65536,(z+0)*65536+8192,(y+1)*65536);
}
zlEndQuads();
}

mvx=f_cos[camera[4]]>>4;
mvy=           65536>>4;
mvz=f_sin[camera[4]]>>4;

for (z=cz0;z<cz1;z++)
for (y=cy0;y<cy1;y++)
for (x=cx0;x<cx1;x++)
if (mp[x][y][z][1]>0)
{
ix=x-cx0;
iy=y-cy0;
iz=z-cz0;
//if (precol[ix][iy][iz][4])
procmp1(x,y,z);
}
if (verts>0)
{
contblock[0]=contblock[0]/verts;
contblock[1]=contblock[1]/verts;
contblock[2]=contblock[2]/verts;
contblock[3]=contblock[0]+contblock[1]+contblock[2];
}

#ifdef PC32
//if (((count)%10)==0) printf("cubes:%i sides:%i verts:%i/%i/%i\n",cubes,sides,sverts,verts,verts0);
//if (((count)%10)==0) printf("a:%i c:%i \n",contblock[3],contblock[4]);
#endif
}

void rendersky(void)
{
s32 x;

switch (mpheader[21])
{
case 1://simulator
zlBeginQuads();
zlBindTexture(80);
s32 x;
x=(count*10 %65536);
zlColor4x(255,255,255,255);
zlTexCoord2x(x,x);
zlVertex3x(-700000,9900,-700000);
zlTexCoord2x(x+2*65536,x);
zlVertex3x(700000,9900,-700000);
zlTexCoord2x(x+2*65536,x+2*65536);
zlVertex3x(700000,9900,700000);
zlTexCoord2x(x,x+2*65536);
zlVertex3x(-700000,9900,700000);
zlEndQuads();
x=(count*8 % 65536);
zlBeginQuads();
zlColor4x(255,255,255,255);
zlTexCoord2x(x,x);
zlVertex3x(-700000,-9900,-700000);
zlTexCoord2x((x+8*65536),x);
zlVertex3x(700000,-9900,-700000);
zlTexCoord2x((x+8*65536),(x+8*65536));
zlVertex3x(700000,-9900,700000);
zlTexCoord2x(x,(x+8*65536));
zlVertex3x(-700000,-9900,700000);
zlEndQuads();

break;
case 2://blue sky
zlBindTexture(60);
x=(count*8 % 65536);
zlBeginQuads();
zlColor4x(255,255,255,255);
zlTexCoord2x(x,x);
zlVertex3x(-700000,9900,-700000);
zlTexCoord2x((x+8*65536),x);
zlVertex3x(700000,9900,-700000);
zlTexCoord2x((x+8*65536),(x+8*65536));
zlVertex3x(700000,9900,700000);
zlTexCoord2x(x,(x+8*65536));
zlVertex3x(-700000,9900,700000);
zlEndQuads();

zlBlend(1);
zlBindTexture(61);
x=-(camera[4]<<6);
zlPush();
zlRotatey(-camera[4]+2024);
zlBeginQuads();
zlColor4x(mpheader[18],mpheader[19],mpheader[20],255);
zlTexCoord2x(        x,    0);zlVertex3x(-88000,8000,70000);
zlTexCoord2x((x+65536),    0);zlVertex3x(88000,8000,70000);
zlTexCoord2x((x+65536),65536);zlVertex3x(88000,-24000,70000);
zlTexCoord2x(        x,65536);zlVertex3x(-88000,-24000,70000);
zlEndQuads();
zlPop();
zlBlend(0);
break;
case 3://autism
zlBindTexture(62);
x=(count*8 % 65536);
zlBeginQuads();
zlColor4x(255,255,255,255);
zlTexCoord2x(x,x);
zlVertex3x(-700000,9900,-700000);
zlTexCoord2x((x+8*65536),x);
zlVertex3x(700000,9900,-700000);
zlTexCoord2x((x+8*65536),(x+8*65536));
zlVertex3x(700000,9900,700000);
zlTexCoord2x(x,(x+8*65536));
zlVertex3x(-700000,9900,700000);
zlEndQuads();
break;
}
}
void showfps(void)
{
zlColor4x(200,0,0,255);
zlPush();zlTranslate(50000,54000,0);zlScale(6000,10000,10000);
l_text=sprintf(s_text,"%i",fps);zlRenderText();zlPop();
}

void showinfo0(void)
{
zlColor4x(178,0,0,255);
zlPush();zlTranslate(-60000,54000,0);zlScale(6000,10000,10000);
l_text=sprintf(s_text,"F%i D%i P%i",meshcount/3,frametime,debugprobe[2]);zlRenderText();zlPop();
}

void predrawmobs(void)
{
u8 i;s32 k;
for (i=0;i<64;i++)
if (mob[i][0]>0)
if (mob[i][41]>0 | i==mobcontrol)
{
switch (mob[i][10])
{
case 0://player
k=mob[i][44];if (k<0) k=-k;k=k*8;
if (k>0) newlight(mob[i][1]-(f_sin[mob[i][7]])*1/5,mob[i][2]-(f_cos[mob[i][7]])*1/5,mob[i][3]+70536,(k)+(k<<8)+(k<<16)+(1<<24));
break;
case 2:newlight(mob[i][1],mob[i][2],mob[i][3]+32768,(32)+(255<<8)+(32<<16)+(1<<24));break;//slime
case 5:newlight(mob[i][1],mob[i][2],mob[i][3]+65536,(255)+(255<<8)+(32<<16)+(1<<24));break;//ghoul
}
}
}

void gamesceneframe(void)
{
///
//fpsdisplay=1;
///
s32 delta;
camerastep();
clearlightcube();
zlFogColor(mpheader[18],mpheader[19],mpheader[20]);
zlFogParam(65536*4,65536*8);
zlClrScr();
zlClrDepth();
zlPush();


delta=gameswitchdelay;
if (delta<0) delta=100+delta;
zlScreen(6553-delta*40,4915-delta*30,6553);

zlRotatez(camera[5]);
zlRotatex(camera[3]);
zlRotatey(camera[4]);
zlDepthTest(0);
rendersky();
zlFog(1);
zlTranslate(-camera[0],-camera[1],-camera[2]);
zlDepthTest(1);
predrawmp1();//lights
predrawmobs();//moar lights
procbullets();
vismobs();
visparticles();
procsprites();
if (thisframenice) RenderMap();
if (thisframenice) drawblendsprites();
zlPop();
zlFog(0);
zlDepthTest(0);
//#ifdef PC32
zlScreen(65536,65536,0);
//#endif



procgui();
if (firstnightrule==0)
if (levelframes>32)
{if (playmode!=ZPM_EDIT) wantnarration=mpheader[16];
firstnightrule=1;
}
procnarration();

if (gameswitchdelay!=0)zlDrawTransmask(255,0,0);

if (fpsdisplay){showfps();showinfo0();}

}
