#include "vars.h"
#include "render.h"
#include "zlmath.h"

firesize[8]={25536,55536,65536,55536,45536,35536,25536,15536};

void procsprites(void)
{
u8 i;
s32 t,tx,ty;
for (i=0;i<31;i++)
if (sprite[i][0]>0)
{
if (sprite[i][1]==6)sprite[i][4]+=200;
if (thisframenice)
switch (sprite[i][1])
{
case 0://slash
zlPush();
zlTranslate(sprite[i][2],sprite[i][4],sprite[i][3]);
zlRotatey(-camera[4]);
zlBindTexture(5);
zlColor4x(255,255,255,255);
zlBeginQuads();
zlTexCoord2x(0,0);zlVertex3x(-95536,15536,0);
zlTexCoord2x(65536,0);zlVertex3x(95536,15536,0);
zlTexCoord2x(65536,65536);zlVertex3x(95536,-15536,0);
zlTexCoord2x(0,65536);zlVertex3x(-95536,-15536,0);
zlEndQuads();
zlPop();
break;
case 1://blood
zlPush();
zlTranslate(sprite[i][2],sprite[i][4],sprite[i][3]);
//zlRotatey(-camera[4]);
zlBindTexture(6);
zlColor4x(sprite[i][5],sprite[i][6],sprite[i][7],255);
zlBeginQuads();
zlTexCoord2x(0,0);zlVertex3x(-65536,1536,-65536);
zlTexCoord2x(65536,0);zlVertex3x(65536,1536,-65536);
zlTexCoord2x(65536,65536);zlVertex3x(65536,1536,65536);
zlTexCoord2x(0,65536);zlVertex3x(-65536,1536,65536);
zlEndQuads();
zlPop();
break;
case 2://gunfire
zlPush();
zlTranslate(sprite[i][2],sprite[i][4],sprite[i][3]);
zlRotatey(-camera[4]);
zlBindTexture(25);
zlColor4x(255,255,255,255);
t=2*firesize[7-sprite[i][0]/2];
zlBeginQuads();
zlTexCoord2x(0,0);zlVertex3x(-t,t,0);
zlTexCoord2x(65536,0);zlVertex3x(t,t,0);
zlTexCoord2x(65536,65536);zlVertex3x(t,-t,0);
zlTexCoord2x(0,65536);zlVertex3x(-t,-t,0);
zlEndQuads();
zlPop();
break;
case 3://bullethole-X
zlPush();
zlTranslate(sprite[i][2],sprite[i][4],sprite[i][3]);
zlBindTexture(27);
zlColor4x(sprite[i][0]*4,sprite[i][0]*4,sprite[i][0]*4,255);
t=30000+sprite[i][0]*100;
zlBeginQuads();
zlTexCoord2x(0,0);zlVertex3x(0,t,-t);
zlTexCoord2x(65536,0);zlVertex3x(0,t,t);
zlTexCoord2x(65536,65536);zlVertex3x(0,-t,t);
zlTexCoord2x(0,65536);zlVertex3x(0,-t,-t);
zlEndQuads();
zlPop();
break;
case 4://bullethole-Y
zlPush();
zlTranslate(sprite[i][2],sprite[i][4],sprite[i][3]);
zlBindTexture(27);
zlColor4x(sprite[i][0]*4,sprite[i][0]*4,sprite[i][0]*4,255);
t=30000+sprite[i][0]*100;
zlBeginQuads();
zlTexCoord2x(0,0);zlVertex3x(-t,t,0);
zlTexCoord2x(65536,0);zlVertex3x(t,t,0);
zlTexCoord2x(65536,65536);zlVertex3x(t,-t,0);
zlTexCoord2x(0,65536);zlVertex3x(-t,-t,0);
zlEndQuads();
zlPop();
break;
case 5://bullethole-Z
zlPush();
zlTranslate(sprite[i][2],sprite[i][4],sprite[i][3]);
zlBindTexture(27);
zlColor4x(sprite[i][0]*4,sprite[i][0]*4,sprite[i][0]*4,255);
t=30000+sprite[i][0]*100;
zlBeginQuads();
zlTexCoord2x(0,0);zlVertex3x(-t,0,t);
zlTexCoord2x(65536,0);zlVertex3x(t,0,t);
zlTexCoord2x(65536,65536);zlVertex3x(t,0,-t);
zlTexCoord2x(0,65536);zlVertex3x(-t,0,-t);
zlEndQuads();
zlPop();
break;
case 6://note
tx=0;
ty=0;
if (sprite[i][5]>2) ty=32768;
if (sprite[i][5]&1>0) tx=32768;


zlPush();
zlTranslate(sprite[i][2],sprite[i][4],sprite[i][3]);
zlRotatey(-camera[4]);
zlBindTexture(41);
if (sprite[i][6]==0)zlColor4x(0,255,255,255);
else
if (sprite[i][6]==1)zlColor4x(255,0,255,255);
else
if (sprite[i][6]==2)zlColor4x(0,0,255,255);
else
zlColor4x(255,255,255,255);

t=16000;
zlBeginQuads();
zlTexCoord2x(tx,ty);zlVertex3x(-t,t,0);
zlTexCoord2x(tx+32768,ty);zlVertex3x(t,t,0);
zlTexCoord2x(tx+32768,ty+32768);zlVertex3x(t,-t,0);
zlTexCoord2x(tx,ty+32768);zlVertex3x(-t,-t,0);
zlEndQuads();
zlPop();
break;

}
sprite[i][0]--;
}

}

void spawnnewsprite(void)
{
u8 i,k;
i=0;
while ((sprite[i][0]>0) & (i<32)) i++;
if (i==32) i=zlrand()/8;
for (k=0;k<8;k++) sprite[i][k]=sprite[32][k];
}
