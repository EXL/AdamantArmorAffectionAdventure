#include "vars.h"
#include "render.h"
#include "zlmath.h"

#include "drawmob.h"
#include "mobai.h"
#include "sprites.h"
#include "bullets.h"


#define FPML(x,y) ((((x)>>7)*((y)>>7))>>2)

/*
00 - enabled (-respawn count)
01 - X
02 - Y
03 - Z (up)
04 ix
05 iy
06 iz
07 angle
08 walkangle
09 walkspeed
10 ID
11 standonground
12 lookx
13 looky
14 wlookx
15 wlooky
19 personal count

20 wasx
21 wasy
22 wasz

23 wantmelee
24 wantshoot

25 targetx
26 targety
27 targetz

28 light 0-767

29 aialarmed
30 aistate
31 wantjump
32 blocked
33 r
34 g
35 b

36 attackcount
37 heycount
38 firecount
39 lhanddelay
40 rhanddelay
41 was drawn
42 damaged
43 newtarget
44 lightmode
*/

void loadmob(unsigned char i)
{
u8 k;
for (k=0;k<32;k++)
mob[i][k]=mob[64][k];
}

unsigned char spawnmob(unsigned char index)
{
u8 i,k;
i=0;
while ((mob[i][0]!=0)&(i<63)) i++;
loadmob(i);

mob[i][0]=1;

mob[i][4]=0;
mob[i][5]=0;
mob[i][6]=0;


mob[i][7]=zlrand()*16;
mob[i][8]=mob[i][7];


mob[i][10]=index;

mob[i][19]=zlrand();


mob[i][25]=mob[i][1];
mob[i][26]=mob[i][2];
mob[i][27]=mob[i][3];


mob[i][30]=AI_PEACE;
for (k=32;k<64;k++) mob[i][k]=0;
return i;
}

void respawnmob(unsigned char i)
{
// OMFG!!!!!!!!
u8 k;

mob[i][0]=1;
mob[i][1]=mob[i][20]*65536+32768;
mob[i][2]=mob[i][21]*65536+32768;
mob[i][3]=mob[i][22]*65536+32768;
mob[i][4]=0;
mob[i][5]=0;
mob[i][5]=0;

if (i==mobcontrol) mob[i][7]=-mpheader[7]*16-1024;
else
mob[i][7]=zlrand()*16;

mob[i][8]=0;
mob[i][9]=0;

mob[i][30]=AI_PEACE;

for (k=32;k<64;k++) mob[i][k]=0;
if (i==mobcontrol) {tension[4]=0;tension[5]=0;tension[6]=0;tension[7]=255;camerasync=8;}

}
u8 mobblood[36]=
{
255,255,255,20,

255,0,0,8,
0,200,0,8,
255,0,0,8,
128,64,64,8,

255,255,0,8,
255,0,0,8,
255,0,0,8,
255,0,0,8
};

void killmob(unsigned char i)
{
u8 cx,cy,cz;

zcplaysound3d(mobsonic[mob[i][10]][12],14,mob[i][1],mob[i][2],mob[i][3]+65536);


cx=mob[i][1]>>16;
cy=mob[i][2]>>16;
cz=mob[i][3]>>16;

while ((cz>0)&&(mp[cx][cy][cz-1][0]==0)) cz--;


sprite[32][0]=512;
sprite[32][1]=1;
sprite[32][2]=mob[i][1];
sprite[32][3]=mob[i][2];
sprite[32][4]=cz*65536+zlrand()*3;
sprite[32][5]=mobblood[mob[i][10]*4];
sprite[32][6]=mobblood[mob[i][10]*4+1];
sprite[32][7]=mobblood[mob[i][10]*4+2];
spawnnewsprite();


mob[i][0]=-64;

}
u8 moblive[17]={3,1,1,1,2, 3,1,10,1, 1,1,1,1, 1,1,1,1};

