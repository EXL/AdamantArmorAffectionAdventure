#include "vars.h"
#include "render.h"
#include "zlmath.h"

void startnaration(unsigned char index)
{
narration=0;wantnarration=0;narrationlength=0;
if (index>0)
{
bgm=index+50;
narration=index;

startnarationtick=tickcount;

}
}



#define SUBTITLE(x,y,z) if (narationticks>x & narationticks<=y) l_text=sprintf(s_text,z);else
#define TIMETRAP(x,y) if (narationticks>x & narationticks<=y)

void creditss(s32 x,s32 y,u8 iii)
{
s32 a,l;
if (narationticks>x & narationticks<=y)
{
l=65536+((f_sin[narationticks&4095])>>6);
a=((narationticks-x)*2048)/(y-x);
a=f_sin[a& 2047]/256;
if (a>255) a=255;
zlPush();
zlBlend(1);
zlBindTexture(iii);
zlColor4x(255,255,255,a);
zlRenderQuad();
zlScale(l,l,l);
zlColor4x(255,255,255,a/2);
zlRenderQuad();
zlScale(l,l,l);
zlColor4x(255,255,255,a/3);

zlRenderQuad();
zlBlend(0);
zlPop();
}

}
void introtext(u8 i)
{
zlPush();
zlBindTexture(i);
zlTranslate(1500,-1500,0);
zlColor4x(0,0,0,255);
zlRenderQuad();
zlTranslate(-1500,1500,0);
zlColor4x(255,255,255,255);
zlRenderQuad();
zlScale(70000,70000,100);
zlTranslate(f_cos[count*14&4095]>>4,f_sin[count*17&4095]>>4,0);
zlColor4x(0,255,255,64);

zlBlend(1);
zlRenderQuad();
zlBlend(0);
zlPop();
}

