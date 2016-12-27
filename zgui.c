#include "vars.h"
#include "render.h"
#include "zlmath.h"


void procnoise(void)
{
s32 x,y,s,i;

for (i=0;i<4;i++)
tension[4+i]=tension[i]+(tension[4+i]-tension[i])*70/72;

if (thisframenice)
if (tension[7]>0)
{
x=zlrand()*256;
y=zlrand()*256;
s=3;
zlBindTexture(127);
zlBlend(1);
zlBeginQuads();
zlColor4x(tension[4],tension[5],tension[6],tension[7]);
zlTexCoord2x(x,y);zlVertex3x(-65536,65536,0);
zlTexCoord2x(65536*s+x,y);zlVertex3x(65536,65536,0);
zlTexCoord2x(65536*s+x,65536*s+y);zlVertex3x(65536,-65536,0);
zlTexCoord2x(x,65536*s+y);zlVertex3x(-65536,-65536,0);
zlEndQuads();
zlBlend(0);
}
}

s32 guialpha=0,guialarmed;

void aaagui(void)
{
u8 k;
s32 t,sx,sy,l,x,y;

guialarmed=0;

if (mob[mobcontrol][39]>0) guialarmed=1;
if (mob[mobcontrol][40]>0) guialarmed=1;
for (k=0;k<64;k++)
if (k!=mobcontrol)
if (mob[k][0]>0)
if (mob[k][30]!=AI_PEACE) guialarmed=1;

if (guialarmed) {if (guialpha<31) guialpha++;}else if (guialpha>0) guialpha--;

if (firstperson)
if (thisframenice)
{
zlColor4x(255,255,255,255);
zlBindTexture(128);
zlBeginQuads();
zlTexCoord2x(0,0);zlVertex3x(-65536,65536,0);
zlTexCoord2x(65536,0);zlVertex3x(65536,65536,0);
zlTexCoord2x(65536,65536);zlVertex3x(65536,-65536,0);
zlTexCoord2x(0,65536);zlVertex3x(-65536,-65536,0);
zlEndQuads();
}

if (checkpointnotify>0)
{
checkpointnotify--;

if (thisframenice)
{
zlColor4x(255,255,255,255);
zlPush();zlTranslate(-53000,-14000,0);
l_text=sprintf(s_text,"THIS IS [CHECKPOINT]");
zlScale(5000,14000,10000);
zlRenderText();zlPop();
}
}


if (guialpha>0)
if (thisframenice)
{

x=-52000;
y=52000;
l=16000+guialpha*100;
if (guialpha<31) zlBlend(1);
for (k=0;k<3;k++)
{
if (k>2-mob[mobcontrol][42] | mob[mobcontrol][0]<=0) t=0; else t=32768;

sx=8000;
if (k==2-mob[mobcontrol][42])
{
sx=9000+f_sin[(count*20)&4095]/30;
}
sy=sx*4/3;

zlColor4x(255,255,255,guialpha*8);
zlBindTexture(26);
zlBeginQuads();
zlTexCoord2x(t+0,0);zlVertex3x(x-sx,y+sy,0);
zlTexCoord2x(t+32768,0);zlVertex3x(x+sx,y+sy,0);
zlTexCoord2x(t+32768,65536);zlVertex3x(x+sx,y-sy,0);
zlTexCoord2x(t+0,65536);zlVertex3x(x-sx,y-sy,0);
zlEndQuads();
x+=l;
}
if (guialpha<31) zlBlend(0);

}
}
s32 flarer,flareg,flareb,flarea,flarex,flarey;
void lensflare(void)
{
s32 x,y,sx,sy,t,x0,y0;
if (lflare[0]>0)
{
/*
flarea=lflare[0]+(flarea-lflare[0])/4;
flarer=lflare[4]+(flarer-lflare[4])/4;
flareg=lflare[5]+(flareg-lflare[5])/4;
flareb=lflare[6]+(flareb-lflare[6])/4;

flarex=lflare[2]+(flarex-lflare[2])/2;
flarey=lflare[3]+(flarey-lflare[3])/2;

*/
flarea=lflare[0];
flarer=lflare[4];
flareg=lflare[5];
flareb=lflare[6];

flarex=lflare[2];
flarey=lflare[3];


x0=flarex;
y0=flarey;


zlBlend(1);
zlBindTexture(28);
zlBeginQuads();

x=x0;y=y0;
sx=35000+f_sin[count*10&4095]/10;sy=(sx/3)*4;
t=0;

zlColor4x(flarer,flareg,flareb,flarea/3);


zlTexCoord2x(t+0,0);zlVertex3x(x-sx,y+sy,0);
zlTexCoord2x(t+32768,0);zlVertex3x(x+sx,y+sy,0);
zlTexCoord2x(t+32768,65536);zlVertex3x(x+sx,y-sy,0);
zlTexCoord2x(t+0,65536);zlVertex3x(x-sx,y-sy,0);

t=32768;

x=x0/2;y=y0/2;
sx=10000;sy=12000;

zlColor4x(flarer,flareg,flareb,flarea/5);


zlTexCoord2x(t+0,0);zlVertex3x(x-sx,y+sy,0);
zlTexCoord2x(t+32768,0);zlVertex3x(x+sx,y+sy,0);
zlTexCoord2x(t+32768,65536);zlVertex3x(x+sx,y-sy,0);
zlTexCoord2x(t+0,65536);zlVertex3x(x-sx,y-sy,0);

x=-x0/2;y=-y0/2;
sx=15000;sy=20000;

zlColor4x(flarer,flareg,flareb,flarea/4);


zlTexCoord2x(t+0,0);zlVertex3x(x-sx,y+sy,0);
zlTexCoord2x(t+32768,0);zlVertex3x(x+sx,y+sy,0);
zlTexCoord2x(t+32768,65536);zlVertex3x(x+sx,y-sy,0);
zlTexCoord2x(t+0,65536);zlVertex3x(x-sx,y-sy,0);

x=-x0/4;y=-y0/4;
sx=4000;sy=6000;

zlColor4x(flarer,flareg,flareb,flarea/4);


zlTexCoord2x(t+0,0);zlVertex3x(x-sx,y+sy,0);
zlTexCoord2x(t+32768,0);zlVertex3x(x+sx,y+sy,0);
zlTexCoord2x(t+32768,65536);zlVertex3x(x+sx,y-sy,0);
zlTexCoord2x(t+0,65536);zlVertex3x(x-sx,y-sy,0);

x=-x0*4/3;y=-y0*4/3;
sx=45000;sy=60000;

zlColor4x(flarer,flareg,flareb,flarea/6);


zlTexCoord2x(t+0,0);zlVertex3x(x-sx,y+sy,0);
zlTexCoord2x(t+32768,0);zlVertex3x(x+sx,y+sy,0);
zlTexCoord2x(t+32768,65536);zlVertex3x(x+sx,y-sy,0);
zlTexCoord2x(t+0,65536);zlVertex3x(x-sx,y-sy,0);

zlEndQuads();
zlBlend(0);
}
}
s32 exitheight=128;
void showexitdialog(void)
{
s32 x,y,s;
exitheight+=((15000-exitheight)>>5);

if (thisframenice)
{
x=zlrand()*256;
y=zlrand()*256;
s=2;
zlBindTexture(127);
zlBeginQuads();
zlColor4x(64,64,64,255);
zlTexCoord2x(x,y);zlVertex3x(-65536,exitheight,0);
zlTexCoord2x(65536*s+x,y);zlVertex3x(65536,exitheight,0);
zlTexCoord2x(65536*s+x,65536*s+y);zlVertex3x(65536,-exitheight,0);
zlTexCoord2x(x,65536*s+y);zlVertex3x(-65536,-exitheight,0);
zlEndQuads();

zlColor4x(255,255,255,255);
zlPush();zlTranslate(-53000,2000,0);
l_text=sprintf(s_text,"PRESS [Y] TO EXIT GAME");
zlScale(5000,9000,10000);
zlRenderText();zlPop();
if (count/20%2==0)
{
zlPush();zlTranslate(-58000,-7000,0);
l_text=sprintf(s_text,"YOU WILL LOSE EVERYTHING");
zlScale(5000,9000,10000);
zlRenderText();zlPop();
}
}
}

