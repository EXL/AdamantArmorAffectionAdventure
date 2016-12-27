#include "vars.h"
#include "render.h"

s32 blenddata[64][8];
u8 blendcount=0;

#define FPML(x,y) ((((x)>>7)*((y)>>7))>>2)

void newblendsprite (unsigned char index,unsigned char alpha, signed long xx, signed long yy, signed long zz)
{
if (blendcount<63)
{

blenddata[blendcount][0]=index;
blenddata[blendcount][1]=alpha;

blenddata[blendcount][2]=xx;
blenddata[blendcount][3]=yy;
blenddata[blendcount][4]=zz;

blenddata[blendcount][5]=-(FPML(xx-camera[0],vcamera[2][0])+FPML(yy-camera[1],vcamera[2][1])+FPML(zz-camera[2],vcamera[2][2]));

blendcount++;
}
}

s32 shw=48000;
u8 blendorder[64];

void drawblendsprites(void)
{
s32 x,y,z;
u8 i,k,l;
s32 vv[4][3];

if (blendcount>0)
{
for (i=0;i<blendcount;i++)
blendorder[i]=i;

if (blendcount>1)
for (i=0;i<blendcount-1;i++)
for (k=0;k<blendcount-1;k++)
if (blenddata[blendorder[k]][5]<blenddata[blendorder[k+1]][5])
{
l=blendorder[k];
blendorder[k]=blendorder[k+1];
blendorder[k+1]=l;
}

zlBlend(1);
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
vv[i][k]=vv[i][k];

for (k=0;k<blendcount;k++)
{
i=blendorder[k];
switch (blenddata[i][0])
{
case 0://shadow
zlColor4x(mpheader[18],mpheader[19],mpheader[20],blenddata[i][1]);
x=blenddata[i][2];
y=blenddata[i][4];
z=blenddata[i][3];

zlBindTexture(4);
zlBeginQuads();
zlTexCoord2x(    0,    0);zlVertex3x(x-shw,    z,y-shw);
zlTexCoord2x(65536,    0);zlVertex3x(x+shw,    z,y-shw);
zlTexCoord2x(65536,65536);zlVertex3x(x+shw,    z,y+shw);
zlTexCoord2x(    0,65536);zlVertex3x(x-shw,    z,y+shw);
zlEndQuads();
break;
case 1://fog
zlColor4x(255,255,255,blenddata[i][1]);
x=blenddata[i][2];
y=blenddata[i][4];
z=blenddata[i][3];
zlBindTexture(42);
zlBeginQuads();
zlTexCoord2x(    0,    0);zlVertex3x(x+vv[0][0],z+vv[0][1],y+vv[0][2]);
zlTexCoord2x(65536,    0);zlVertex3x(x+vv[1][0],z+vv[1][1],y+vv[1][2]);
zlTexCoord2x(65536,65536);zlVertex3x(x+vv[2][0],z+vv[2][1],y+vv[2][2]);
zlTexCoord2x(    0,65536);zlVertex3x(x+vv[3][0],z+vv[3][1],y+vv[3][2]);
zlEndQuads();
break;
}
}
zlBlend(0);
blendcount=0;
}
}