void narrationsubtitles(void)
{
s32 i,k,l,sc,r,g,b,a;

l_text=0;
switch (narration)
{
case 1:
SUBTITLE(3000,5000,"THE MISSION SIMULATION")
SUBTITLE(5000,6500,"PROGRAM IS ONLINE")
SUBTITLE(6500,9000,"FOR YOUR COMFORT")
if (narationticks>12000) narration=0;
break;
case 2:
SUBTITLE(100,1800,"WELCOME TO THE SIMULATION")
SUBTITLE(1800,2600,"PROGRAM WHERE YOUR")
SUBTITLE(2600,5000,"GREAT JOURNEY BEGINS")
SUBTITLE(5500,6800,"I AM ARTIFICAL")
SUBTITLE(6800,7800,"INTELIGENCE THAT WILL")
SUBTITLE(7800,8600,"PROVIDE YOUR")
SUBTITLE(8600,10000,"TUTORIAL ENVIROMENT")
SUBTITLE(10700,11800,"REGULAR VISITING")
SUBTITLE(11800,12700,"TUTORIAL HELPS")
SUBTITLE(12700,14200,"IMPROVE YOUR TOTAL")
SUBTITLE(14200,15500,"MISSION PERFOMANCE")

SUBTITLE(16300,17400,"YOU WILL LEARN NOW")
SUBTITLE(17400,18800,"THE BASICS CONTROLS")
SUBTITLE(18800,20000,"OF MANIPULATING YOUR")
SUBTITLE(20000,21400,"CHARACTER ON MISSIONS")

SUBTITLE(21600,22600,"TRY MOVING YOUR")
SUBTITLE(22600,23700,"CHARACTER IN SPACE")
SUBTITLE(23700,24800,"USING STANDART")
SUBTITLE(24800,26000,"CONTROL METHOD")

SUBTITLE(29800,30600,"LOOK AROUND")
SUBTITLE(30600,32000,"USING [TOUCHSCREEN]")

SUBTITLE(35300,36600,"THE [RIGHT TRIGGER]")
SUBTITLE(36600,37600,"ALLOWS YOU TO LOOK FROM")
SUBTITLE(37600,38700,"FIRST PERSON")
SUBTITLE(38700,39400,"PERSPECTIVE")

SUBTITLE(42000,43000,"YOU CAN JUMP WITH")
SUBTITLE(43000,44000,"[X] BUTTON")

SUBTITLE(46000,48300,"BE CAREFUL WHILE JUMP")
SUBTITLE(48500,49400,"TAKE YOUR TIME")
SUBTITLE(49400,50400,"EVALUATING YOUR")
SUBTITLE(50400,51000,"ENVIROMENT")
SUBTITLE(51000,52300,"FROM HELM CAMERA")

SUBTITLE(53600,54900,"TO SWING YOUR BLADE")
SUBTITLE(55000,56500,"PRESS [B] BUTTON")

SUBTITLE(58900,60300,"LEFT TRIGGER IS USED")
SUBTITLE(60300,62000,"TO MANUAL AIM YOUR GUN")

SUBTITLE(65000,66400,"[Y] BUTTON IS USED TO")
SUBTITLE(66400,68000,"CALL FOR SOME ATTENTION")

SUBTITLE(70300,71500,"YOUR TRAINING OBJECTIVE")
SUBTITLE(71500,73000,"IS TO REACH THE NEXT")
SUBTITLE(73000,74500,"SIMULATION CHECKPOINT")


if (narationticks>77000) narration=0;
break;
case 3:
SUBTITLE(5500,7000,"USE YOUR FLASHLIGHT")
SUBTITLE(7000,7700,"TO LIGHT UP")
SUBTITLE(7000,8600,"THE DARK CORNERS")

SUBTITLE(11200,12300,"BUT SHADOWS COULD BE")
SUBTITLE(12300,13500,"A YOUR FRIEND TOO")

SUBTITLE(17200,19000,"TRY TO AVOID VIOLENCE")

SUBTITLE(26000,27500,"DO NOT FORGET TO PICK UP")
SUBTITLE(27500,29000,"CAMPAIGN GAME DISC")

SUBTITLE(36200,37800,"THERE ALSO A SECRET DISC")
SUBTITLE(37800,39300,"COULD BE HIDDEN SOMEWHERE")
SUBTITLE(39300,40300,"ON THAT LEVEL")

if (narationticks>45000) narration=0;
break;
case 4:
SUBTITLE(1000,3000,"TUTORIAL STAGE IS OVER")
if (narationticks>4000) narration=0;
break;
case 5: //intro
narrationlength=135000;
/*
TIMETRAP(0,8192)
{
zlPush();
TIMETRAP(0,4096) i=146; else i=140;

k=f_cos[narationticks&4095]>>5;
l=f_sin[narationticks&4095]>>5;

r=f_sin[(narationticks/2)&2047]>>8;
g=f_sin[(narationticks/2)&2047]>>8;
b=f_sin[(narationticks/2)&2047]>>8;

a=f_sin[(narationticks/3)&2047]>>8;

if (r>255) r=255;
if (g>255) g=255;
if (b>255) b=255;
if (a>255) a=255;


zlColor4x(r,g,b,255);
zlRenderScreen(i);
zlBlend(1);
sc=66000+((f_sin[narationticks&2047])>>6);
zlTranslate(k,l,0);
zlScale(sc,sc,sc);
zlColor4x(r,g,b,a/2);
zlRenderScreen(i);
zlTranslate(k,l,0);
zlScale(sc,sc,sc);
zlColor4x(r,g,b,a/4);
zlRenderScreen(i);
zlBlend(0);

zlPop();
}
else
TIMETRAP(8192,10216)
{
zlColor4x(0,0,0,255-(narationticks-8192)/8);
zlBlend(1);
zlRenderScreen(140);
zlBlend(0);
}
else
*/
TIMETRAP(82500,135000)
{
zlPush();
zlTranslate(0,16000,0);
zlScale(55000,40000,0);
zlColor4x(255,255,255,200);

zlBindTexture(7);
zlBlend(1);
zlRenderQuad();
zlColor4x(255,255,255,64);
zlScale(70000,70000,0);
zlRenderQuad();

zlBlend(0);
zlPop();
}

TIMETRAP(8000,23000)
{
introtext(152);
}
TIMETRAP(24000,32000)
{
introtext(153);
}
TIMETRAP(32000,45000)
{
introtext(154);
}
TIMETRAP(45000,52000)
{
introtext(155);
}
TIMETRAP(56000,71000)
{
introtext(156);
}
TIMETRAP(76000,82000)
{
introtext(157);
}


SUBTITLE(1000,2000,"IN THE BEGINNING OF THE")
SUBTITLE(2000,4200,"TWENTY FIRST CENTURY")
SUBTITLE(4200,5250,"THE CIVILIZATION")
SUBTITLE(5250,6500,"WAS IN CHAOS")

SUBTITLE(87500,89300,"THE ARMOR THEY WEAR")
SUBTITLE(89300,91300,"IS MADE OF ADAMANTIUM")


if (narationticks>135000) narration=0;
break;//intro end
case 6: //credits
narrationlength=65000;
k=4700;
for (i=0;i<=13;i++)
creditss(1000+i*k,1000+(i+1)*k,210+i);

if (narationticks>65000) narration=0;
break;
case 7: //endgame
narrationlength=30000;
creditss(5000,30000,224);

if (narationticks>30000) narration=0;
break;
case 8: //cheats
narrationlength=60000;
creditss(0000,60000,225);
if (narationticks>60000) narration=0;
break;


case 10://forbiden temple intro[14]
narrationlength=65000;
//SUBTITLE(1000,3000,"TUTORIAL STAGE IS OVER")
if (narationticks>65000) narration=0;
break;

}

//////////////////
if (l_text>0)
{

zlColor4x(255,255,255,255);
zlPush();zlTranslate(-60000,-54000,0);
zlScale(5000,14000,10000);
zlRenderText();zlPop();

}
}

void procnarration(void)
{
if (narration==0)
if (wantnarration>0) startnaration(wantnarration);

if (narration)
{
narationticks=tickcount-startnarationtick;
narrationsubtitles();
/*
zlColor4x(255,255,255,255);
zlPush();zlTranslate(-60000,24000,0);zlScale(6000,10000,10000);
l_text=sprintf(s_text,"[%i] %i",narration,narationticks);zlRenderText();zlPop();
*/
}

}