void autismgui(void)
{
s32 z;

z=0;
if (autismdelay>400) z=(autismdelay-400)*55;
if (autismdelay<128) z=-(128-autismdelay)*155;

if (autismdelay>0) autismdelay-=5;


if (thisframenice)
{

zlPush();
zlBindTexture(terrtexx[1+autismstuff][1]);
zlTranslate(45000-z,-52000+z,0);
zlScale(30000+z/2,30000+z/2,10000);
zlBeginQuads();
zlColor4x(255,255,255,255);
zlTexCoord2x(0,0);zlVertex3x(-32768,32768,0);
zlTexCoord2x(65536,0);zlVertex3x(32768,32768,0);
zlTexCoord2x(65536,65536);zlVertex3x(32768,-32768,0);
zlTexCoord2x(0,65536);zlVertex3x(-32768,-32768,0);

zlColor4x(205,205,205,205);
zlTexCoord2x(0,0);zlVertex3x(-45536,45536,0);
zlTexCoord2x(65536,0);zlVertex3x(-32768,32768,0);
zlTexCoord2x(65536,65536);zlVertex3x(-32768,-32768,0);
zlTexCoord2x(0,65536);zlVertex3x(-45536,0,0);

zlBindTexture(terrtexx[1+autismstuff][0]);
zlColor4x(225,225,225,225);
zlTexCoord2x(0,0);zlVertex3x(-32768,32768,0);
zlTexCoord2x(65536,0);zlVertex3x(32768,32768,0);
zlTexCoord2x(65536,65536);zlVertex3x(6768,45768,0);
zlTexCoord2x(0,65536);zlVertex3x(-45768,45768,0);

zlEndQuads();
zlPop();
}
}

