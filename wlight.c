#include "vars.h"
#include "zlmath.h"

#define FPML(x,y) ((((x)>>7)*((y)>>7))>>2)
#define FPDV(x,y)	((((x)<<6)/((y)>>6))<<4)
u8 isinlight(s32 x,s32 y,s32 z)
{
u8 light=0,block=0,steps=0;
s32 xx,yy,zz;

xx=x;
yy=y;
zz=z;

while ((light==0)&(block==0)&(steps<150))
{
steps++;
xx+=lightgv[0];
yy+=lightgv[1];
zz+=lightgv[2];

if (xx<0) light=1;
if (yy<0) light=1;
if (zz<0) light=1;
if (xx>rmapmaxh) light=1;
if (zz>rmapmaxh) light=1;
if (yy>rmapmaxy) light=1;


if (light==0)
if (mp[xx/65536][zz/65536][yy/65536][0]>0) block=1;
}


return light;
}

s32 lcubew=21,lcubeh=19;

void newlight(signed long x,signed long y,signed long z, unsigned long lightdata)
{
u8 r,g,b,lsize;
s32 ix,iy,iz,cx0,cy0,cz0,cx1,cy1,cz1,xx,yy,zz,ccx,ccy,ccz;

if (thisframenice)
{
//parsing
r=lightdata & 255;
lightdata=lightdata>>8;
g=lightdata & 255;
lightdata=lightdata>>8;
b=lightdata & 255;
lightdata=lightdata>>8;
lsize=lightdata & 255;
lightdata=lightdata>>8;

xx=x>>16;yy=y>>16;zz=z>>16;


cx0=xx-lsize;cx1=xx+lsize+1;

cy0=yy-lsize;cy1=yy+lsize+1;

cz0=zz-lsize;cz1=zz+lsize+1;

if (cx0<0) cx0=0;
if (cy0<0) cy0=0;
if (cz0<0) cz0=0;
if (cx1>mpheader[8]) cx1=mpheader[8];
if (cy1>mpheader[8]) cy1=mpheader[8];
if (cz1>mpheader[9]) cz1=mpheader[9];

for (ix=cx0;ix<cx1;ix++)
for (iy=cy0;iy<cy1;iy++)
for (iz=cz0;iz<cz1;iz++)
{
mcube[ix][iy][iz][0]+=r>>2;
mcube[ix][iy][iz][1]+=g>>2;
mcube[ix][iy][iz][2]+=b>>2;
}

//flare
s32 rg=-(FPML(x-camera[0],vcamera[2][0])+FPML(z-camera[1],vcamera[2][1])+FPML(y-camera[2],vcamera[2][2]));
s32 rx,ry,dist0,dist;

if (rg>0)
if (rg<lflare[1])
{
rx=(FPML(x-camera[0],vcamera[0][0])+FPML(z-camera[1],vcamera[0][1])+FPML(y-camera[2],vcamera[0][2]));
ry=-(FPML(x-camera[0],vcamera[1][0])+FPML(z-camera[1],vcamera[1][1])+FPML(y-camera[2],vcamera[1][2]));
dist0=6556;
rx=FPDV(FPML(rx,65536+6553),(rg+6553));
ry=FPDV(FPML(ry,65536+6553),(rg+6553));

if (rx>-65536)
if (ry>-65536)
if (rx<65536)
if (ry<65536)
{
i_probe[0]=x;
i_probe[1]=y;
i_probe[2]=z;
i_probe[3]=camera[0];
i_probe[4]=camera[2];
i_probe[5]=camera[1];
if (i_probe_act())
{
lflare[0]=255;
lflare[1]=rg;//far
lflare[2]=rx;
lflare[3]=ry;
lflare[4]=r;
lflare[5]=g;
lflare[6]=b;
}
}
}
//flare end
}
}
void clearlightcube(void)
{
u8 x,y,z;
s32 ix,iy,iz,cx0,cy0,cz0,cx1,cy1,cz1,xx,yy,zz,ccx,ccy,ccz;

if (thisframenice)
{

xx=camera[0]>>16;yy=camera[2]>>16;zz=camera[1]>>16;

cx0=xx-10;cx1=xx+11;
cy0=yy-10;cy1=yy+11;
cz0=zz-9;cz1=zz+10;


if (cx0<0) cx0=0;
if (cy0<0) cy0=0;
if (cz0<0) cz0=0;
if (cx1>mpheader[8]) cx1=mpheader[8];
if (cy1>mpheader[8]) cy1=mpheader[8];
if (cz1>mpheader[9]) cz1=mpheader[9];


for (x=cx0;x<cx1;x++)
for (y=cy0;y<cy1;y++)
for (z=cz0;z<cz1;z++)
{
mcube[x][y][z][0]=(mcube[x][y][z][0]*7)>>3;
mcube[x][y][z][1]=(mcube[x][y][z][1]*7)>>3;
mcube[x][y][z][2]=(mcube[x][y][z][2]*7)>>3;
}

lflare[0]=0;//black
lflare[1]=65536*18;//and very far
}
}

void lcuberead(signed long x,signed long y,signed long z)
{
s32 cz1,xx,yy,zz;

lcuber[0]=0;
lcuber[1]=0;
lcuber[2]=0;

xx=(x>>16);
yy=(y>>16);
zz=(z>>16);

if (xx>=0)
if (yy>=0)
if (zz>=0)
if (xx<mpheader[8]-1)
if (yy<mpheader[8]-1)
if (zz<mpheader[9]-1)
{
lcuber[0]=mcube[xx][yy][zz][0];
lcuber[1]=mcube[xx][yy][zz][1];
lcuber[2]=mcube[xx][yy][zz][2];
}




}
