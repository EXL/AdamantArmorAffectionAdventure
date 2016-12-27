#include "vars.h"
#include "camera.h"
#include "intro.h"

#define FPML(x,y) ((((x)>>7)*((y)>>7))>>2)

void procplaycontrol(void)
{

s32 ix,iy;

if (mousebutton[0])
{
ix=(mouseaxis[0]-holdmouseaxis[0])/4/(screenwidth/320);
iy=(mouseaxis[1]-holdmouseaxis[1])/4/(screenheight/240);

camera[3]+=iy;
camera[4]+=ix;
}

if (axis[1])
{camera[0]+=axis[1]*vcamera[2][0]/4096;camera[1]+=axis[1]*vcamera[2][1]/4096;camera[2]+=axis[1]*vcamera[2][2]/4096;}
if (axis[0])
{camera[0]+=axis[0]*vcamera[0][0]/4096;camera[1]+=axis[0]*vcamera[0][1]/4096;camera[2]+=axis[0]*vcamera[0][2]/4096;}





if (button[4]) camera[5]-=15;
if (button[5]) camera[5]+=15;

if (button[8]==1) newgamemode=ZGM_MENU;

}

void procgamecontrol(void)
{
if (narration==0) bgm=mpheader[1];


if (mousebutton[0]==1)
if (mouseaxis[0]>300)
if (mouseaxis[1]<20)
fpsdisplay=((fpsdisplay+1) & 1);

if (endlevel==0)
if (loserwantexit>0)
{

if (button[3]==1) {loserwantexit=0;newgamemode=ZGM_MENU;zcplaysound(3);}

if (button[0]==1 | button[1]==1 | button[2]==1) {loserwantexit=0;zcplaysound(2);}

}
else
{
if (gameswitchdelay==0)
if (button[8]==1) {loserwantexit=1;zcplaysound(3);}

if (mobcontrol==64)
{
procintro();
if (button[0]==1 | button[1]==1 | button[2]==1 |button[3]==1 |button[8]==1 |button[9]==1 | mousetap==1)
{
mob[64][1]=mpheader[4]*65536+32768;
mob[64][2]=mpheader[5]*65536+32768;
mob[64][3]=mpheader[6]*65536+1192;
mob[64][20]=mpheader[4];
mob[64][21]=mpheader[5];
mob[64][22]=mpheader[6];
mobcontrol=spawnmob(0);
mob[mobcontrol][7]=-1024-mpheader[7]*16;
tension[4]=0;tension[5]=0;tension[6]=0;tension[7]=255;
camerasync=8;
}

}
else
if (mob[mobcontrol][0]<0)
{
firstperson=0;
}
else
{



if (firstperson==0)
if (button[4]>0) {if (playeraim==0)zcplaysound3d(16,5,mob[mobcontrol][1],mob[mobcontrol][2],mob[mobcontrol][3]+65536);playeraim=16;} else if (playeraim>0) playeraim--;

firstperson=0;
if (playeraim==0)
if (mob[mobcontrol][36]==0)
if (mob[mobcontrol][37]==0)
if (mob[mobcontrol][38]==0)
if (button[5]>0) firstperson=1;

if (playeraim==16)
{
mob[mobcontrol][40]=512;
mob[mobcontrol][13]-=axis[0]/8;
mob[mobcontrol][12]+=axis[1]/8;

if (mob[mobcontrol][13]>512) {mob[mobcontrol][7]+=mob[mobcontrol][13]-512;mob[mobcontrol][13]=512;}
else
if (mob[mobcontrol][13]<-256) {mob[mobcontrol][7]+=mob[mobcontrol][13]+256;mob[mobcontrol][13]=-256;}
if (mob[mobcontrol][12]>512) mob[mobcontrol][12]=512;
else
if (mob[mobcontrol][12]<-512) mob[mobcontrol][12]=-512;

if (mob[mobcontrol][36]==0)
if (mob[mobcontrol][37]==0)
if (mob[mobcontrol][38]==0)
{
if (button[2]==1) mob[mobcontrol][38]=64;//shoot
if (button[5]==1) mob[mobcontrol][38]=64;//shoot
if (button[0]==1) mob[mobcontrol][38]=64;//shoot
}

}
else
{
mob[mobcontrol][7]-=axis[0]/4;

if (firstperson==1)
{
mob[mobcontrol][12]+=axis[1]/4;
if (mob[mobcontrol][12]>768) mob[mobcontrol][12]=768;
else
if (mob[mobcontrol][12]<-768) mob[mobcontrol][12]=-768;
}
else
mob[mobcontrol][9]+=axis[1]+axis[0]/5;

if (firstperson==0)
if (button[1]==1) mob[mobcontrol][31]=5;

if (firstperson==0)
if (mob[mobcontrol][36]==0)
if (mob[mobcontrol][37]==0)
if (mob[mobcontrol][38]==0)
{
if (button[2]==1) mob[mobcontrol][36]=64;//melee
if (button[3]==1) mob[mobcontrol][37]=64;//scream
if (button[0]==1) mob[mobcontrol][38]=64;//shoot
}

if (button[9]==1)
if (mob[mobcontrol][44]==0) {mob[mobcontrol][44]=1;zcplaysound3d(14,5,mob[mobcontrol][1],mob[mobcontrol][2],mob[mobcontrol][3]+65536);} else mob[mobcontrol][44]=-mob[mobcontrol][44];


if (mousebutton[0])
{
mob[mobcontrol][13]-=(mouseaxis[0]-holdmouseaxis[0])/4/(screenwidth/320);
mob[mobcontrol][12]+=(mouseaxis[1]-holdmouseaxis[1])/4/(screenheight/240);
if (mob[mobcontrol][13]>512) mob[mobcontrol][13]=512;
else
if (mob[mobcontrol][13]<-512) mob[mobcontrol][13]=-512;
if (mob[mobcontrol][12]>256) mob[mobcontrol][12]=256;
else
if (mob[mobcontrol][12]<-256) mob[mobcontrol][12]=-256;
}
else
{
mob[mobcontrol][13]=mob[mobcontrol][13]*9/10;


if (firstperson==0)mob[mobcontrol][12]=mob[mobcontrol][12]*9/10;

}
}
if (firstperson==1) fpscamerasimple(); else tpscamera();
}
}
}

