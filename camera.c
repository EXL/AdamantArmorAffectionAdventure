#include "vars.h"


#define FPML(x,y) ((((x)>>7)*((y)>>7))>>2)

s32 cm[4][4],mm[4][4],cmm[4][4],vv[4];


u8 comfortcube(s32 x,s32 y,s32 z,s32 csizex,s32 csizey)
{
u8 nice=1;

if (x-csizex<0) nice=0;
else
if (y-csizex<0) nice=0;
else
if (z-csizey<0) nice=0;
else
if (x+csizex>=truemaxmapx) nice=0;
else
if (y+csizex>=truemaxmapx) nice=0;
else
if (z+csizey>=truemaxmaph) nice=0;
else
if (mp[((x-csizex)>>16)][((y-csizex)>>16)][((z-csizey)>>16)][0]>0) nice=0;
else
if (mp[((x+csizex)>>16)][((y-csizex)>>16)][((z-csizey)>>16)][0]>0) nice=0;
else
if (mp[((x-csizex)>>16)][((y+csizex)>>16)][((z-csizey)>>16)][0]>0) nice=0;
else
if (mp[((x+csizex)>>16)][((y+csizex)>>16)][((z-csizey)>>16)][0]>0) nice=0;
else
if (mp[((x-csizex)>>16)][((y-csizex)>>16)][((z+csizey)>>16)][0]>0) nice=0;
else
if (mp[((x+csizex)>>16)][((y-csizex)>>16)][((z+csizey)>>16)][0]>0) nice=0;
else
if (mp[((x-csizex)>>16)][((y+csizex)>>16)][((z+csizey)>>16)][0]>0) nice=0;
else
if (mp[((x+csizex)>>16)][((y+csizex)>>16)][((z+csizey)>>16)][0]>0) nice=0;



return nice;

}

void camerastep(void)
{
s32 t,x,y;

cm[0][0]=65536;cm[1][0]=0;    cm[2][0]=0;    cm[3][0]=0;
cm[0][1]=0;    cm[1][1]=-65536;cm[2][1]=0;    cm[3][1]=0;
cm[0][2]=0;    cm[1][2]=0;    cm[2][2]=65536;cm[3][2]=0;
cm[0][3]=0;    cm[1][3]=0;    cm[2][3]=0;    cm[3][3]=65536;

camera[3]=camera[3]%4096;
if (camera[3]<0) camera[3]=4096+camera[3];
camera[4]=camera[4]%4096;
if (camera[4]<0) camera[4]=4096+camera[4];
camera[5]=camera[5]%4096;
if (camera[5]<0) camera[5]=4096+camera[5];

//y
mm[0][0]=f_cos[camera[4]];mm[1][0]=0;    mm[2][0]=-f_sin[camera[4]];mm[3][0]=0;
mm[0][1]=0;               mm[1][1]=65536;mm[2][1]=0;                mm[3][1]=0;
mm[0][2]=f_sin[camera[4]];mm[1][2]=0;    mm[2][2]= f_cos[camera[4]];mm[3][2]=0;
mm[0][3]=0;               mm[1][3]=0;    mm[2][3]=0;                mm[3][3]=65536;

for (y=0;y<4;y++)
for (x=0;x<4;x++)
{
cmm[x][y]=0;
for (t=0;t<4;t++)
cmm[x][y]+=FPML(cm[t][y],mm[x][t]);
}
for (y=0;y<4;y++)
for (x=0;x<4;x++)
cm[x][y]=cmm[x][y];

//x
mm[0][0]=65536;mm[1][0]=0;                mm[2][0]=0;                mm[3][0]=0;
mm[0][1]=0;    mm[1][1]=f_cos[camera[3]]; mm[2][1]=-f_sin[camera[3]];mm[3][1]=0;
mm[0][2]=0;    mm[1][2]=f_sin[camera[3]]; mm[2][2]= f_cos[camera[3]];mm[3][2]=0;
mm[0][3]=0;    mm[1][3]=0;                mm[2][3]=0;                mm[3][3]=65536;

for (y=0;y<4;y++)
for (x=0;x<4;x++)
{
cmm[x][y]=0;
for (t=0;t<4;t++)
cmm[x][y]+=FPML(cm[t][y],mm[x][t]);
}

for (y=0;y<4;y++)
for (x=0;x<4;x++)
cm[x][y]=cmm[x][y];
//z
mm[0][0]=f_cos[camera[5]];mm[1][0]=-f_sin[camera[5]];mm[2][0]=0;    mm[3][0]=0;
mm[0][1]=f_sin[camera[5]];mm[1][1]= f_cos[camera[5]];mm[2][1]=0;    mm[3][1]=0;
mm[0][2]=0;               mm[1][2]=0;                mm[2][2]=65536;mm[3][2]=0;
mm[0][3]=0;               mm[1][3]=0;                mm[2][3]=0;    mm[3][3]=65536;

for (y=0;y<4;y++)
for (x=0;x<4;x++)
{
cmm[x][y]=0;
for (t=0;t<4;t++)
cmm[x][y]+=FPML(cm[t][y],mm[x][t]);
}

for (y=0;y<4;y++)
for (x=0;x<4;x++)
cm[x][y]=cmm[x][y];

//end

vv[0]=65536;vv[1]=0;vv[2]=0;vv[3]=65536;
for (t=0;t<4;t++)
{
vcamera[0][t]=0;
for (x=0;x<4;x++)
vcamera[0][t]+=FPML(vv[x],cmm[x][t]);
}

vv[0]=0;vv[1]=65536;vv[2]=0;vv[3]=65536;
for (t=0;t<4;t++)
{
vcamera[1][t]=0;
for (x=0;x<4;x++)
vcamera[1][t]+=FPML(vv[x],cmm[x][t]);
}
vv[0]=0;vv[1]=0;vv[2]=65536;vv[3]=65536;
for (t=0;t<4;t++)
{
vcamera[2][t]=0;
for (x=0;x<4;x++)
vcamera[2][t]+=FPML(vv[x],cmm[x][t]);
}


if (camera[0]<0) camera[0]=0;
if (camera[1]<0) camera[1]=0;
if (camera[2]<0) camera[2]=0;

if (camera[0]>truemaxmapx) camera[0]=truemaxmapx;
if (camera[1]>truemaxmaph) camera[1]=truemaxmaph;
if (camera[2]>truemaxmapx) camera[2]=truemaxmapx;

}