void hurtmob(unsigned char i)
{
u8 k,b,ii;
ii=4*mob[i][10];
b=mobblood[ii+3];
if (b)
for (k=0;k<b;k++)
{
pr[128][0]=32+zlrand()/2;

pr[128][1]=mobblood[ii];
pr[128][2]=mobblood[ii+1];
pr[128][3]=mobblood[ii+2];

pr[128][4]=mob[i][1]+(128-zlrand())*300;
pr[128][5]=mob[i][3]+45536+(128-zlrand())*400;
pr[128][6]=mob[i][2]+(128-zlrand())*300;

pr[128][10]=0;
pr[128][12]=0;
pr[128][13]=0;

pr[128][14]=0;
pr[128][15]=0;

genpartdir(128);

newparticle();
}

if (i==mobcontrol) {vibro=128;tension[4]=255;tension[5]=0;tension[6]=0;tension[7]=255;}

mob[i][42]++;

if (mob[i][42]>=moblive[mob[i][10]]) {killmob(i);} else zcplaysound3d(mobsonic[mob[i][10]][11],7,mob[i][1],mob[i][2],mob[i][3]+65536);
}

s32 meleerange=65536;
void mobstrike(u8 i)
{
u8 k;
s32 xx,yy,dd;
if (i==mobcontrol) if (vibro<88) vibro=88;

zcplaysound3d(11,5,mob[i][1],mob[i][2],mob[i][3]);


if (mob[i][10]==0)
{
sprite[32][0]=6;
sprite[32][1]=0;
sprite[32][2]=mob[i][1]-f_cos[mob[i][7]]/2;
sprite[32][3]=mob[i][2]+f_sin[mob[i][7]]/2;
sprite[32][4]=mob[i][3]+41100;
sprite[32][5]=0;
sprite[32][6]=0;
sprite[32][7]=0;
spawnnewsprite();
}

for (k=0;k<64;k++)
if (mob[k][0]>0)
if (k!=i)
if (mob[i][1]-mob[k][1]<meleerange)
if (mob[i][2]-mob[k][2]<meleerange)
if (mob[i][1]-mob[k][1]>-meleerange)
if (mob[i][2]-mob[k][2]>-meleerange)
if (mob[i][3]-mob[k][3]<meleerange)
if (mob[i][3]-mob[k][3]>-meleerange)
{
xx=mob[k][1]-mob[i][1];
yy=mob[k][2]-mob[i][2];

dd=FPML(xx,-f_cos[mob[i][7]])+FPML(yy,f_sin[mob[i][7]]);
if (dd>0) hurtmob(k);
}

}
s32 alarmrange=8*65536;
void mobalarm(u8 i,u8 bad)
{
u8 k;
s32 xx,yy;
for (k=0;k<64;k++)
if (k!=i)
if (mob[k][30]==AI_PEACE)
{
xx=mob[k][1]-mob[i][1];
yy=mob[k][2]-mob[i][2];
if (xx<alarmrange)
if (yy<alarmrange)
if (xx>-alarmrange)
if (xx>-alarmrange)
{
mob[k][25]=mob[i][1];
mob[k][26]=mob[i][2];
mob[k][27]=mob[i][3];
mob[k][43]=1;
if (bad) {mob[k][30]=AI_ATTACK;mob[k][29]=256;}
}

}
}