void procautism(void)
{
s32 x,y,z,steps,ix,iy,iz,block;
if (narration==0) bgm=mpheader[1];
if (loserwantexit>0)
{

if (button[3]==1) {loserwantexit=0;newgamemode=ZGM_MENU;zcplaysound(3);}

if (button[0]==1 | button[1]==1 | button[2]==1) {loserwantexit=0;zcplaysound(2);}

}
else
{
if (gameswitchdelay==0)
if (button[8]==1) {loserwantexit=1;zcplaysound(3);}

if (mobcontrol==64)
{
mob[64][1]=mpheader[4]*65536+32768;
mob[64][2]=mpheader[5]*65536+32768;
mob[64][3]=mpheader[6]*65536+1192;
mob[64][20]=mpheader[4];
mob[64][21]=mpheader[5];
mob[64][22]=mpheader[6];
mobcontrol=spawnmob(0);
mob[mobcontrol][7]=-1024-mpheader[7]*16;
tension[4]=0;tension[5]=0;tension[6]=0;tension[7]=0;
camerasync=8;
}
//cameraautism();

camera[0]=mob[mobcontrol][1];
camera[1]=mob[mobcontrol][3]+65536+32000+FPML(f_sin[count*33%4096]/5,10*mob[mobcontrol][9]);
camera[2]=mob[mobcontrol][2];
camera[3]=mob[mobcontrol][12]+consoleturn[0]/4;
camera[4]=-mob[mobcontrol][7]-1024;
camera[5]=consoleturn[1]/4;


mob[mobcontrol][7]-=axis[0]/4;
mob[mobcontrol][9]+=axis[1]*3/2;
if (button[1]==1) mob[mobcontrol][31]=5;
if (button[4]>0)
if (mob[mobcontrol][12]<1024) mob[mobcontrol][12]+=32;
if (button[5]>0)
if (mob[mobcontrol][12]>-1024) mob[mobcontrol][12]-=32;
if (mousebutton[0])
{
mob[mobcontrol][7]-=(mouseaxis[0]-holdmouseaxis[0])/4/(screenwidth/320);
mob[mobcontrol][12]+=(mouseaxis[1]-holdmouseaxis[1])/4/(screenheight/240);
if (mob[mobcontrol][12]>1024) mob[mobcontrol][12]=1024;
else
if (mob[mobcontrol][12]<-1024) mob[mobcontrol][12]=-1024;
}
else
{
mob[mobcontrol][13]=mob[mobcontrol][13]*9/10;
if (mob[mobcontrol][9]<-256 | mob[mobcontrol][9]>256)
mob[mobcontrol][12]=mob[mobcontrol][12]*9/10;
}
//
if (button[3]==1) {autismstuff=(autismstuff+1)%8;autismdelay=436;}

if (button[0]==1 | button[2]==1)
{
x=camera[0];y=camera[2];z=camera[1];

ix=-vcamera[2][0];iy=-vcamera[2][2];iz=-vcamera[2][1];

x+=ix;y+=iy;z+=iz;

ix=ix>>2;iy=iy>>2;iz=iz>>2;

block=0;
if (x>0 & y>0 & z>0 & x<truemaxmapx & y<truemaxmapx & z<truemaxmaph)
{
steps=0;
while (block==0 & steps<9)
{
steps++;
x+=ix;
y+=iy;
z+=iz;
block=1;
if (x>0 & y>0 & z>0 & x<truemaxmapx & y<truemaxmapx & z<truemaxmaph)
{
block=0;
if (mp[x>>16][y>>16][z>>16][0]>0) block=2;

}

if (block==2)
if (button[2]==1)
{mpedit((x)>>16,(y)>>16,(z)>>16,0);autismdelay=512;vibro=127;zcplaysound(13);}
else
{
block=2;
x=x-ix;
y=y-iy;
z=z-iz;
x=x>>16;
y=y>>16;
z=z>>16;
if (((x)<<16)+32768-mob[mobcontrol][1]<65536)
if (((x)<<16)+32768-mob[mobcontrol][1]>-65536)
if (((y)<<16)+32768-mob[mobcontrol][2]<65536)
if (((y)<<16)+32768-mob[mobcontrol][2]>-65536)
if (((z)<<16)+32768-mob[mobcontrol][3]<120536)
if (((z)<<16)+32768-mob[mobcontrol][3]>-32636)
block=1;

if (block==2)
{mpedit((x),(y),(z),1+autismstuff);autismdelay=512;vibro=127;zcplaysound(13);}
}
}

}



}
//
}
}
void proczveryle(void)
{
if (narration==0) bgm=mpheader[1];
if (loserwantexit>0)
{

if (button[3]==1) {loserwantexit=0;newgamemode=ZGM_MENU;zcplaysound(3);}

if (button[0]==1 | button[1]==1 | button[2]==1) {loserwantexit=0;zcplaysound(2);}

}
else
{
if (gameswitchdelay==0)
if (button[8]==1) {loserwantexit=1;zcplaysound(3);}

if (mobcontrol==64)
{
mob[64][1]=mpheader[4]*65536+32768;
mob[64][2]=mpheader[5]*65536+32768;
mob[64][3]=mpheader[6]*65536+1192;
mob[64][20]=mpheader[4];
mob[64][21]=mpheader[5];
mob[64][22]=mpheader[6];
mobcontrol=spawnmob(0);
mob[mobcontrol][7]=-1024-mpheader[7]*16;
tension[4]=0;tension[5]=0;tension[6]=0;tension[7]=0;
camerasync=8;
}
//cameraautism();

camera[0]=mob[mobcontrol][1];
camera[1]=mob[mobcontrol][3]+65536+16000+FPML(f_sin[count*33%4096]/5,10*mob[mobcontrol][9]);
camera[2]=mob[mobcontrol][2];
camera[3]=mob[mobcontrol][12]+consoleturn[0]/4;
camera[4]=-mob[mobcontrol][7]-1024;
camera[5]=consoleturn[1]/4;


mob[mobcontrol][7]-=axis[0]/4;
mob[mobcontrol][9]+=axis[1]*3/2;
if (button[1]==1) mob[mobcontrol][31]=5;






if (mousebutton[0])
{
mob[mobcontrol][7]-=(mouseaxis[0]-holdmouseaxis[0])/4/(screenwidth/320);
mob[mobcontrol][12]+=(mouseaxis[1]-holdmouseaxis[1])/4/(screenheight/240);
if (mob[mobcontrol][12]>768) mob[mobcontrol][12]=768;
else
if (mob[mobcontrol][12]<-768) mob[mobcontrol][12]=-768;
}
else
{
mob[mobcontrol][13]=mob[mobcontrol][13]*9/10;

mob[mobcontrol][12]=mob[mobcontrol][12]*9/10;
}
}
}
