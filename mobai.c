#include "vars.h"
#include "zlmath.h"

s32 ta,taa,range,insight,ta;
s32 x,y,z,dx,dy,dz,vx,vy;

s32 airange=5*65536;

u8 mobsee(u8 i0,u8 i1)
{
s32 x,y,z,ix,iy,iz,d,d0,i;
u8 see=1;

x=mob[i0][1];
y=mob[i0][2];
z=mob[i0][3]+45536;

ix=mob[i1][1]-x;
iy=mob[i1][2]-y;
iz=(mob[i1][3]+45536)-z;

if (ix>0) d=ix; else d=-ix;

if (iy>0) d0=iy; else d0=-iy;
if (d0>d) d=d0;

if (iz>0) d0=iz; else d0=-iz;
if (d0>d) d=d0;

d=d/16192;
if (d<1) d=1;
ix=ix/d;
iy=iy/d;
iz=iz/d;

i=0;
while ((i<d)&(see==1))
{
i++;
x+=ix;
y+=iy;
z+=iz;
if (mp[x>>16][y>>16][z>>16][0]>0) see=0;

}

return see;
}

void mobpeace(unsigned char i)
{
u8 aiact;


if (((mob[i][19]) % 128)==0)
{
x=mob[i][1]>>16;
y=mob[i][2]>>16;
z=mob[i][3]>>16;

aiact=mp[x][y][z][1];
mob[i][27]=mob[i][3];

mob[i][25]=(((mob[i][1]>>16)<<16)+32768);
mob[i][26]=(((mob[i][2]>>16)<<16)+32768);

if (aiact<2 | aiact>5) aiact=2+(zlrand()>>5)%4;

if (aiact==2) mob[i][26]-=65536; else
if (aiact==3) mob[i][25]+=65536; else
if (aiact==4) mob[i][26]+=65536; else
if (aiact==5) mob[i][25]-=65536;

mob[i][14]=-256+zlrand()*2;
mob[i][15]=-512+zlrand()*4;
mob[i][43]=1;

if (zlrand()%2==1) zcplaysound3d(mobsonic[mob[i][10]][8],4,mob[i][1],mob[i][2],mob[i][3]+65536);
}

if (mob[i][43])
mob[i][8]=2047-zarctan(mob[i][25]-mob[i][1],mob[i][26]-mob[i][2]);
mob[i][43]=0;

mob[i][7]=mob[i][7]+cturn(mob[i][7],mob[i][8])/10;
mob[i][9]=-200;

mob[i][12]=mob[i][12]+cturn(mob[i][12],mob[i][14])/16;
mob[i][13]=mob[i][13]+cturn(mob[i][13],mob[i][15])/16;


if (insight)
{
mob[i][29]=256;
mob[i][30]=AI_ATTACK;
mob[i][25]=mob[mobcontrol][1];
mob[i][26]=mob[mobcontrol][2];
mob[i][27]=mob[mobcontrol][3];
zcplaysound3d(mobsonic[mob[i][10]][9],14,mob[i][1],mob[i][2],mob[i][3]+65536);

}

}

u8 attackstyle[17]={0, 3,1,2,1, 1,4,1,1,  1,1,1,1,1,1,1,1};

void mobattack(unsigned char i)
{
mob[i][9]=-600;

if (mob[i][32]) mob[i][31]=1;
if (insight==0) mob[i][29]--;

if (((mob[i][19]) % 16)==0)
{
if (insight)
{
mob[i][25]=mob[mobcontrol][1];
mob[i][26]=mob[mobcontrol][2];
mob[i][27]=mob[mobcontrol][3];

mob[i][29]=256;
}
else
if (mob[i][29]<=0) {mob[i][29]=0;mob[i][30]=AI_PEACE;zcplaysound3d(mobsonic[mob[i][10]][10],8,mob[i][1],mob[i][2],mob[i][3]+65536);
}

ta=2047-zarctan(mob[i][25]-mob[i][1],mob[i][26]-mob[i][2]);
//ta=

if (zlrand()%8==1) zcplaysound3d(mobsonic[mob[i][10]][8],4,mob[i][1],mob[i][2],mob[i][3]+65536);
mob[i][8]=ta;

//if (mob[i][3]-mob[mobcontrol][3]>32768 | mob[i][3]-mob[mobcontrol][3]<-32768)
if (range>32536)
mob[i][12]=-zarctan(range,-mob[i][3]+mob[mobcontrol][3]);
else
mob[i][12]=0;
if (mob[i][12]<-2048) mob[i][12]+=4096;
//printf("%i\n",mob[i][12]);

if (mob[i][12]>768) mob[i][12]=768;
else
if (mob[i][12]<-768) mob[i][12]=-768;
}

mob[i][7]=mob[i][7]+cturn(mob[i][7],mob[i][8])/10;

//mob[i][12]=0;
mob[i][13]=0;
mob[i][14]=0;
mob[i][15]=0;

switch (attackstyle[mob[i][10]])
{
case 1://melee
if (mob[i][36]==0)
if (insight)
if (range<60000)
if (mob[i][3]-mob[mobcontrol][3]>-100000)
if (mob[i][3]-mob[mobcontrol][3]<100000)
mob[i][36]=64;
break;
case 2://shoot
if (mob[i][38]==0)
if (insight)
//if (range<60000)
mob[i][38]=64;
break;
case 3://happy melee
if (mob[i][36]==0)
if (mob[i][37]==0)
if (insight)
if (range<60000)
if (mob[i][3]-mob[mobcontrol][3]>-100000)
if (mob[i][3]-mob[mobcontrol][3]<100000)
if (zlrand()&1==1)
mob[i][36]=64;
else
mob[i][37]=64;
break;
case 4://happy
if (mob[i][37]==0)
if (insight)
if (range<60000)
if (mob[i][3]-mob[mobcontrol][3]>-100000)
if (mob[i][3]-mob[mobcontrol][3]<100000)
mob[i][37]=64;
break;
}

}

void mobai(unsigned char i)
{
s32 airange0;
insight=1;
if (mobcontrol==64) insight=0;
else
{
dx=mob[mobcontrol][1]-mob[i][1];
dy=mob[mobcontrol][2]-mob[i][2];
dz=mob[mobcontrol][3]-mob[i][3];

range=fastrange(dx,dy);
airange0=airange*mob[mobcontrol][28]/768;

if (range<airange0) range=srange(dx,dy); else insight=0;

if (range>airange0) insight=0;

if (insight)
{
ta=2047-zarctan(dx,dy);
taa=cturn(ta,mob[i][7]+mob[i][13]);

if (playmode!=ZPM_ZVERYLE) if (taa<-512 | taa>512) insight=0;

if (insight) if (mobsee(i,mobcontrol)==0) insight=0;
}

}


switch (mob[i][30])
{
case AI_DISABLED: break;
case AI_PEACE: mobpeace(i); break;
case AI_ATTACK: mobattack(i); break;

}


}

