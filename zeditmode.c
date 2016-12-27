#include "vars.h"
#include "render.h"
#include "wmapload.h"

char playmode_s[9][16]={
"NONE",
"FLYINTRO",
"EDIT O_O",
"TUTORIAL",//do not want
"AAA",
"AUTISM",
"ZOMBIEH",
"ZVERYLE",
"CUTSCENE"
};

u8 editswitch,cameraid,editlevel,editspeed;
s8 editmenupos;
s32 editmenuposw=13*1024+200;

s32 curx,cury,curz;

u8 ebrush=10,ebrush1=1;
s8 ebrushdelay=0,showdelay=0;

u8 brushindex;

s8 brushdata[40]=
{//x0 x1,z0 z1
0,0,0,0,
0,0,0,1,
0,0,0,2,
0,1,0,0,
0,1,0,1,
0,1,0,2,
-1,1,0,0,
-1,1,0,1,
-1,1,0,2,
-1,1,-1,1
};

void brushact(u8 index,s32 x,s32 y,s32 z)
{
s32 xx,yy,zz;
for (xx=brushdata[brushindex*4+0];xx<=brushdata[brushindex*4+1];xx++)
for (yy=brushdata[brushindex*4+0];yy<=brushdata[brushindex*4+1];yy++)
for (zz=brushdata[brushindex*4+2];zz<=brushdata[brushindex*4+3];zz++)
mpedit(xx+x,yy+y,zz+z,index);
}