/*
tpscam
0- angle x
1- angle y
2- angle z

6,7 first bone

10,11 second
*/
s32 inertion[3]={0,0,0};

void fpscamerasimple(void)
{
camera[0]=mob[mobcontrol][1];
camera[1]=mob[mobcontrol][3]+65536+12000;
camera[2]=mob[mobcontrol][2];
camera[3]=mob[mobcontrol][12];
camera[4]=-mob[mobcontrol][7]-1024;
camera[5]=0;
camerasync=2;
}

void tpscamera(void)
{
s32 x,y,z,t0,delta,dx,dy,dz,ix,iy,iz,i,steps,tuneturn,slashtune,firetune,dist;

slashtune=f_sin[mob[mobcontrol][36]*16]/256;
firetune=f_sin[mob[mobcontrol][38]*8]/256;

portraitmode=0;
//if (gsensor[0]<-900) portraitmode=1;


x=mob[mobcontrol][1];
y=mob[mobcontrol][2];
z=mob[mobcontrol][3];

dx=x;
dy=y;
dz=z+65536+32768;

z+=65536+playeraim*1000-slashtune*50-firetune*40;

t0=tpscam[7];
t0=t0 & 4095;
if (t0<0) t0=4095-t0;

x+=f_cos[t0]*1;
y+=f_sin[t0]*1;

t0=tpscam[11];
t0=t0 & 4095;
if (t0<0) t0=4095-t0;


//!!!! 9/4

dist=90-playeraim*2-slashtune/10+firetune/10;
x+=f_cos[t0]*(dist)/(40);
y+=f_sin[t0]*(dist)/(40);

tuneturn=-playeraim*60-mob[mobcontrol][13]/3+firetune;

if (portraitmode) tuneturn+=2048;
//if playeraim


//relaxation
delta=((tuneturn+2348-mob[mobcontrol][7])-tpscam[7]);
delta=delta & 4095;
if (delta>2048) delta=-4096+delta;
if (delta<-2048) delta=4096+delta;

tpscam[7]+=delta/9;;

if (portraitmode)
delta=((2048-mob[mobcontrol][7])-tpscam[11]);
else
delta=((-mob[mobcontrol][7])-tpscam[11]);


delta=delta & 4095;
if (delta>2048) delta=-4096+delta;
if (delta<-2048) delta=4096+delta;

tpscam[11]+=delta/40;

//relaxation


if (playeraim)
{
tpscam[3]=-mob[mobcontrol][6]/50+mob[mobcontrol][12]/2;
tpscam[4]=-1024+tpscam[11]-mob[mobcontrol][13]/2;
z+=mob[mobcontrol][12]*100;
}
else
{
tpscam[3]=-mob[mobcontrol][6]/50+mob[mobcontrol][12];
tpscam[4]=-1024+tpscam[11]-mob[mobcontrol][13];
}
steps=8;
z+=48*consoleturn[0];


ix=(x-dx)/steps;
iy=(y-dy)/steps;
iz=(z-dz)/steps;
i=0;
while ((i<steps)&(comfortcube(dx,dy,dz,23000,19192)>0))
{
i++;
dx+=ix;
dy+=iy;
dz+=iz;

}
tpscam[0]=dx;
tpscam[1]=dz;
tpscam[2]=dy;

tpscam[1]+=f_sin[count*3%4096]/16;

if (camerasync>0)
{
camerasync--;
for (i=0;i<3;i++) camera[i]=tpscam[i];
}
else
for (i=0;i<3;i++)
camera[i]=camera[i]+(tpscam[i]-camera[i])/9;

inertion[2]+=(gsensor[3]*2-inertion[2])/8;
inertion[0]+=(gsensor[4]*2-inertion[0])/8;
inertion[1]=0;

//if (portraitmode) inertion[1]=2048;
//if (portraitmode) inertion[2]=1024;

camera[3]=tpscam[3]+inertion[0];
camera[4]=tpscam[4]+inertion[1];
camera[5]=tpscam[5]+inertion[2];
camera[3]+=consoleturn[0]/2;
camera[5]+=consoleturn[1];


}
