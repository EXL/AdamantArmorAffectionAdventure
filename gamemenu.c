#include "vars.h"
#include "render.h"
#include "zcsound.h"

s32 mmpos,lmmpos;


char menutext1[9][16]=
{
"TRAINING",
"MISSION",
"AUTISM MODE",
"EXTREME",
"ZOMBIE HORDE",
"ZVERYLE",
"SYSTEM CONFIG",
"EXIT GAME",
"LOCKED"
};

char menutext2[9][32]=
{
"COMBAT SIMULATION",
"THE MAIN CAMPAIGN",
"ENJOY THE PEACE",
"FRAG YOUR ENEMIES",
"SURVIVE THE UNDEAD ATTACK",
"CHALLENGE OF FANTASY GAME",
"SETUP YOUR ENVIROMENT",
"FAIL YOUR DESTINY",
"FIND THIS GAME DISC"
};


void gamemenuback(void)
{
s32 t;

zlFogColor(0,128,255);
zlClrScr();
zlPush();
zlBlend(1);

zlBeginQuads();

t=count*70;
zlBindTexture(9);
zlColor4x(255,0,0,64);
zlTexCoord2x(t+65536,0);
zlVertex3x(-65536,65536,0);
zlTexCoord2x(t+65536,65536);
zlVertex3x(-45536,65536,0);

zlColor4x(0,0,0,64);
zlTexCoord2x(t,65536);
zlVertex3x(-45536,-65536,0);
zlTexCoord2x(t,0);
zlVertex3x(-65536,-65536,0);

t=count*100;
zlBindTexture(9);
zlColor4x(0,255,0,128);
zlTexCoord2x(t,0);
zlVertex3x(-65536,-55536,0);
zlTexCoord2x(t+65536,0);
zlVertex3x(65536,-55536,0);

zlColor4x(0,0,0,255);

zlTexCoord2x(t+65536,65536);
zlVertex3x(65536,-65536,0);
zlTexCoord2x(t,65536);
zlVertex3x(-65536,-65536,0);

t=count*110;
zlBindTexture(9);
zlColor4x(0,0,255,255);
zlTexCoord2x(t,0);
zlVertex3x(-65536,65536,0);
zlTexCoord2x(t+65536,0);
zlVertex3x(65536,65536,0);

zlColor4x(0,255,200,128);

zlTexCoord2x(t+65536,65536);
zlVertex3x(65536,55536,0);
zlTexCoord2x(t,65536);
zlVertex3x(-65536,55536,0);

t=count*60;
zlBindTexture(10);

t=count*50;
zlBindTexture(10);

zlColor4x(0,0,0,0);

zlTexCoord2x(t,65536*2);
zlVertex3x(-20000,65536,0);
zlTexCoord2x(t,0);
zlVertex3x(-20000,-65536,0);

zlColor4x(255,0,0,64);

zlTexCoord2x(t+65536*2,0);
zlVertex3x(65536,-65536,0);
zlTexCoord2x(t+65536*2,65536*2);
zlVertex3x(65536,65536,0);

t=count*40;
zlBindTexture(10);

zlColor4x(255,255,255,0);

zlTexCoord2x(t,65536*2);
zlVertex3x(0,65536,0);
zlTexCoord2x(t,0);
zlVertex3x(0,-65536,0);

zlColor4x(255,255,128,128);

zlTexCoord2x(t+65536*2,0);
zlVertex3x(65536,-65536,0);
zlTexCoord2x(t+65536*2,65536*2);
zlVertex3x(65536,65536,0);

zlEndQuads();
zlBlend(0);
zlPop();

}

