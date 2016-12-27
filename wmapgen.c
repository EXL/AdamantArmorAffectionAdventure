#include "vars.h"
#include "stdlib.h"


void generateautismmap(void)
{
//I'm not so retard
}


void generatemap(void)
{
generateautismmap();
}

void generateeditmap(void)
{
u8 t,i,x,y;
t=10;
mpheader[8]=10;
mpheader[9]=6;

mpheader[10]=32;
mpheader[11]=32;
mpheader[12]=32;
mpheader[13]=225;
mpheader[14]=225;
mpheader[15]=225;

mpheader[2]=0;
mpheader[3]=0;
mpheader[16]=0;
mpheader[17]=0;


mpheader[18]=64;
mpheader[19]=64;
mpheader[20]=64;

mp[0][1][0][0]=t;
mp[0][0][0][0]=t;
mp[1][0][0][0]=t;

}