void zeditpaint(void)
{
s32 x,y,z,l,lx,ix,iy,i,id,dx,dy,xx,yy,zz;

lx=65536/5;
l=65536/4;
zlPush();
zlColor4x(255,255,255,255);
zlBeginQuads();
for (y=-4;y<4;y++)
for (x=-5;x<5;x++)
{
ix=curx+x;
iy=cury-y;
if (ix>=0)
if (iy>=0)
if (ix<mpheader[8])
if (iy<mpheader[8])
{
zlColor4x(255,255,255,255);
if (mp1mode==1)
{

if (curz>0)
if (mp[ix][iy][curz-1][0]>0)
{
zlBindTexture(terrtexx[mp[ix][iy][curz-1][0]][0]);zlColor4x(64,64,64,255);
zlTexCoord2x(    0,    0);zlVertex3x((x+0)*lx,(y+0)*l,0);
zlTexCoord2x(65536,    0);zlVertex3x((x+1)*lx,(y+0)*l,0);
zlTexCoord2x(65536,65536);zlVertex3x((x+1)*lx,(y+1)*l,0);
zlTexCoord2x(    0,65536);zlVertex3x((x+0)*lx,(y+1)*l,0);
}

id=mp[ix][iy][curz][1];
if (id)
{
zlBindTexture(2);
zlColor4x(255,255,255,255);
dx=id%8;
dy=id/8;

zlTexCoord2x((dx+0)*8192,(dy+1)*8192);zlVertex3x((x+0)*lx,(y+0)*l,0);
zlTexCoord2x((dx+1)*8192,(dy+1)*8192);zlVertex3x((x+1)*lx,(y+0)*l,0);
zlTexCoord2x((dx+1)*8192,(dy+0)*8192);zlVertex3x((x+1)*lx,(y+1)*l,0);
zlTexCoord2x((dx+0)*8192,(dy+0)*8192);zlVertex3x((x+0)*lx,(y+1)*l,0);
}
else
{
if (mp[ix][iy][curz][0]>0)
{
zlColor4x(255,255,255,255);
zlBindTexture(terrtexx[mp[ix][iy][curz][0]][0]);
zlTexCoord2x(    0,    0);zlVertex3x((x+0)*lx,(y+0)*l,0);
zlTexCoord2x(65536,    0);zlVertex3x((x+1)*lx,(y+0)*l,0);
zlTexCoord2x(65536,65536);zlVertex3x((x+1)*lx,(y+1)*l,0);
zlTexCoord2x(    0,65536);zlVertex3x((x+0)*lx,(y+1)*l,0);
}
//else

}

}
else//normal
{


if (mp[ix][iy][curz][0]>0) zlBindTexture(terrtexx[mp[ix][iy][curz][0]][0]);
else
{
if (curz>0)
{
if (mp[ix][iy][curz-1][0]>0) {zlBindTexture(terrtexx[mp[ix][iy][curz-1][0]][0]);zlColor4x(64,64,64,255);}
else zlBindTexture(1);
}
else zlBindTexture(1);
}
if (curz>0)
if (mp[ix][iy][curz][0]>0)
if (mp[ix][iy][curz-1][0]==0) {zlEndQuads();zlBlend(1);zlBeginQuads();zlColor4x(255,255,255,168);}

zlTexCoord2x(    0,    0);zlVertex3x((x+0)*lx,(y+0)*l,0);
zlTexCoord2x(65536,    0);zlVertex3x((x+1)*lx,(y+0)*l,0);
zlTexCoord2x(65536,65536);zlVertex3x((x+1)*lx,(y+1)*l,0);
zlTexCoord2x(    0,65536);zlVertex3x((x+0)*lx,(y+1)*l,0);

if (curz>0)
if (mp[ix][iy][curz][0]>0)
if (mp[ix][iy][curz-1][0]==0) {zlEndQuads();zlBlend(0);zlBeginQuads();}

}
}
}
zlEndQuads();
zlPop();
//s8 i;
if (ebrushdelay)
{
if (ebrushdelay>0) ebrushdelay--; else ebrushdelay++;
showdelay=125;
}
if (showdelay)
{
showdelay--;
zlBlend(1);
zlBeginQuads();
zlBindTexture(0);
zlColor4x(255,255,255,200);
zlTexCoord2x(0    ,65536);zlVertex3x(-65536,-35536,0);
zlTexCoord2x(65536,65536);zlVertex3x(65536,-35536,0);
zlTexCoord2x(65536,    0);zlVertex3x(65536,-65536,0);
zlTexCoord2x(    0,    0);zlVertex3x(-65536,-65536,0);
zlEndQuads();
zlBlend(0);
zlPush();
zlTranslate(ebrushdelay*400,-48000,0);
zlScale(10000,10000,10000);
for (x=-3;x<4;x++)
{
if (mp1mode)
i=ebrush1+x;
else
i=ebrush+x;
if (i>=0)
if ((i<40 & mp1mode==0)|(i<64 & mp1mode==1))
{
zlPush();
zlTranslate(145536*x,0,0);
if (x==0) zlColor4x(255,255,255,255);
else zlColor4x(showdelay*2,showdelay*2,showdelay*2,255);

zlBeginQuads();
if (mp1mode)
{
id=i;
dx=id%8;
dy=id/8;
zlBindTexture(2);
zlTexCoord2x((dx+0)*8192,(dy+0)*8192);zlVertex3x(-65536, 65536,0);
zlTexCoord2x((dx+1)*8192,(dy+0)*8192);zlVertex3x( 65536, 65536,0);
zlTexCoord2x((dx+1)*8192,(dy+1)*8192);zlVertex3x( 65536,-65536,0);
zlTexCoord2x((dx+0)*8192,(dy+1)*8192);zlVertex3x(-65536,-65536,0);

}
else
{
zlBindTexture(terrtexx[i][1]);
zlTexCoord2x(    0,    0);zlVertex3x(-65536,65536,0);
zlTexCoord2x(65536,    0);zlVertex3x(65536,65536,0);
zlTexCoord2x(65536,65536);zlVertex3x(65536,-65536,0);
zlTexCoord2x(    0,65536);zlVertex3x(-65536,-65536,0);

}
zlEndQuads();
zlPop();
}
}

zlPop();
}

camera[0]+=axis[0]*20;
camera[2]+=axis[1]*20;

if (button[0]==1) {mp1mode=(mp1mode+1)%2;}

if (button[1]==1) camera[1]-=65536;
if (button[3]==1) camera[1]+=65536;

if (mp1mode)
{
if (button[4]==1 | (button[4]>30 & (((count) % 4)==1) )) if (ebrush1>0) {ebrush1--;ebrushdelay=-30;};
if (button[5]==1 | (button[5]>30 & (((count) % 4)==1) )) if (ebrush1<63) {ebrush1++;ebrushdelay=+30;};
}
else
{
if (button[4]==1 | (button[4]>30 & (((count) % 4)==1) )) if (ebrush>0) {ebrush--;ebrushdelay=-30;};
if (button[5]==1 | (button[5]>30 & (((count) % 4)==1) )) if (ebrush<39) {ebrush++;ebrushdelay=+30;};
}

if (mousebutton[0])
{
x=mouseaxis[0]/32-5+curx;
y=mouseaxis[1]/30-3+cury;
if (x>=0)
if (y>=0)
if (x<mpheader[8])
if (y<mpheader[8])
{
if (mp1mode==0) brushact(ebrush,x,y,curz);
else mp[x][y][curz][1]=ebrush1;
}
}

if (button[2]==1)
if (mp1mode==0)
{
if (button[4]>0 & button[5]>0)
{
for (x=0;x<mpheader[8];x++)
for (y=0;y<mpheader[8];y++)
for (z=0;z<mpheader[9];z++)
mpedit(x,y,z,ebrush);

}
else
for (x=-5;x<5;x++)
for (y=-3;y<5;y++)
mpedit(x+curx,y+cury,curz,ebrush);
}

}