u8 mmsel,mmlastsel,mmseldelay;
s32 menutilt=0;
void gamemenufront(void)
{
u8 i;
s32 delta;

menutilt+=((-gsensor[0]-menutilt)>>4);

for (i=0;i<8;i++)
{
zlPush();

if (i==mmsel)
{
zlTranslate(-40000,+mmpos*260-i*30000,0);
zlScale(20000-mmseldelay*1550,20000-mmseldelay*1550,20000);
}
else
{
delta=mmpos-(i*128-32);
if (delta<0) delta=-delta;
zlTranslate(-40000+f_sin[delta]/2,+mmpos*260-i*30000,0);
zlScale(10000,10000,10000);

}
zlScale(49152,65536,65536);
if (i==6) zlRotatez(count*15);

zlBindTexture(16+i);

zlRotatez(menutilt);

zlBeginQuads();
if (configdata[i]) zlColor4x(255,255,255,255);
else zlColor4x(0,0,0,255);

zlTexCoord2x(0,0);zlVertex3x(-65536,65536,0);
zlTexCoord2x(0,65536);zlVertex3x(-65536,-65536,0);
zlTexCoord2x(65536,65536);zlVertex3x(65536,-65536,0);
zlTexCoord2x(65536,0);zlVertex3x(65536,65536,0);

zlEndQuads();

zlPop();

}
zlPush();
zlBindTexture(16+mmsel);

zlTranslate(24000,-20000,0);
zlScale(40000+mmseldelay*10000,40000,40000);
zlScale(49152,65536,65536);
zlRotatez(f_sin[count*10%4096]/1000+menutilt);
zlBlend(1);
if (configdata[mmsel]) zlColor4x(255,255,255,255-mmseldelay*16);
else
zlColor4x(0,0,0,255-mmseldelay*16);

zlBeginQuads();
zlTexCoord2x(100,100);zlVertex3x(-65536,65536,0);
zlTexCoord2x(100,65436);zlVertex3x(-65536,-65536,0);
zlTexCoord2x(65436,65436);zlVertex3x(65536,-65536,0);
zlTexCoord2x(65436,100);zlVertex3x(65536,65536,0);
zlEndQuads();

if (configdata[mmsel])
{
zlColor4x(255,255,255,(255-mmseldelay*16)/2);
zlScale(70000+((f_sin[count*15&4095])>>3),70000+((f_sin[(count*18)&4095])>>3),0);
zlBeginQuads();
zlTexCoord2x(100,100);zlVertex3x(-65536,65536,0);
zlTexCoord2x(100,65436);zlVertex3x(-65536,-65536,0);
zlTexCoord2x(65436,65436);zlVertex3x(65536,-65536,0);
zlTexCoord2x(65436,100);zlVertex3x(65536,65536,0);
zlEndQuads();

zlColor4x(255,255,255,(255-mmseldelay*16)/4);
zlScale(70000+((f_sin[count*12&4095])>>3),70000+((f_sin[(count*13)&4095])>>3),0);
zlBeginQuads();
zlTexCoord2x(100,100);zlVertex3x(-65536,65536,0);
zlTexCoord2x(100,65436);zlVertex3x(-65536,-65536,0);
zlTexCoord2x(65436,65436);zlVertex3x(65536,-65536,0);
zlTexCoord2x(65436,100);zlVertex3x(65536,65536,0);
zlEndQuads();

}
zlBlend(0);
zlPop();

s32 t;

t=f_cos[count*20% 4096]/100;
zlPush();
zlTranslate(30000,45000,0);
zlScale(30000+t,20000+t,10000);
zlColor4x(255,255,255,255);
zlBeginQuads();
zlBindTexture(7);
zlTexCoord2x(0,0);
zlVertex3x(-65536,65536,0);
zlTexCoord2x(65536,0);
zlVertex3x(65536,65536,0);

zlTexCoord2x(65536,65536);
zlVertex3x(65536,-65536,0);
zlTexCoord2x(0,65536);
zlVertex3x(-65536,-65536,0);
zlEndQuads();

zlBlend(1);
zlScale(70000+t,70000+t,10000);
zlColor4x(255,255,255,64);
zlBeginQuads();
zlBindTexture(7);
zlTexCoord2x(0,0);
zlVertex3x(-65536,65536,0);
zlTexCoord2x(65536,0);
zlVertex3x(65536,65536,0);

zlTexCoord2x(65536,65536);
zlVertex3x(65536,-65536,0);
zlTexCoord2x(0,65536);
zlVertex3x(-65536,-65536,0);
zlEndQuads();
zlPop();

zlBeginQuads();
zlColor4x(255,255,255,200);
zlBindTexture(0);
zlTexCoord2x(0,0);
zlVertex3x(-65536,-35536,0);
zlTexCoord2x(65536,0);
zlVertex3x(65536,-35536,0);

zlColor4x(64,64,64,32);

zlTexCoord2x(65536,65536);
zlVertex3x(65536,-65536,0);
zlTexCoord2x(0,65536);
zlVertex3x(-65536,-65536,0);
zlEndQuads();

zlBlend(0);

if (configdata[mmsel])
l_text=sprintf(s_text,"%s",menutext1[mmsel]);
else
l_text=sprintf(s_text,"%s",menutext1[8]);

zlPush();
zlTranslate(-62000-mmseldelay*1000,-55768,0);
zlScale(9000,20000,10000);
zlColor4x(255,255,255,255);
zlRenderText();
zlPop();
if (configdata[mmsel])
l_text=sprintf(s_text,"%s",menutext2[mmsel]);
else
l_text=sprintf(s_text,"%s",menutext2[8]);
zlPush();
zlTranslate(-62000+mmseldelay*2000,-63768,0);
zlScale(5000,12000,10000);
zlColor4x(200,200,200,255);
zlRenderText();
zlPop();

}

