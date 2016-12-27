#include <stdlib.h>
#include <stdio.h>

#include "vars.h"
#include "wmapgen.h"
#include "wlight.h"

#include "mobs.h"

#define FPML(x,y) ((((x)>>7)*((y)>>7))>>2)

void clearmap(void)
{
u16 x,y,z,i;
for (z=0;z<mapmaxy;z++)
for (y=0;y<mapmaxh;y++)
for (x=0;x<mapmaxh;x++)
{
mp[x][y][z][0]=0;
mp[x][y][z][1]=0;
mpb[x][y][z]=0;
intrestingmp[x][y][z]=0;
}

for (z=0;z<=mapmaxy;z++)
for (y=0;y<=mapmaxh;y++)
for (x=0;x<=mapmaxh;x++)
intrestingvertex[x][y][z]=0;


for (i=0;i<64;i++)
mob[i][0]=0;
}


void scanmpxyz(u8 x,u8 y,u8 z)
{
u8 flag;

if (x>=0)
if (y>=0)
if (z>=0)
if (x<=mpheader[8]-1)
if (y<=mpheader[8]-1)
if (z<=mpheader[9]-1)
if (mp[x][y][z][0]>0)
{
intrestingmp[x][y][z]=0;flag=0;

if (x>0) if (mp[x-1][y][z][0]==0) flag=1;
if (y>0) if (mp[x][y-1][z][0]==0) flag=1;
if (z>0) if (mp[x][y][z-1][0]==0) flag=1;

if (z<mpheader[9]) if (mp[x][y][z+1][0]==0) flag=1;
if (x<mpheader[8]) if (mp[x+1][y][z][0]==0) flag=1;
if (y<mpheader[8]) if (mp[x][y+1][z][0]==0) flag=1;

intrestingmp[x][y][z]=flag;

if (flag)
{
intrestingvertex[x][y][z]=1;
intrestingvertex[x][y][z+1]=1;
intrestingvertex[x][y+1][z]=1;
intrestingvertex[x][y+1][z+1]=1;
intrestingvertex[x+1][y][z]=1;
intrestingvertex[x+1][y][z+1]=1;
intrestingvertex[x+1][y+1][z]=1;
intrestingvertex[x+1][y+1][z+1]=1;
}
}
}

void maplight(u8 x,u8 y,u8 z)
{
if (intrestingvertex[x][y][z])
{
mpc[x][y][z]=0;
if (isinlight(x*65536,z*65536,y*65536)>0) mpc[x][y][z]=1;
}
}
void rescanmaphead(void)
{
u8 i;

for (i=0;i<6;i++) lightg[0+i]=(mpheader[10+i]);

for (i=0;i<3;i++) lightgv[0+i]=mpheader[23+i]*512-65536;

for (i=0;i<3;i++)
lightg[6+i]=lightg[i]+(lightg[3+i]+lightg[i])/4;

}
void rescanmap(void)
{
u16 x,y,z,xx,zz;

rescanmaphead();

zz=mpheader[9];
xx=mpheader[8];
for (z=0;z<zz;z++)
for (y=0;y<xx;y++)
for (x=0;x<xx;x++)
{
intrestingmp[x][y][z]=0;

scanmpxyz(x,y,z);
}


}
void rescanlight(void)
{
s32 xx,zz,x,y,z;
zz=mpheader[9];
xx=mpheader[8];

for (z=0;z<=zz;z++)
for (y=0;y<=xx;y++)
for (x=0;x<=xx;x++)
maplight(x,y,z);
}

void scanborderlight(void)
{
s32 xx,zz,x,y,z;
zz=mpheader[9];
xx=mpheader[8];

truemaxmapx=(xx)*65536;
truemaxmaph=(zz)*65536;


for (z=0;z<=zz;z++)
maplight(xx,xx,z);
for (y=0;y<=xx;y++)
maplight(xx,y,zz);
for (x=0;x<=xx;x++)
maplight(x,xx,zz);
}