void procendlevel(void)
{
s32 i;
if (endlevel<255)
{
if (ltime[0]==0 & ltime[1]==0)
{
ltime[0]=(currenttick-levelstarttick)/60000;
ltime[1]=((currenttick-levelstarttick)/1000)%60;

if (level>=2 & level<10)
{
i=level-2;
if (ltime[0]*60+ltime[1]<configdata[16+i*2]*60+configdata[16+i*2+1])
{
configdata[16+i*2]=ltime[0];
configdata[16+i*2+1]=ltime[1];
if (i<8)
if (configdata[16+(i+1)*2]==199) configdata[16+(i+1)*2]=99;


}
}
}


zlBindTexture(64);
zlBlend(1);
zlBeginQuads();
zlColor4x(0,0,0,255-endlevel);
zlTexCoord2x(0,0);zlVertex3x(-65536,65536,0);
zlTexCoord2x(65536,0);zlVertex3x(65536,65536,0);
zlTexCoord2x(65536,65536);zlVertex3x(65536,-65536,0);
zlTexCoord2x(0,65536);zlVertex3x(-65536,-65536,0);
zlEndQuads();
zlBlend(0);

if (playmode==ZPM_AAA)
{
zlColor4x(255,255,255,255);
zlPush();zlTranslate(-38000,20000,0);
l_text=sprintf(s_text,"TIME ATTACK");
zlScale(5000,9000,10000);
zlRenderText();zlPop();
zlColor4x(255,255,128,255);
zlPush();zlTranslate(-38000,00,0);
l_text=sprintf(s_text,"%i%i%iM%i%iS",ltime[0]/100,ltime[0]/10%10,ltime[0]%10, ltime[1]/10,ltime[1]%10);
zlScale(5000,9000,10000);
zlRenderText();zlPop();
}

}

if (narration==0 | playmode==ZPM_MOVIE)
if (endlevel>32)
{
endlevel--;
if (endlevel==32)
{//reallyend;
if (mpheader[22]==0) newgamemode=ZGM_MENU;
else
if (mpheader[22]==1)zcoreenabled=0;
else LoadNewMap(mpheader[22]);
}
}
}

void procgui(void)
{
if (gameswitchdelay==0)
if (thisframenice)
lensflare();

if (loserwantexit) showexitdialog(); else exitheight=65536;
if (mobcontrol<64)
switch (playmode)
{
case ZPM_AAA:aaagui();break;
case ZPM_AUTISM:autismgui();break;

}
if (endlevel>0) procendlevel();
}