u8 cheatcodes[4][8]=
{
{2,2,1,2,4,4,1,1},//unlock all XXAXYYAA
{2,1,2,1,2,1,1,4},//nekoskin XAXAXAAY
{4,4,4,1,1,1,2,4},//researcherskin YYYAAAXY
{1,4,1,2,4,4,2,4}//dev mode AYAXYYXY
};
u8 cheatinput[8]={0,0,0,0,0,0,0,0};

void trycheat(void)
{
s8 i,k,l,cheat[4],ii;
if (button[0]==1 | button[1]==1 | button[3]==1)
{
for (i=0;i<7;i++)
cheatinput[i]=cheatinput[i+1];
if (button[0]==1) cheatinput[7]=1;
else
if (button[1]==1) cheatinput[7]=2;
else
if (button[3]==1) cheatinput[7]=4;
//digestion
for (i=0;i<4;i++) cheat[i]=1;

for (i=0;i<8;i++)
{

for (l=0;l<4;l++)
if (cheatinput[i]!=cheatcodes[l][i]) cheat[l]=0;
}
if (cheat[0]!=0 | cheat[1]!=0 | cheat[2]!=0 |cheat[3]!=0)
{
for (i=0;i<8;i++)
cheatinput[i]=0;
}
if (cheat[0])
{
configdata[1]=1;
configdata[2]=1;
//configdata[3]=0;
//configdata[4]=0;
//configdata[5]=0;
for (ii=0;ii<8;ii++){configdata[16+ii*2]=99;configdata[17+ii*2]=59;}

zcplaysound(36);
}
if (cheat[1])
{
zcplaysound(21);secretskin=1;
}
if (cheat[2])
{
zcplaysound(30);secretskin=6;
}
if (cheat[3])
if (gameswitchdelay==0)
{
zcplaysound(38);
newgamemode=ZGM_GAMEPLAY;
playmode=ZPM_EDIT;
LoadNewMap(255);
}

}
}

void gamemenukey(void)
{
trycheat();

if (button[2]==1 || mousetap)
if (configdata[mmsel]==0)
zcplaysound(2);

else
switch (mmsel)
{
case 0: zcplaysound(1); newgamemode=ZGM_GAMEPLAY;playmode=ZPM_AAA;LoadNewMap(1); break;//Training
case 1: zcplaysound(12); newgamemode=ZGM_SELECTOR;break;//Campaing

case 2: zcplaysound(12); newgamemode=ZGM_GAMEPLAY;playmode=ZPM_AUTISM;LoadNewMap(20); break;//Autism
case 3: zcplaysound(12); newgamemode=ZGM_GAMEPLAY;playmode=ZPM_AAA;LoadNewMap(23); break;//extreme
case 4: zcplaysound(12); newgamemode=ZGM_GAMEPLAY;playmode=ZPM_AAA;LoadNewMap(24); break;//zombie

case 5: zcplaysound(1); newgamemode=ZGM_GAMEPLAY;playmode=ZPM_ZVERYLE;LoadNewMap(25); break;//zveryle


case 6: zcplaysound(1); newgamemode=ZGM_CONFIG; break;

case 7: zcplaysound(23);newgamemode=ZGM_GAMEPLAY;LoadNewMap(10); break;
}

u32 w;
if (mousebutton[0]>1)
mmpos+=(mouseaxis[1]-holdmouseaxis[1])/7;


if ((axis[1]<-10)|(axis[1]>10))
{
mmpos+=axis[1]/30;
}
else
{
w=((mmpos)%128) -64;
if (w>0) mmpos--; else
if (w<0) mmpos++;
}

if (mmpos<0) mmpos=0;
else
if (mmpos>128*7) mmpos=128*7;
mmlastsel=mmsel;
mmsel =(mmpos+64)/128;
if (mmseldelay) mmseldelay--;

if (mmlastsel!=mmsel) {mmseldelay=16;zcplaysound(3);}
}