void mobfire(u8 i)
{
s32 xx,yy,zz,ix,iy,iz,t,a0,a1;

zcplaysound3d(12,10,mob[i][1],mob[i][2],mob[i][3]);
mobalarm(i,1);

if (mob[i][10]==0)
{//left hand
xx=mob[i][1]+(f_sin[mob[i][7]])*2/5;
yy=mob[i][2]+(f_cos[mob[i][7]])*2/5;
}
else
{//righthand
xx=mob[i][1]-(f_sin[mob[i][7]])*2/5;
yy=mob[i][2]-(f_cos[mob[i][7]])*2/5;
}

zz=mob[i][3]+65536;
a1=mob[i][12];
a0=mob[i][7]+mob[i][13];
if (a0<0) a0=4096+a0;
a0=a0 & 4095;
if (a1<0) a1=4096+a1;
a1=a1 & 4095;

t=f_cos[a1];
iz=-f_sin[a1];
ix=-FPML(f_cos[a0],t);
iy=FPML(f_sin[a0],t);

ix=ix>>3;
iy=iy>>3;
iz=iz>>3;

xx+=ix*5;
yy+=iy*5;
zz+=iz*5;

sprite[32][0]=14;
sprite[32][1]=2;
sprite[32][2]=xx;
sprite[32][3]=yy;
sprite[32][4]=zz;
sprite[32][5]=0;
sprite[32][6]=0;
sprite[32][7]=0;
spawnnewsprite();

pr[128][0]=55;

pr[128][1]=255;
pr[128][2]=255;
pr[128][3]=100;

pr[128][4]=xx;
pr[128][5]=zz;
pr[128][6]=yy;
genpartdir(128);
pr[128][7]+=ix/4;
pr[128][8]+=iz/4;
pr[128][9]+=iy/4;

pr[128][14]=0;
pr[128][15]=0;

newparticle();
pr[128][0]=40;
pr[128][1]=255;
pr[128][2]=0;
pr[128][3]=0;
genpartdir(128);
pr[128][7]+=ix/2;
pr[128][8]+=iz/2;
pr[128][9]+=iy/2;
newparticle();
pr[128][0]=30;
pr[128][1]=255;
pr[128][2]=255;
pr[128][3]=255;
genpartdir(128);
pr[128][7]+=ix/3;
pr[128][8]+=iz/3;
pr[128][9]+=iy/3;
newparticle();
pr[128][0]=128;
pr[128][1]=128;
pr[128][2]=128;
pr[128][3]=128;
genpartdir(128);
pr[128][7]-=ix/4;
pr[128][8]-=iz/4;
pr[128][9]-=iy/4;
newparticle();



bullet[32][0]=64;
bullet[32][1]=xx;
bullet[32][2]=yy;
bullet[32][3]=zz;
bullet[32][4]=ix;
bullet[32][5]=iy;
bullet[32][6]=iz;
bullet[32][7]=a1;
bullet[32][8]=a0;
newbullet();


if (i==mobcontrol) if (vibro<100) vibro=100;
}

s32 mobw=26000,mobh=65536+40000;

u8 whatmp1;

