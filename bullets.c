#include "vars.h"
#include "render.h"
#include "particles.h"
#include "zlmath.h"
#include "wlight.h"

#include "sprites.h"
#include "zcsound.h"
#include "mobs.h"

s32 mobhitx=25000,mobhitz=65536+32768;

void procbullets(void)
{
u8 i,k,blocked;s32 t,x,y,z,bx,by,bz,ix,iy,iz,nya;
for (i=0;i<32;i++)
if (bullet[i][0]>0)
{
bullet[i][1]+=bullet[i][4];
bullet[i][2]+=bullet[i][5];
bullet[i][3]+=bullet[i][6];

if (thisframenice)
{
zlPush();
zlTranslate(bullet[i][1],bullet[i][3],bullet[i][2]);
zlRotatey(bullet[i][8]);
zlRotatez(bullet[i][7]);
zlRotatex(zlrand()*16);
zlBindTexture(24);
zlColor4x(255,255,255,255);
t=f_sin[128+bullet[i][0]*14];
zlBeginQuads();
zlTexCoord2x(0,0);zlVertex3x(0,t,-t);
zlTexCoord2x(16384,0);zlVertex3x(0,t,t);
zlTexCoord2x(16384,65536);zlVertex3x(0,-t,t);
zlTexCoord2x(0,65536);zlVertex3x(0,-t,-t);

zlTexCoord2x(16384,0);zlVertex3x(-t,t,0);
zlTexCoord2x(65536,0);zlVertex3x(t*3,t,0);
zlTexCoord2x(65536,65536);zlVertex3x(t*3,-t,0);
zlTexCoord2x(16384,65536);zlVertex3x(-t,-t,0);

zlTexCoord2x(16384,0);zlVertex3x(-t,0,t);
zlTexCoord2x(65536,0);zlVertex3x(t*3,0,t);
zlTexCoord2x(65536,65536);zlVertex3x(t*3,0,-t);
zlTexCoord2x(16384,65536);zlVertex3x(-t,0,-t);

zlEndQuads();
zlPop();
}
blocked=0;bullet[i][0]--;
x=bullet[i][1];
y=bullet[i][2];
z=bullet[i][3];

//ld=(255)+(255<<8)+(255<<16)+(2<<24);
newlight(x,y,z,(255)+(168<<8)+(0<<16)+(2<<24));

if (x<0) blocked=2;
else
if (y<0) blocked=2;
else
if (z<0) blocked=2;
else
if (x>=truemaxmapx) blocked=2;
else
if (y>=truemaxmapx) blocked=2;
else
if (z>=truemaxmaph) blocked=2;
else
if (mpb[((x)>>16)][((y)>>16)][((z)>>16)]) blocked=1;
if (blocked)
{
bullet[i][0]=0;
zcplaysound3d(13,4,x,y,z);


if (blocked==1)
{
for (k=0;k<4;k++)
{
pr[128][0]=55+k*15;

pr[128][1]=32;
pr[128][2]=32;
pr[128][3]=32;

pr[128][4]=x-bullet[i][4];
pr[128][5]=z-bullet[i][6];
pr[128][6]=y-bullet[i][5];
genpartdir(128);
pr[128][7]-=bullet[i][4]/2;
pr[128][8]-=bullet[i][6]/2;
pr[128][9]-=bullet[i][5]/2;

pr[128][14]=0;
pr[128][15]=0;
newparticle();
}
//bullethole
nya=0;
ix=bullet[i][4];
iy=bullet[i][5];
iz=bullet[i][6];

bx=x-ix;
by=y-iy;
bz=z-iz;
sprite[32][2]=bx;
sprite[32][3]=by;
sprite[32][4]=bz;

if (mp[(bx+ix)>>16][(by)>>16][(bz)>>16][0]>0)
{
sprite[32][1]=3;nya=1;
if (ix<0) sprite[32][2]=((bx>>16)<<16)+1000; else sprite[32][2]=((bx>>16)<<16)+64000;
}
else
if (mp[(bx)>>16][(by+iy)>>16][(bz)>>16][0]>0)
{
sprite[32][1]=4;nya=1;
if (iy<0) sprite[32][3]=((by>>16)<<16)+1000; else sprite[32][3]=((by>>16)<<16)+64000;
}
else
if (mp[(bx)>>16][(by)>>16][(bz+iz)>>16][0]>0)
{
sprite[32][1]=5;nya=1;
if (iz<0) sprite[32][4]=((bz>>16)<<16)+1000; else sprite[32][4]=((bz>>16)<<16)+64000;
}
if (nya)
{
sprite[32][0]=64;
sprite[32][5]=0;
sprite[32][6]=0;
sprite[32][7]=0;
spawnnewsprite();
}
//bullethole end
}
}
else
for (k=0;k<64;k++)
if (mob[k][0]>0)
if (x-mob[k][1]<mobhitx)
if (x-mob[k][1]>-mobhitx)
if (y-mob[k][2]<mobhitx)
if (y-mob[k][2]>-mobhitx)
if (z-mob[k][3]<mobhitz)
if (z-mob[k][3]>0)
{
hurtmob(k);
bullet[i][0]=0;
}


}
}

void newbullet(void)
{
u8 i=0,k;
while ((bullet[i][0]>0)&(i<32)) i++;
if (i==32) i=((zlrand())>>3);
for (k=0;k<16;k++) bullet[i][k]=bullet[32][k];
}