void trytoshade(s32 x,s32 y,s32 z)
{
//u32 x,y,z;

if (z>0)
if (y>0)
if (x>0)
if (z<mpheader[9]-1)
if (y<mpheader[8]-1)
if (x<mpheader[8]-1)
if (mpc[x][y][z]==1)
{
if (mp[x-1][y-1][z-1][0]>0)
if (mp[x-1][y][z-1][0]>0)
if (mp[x][y-1][z-1][0]>0)
if (mp[x][y][z-1][0]>0)
if (mp[x-1][y-1][z][0]>0 | mp[x-1][y][z][0]>0 | mp[x][y-1][z][0]>0 | mp[x][y][z][0]>0)
mpc[x][y][z]=2;
}
}
void trytoshadethineautism(s32 x,s32 y,s32 z)
{
//u32 x,y,z;

if (z>0)
if (y>0)
if (x>0)
if (z<mpheader[9]-1)
if (y<mpheader[8]-1)
if (x<mpheader[8]-1)
if (intrestingvertex[x][y][z])
{
if (mp[x-1][y-1][z-1][0]>0)
if (mp[x-1][y][z-1][0]>0)
if (mp[x][y-1][z-1][0]>0)
if (mp[x][y][z-1][0]>0)
if (mp[x-1][y-1][z][0]>0 | mp[x-1][y][z][0]>0 | mp[x][y-1][z][0]>0 | mp[x][y][z][0]>0)
mpc[x][y][z]=2;
}
}

void mpedit(unsigned char x,unsigned char y,unsigned char z,unsigned char i)
{
mp[x][y][z][0]=i;
if (i==0) intrestingmp[x][y][z]=0;

if (i==0) mpb[x][y][z]=0; else mpb[x][y][z]=1;

scanmpxyz(x,y,z);

scanmpxyz(x-1,y,z);
scanmpxyz(x+1,y,z);

scanmpxyz(x,y-1,z);
scanmpxyz(x,y+1,z);

scanmpxyz(x,y,z-1);
scanmpxyz(x,y,z+1);

mpc[x][y][z]=0;
mpc[x+1][y][z]=0;
mpc[x][y+1][z]=0;
mpc[x+1][y+1][z]=0;
mpc[x][y][z+1]=0;
mpc[x][y+1][z+1]=0;
mpc[x+1][y][z+1]=0;
mpc[x+1][y+1][z+1]=0;

if (playmode==ZPM_AUTISM)
{
trytoshadethineautism(x,y,z);
trytoshadethineautism(x+1,y,z);
trytoshadethineautism(x+1,y+1,z);
trytoshadethineautism(x,y+1,z);
trytoshadethineautism(x,y,z+1);
trytoshadethineautism(x+1,y,z+1);
trytoshadethineautism(x+1,y+1,z+1);
trytoshadethineautism(x,y+1,z+1);
}
else
{
maplight(x,y,z);
maplight(x+1,y,z);
maplight(x+1,y+1,z);
maplight(x,y+1,z);
maplight(x,y,z+1);
maplight(x+1,y,z+1);
maplight(x+1,y+1,z+1);
maplight(x,y+1,z+1);


trytoshade(x,y,z);
trytoshade(x+1,y,z);
trytoshade(x+1,y+1,z);
trytoshade(x,y+1,z);
trytoshade(x,y,z+1);
trytoshade(x+1,y,z+1);
trytoshade(x+1,y+1,z+1);
trytoshade(x,y+1,z+1);
}
}

/*
MAP HEADER

00 - playmode
01 - BGM
02 - narration1
03 - narration2
04 - playerx
05 - playery
06 - playerz
07 - playera

08 - maxh
09 - maxy
10 - light_r0
11 - light_g0
12 - light_b0
13 - light_r1
14 - light_g1
15 - light_b1

16 - >narration0
17 - >narration3
18 - fog_r
19 - fog_g
20 - fog_b
21 - sky
22 - nextmap
23 - light0
24 - light1
25 - light2
26 -
27 -

28-63 - 6x6 Animated camera[6] pos;

*/
u8 mp2block[64]=
{
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,1,2,2,2,0,

0,0,0,2,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0
};