void mobstep(unsigned short i)
{
if ((mob[i][19]&63)==0)
{
if ((whatmp1==7))
{
pr[128][0]=256+zlrand();

pr[128][1]=0;
pr[128][2]=0;
pr[128][3]=128+zlrand()/4;

pr[128][4]=mob[i][1];
pr[128][5]=mob[i][3]+19142;
pr[128][6]=mob[i][2];

pr[128][10]=0;
pr[128][12]=0;
pr[128][13]=0;

pr[128][14]=0;
pr[128][15]=0;

genpartdir(128);
pr[128][8]=1000;
newparticle();
zcplaysound3d(mobsonic[mob[i][10]][4],5,mob[i][1],mob[i][2],mob[i][3]);
}
else
zcplaysound3d(mobsonic[mob[i][10]][((+zlrand())>>6)],5,mob[i][1],mob[i][2],mob[i][3]);
}
}
void mobsing(u8 i)
{
s32 x,y,z;
x=mob[i][1]-32768+zlrand()*256;
y=mob[i][2]-32768+zlrand()*256;
z=mob[i][3]+65536+zlrand()*128;

x+=vcamera[2][0]>>2;
y+=vcamera[2][2]>>2;
z+=vcamera[2][1]>>2;


sprite[32][0]=32;
sprite[32][1]=6;
sprite[32][2]=x;
sprite[32][3]=y;
sprite[32][4]=z;
sprite[32][5]=zlrand() % 4;//index
sprite[32][6]=zlrand() % 4;//color
sprite[32][7]=0;
spawnnewsprite();
zcplaysound3d(mobsonic[mob[i][10]][7],7,mob[i][1],mob[i][2],mob[i][3]+65536);

mobalarm(i,0);
}
void procmob(unsigned char i)
{

u8 blockx,blocky,blockz;

s32 x,y,z;
s32 xx0[2],yy0[2],zz0[3];
s32  xx[2], yy[2], zz[3];

mob[i][19]++;
if (i!=mobcontrol) mobai(i);

//interface
whatmp1=mp[((mob[i][1])>>16)][((mob[i][2])>>16)][((mob[i][3])>>16)][1];

mob[i][7]=mob[i][7] & 4095;
if (mob[i][7]<0) mob[i][7]+=4095;

if (mob[i][9]!=0)
{
if (mob[i][11])
if (mob[i][9]>100 | mob[i][9]<-100) mobstep(i);

mob[i][4]+=FPML(mob[i][9],f_cos[mob[i][7]]);
mob[i][5]-=FPML(mob[i][9],f_sin[mob[i][7]]);
mob[i][9]=(mob[i][9]*7)/8;
}

//interface
//insight
if (mob[i][44]<0) mob[i][44]++;
else
if (mob[i][44]>0) if (mob[i][44]<31) mob[i][44]++;
//insight
if (mob[i][36]>0)
{
mob[i][36]--;

if (mob[i][39]==0)if (i==mobcontrol) zcplaysound3d(15,3,mob[i][1],mob[i][2],mob[i][3]+65536);
mob[i][39]=512;
if (mob[i][36]==31) mobstrike(i);
}
if (mob[i][37]>0)
{
mob[i][37]--;
if (mob[i][37]% 16==7) mobsing(i);
}
if (mob[i][38]>0)
{
if (mob[i][38]==63) mobfire(i);
mob[i][38]--;
if (mob[i][40]==0)if (i==mobcontrol) zcplaysound3d(15,3,mob[i][1],mob[i][2],mob[i][3]+65536);
mob[i][40]=512;
}
if (mob[i][39]>0) {mob[i][39]--;if (mob[i][39]==0)if (i==mobcontrol) zcplaysound3d(15,5,mob[i][1],mob[i][2],mob[i][3]+65536);}
if (mob[i][40]>0) {mob[i][40]--;if (mob[i][40]==0)if (i==mobcontrol) zcplaysound3d(15,5,mob[i][1],mob[i][2],mob[i][3]+65536);}

//
mob[i][11]=0;// i fly

blockx=0;
blocky=0;
blockz=0;
mob[i][32]=0;
x=mob[i][1];
y=mob[i][2];
z=mob[i][3];


xx0[0]=x-mobw;xx0[1]=x+mobw;
yy0[0]=y-mobw;yy0[1]=y+mobw;
zz0[0]=z+   0;zz0[1]=z+mobh;zz0[2]=z+mobh/2;

xx[0]=x-mobw+mob[i][4];xx[1]=x+mobw+mob[i][4];
yy[0]=y-mobw+mob[i][5];yy[1]=y+mobw+mob[i][5];
zz[0]=z+   0+mob[i][6];zz[1]=z+mobh+mob[i][6];zz[2]=z+(mobh/2)+mob[i][6];

//recalc pos after noblock move

//z
if (mob[i][6]!=0)
{
if (mob[i][6]>=0)
{//iz>0
if ((zz[1]>>16)>=mpheader[9]) blockz=1;
else
if (mpb[xx0[0]>>16][yy0[0]>>16][zz[1]>>16]>0) blockz=1;else
if (mpb[xx0[1]>>16][yy0[0]>>16][zz[1]>>16]>0) blockz=1;else
if (mpb[xx0[1]>>16][yy0[1]>>16][zz[1]>>16]>0) blockz=1;else
if (mpb[xx0[0]>>16][yy0[1]>>16][zz[1]>>16]>0) blockz=1;
}
else
{//iz<0
if (zz[0]<0) {blockz=1;killmob(i);}else
if (mpb[xx0[0]>>16][yy0[0]>>16][zz[0]>>16]>0) blockz=1;else
if (mpb[xx0[1]>>16][yy0[0]>>16][zz[0]>>16]>0) blockz=1;else
if (mpb[xx0[1]>>16][yy0[1]>>16][zz[0]>>16]>0) blockz=1;else
if (mpb[xx0[0]>>16][yy0[1]>>16][zz[0]>>16]>0) blockz=1;

if (blockz) mob[i][11]=1;
}

if (blockz)
if (mob[i][6]<-1000)
{
zcplaysound3d(8,5,mob[i][1],mob[i][2],mob[i][3]);

if (i==mobcontrol)
if (vibro<88) vibro=88;
}


if (blockz==0) {mob[i][3]+=mob[i][6];zz0[0]+=mob[i][6];zz0[1]+=mob[i][6];zz0[2]+=mob[i][6];} else {mob[i][6]=mob[i][6]>>2;}
}
//z
//x
if (mob[i][4]!=0)
{
if (mob[i][4]>=0)
{//ix>0
if ((xx[1]>>16)>=mpheader[8]) blockx=1;else
if (mpb[xx[1]>>16][yy0[0]>>16][zz0[0]>>16]>0) blockx=1;else
if (mpb[xx[1]>>16][yy0[1]>>16][zz0[0]>>16]>0) blockx=1;else
if (mpb[xx[1]>>16][yy0[0]>>16][zz0[1]>>16]>0) blockx=1;else
if (mpb[xx[1]>>16][yy0[1]>>16][zz0[1]>>16]>0) blockx=1;else
if (mpb[xx[1]>>16][yy0[0]>>16][zz0[2]>>16]>0) blockx=1;else
if (mpb[xx[1]>>16][yy0[1]>>16][zz0[2]>>16]>0) blockx=1;
}
else
{//ix<0
if (xx[0]<0) blockx=1;else
if (mpb[xx[0]>>16][yy0[0]>>16][zz0[0]>>16]>0) blockx=1;else
if (mpb[xx[0]>>16][yy0[1]>>16][zz0[0]>>16]>0) blockx=1;else
if (mpb[xx[0]>>16][yy0[0]>>16][zz0[1]>>16]>0) blockx=1;else
if (mpb[xx[0]>>16][yy0[1]>>16][zz0[1]>>16]>0) blockx=1;else
if (mpb[xx[0]>>16][yy0[0]>>16][zz0[2]>>16]>0) blockx=1;else
if (mpb[xx[0]>>16][yy0[1]>>16][zz0[2]>>16]>0) blockx=1;
}
if (blockx==0) {mob[i][1]+=mob[i][4];xx0[0]+=mob[i][4];xx0[1]+=mob[i][4];} else {mob[i][4]=-mob[i][4]>>2;}
}
//x

//y
if (mob[i][5]!=0)
{
if (mob[i][5]>=0)
{//iy>0
if ((yy[1]>>16)>=mpheader[8]) blocky=1;else
if (mpb[xx0[0]>>16][yy[1]>>16][zz0[0]>>16]>0) blocky=1;else
if (mpb[xx0[1]>>16][yy[1]>>16][zz0[0]>>16]>0) blocky=1;else
if (mpb[xx0[0]>>16][yy[1]>>16][zz0[1]>>16]>0) blocky=1;else
if (mpb[xx0[1]>>16][yy[1]>>16][zz0[1]>>16]>0) blocky=1;else
if (mpb[xx0[0]>>16][yy[1]>>16][zz0[2]>>16]>0) blocky=1;else
if (mpb[xx0[1]>>16][yy[1]>>16][zz0[2]>>16]>0) blocky=1;
}
else
{//iy<0
if (yy[0]<0) blocky=1;else
if (mpb[xx0[0]>>16][yy[0]>>16][zz0[0]>>16]>0) blocky=1;else
if (mpb[xx0[1]>>16][yy[0]>>16][zz0[0]>>16]>0) blocky=1;else
if (mpb[xx0[0]>>16][yy[0]>>16][zz0[1]>>16]>0) blocky=1;else
if (mpb[xx0[1]>>16][yy[0]>>16][zz0[1]>>16]>0) blocky=1;else
if (mpb[xx0[0]>>16][yy[0]>>16][zz0[2]>>16]>0) blocky=1;else
if (mpb[xx0[1]>>16][yy[0]>>16][zz0[2]>>16]>0) blocky=1;
}
if (blocky==0) {mob[i][2]+=mob[i][5];} else {mob[i][5]=-mob[i][5]>>2;}
}
//y
if (blockx | blocky) mob[i][32]=1;
if (mob[i][31])
{
mob[i][31]--;
if (mob[i][11]) {mob[i][6]=4000;zcplaysound3d(9,5,mob[i][1],mob[i][2],mob[i][3]);
}
}

mob[i][4]=mob[i][4]>>1;
mob[i][5]=mob[i][5]>>1;
if (mob[i][6]>-2000) mob[i][6]-=100;


}