void zeditrender(void)
{
s32 t,xx,yy,zz;

zlPush();
zlScreen(6553,4915,6553);

zlRotatez(camera[5]);
zlRotatex(camera[3]);
zlRotatey(camera[4]);
zlTranslate(-camera[0],-camera[1],-camera[2]);

zlDepthTest(1);
zlBindTexture(1);
t=65536+f_sin[count*10%4096]/4;

for (xx=brushdata[brushindex*4+0];xx<=brushdata[brushindex*4+1];xx++)
for (yy=brushdata[brushindex*4+0];yy<=brushdata[brushindex*4+1];yy++)
for (zz=brushdata[brushindex*4+2];zz<=brushdata[brushindex*4+3];zz++)
{
zlPush();
zlTranslate((curx+xx)*65536+32768,(curz+zz)*65536+32768,(cury+yy)*65536+32768);
zlScale(t,66600,t);
zlBeginQuads();
zlColor4x(255,255,255,255);
zlTexCoord2x(    0,    0);zlVertex3x(-32768,-32768,-32768);
zlTexCoord2x(65536,    0);zlVertex3x(32768,-32768,-32768);
zlTexCoord2x(65536,65536);zlVertex3x(32768,-32768,32768);
zlTexCoord2x(    0,65536);zlVertex3x(-32768,-32768,32768);

zlTexCoord2x(    0,    0);zlVertex3x(-32768,32768,-32768);
zlTexCoord2x(65536,    0);zlVertex3x(32768,32768,-32768);
zlTexCoord2x(65536,65536);zlVertex3x(32768,32768,32768);
zlTexCoord2x(    0,65536);zlVertex3x(-32768,32768,32768);

zlTexCoord2x(    0,    0);zlVertex3x(-32768,-32768,-32768);
zlTexCoord2x(65536,    0);zlVertex3x(32768,-32768,-32768);
zlTexCoord2x(65536,65536);zlVertex3x(32768,32768,-32768);
zlTexCoord2x(    0,65536);zlVertex3x(-32768,32768,-32768);

zlTexCoord2x(    0,    0);zlVertex3x(-32768,-32768,32768);
zlTexCoord2x(65536,    0);zlVertex3x(32768,-32768,32768);
zlTexCoord2x(65536,65536);zlVertex3x(32768,32768,32768);
zlTexCoord2x(    0,65536);zlVertex3x(-32768,32768,32768);

zlEndQuads();
zlPop();
}
zlDepthTest(0);

zlPop();
zlScreen(65536,65536,0);
zlPush();zlTranslate(-63000,-63000,0);zlScale(5000,8000,8000);
l_text=sprintf(s_text,"%i %i %i [%i] B:%i",curx,cury,curz,ebrush,brushindex);zlRenderText();zlPop();

}


void loadcview(unsigned char i)
{
camera[0]=mpheader[28+i*6+0]*65536+32768;
camera[1]=mpheader[28+i*6+1]*65536+32768;
camera[2]=mpheader[28+i*6+2]*65536+32768;

camera[3]=mpheader[28+i*6+3]*16;
camera[4]=mpheader[28+i*6+4]*16;
camera[5]=mpheader[28+i*6+5]*16;
}

void savecview(u8 i)
{
mpheader[28+i*6+0]=camera[0]/65536;
mpheader[28+i*6+1]=camera[1]/65536;
mpheader[28+i*6+2]=camera[2]/65536;

mpheader[28+i*6+3]=camera[3]/16;
mpheader[28+i*6+4]=camera[4]/16;
mpheader[28+i*6+5]=camera[5]/16;
}