void gamemenu(void)
{
s32 delta;
bgm=1;
zlPush();
if (gameswitchdelay==0)
gamemenukey();
else
{
delta=gameswitchdelay;
if (delta<0) delta=100+delta;
delta=1000*(delta);
zlScale(65536+delta*3,65536+delta,10000);
zlRotatez(delta/100);
}

gamemenuback();
gamemenufront();

zlPop();
if (gameswitchdelay!=0)zlDrawTransmask(0,0,255);

}
char fstxt[3][8]={"NONE","LOW","HIGH"};

char conftxt[8][32]=
{
"[BACK TO MENU]",
"SOUND VOLUME 000",
"MUSIC VOLUME 000",
"VIBRATION    ON",
"G-SENSOR     ON",
"AIM MODE     LOL",
"NOISE EFFECT OFF",
"[RESET GAME]"
};
s8 confsel=0,axisact=0,newaxisact;

void menuconfigcontrol(void)
{
u8 ii;
if ((button[9]==1) | (button[8]==1)) {zcplaysound(1); newgamemode=ZGM_MENU;}
newaxisact=0;
if (axis[1]>60) newaxisact=2;else
if (axis[1]<-60) newaxisact=1;

if (newaxisact!=axisact)
{
axisact=newaxisact;
if (axisact==1) if (confsel>0) {zcplaysound(3);confsel--;}
if (axisact==2) if (confsel<7) {zcplaysound(3);confsel++;}
}
if (confsel==1)
{
if (axis[0]>10) if (configdata[8]<128) configdata[8]++;
if (axis[0]<-10) if (configdata[8]>0) configdata[8]--;
}
if (confsel==2)
{
if (axis[0]>10) if (configdata[9]<128) configdata[9]++;
if (axis[0]<-10) if (configdata[9]>0) configdata[9]--;
}

if (button[2]==1)
switch (confsel)
{
case 0: zcplaysound(1); newgamemode=ZGM_MENU;break;
case 3: zcplaysound(1); configdata[10]=(configdata[10]+1)&1;break;
case 4: zcplaysound(1); configdata[11]=(configdata[11]+1)&1;break;
case 5: zcplaysound(1); configdata[12]=(configdata[12]+1)%3;break;
case 6: zcplaysound(1); configdata[13]=(configdata[13]+1)&1;break;

case 7:
zcplaysound(1); newgamemode=ZGM_GAMEPLAY;LoadNewMap(0);secretskin=0;
configdata[1]=0;
configdata[2]=0;
configdata[3]=0;
configdata[4]=0;
configdata[5]=0;
for (ii=0;ii<8;ii++)
{configdata[16+ii*2]=199;configdata[17+ii*2]=59;}
configdata[16]=99;
break;
}
sprintf(conftxt[1],"SOUND VOLUME %i%i%i",configdata[8]/100,configdata[8]/10%10,configdata[8]%10);
sprintf(conftxt[2],"MUSIC VOLUME %i%i%i",configdata[9]/100,configdata[9]/10%10,configdata[9]%10);
if (configdata[10]) sprintf(conftxt[3],"VIBRATION  <ON>"); else sprintf(conftxt[3],"VIBRATION  <OFF>");
if (configdata[11]) sprintf(conftxt[4],"G-SENSE    <ON>"); else sprintf(conftxt[4],"G-SENSE    <OFF>");
sprintf(conftxt[5],"TURBO MODE <%s>",fstxt[configdata[12]]);
if (configdata[13]) sprintf(conftxt[6],"FILM GRAIN <ON>"); else sprintf(conftxt[6],"FILM GRAIN <OFF>");


}

