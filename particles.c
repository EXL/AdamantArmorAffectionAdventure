#include "vars.h"
#include "zlmath.h"
#include "render.h"



#define FPML(x,y) ((((x)>>7)*((y)>>7))>>2)

void genpartdir(unsigned char index)
{
s32 a0,a1,sp;

a0=zlrand()*16;
a1=zlrand()*16;

sp=6+(zlrand() && 3);

pr[index][7]=f_cos[a0]>>sp;
pr[index][8]=f_cos[a1]>>sp;
pr[index][9]=f_sin[a0]>>sp;

if (pr[index][15]==1) pr[index][8]=0;


}


void visparticles(void)
{
u16 i,k,block;
s32 x,y,z;
s32 vv[4][3];
vv[0][0]=-vcamera[0][0]-vcamera[1][0];
vv[0][1]=-vcamera[0][1]-vcamera[1][1];
vv[0][2]=-vcamera[0][2]-vcamera[1][2];

vv[1][0]=vcamera[0][0]-vcamera[1][0];
vv[1][1]=vcamera[0][1]-vcamera[1][1];
vv[1][2]=vcamera[0][2]-vcamera[1][2];

vv[2][0]=vcamera[0][0]+vcamera[1][0];
vv[2][1]=vcamera[0][1]+vcamera[1][1];
vv[2][2]=vcamera[0][2]+vcamera[1][2];

vv[3][0]=-vcamera[0][0]+vcamera[1][0];
vv[3][1]=-vcamera[0][1]+vcamera[1][1];
vv[3][2]=-vcamera[0][2]+vcamera[1][2];
for (i=0;i<4;i++)
for (k=0;k<3;k++)
vv[i][k]=vv[i][k]>>3;

zlBeginQuads();
if (playmode==ZPM_ZVERYLE) zlBindTexture(180); else zlBindTexture(3);
for (i=0;i<128;i++)
if (pr[i][0]>0)
{
if (thisframenice)
switch (pr[i][15])
{
case 0:
zlColor4x(pr[i][1],pr[i][2],pr[i][3],255);

zlTexCoord2x(    0,    0);zlVertex3x(pr[i][4]+vv[0][0],pr[i][5]+vv[0][1],pr[i][6]+vv[0][2]);
zlTexCoord2x(65536,    0);zlVertex3x(pr[i][4]+vv[1][0],pr[i][5]+vv[1][1],pr[i][6]+vv[1][2]);
zlTexCoord2x(65536,65536);zlVertex3x(pr[i][4]+vv[2][0],pr[i][5]+vv[2][1],pr[i][6]+vv[2][2]);
zlTexCoord2x(    0,65536);zlVertex3x(pr[i][4]+vv[3][0],pr[i][5]+vv[3][1],pr[i][6]+vv[3][2]);

break;
case 1:
newblendsprite(1,(f_sin[(pr[i][0]*4)])/266,pr[i][4],pr[i][5],pr[i][6]);
break;
}

pr[i][0]--;
if (-(FPML(pr[i][4]-camera[0],vcamera[2][0])+FPML(pr[i][5]-camera[1],vcamera[2][1])+FPML(pr[i][6]-camera[2],vcamera[2][2]))<0) pr[i][0]=0;

x=pr[i][4]+6*pr[i][7];
y=pr[i][6]+6*pr[i][9];
z=pr[i][5]+6*pr[i][8];
block=0;
x=x>>16;
y=y>>16;
z=z>>16;

if (x<0) block=1;else
if (y<0) block=1;else
if (z<0) block=1;else
if (x>=mpheader[8]) block=1;else
if (y>=mpheader[8]) block=1;else
if (z>=mpheader[9]) block=1;else
if (mp[x][y][z][0]>0) block=1;

if (block==0)
{
pr[i][4]+=pr[i][7];
pr[i][5]+=pr[i][8];
pr[i][6]+=pr[i][9];
}
if (pr[i][0]% 128==127) genpartdir(i);

}
zlEndQuads();
}

u8 nepa=0;
void newparticle(void)
{
u8 i;
u8 k;
i=0;
while ((pr[i][0]>0)&&(i<128)) {i++;}
if (i==128) {i=(nepa);nepa=(nepa+1)%128;}

for (k=0;k<16;k++)
pr[i][k]=pr[128][k];
}