void zeditcontrol(void)
{
s32 ix,iy;

if (mousebutton[0])
{
ix=(mouseaxis[0]-holdmouseaxis[0])/4/(screenwidth/320);
iy=(mouseaxis[1]-holdmouseaxis[1])/4/(screenheight/240);
camera[3]+=iy;
camera[4]+=ix;
}

if (axis[1]){camera[0]+=axis[1]*vcamera[2][0]/4096;camera[1]+=axis[1]*vcamera[2][1]/4096;camera[2]+=axis[1]*vcamera[2][2]/4096;}
if (axis[0]){camera[0]+=axis[0]*vcamera[0][0]/4096;camera[1]+=axis[0]*vcamera[0][1]/4096;camera[2]+=axis[0]*vcamera[0][2]/4096;}

if (button[0]) brushact(0,curx,cury,curz);
if (button[2]) brushact(ebrush,curx,cury,curz);

if (button[1]==1) if (brushindex>0) brushindex--;
if (button[3]==1) if (brushindex<9) brushindex++;


}


void zeditmenu(void)
{
zlBlend(1);
zlBeginQuads();
zlBindTexture(0);
zlColor4x(64,64,255,128);
zlTexCoord2x(0,0);zlVertex3x(-65536,65536,0);
zlTexCoord2x(65536,0);zlVertex3x(65536,65536,0);
zlTexCoord2x(65536,65536);zlVertex3x(65536,-65536,0);
zlTexCoord2x(0,65536);zlVertex3x(-65536,-65536,0);

zlEndQuads();

if (editmenupos<11)
{
zlColor4x(255,0,0,128);
zlBindTexture(0);
zlPush();
zlTranslate(0,55000-10000*editmenupos,0);zlScale(64000,5000,10000);
zlBeginQuads();
zlTexCoord2x(0,0);zlVertex3x(-65536,65536,0);
zlTexCoord2x(65536,0);zlVertex3x(65536,65536,0);
zlTexCoord2x(65536,65536);zlVertex3x(65536,-65536,0);
zlTexCoord2x(0,65536);zlVertex3x(-65536,-65536,0);
zlEndQuads();
zlPop();
zlBlend(0);

zlColor4x(255,255,255,255);

zlPush();zlTranslate(-60000,50000,0);zlScale(6000,10000,10000);
l_text=sprintf(s_text,"PMODE:%s",playmode_s[mpheader[0]]);zlRenderText();zlPop();

if (editmenupos==0)
{
if (button[2]==1) if (mpheader[0]<8) mpheader[0]++;
if (button[0]==1) if (mpheader[0]>0) mpheader[0]--;
}

zlPush();zlTranslate(-60000,40000,0);zlScale(6000,10000,10000);
l_text=sprintf(s_text,"BGM  :%i Y-PLAY",mpheader[1]);zlRenderText();zlPop();

if (editmenupos==1)
{
if (button[3]==1) bgm=mpheader[1];
if (button[2]==1) mpheader[1]++;
if (button[0]==1) mpheader[1]--;
}


zlPush();zlTranslate(-60000,30000,0);zlScale(6000,10000,10000);
l_text=sprintf(s_text,"SIZE :%i_%i_%i",mpheader[8],mpheader[8],mpheader[9]);zlRenderText();zlPop();

if (editmenupos==2)
{
if (button[2]==1) if (mpheader[8]<128) mpheader[8]++;
if (button[0]==1) if (mpheader[8]>4) mpheader[8]--;

if (button[3]==1) if (mpheader[9]<64) mpheader[9]++;
if (button[1]==1) if (mpheader[9]>4) mpheader[9]--;
}


zlPush();zlTranslate(-60000,20000,0);zlScale(6000,10000,10000);
l_text=sprintf(s_text,"SKY  :%i",mpheader[21]);zlRenderText();zlPop();

if (editmenupos==3)
{
if (button[2]==1) mpheader[21]++;
if (button[0]==1) mpheader[21]--;
}

zlPush();zlTranslate(-60000,10000,0);zlScale(6000,10000,10000);
l_text=sprintf(s_text,"FOG_C: R%i G%i B%i",mpheader[18],mpheader[19],mpheader[20]);zlRenderText();zlPop();

if (editmenupos==4)
{
if (button[2]) if (mpheader[18]<255)mpheader[18]++;
if (button[0]) if (mpheader[18]>0)mpheader[18]--;

if (button[3]) if (mpheader[19]<255)mpheader[19]++;
if (button[1]) if (mpheader[19]>0)mpheader[19]--;

if (button[5]) if (mpheader[20]<255)mpheader[20]++;
if (button[4]) if (mpheader[20]>0)mpheader[20]--;
}

zlPush();zlTranslate(-60000,00000,0);zlScale(6000,10000,10000);
l_text=sprintf(s_text,"DARK : R%i G%i B%i",mpheader[10],mpheader[11],mpheader[12]);zlRenderText();zlPop();

if (editmenupos==5)
{
if (button[2]) if (mpheader[10]<255) mpheader[10]++;
if (button[0]) if (mpheader[10]>0) mpheader[10]--;

if (button[3]) if (mpheader[11]<255)mpheader[11]++;
if (button[1]) if (mpheader[11]>0)mpheader[11]--;

if (button[5]) if (mpheader[12]<255)mpheader[12]++;
if (button[4]) if (mpheader[12]>0)mpheader[12]--;
}

zlPush();zlTranslate(-60000,-10000,0);zlScale(6000,10000,10000);
l_text=sprintf(s_text,"LIGHT: R%i G%i B%i",mpheader[13],mpheader[14],mpheader[15]);zlRenderText();zlPop();

if (editmenupos==6)
{
if (button[2]) if (mpheader[13]<255) mpheader[13]++;
if (button[0]) if (mpheader[13]>0)mpheader[13]--;

if (button[3]) if (mpheader[14]<255)mpheader[14]++;
if (button[1]) if (mpheader[14]>0)mpheader[14]--;

if (button[5]) if (mpheader[15]<255)mpheader[15]++;
if (button[4]) if (mpheader[15]>0)mpheader[15]--;
}

zlPush();zlTranslate(-60000,-20000,0);zlScale(6000,10000,10000);
l_text=sprintf(s_text,"L POS: %i %i %i(Y)",mpheader[23],mpheader[24],mpheader[25]);zlRenderText();zlPop();

if (editmenupos==7)
{
if (button[2]==1)
{
mpheader[23]=(vcamera[2][0]+65536)/512;
mpheader[24]=(vcamera[2][1]+65536)/512;
mpheader[25]=(vcamera[2][2]+65536)/512;
rescanmaphead();
rescanlight();
}
else
if (button[3]==1) {rescanlight();}

}
zlPush();zlTranslate(-60000,-30000,0);zlScale(6000,10000,10000);
l_text=sprintf(s_text,"VIEW : %i/5 (Y-LOAD)",cameraid);zlRenderText();zlPop();

if (editmenupos==8)
{
if (button[2]==1) if (cameraid<5) cameraid++;
if (button[0]==1) if (cameraid>0) cameraid--;

if (button[3]==1) loadcview(cameraid);
}

zlPush();zlTranslate(-60000,-40000,0);zlScale(6000,10000,10000);
l_text=sprintf(s_text,"<SAVE VIEW>");zlRenderText();zlPop();
if (editmenupos==9)
if (button[2]==1)
{
savecview(cameraid);
loadcview(cameraid);
}

zlPush();zlTranslate(-60000,-50000,0);zlScale(6000,10000,10000);
l_text=sprintf(s_text,"<RESCAN MAP>");zlRenderText();zlPop();
if (editmenupos==10)
if (button[2]==1)
rescanmap();

zlPush();zlTranslate(-10000,-61000,0);zlScale(6000,10000,10000);
l_text=sprintf(s_text,"[NEXT PAGE]");zlRenderText();zlPop();

}
else
{
zlColor4x(255,0,0,128);
zlBindTexture(0);
zlPush();
zlTranslate(0,55000-10000*(editmenupos-11),0);zlScale(64000,5000,10000);
zlBeginQuads();
zlTexCoord2x(0,0);zlVertex3x(-65536,65536,0);
zlTexCoord2x(65536,0);zlVertex3x(65536,65536,0);
zlTexCoord2x(65536,65536);zlVertex3x(65536,-65536,0);
zlTexCoord2x(0,65536);zlVertex3x(-65536,-65536,0);
zlEndQuads();
zlPop();
zlBlend(0);

zlColor4x(255,255,255,255);

zlPush();zlTranslate(-60000,50000,0);zlScale(6000,10000,10000);
l_text=sprintf(s_text,"NAR1 %i NAR2 %i",mpheader[2],mpheader[3]);zlRenderText();zlPop();
if (editmenupos==11)
{
if (button[2]==1) mpheader[2]++;
if (button[0]==1) mpheader[2]--;

if (button[3]==1) mpheader[3]++;
if (button[1]==1) mpheader[3]--;
}

zlPush();zlTranslate(-60000,40000,0);zlScale(6000,10000,10000);
l_text=sprintf(s_text,"NEXT MAP : %i",mpheader[22]);zlRenderText();zlPop();

if (editmenupos==12)
{
if (button[2]==1 | button[2]>64) mpheader[22]++;
if (button[0]==1 | button[0]>64) mpheader[22]--;
}

zlPush();zlTranslate(-60000,30000,0);zlScale(6000,10000,10000);
l_text=sprintf(s_text,"MAP ID   : %i",editlevel);zlRenderText();zlPop();

if (editmenupos==13)
{
if (button[2]==1 | button[2]>64) editlevel++;
if (button[0]==1 | button[0]>64) editlevel--;
}

zlPush();zlTranslate(-60000,20000,0);zlScale(6000,10000,10000);
l_text=sprintf(s_text,"<LOAD MAP>");zlRenderText();zlPop();
if (editmenupos==14) if (button[2]==1)
{
LoadNewMap(editlevel);
//editswitch=0;
loadcview(0);

}
zlPush();zlTranslate(-60000,10000,0);zlScale(6000,10000,10000);
l_text=sprintf(s_text,"<SAVE MAP>");zlRenderText();zlPop();
if (editmenupos==15) if (button[2]==1)
{
savemapdisc(editlevel);
//editswitch=0;
}

zlPush();zlTranslate(-60000,00000,0);zlScale(6000,10000,10000);
l_text=sprintf(s_text,"<TEST MAP>");zlRenderText();zlPop();
if (editmenupos==16) if (button[2]==1)
{
level=editlevel;
lastlevel=255;
gamemode=ZGM_NONE;
newgamemode=ZGM_GAMEPLAY;
playmode=mpheader[0];
}
zlPush();zlTranslate(-60000,-10000,0);zlScale(6000,10000,10000);
l_text=sprintf(s_text,"<START NORMAL GAME>");zlRenderText();zlPop();
if (editmenupos==17) if (button[2]==1)
if (gameswitchdelay==0)
{
playmode=ZPM_MOVIE;
LoadNewMap(0);
}
zlPush();zlTranslate(-60000,-20000,0);zlScale(6000,10000,10000);
l_text=sprintf(s_text,"NAR0 %i NAR3 %i",mpheader[16],mpheader[17]);zlRenderText();zlPop();
if (editmenupos==18)
{
if (button[2]==1 | button[2]>64) mpheader[16]++;
if (button[0]==1 | button[0]>64) mpheader[16]--;

if (button[3]==1 | button[3]>64) mpheader[17]++;
if (button[1]==1 | button[1]>64) mpheader[17]--;
}


zlPush();zlTranslate(-60000,-30000,0);zlScale(6000,10000,10000);
l_text=sprintf(s_text,"SPAWN %i %i %i %i",mpheader[4],mpheader[5],mpheader[6],mpheader[7]);zlRenderText();zlPop();
if (editmenupos==19) if (button[2]==1)
{
mpheader[4]=camera[0]/65536;
mpheader[5]=camera[2]/65536;
mpheader[6]=camera[1]/65536;
mpheader[7]=camera[4]/16;
}

}
editmenuposw+=axis[1];

if (editmenuposw<0) editmenuposw=0;
if (editmenuposw>20480) editmenuposw=20480;

editmenupos=editmenuposw/1024;


}



void proceditmode(void)
{
switch (editswitch)
{
case 0://fly
zeditcontrol();
zeditrender();
if (button[4]) camera[5]-=5;
if (button[5]) camera[5]+=5;

if (button[8]==1) editswitch=1;
if (button[9]==1) editswitch=2;
break;
case 1:// menu
zeditmenu();
if (button[8]==1) editswitch=0;
if (button[9]==1) editswitch=0;
break;
case 2:// painter
zeditpaint();
if (button[9]==1) editswitch=0;
if (button[8]==1) editswitch=0;
break;

}
curx=camera[0]-2*vcamera[2][0];
cury=camera[2]-2*vcamera[2][2];
curz=camera[1]-2*vcamera[2][1];

curx=curx>>16;
cury=cury>>16;
curz=curz>>16;

if (curx<0) curx=0;
if (cury<0) cury=0;
if (curz<0) curz=0;
if (curx>=mpheader[8]) curx=mpheader[8]-1;
if (cury>=mpheader[8]) cury=mpheader[8]-1;
if (curz>=mpheader[9]) curz=mpheader[9]-1;

}