void gameconfig(void)
{
s32 tx,ty,delta,i;
bgm=2;

zlFogColor(0,0,0);
zlClrScr();
zlPush();

if (gameswitchdelay==0)
menuconfigcontrol();
else
{
delta=gameswitchdelay;
if (delta<0) delta=100+delta;
delta=1000*(delta);
zlScale(65536+delta*4,65536+delta,10000);
zlRotatez(-delta/80);
}

zlBindTexture(80);
zlColor4x(255,255,255,255);
tx=(count & 65535)*160;
ty=(count & 65535)*40;
zlBeginQuads();
zlTexCoord2x(tx,ty);zlVertex3x(-65536,65536,0);
zlTexCoord2x(tx+65536,ty);zlVertex3x(65536,65536,0);
zlTexCoord2x(tx+65536,ty+65536);zlVertex3x(65536,-65536,0);
zlTexCoord2x(tx,ty+65536);zlVertex3x(-65536,-65536,0);
zlEndQuads();

tx=f_sin[(count*15)&4095];
ty=f_cos[(count*8)&4095];
zlBlend(1);
zlColor4x(255,255,255,64);
zlBeginQuads();
zlTexCoord2x(tx,ty);zlVertex3x(-65536,65536,0);
zlTexCoord2x(tx+65536,ty);zlVertex3x(65536,65536,0);
zlTexCoord2x(tx+65536,ty+65536);zlVertex3x(65536,-65536,0);
zlTexCoord2x(tx,ty+65536);zlVertex3x(-65536,-65536,0);
zlEndQuads();

zlBindTexture(0);
zlBeginQuads();
zlColor4x(0,0,255,128);
zlTexCoord2x(0,65536);zlVertex3x(-65536,65536,0);
zlTexCoord2x(65536,65366);zlVertex3x(65536,65536,0);
zlColor4x(255,255,255,64);
zlTexCoord2x(65536,0);zlVertex3x(65536,45536,0);
zlTexCoord2x(0,0);zlVertex3x(-65536,45536,0);

zlColor4x(255,0,0,128);
zlTexCoord2x(0,65536);zlVertex3x(-65536,-65536,0);
zlTexCoord2x(65536,65366);zlVertex3x(65536,-65536,0);
zlColor4x(255,255,255,64);
zlTexCoord2x(65536,0);zlVertex3x(65536,-45536,0);
zlTexCoord2x(0,0);zlVertex3x(-65536,-45536,0);
zlEndQuads();

zlBlend(0);
zlColor4x(255,255,255,255);

for (i=0;i<8;i++)
{
l_text=sprintf(s_text,"%s",conftxt[i]);

zlPush();
zlTranslate(-62000,45768-15000*i,0);
zlScale(7000,14000,10000);
tx=200+f_sin[(count*60)&4095]/1400;
if (i==confsel) zlColor4x(tx,tx,tx,255);
else zlColor4x(64,64,64,255);
zlRenderText();
zlPop();
}



zlPop();
if (gameswitchdelay!=0)zlDrawTransmask(0,255,0);

}

s32 selectordata=0,selectordata0=0,selsd=0,oldselsd=0;

u8 seltarget[8]={2,3,4,5,14,7,8,9};

char lvlname[8][32]=
{
"SENTINEL RUINS",
"GREENMOSS CAVERN",
"CLIFFHANGER RAGE",
"CANYON OF DOOM",
"FORBIDEN TEMPLE",
"HELLZONE BLAST",
"SURFACE GUARD",
"LAST LABORATORY"
};

