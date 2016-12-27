#include "vars.h"
#include "zctables.h"

#define FPML(x,y) ((((x)>>7)*((y)>>7))>>2)
#define FPDV(x,y)	((((x)<<2)/((y)>>4))<<10)

u16 zlseed=0;

unsigned char zlrand(void)
{
zlseed=(zlseed+1) & 4095;
return f_rnd[zlseed];
}



signed long viszscreen(signed long xx,signed long yy,signed long zz)
{
s32 range;
range=-(FPML(xx-camera[0],vcamera[2][0])+FPML(yy-camera[1],vcamera[2][1])+FPML(zz-camera[2],vcamera[2][2]));
return range;
}

signed long visxscreen(signed long xx,signed long yy,signed long zz)
{
s32 range;
range=-(FPML(xx-camera[0],vcamera[0][0])+FPML(yy-camera[1],vcamera[0][1])+FPML(zz-camera[2],vcamera[0][2]));
return range;
}

signed long visyscreen(signed long xx,signed long yy,signed long zz)
{
s32 range;
range=-(FPML(xx-camera[0],vcamera[1][0])+FPML(yy-camera[1],vcamera[1][1])+FPML(zz-camera[2],vcamera[1][2]));
return range;
}

signed long zarctan(signed long argx,signed long argy)
{
signed long vl;
signed long d,res;

argx=argx>>4;

if (argx==0)
 {
  res=1024;
 }
 else
 {
 d=1024;res=512;
 argy=argy<<2;

 vl=argy/argx;
 vl=vl<<10;

 if (vl<0) vl=-vl;
 while (d>1)
  {
   d=d>>1;
  if (f_tan[res]>vl) res=res-d;
  else
  if (f_tan[res]<vl) res=res+d;
  else d=0;
  }

 }
if ((argx<=0)&(argy>0)) res=2048-res;
else
if ((argx<=0)&(argy<0)) res=2048+res;
else
if ((argx>=0)&(argy<0)) res=4096-res;

return res;
}

signed long cturn(signed long angle0,signed long angle1)
{
signed long de=(angle1-angle0);
if (de>2048) de=-4096+de;
else
if (de<-2048) de=4096+de;

return de;
}

signed long fastrange(signed long argx,signed long argy)
{
signed long rs0,rs1;
rs0=argx;
rs1=argy;
if (rs0<0) rs0= - rs0;
if (rs1<0) rs1= - rs1;
if (rs0>rs1) return rs0; else return rs1;
}


signed long srange(signed long argx,signed long argy)
{
signed long res;
float t0,t1,val;
t0=argx/65536;
t0=t0*t0;
t1=argy/65536;
t1=t1*t1;

val=sqrt(t0+t1);
val=val*65535;
res=val;
return (res);
}

unsigned char i_probe_act(void)
{
u8 see=1;
s32 steps,ix,iy,iz,ii,t,xx,yy,zz;
ix=-i_probe[0]+i_probe[3];
iy=-i_probe[1]+i_probe[4];
iz=-i_probe[2]+i_probe[5];
if (ix<0) ii=-ix; else ii=ix;
if (iy<0) t=-iy; else t=iy;
if (t>ii) ii=t;
if (iz<0) t=-iz; else t=iz;
if (t>ii) ii=t;
steps=ii/16000;
if (steps<1) steps=1;
ix=ix/steps;
iy=iy/steps;
iz=iz/steps;

xx=i_probe[0];
yy=i_probe[1];
zz=i_probe[2];

xx+=ix;
yy+=iy;
zz+=iz;
steps-=2;

while (steps>0 & see>0)
{
if (mp[xx>>16][yy>>16][zz>>16][0]>0) see=0;
xx+=ix;
yy+=iy;
zz+=iz;
steps--;
}
//printf("%i %i %i (%i %i %i) %i %i %i\n",i_probe[0]>>16,i_probe[1]>>16,i_probe[2]>>16,xx>>16,yy>>16,zz>>16,i_probe[3]>>16,i_probe[4]>>16,i_probe[5]>>16);
//printf("%i %i %i \n",xx>>16,yy>>16,zz>>16);

return see;
}

signed long zabs(signed long argx)
{
if (argx<0) return argx; else return -argx;
}
