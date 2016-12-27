#include "vars.h"

void procintro(void)
{
s32 pos[2][6],t,tc,delta;
u8 i,i0,i1;

i0=0;
i1=1;


tc=512;
i0=((levelframes/tc))%6;
i1=((levelframes/tc)+1)%6;

t=levelframes % tc;

for (i=0;i<3;i++)
{
pos[0][i]=mpheader[28+i0*6+i]*65536+32768;
pos[1][i]=mpheader[28+i1*6+i]*65536+32768;

camera[i]=pos[0][i]+(pos[1][i]-pos[0][i])*t/tc;
}
for (i=3;i<6;i++)
{
pos[0][i]=mpheader[28+i0*6+i]*16;
pos[1][i]=mpheader[28+i1*6+i]*16;

delta=(pos[1][i]-pos[0][i]);
if (delta>2048) delta=-4096+delta;
if (delta<-2048) delta=4096+delta;

camera[i]=pos[0][i]+delta*t/tc;
}

camera[3]+=consoleturn[0]/3;
camera[5]+=consoleturn[1];


}


void procmovie(void)
{
s32 pos[2][6],t,tc,delta,tt,i,i0,i1;
/*
if (narration==0)
{//how we switch map?

}
else*/
if (narrationlength>0)
if (narrationlength<narationticks)
{
if (endlevel==0) endlevel=255;
}
else
{
//endlevel=255;
tc=narrationlength/5;

tt=narationticks;
i0=((tt/tc))%6;
i1=((tt/tc)+1)%6;

t=narationticks % tc;
//t=t/tscale;
t=t>>4;
tc=tc>>4;

for (i=0;i<3;i++)
{
pos[0][i]=mpheader[28+i0*6+i]*65536+32768;
pos[1][i]=mpheader[28+i1*6+i]*65536+32768;

camera[i]=pos[0][i]+((pos[1][i]-pos[0][i])/4)*t/tc*4;
}
for (i=3;i<6;i++)
{
pos[0][i]=mpheader[28+i0*6+i]*16;
pos[1][i]=mpheader[28+i1*6+i]*16;

delta=(pos[1][i]-pos[0][i]);
if (delta>2048) delta=-4096+delta;
if (delta<-2048) delta=4096+delta;

camera[i]=pos[0][i]+(delta*t)/tc;
}
camera[3]+=consoleturn[0]/3;
camera[5]+=consoleturn[1];
}




if (endlevel==0 | endlevel==255)
if (button[0]==1 | button[1]==1 | button[2]==1 |button[3]==1 |button[8]==1 |button[9]==1 | mousetap==1) {/*narration=0;*/endlevel=255;zcplaysound(1);}
}