void gameselector(void)
{
s32 sc,i;

bgm=11;
zlPush();
if (gameswitchdelay!=0)
{
sc=gameswitchdelay;
if (sc<0) sc=100+sc;
sc=sc*256*3;
zlScale(65536+sc*4,65536+sc,1<<16);
zlRotatez(-sc/80);
}

zlColor4x(255,255,255,255);
zlBindTexture(138);
zlRenderQuad();
zlPush();
zlBlend(1);
sc=65536+1000+f_sin[(count*10)&4095]/100;
zlScale(sc,sc,sc);
zlColor4x(255,255,255,128);
zlRenderQuad();

zlScale(sc,sc,sc);
zlColor4x(255,255,255,64);
zlRenderQuad();

zlBlend(0);
zlPop();

selectordata0+=(selectordata-selectordata0)>>3;
selsd=(selectordata0+128)/378;
if (selsd<0) selsd=0; else if (selsd>7) selsd=7;
if (selsd!=oldselsd) {zcplaysound(3);oldselsd=selsd;}

if (selectordata<-256) selectordata=-256; else
if (selectordata>3000) selectordata=3000;

for (i=0;i<8;i++)
{
zlPush();
zlTranslate(i*90000-10000-selectordata0*235,5000,0);
zlScale(49152,65536,65536);
zlRotatez(consoleturn[1]);
if (i==selsd)sc=50000; else sc=40000;
sc+=f_sin[(800*i+count*6)&4095]/20;
zlScale(sc,sc,sc);
zlColor4x(255,255,255,255);
zlBindTexture(130+i);
zlRenderQuad();

if (i==selsd)
{
zlBlend(1);
sc=66536+f_sin[(count*25)&4095]/20;
zlScale(sc,sc,sc);
zlColor4x(255,255,255,128);
zlRenderQuad();
zlScale(sc,sc,sc);
zlColor4x(255,255,255,64);
zlRenderQuad();

sc=3*65536;
zlScale(sc,sc,sc);
zlColor4x(255,255,255,32);
zlRenderQuad();

zlBlend(0);
}


zlPop();
}
zlBlend(1);
zlPush();
zlColor4x(0,0,0,128);
zlTranslate(-73000-f_sin[(count*17)&4095]/2,-59768,0);
zlScale(12000,24000,10000);
zlRenderText();
zlPop();
zlBlend(0);
zlPop();

zlColor4x(255,255,0,255);
if (configdata[16+selsd*2]/100==0)
{
l_text=sprintf(s_text,"TIME %i%i%i:%i%i",configdata[16+selsd*2]/100,configdata[16+selsd*2]/10%10,configdata[16+selsd*2]%10,configdata[16+selsd*2+1]/10,configdata[16+selsd*2+1]%10);
}
else
l_text=sprintf(s_text,"[DO NOT WANT]");

zlPush();
zlTranslate(-52000,45768,0);
zlScale(6500,14000,10000);
zlRenderText();
zlPop();



zlColor4x(255,255,255,255);
l_text=sprintf(s_text,"%s",lvlname[selsd]);
zlPush();
zlTranslate(-52000,-55768,0);
zlScale(6500,14000,10000);
zlRenderText();
zlPop();
zlBlend(1);
zlPush();
zlColor4x(255,128,64,64);
zlTranslate(-63000+f_sin[(count*7)&4095]/3,-57768,0);
zlScale(9000,19000,10000);
zlRenderText();
zlPop();
zlBlend(0);
zlPop();

if (gameswitchdelay==0)
{
if ((axis[0]<-32) | (axis[0]>32)) selectordata+=axis[0]/8;
else selectordata+=((selsd*378)-selectordata)>>3;

if (button[2]==1 | (button[0]==1))
if (configdata[16+selsd*2]/100==0)
{zcplaysound(1);newgamemode=ZGM_GAMEPLAY;playmode=ZPM_AAA;LoadNewMap(seltarget[selsd]);}
else
{zcplaysound(2);}
if (button[1]==1 | button[1]==3 | button[8]==1 | button[9]==1) {zcplaysound(2);newgamemode=ZGM_MENU;}
}
if (gameswitchdelay!=0)zlDrawTransmask(255,0,0);
}

s32 ccticks,ccstate=0,zerotick=0;
#define TIMETRAP(x,y) if (ccticks>x & ccticks<=y)

void gamelogo(void)
{
s32 r,g,b,a,i,sc,k,l;
bgm=58;
if (ccstate==0 & count>1) {zerotick=tickcount;ccstate=1;}
else
{
ccticks=tickcount-zerotick;
if (ccticks>9000) {newgamemode=ZGM_GAMEPLAY;level=0;playmode=ZPM_AAA;}
TIMETRAP(0,8192)
{
zlPush();
TIMETRAP(0,4096) i=146; else i=140;

k=f_cos[ccticks&4095]>>5;
l=f_sin[ccticks&4095]>>5;

r=f_sin[(ccticks/2)&2047]>>8;
g=f_sin[(ccticks/2)&2047]>>8;
b=f_sin[(ccticks/2)&2047]>>8;

a=f_sin[(ccticks/3)&2047]>>8;

if (r>255) r=255;
if (g>255) g=255;
if (b>255) b=255;
if (a>255) a=255;


zlColor4x(r,g,b,255);
zlRenderScreen(i);
zlBlend(1);
sc=66000+((f_sin[ccticks&2047])>>6);
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
zlColor4x(0,0,0,255-(ccticks-8192)/8);
zlBlend(1);
zlRenderScreen(140);
zlBlend(0);
}
}
}