void pushmobs(void)
{
u8 i,k;
s32 dx,dy,dz,size;
size=45536;

for (i=0;i<63;i++)
if (mob[i][0]>0)
for (k=i+1;k<64;k++)
if (mob[k][0]>0)
{
dx=mob[i][1]-mob[k][1];
dy=mob[i][2]-mob[k][2];
dz=mob[i][3]-mob[k][3];

if (dx>-size)
if (dy>-size)
if (dx<size)
if (dy<size)
if (dz<65536)
if (dz>-65536)
{
mob[i][4]+=dx>>5;
mob[i][5]+=dy>>5;

mob[k][4]-=dx>>5;
mob[k][5]-=dy>>5;
}

}

}

void mobloot(u8 i)
{
s32 x,y,z,k,xx,yy,zz;
x=mob[i][1]>>16;
y=mob[i][2]>>16;
z=mob[i][3]>>16;
switch (mp[x][y][z][1])
{
case 1://exit
if (endlevel==0)
{
narration=0;
wantnarration=mpheader[17];
endlevel=256;
}
break;

case 40://campaing disc
mp[x][y][z][1]=0;configdata[1]=1;zcplaysound(1);
for (k=0;k<16;k++)
{
pr[128][0]=256+2*zlrand();
pr[128][1]=zlrand();pr[128][2]=zlrand();pr[128][3]=zlrand();
pr[128][4]=x*65536+32768;pr[128][5]=z*65536+32768;pr[128][6]=y*65536+32768;
pr[128][10]=0;pr[128][12]=0;pr[128][13]=0;pr[128][14]=0;pr[128][15]=0;
genpartdir(128);
newparticle();
}
tension[4]=0;tension[5]=0;tension[6]=255;tension[7]=255;
break;
case 41://autism disc
mp[x][y][z][1]=0;configdata[2]=1;zcplaysound(1);
for (k=0;k<16;k++)
{
pr[128][0]=256+2*zlrand();
pr[128][1]=zlrand();pr[128][2]=zlrand();pr[128][3]=zlrand();
pr[128][4]=x*65536+32768;pr[128][5]=z*65536+32768;pr[128][6]=y*65536+32768;
pr[128][10]=0;pr[128][12]=0;pr[128][13]=0;pr[128][14]=0;pr[128][15]=0;
genpartdir(128);
newparticle();
}
tension[4]=0;tension[5]=0;tension[6]=255;tension[7]=255;
break;
case 42://death disc
mp[x][y][z][1]=0;configdata[3]=1;zcplaysound(1);
for (k=0;k<16;k++)
{
pr[128][0]=256+2*zlrand();
pr[128][1]=zlrand();pr[128][2]=zlrand();pr[128][3]=zlrand();
pr[128][4]=x*65536+32768;pr[128][5]=z*65536+32768;pr[128][6]=y*65536+32768;
pr[128][10]=0;pr[128][12]=0;pr[128][13]=0;pr[128][14]=0;pr[128][15]=0;
genpartdir(128);
newparticle();
}
tension[4]=0;tension[5]=0;tension[6]=255;tension[7]=255;
break;
case 43://zombie disc
mp[x][y][z][1]=0;configdata[4]=1;zcplaysound(1);
for (k=0;k<16;k++)
{
pr[128][0]=256+2*zlrand();
pr[128][1]=zlrand();pr[128][2]=zlrand();pr[128][3]=zlrand();
pr[128][4]=x*65536+32768;pr[128][5]=z*65536+32768;pr[128][6]=y*65536+32768;
pr[128][10]=0;pr[128][12]=0;pr[128][13]=0;pr[128][14]=0;pr[128][15]=0;
genpartdir(128);
newparticle();
}
tension[4]=0;tension[5]=0;tension[6]=255;tension[7]=255;
break;
case 44://zveryle disc
mp[x][y][z][1]=0;configdata[5]=1;zcplaysound(1);
for (k=0;k<16;k++)
{
pr[128][0]=256+2*zlrand();
pr[128][1]=zlrand();pr[128][2]=zlrand();pr[128][3]=zlrand();
pr[128][4]=x*65536+32768;pr[128][5]=z*65536+32768;pr[128][6]=y*65536+32768;
pr[128][10]=0;pr[128][12]=0;pr[128][13]=0;pr[128][14]=0;pr[128][15]=0;
genpartdir(128);
newparticle();
tension[4]=0;tension[5]=0;tension[6]=255;tension[7]=255;
}
break;
case 45://narration 1
if (levelnarration[0]==0)
{
levelnarration[0]=1;
wantnarration=mpheader[2];
}

break;
case 46://narration 2
if (levelnarration[1]==0)
{
levelnarration[1]=1;
wantnarration=mpheader[3];
}

break;
case 47://checkpoint
checkpointnotify=128;

mob[mobcontrol][20]=x;
mob[mobcontrol][21]=y;
mob[mobcontrol][22]=z;

mpheader[7]=(4096-1024-mob[mobcontrol][7])/16;

for (xx=x-2;xx<=x+2;xx++)
for (yy=y-2;yy<=y+2;yy++)
if (xx>0)
if (yy>0)
if (xx<=mpheader[8])
if (yy<=mpheader[8])
if (mp[xx][yy][z][1]==47) mp[xx][yy][z][1]=0;


break;
}

}

void vismobs(void)
{
u8 i;

pushmobs();///////////////////////////////////////////////////
for (i=0;i<64;i++)
if (mob[i][0]!=0)
{
if (mob[i][0]>0)
{//alive
procmob(i);
if (i==mobcontrol) mobloot(i);

if (thisframenice) drawmob(i);
}//alive
else
{//respawning
mob[i][0]++;


if (mob[i][0]==0) respawnmob(i);
}//respawning

}
}

void clearmob(unsigned char i)
{
mob[i][0]=0;
}

void spawnallmobs(void)
{
u16 x,y,z;

for (z=0;z<mpheader[9];z++)
for (y=0;y<mpheader[8];y++)
for (x=0;x<mpheader[8];x++)
if (mp[x][y][z][1]>=48)
{
mob[64][1]=x*65536+32768;
mob[64][2]=y*65536+32768;
mob[64][3]=z*65536+8192;

mob[64][20]=x;
mob[64][21]=y;
mob[64][22]=z;

spawnmob(mp[x][y][z][1]-47);
mp[x][y][z][1]=0;
}
}