char spath[128];
void loadmapdisc(unsigned char index)
{
u32 i,x,y,z;
FILE *fp;

u8 c;
sprintf(spath,"maps/%i%i.aaa",index/10,index%10);
fp=fopen(spath,"rb");

for (i=0;i<64;i++) mpheader[i]=fgetc(fp);

for (z=0;z<mpheader[9];z++)
for (y=0;y<mpheader[8];y++)
for (x=0;x<mpheader[8];x++)
{
mp[x][y][z][0]=fgetc(fp);

if (mp[x][y][z][0]) mpb[x][y][z]=1;

c=fgetc(fp);
mpc[x][y][z]=0;
intrestingmp[x][y][z]=0;

if (c & 128) mpc[x][y][z]=1;
if (c & 64)
{
intrestingmp[x][y][z]=1;
intrestingvertex[x][y][z]=1;
intrestingvertex[x][y][z+1]=1;
intrestingvertex[x][y+1][z]=1;
intrestingvertex[x][y+1][z+1]=1;
intrestingvertex[x+1][y][z]=1;
intrestingvertex[x+1][y][z+1]=1;
intrestingvertex[x+1][y+1][z]=1;
intrestingvertex[x+1][y+1][z+1]=1;
}
c=c & 63;
mp[x][y][z][1]=c;
if (mp2block[c])
{
mpb[x][y][z]=1;
if (mp2block[c]==2) if (z+1<mpheader[9]) mpb[x][y][z+1]=1;
}
}

fclose(fp);
}
void savemapdisc(unsigned char index)
{
u32 i,x,y,z;
FILE *fp;
u8 c;

sprintf(spath,"maps/%i%i.aaa",index/10,index%10);
fp=fopen(spath,"wb");

for (i=0;i<64;i++) fputc(mpheader[i],fp);
for (z=0;z<mpheader[9];z++)
for (y=0;y<mpheader[8];y++)
for (x=0;x<mpheader[8];x++)
{
fputc(mp[x][y][z][0],fp);
c=mp[x][y][z][1];
if (intrestingmp[x][y][z]>0) c=c | 64;
if (mpc[x][y][z]>0) c=c | 128;

fputc(c,fp);
}

fclose(fp);
}

void reshadelight(void)
{
u32 i,x,y,z;

for (z=1;z<mpheader[9]-1;z++)
for (y=1;y<mpheader[8]-1;y++)
for (x=1;x<mpheader[8]-1;x++)
if (mpc[x][y][z]==1)
{
if (mp[x-1][y-1][z-1][0]>0)
if (mp[x-1][y][z-1][0]>0)
if (mp[x][y-1][z-1][0]>0)
if (mp[x][y][z-1][0]>0)
if (mp[x-1][y-1][z][0]>0 | mp[x-1][y][z][0]>0 | mp[x][y-1][z][0]>0 | mp[x][y][z][0]>0)
mpc[x][y][z]=2;
}
}

void reshadealllight(void)
{
u32 i,x,y,z;

for (z=1;z<mpheader[9]-1;z++)
for (y=1;y<mpheader[8]-1;y++)
for (x=1;x<mpheader[8]-1;x++)
if (intrestingvertex[x][y][z])
{
if (mp[x-1][y-1][z-1][0]>0)
if (mp[x-1][y][z-1][0]>0)
if (mp[x][y-1][z-1][0]>0)
if (mp[x][y][z-1][0]>0)
if (mp[x-1][y-1][z][0]>0 | mp[x-1][y][z][0]>0 | mp[x][y-1][z][0]>0 | mp[x][y][z][0]>0)
mpc[x][y][z]=2;
}
}

void LoadNewMap(unsigned char index)
{
mp1mode=0;narration=0;loserwantexit=0;endlevel=0;firstnightrule=0;
clearmap();
level=index;
lastlevel=index;
if (playmode==ZPM_EDIT && index==255) generateeditmap();
else loadmapdisc(index);

rescanmaphead();
scanborderlight();
if (playmode==ZPM_AUTISM) reshadealllight();
else
reshadelight();
wantnarration=0;
if (playmode!=ZPM_EDIT) {playmode=mpheader[0];spawnallmobs();}
levelnarration[0]=0;
levelnarration[1]=0;
mobcontrol=64;checkpointnotify=0;wantnarration=0;levelframes=0;levelstarttick=SDL_GetTicks();ltime[0]=0;ltime[1]=0;
}
