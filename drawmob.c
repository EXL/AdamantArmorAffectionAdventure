#include "vars.h"
#include "render.h"
#include "zlmath.h"
#include "wlight.h"
#include "veryblend.h"


s32 r,g,b,iii_index;

#define FPML(x,y) ((((x)>>7)*((y)>>7))>>2)

void rendermobbody(void)
{
zlBeginQuads();
//front
zlTexCoord2x( 8*4096, 6*4096);zlVertex3x(-8192, 49152,-16384);
zlTexCoord2x( 8*4096, 9*4096);zlVertex3x(-8192,     0,-16384);
zlTexCoord2x(10*4096, 9*4096);zlVertex3x(-8192,     0, 16384);
zlTexCoord2x(10*4096, 6*4096);zlVertex3x(-8192, 49152, 16384);
//back
zlTexCoord2x(13*4096, 6*4096);zlVertex3x(8192, 49152,-16384);
zlTexCoord2x(13*4096, 9*4096);zlVertex3x(8192,     0,-16384);
zlTexCoord2x(11*4096, 9*4096);zlVertex3x(8192,     0, 16384);
zlTexCoord2x(11*4096, 6*4096);zlVertex3x(8192, 49152, 16384);

//top
zlTexCoord2x( 8*4096, 5*4096);zlVertex3x(8192, 49152,-16384);
zlTexCoord2x( 8*4096, 6*4096);zlVertex3x(-8192, 49152,-16384);
zlTexCoord2x(10*4096, 6*4096);zlVertex3x(-8192, 49152, 16384);
zlTexCoord2x(10*4096, 5*4096);zlVertex3x(8192, 49152, 16384);

//bottom
zlTexCoord2x( 8*4096, 9*4096);zlVertex3x(8192, 0,-16384);
zlTexCoord2x( 8*4096, 10*4096);zlVertex3x(-8192, 0,-16384);
zlTexCoord2x(10*4096, 10*4096);zlVertex3x(-8192, 0, 16384);
zlTexCoord2x(10*4096, 9*4096);zlVertex3x(8192, 0, 16384);

//right
zlTexCoord2x(8*4096, 6*4096);zlVertex3x(-8192, 49152,-16384);
zlTexCoord2x(8*4096, 9*4096);zlVertex3x(-8192,     0,-16384);
zlTexCoord2x(7*4096, 9*4096);zlVertex3x( 8192,     0,-16384);
zlTexCoord2x(7*4096, 6*4096);zlVertex3x( 8192, 49152,-16384);

//left
zlTexCoord2x(10*4096, 6*4096);zlVertex3x(-8192, 49152,16384);
zlTexCoord2x(10*4096, 9*4096);zlVertex3x(-8192,     0,16384);
zlTexCoord2x(11*4096, 9*4096);zlVertex3x( 8192,     0,16384);
zlTexCoord2x(11*4096, 6*4096);zlVertex3x( 8192, 49152,16384);

zlEndQuads();
}

s32 facedata[12]={2,7, 0,14, 2,14, 4,14, 6,14, 8,14 };
u8 facemask[4]={0,1,0,2};

void rendermobhead(void)
{
u8 faceid;

if (mob[iii_index][30]==AI_ATTACK)
faceid=3+facemask[(((mob[iii_index][19])/10)%4)];
else
faceid=facemask[(((mob[iii_index][19])/80)%4)];

zlBeginQuads();
//front
zlTexCoord2x( facedata[faceid*2]*4096, facedata[faceid*2+1]*4096);zlVertex3x(-16383, 32178,-16384);
zlTexCoord2x( facedata[faceid*2]*4096, (facedata[faceid*2+1]+2)*4096);zlVertex3x(-16384,     0,-16384);
zlTexCoord2x((facedata[faceid*2]+2)*4096, (facedata[faceid*2+1]+2)*4096);zlVertex3x(-16384,     0, 16384);
zlTexCoord2x((facedata[faceid*2]+2)*4096, facedata[faceid*2+1]*4096);zlVertex3x(-16384, 32178, 16384);
//back

zlTexCoord2x(4*4096, 11*4096);zlVertex3x(16384, 32178,-16384);
zlTexCoord2x(4*4096, 13*4096);zlVertex3x(16384,     0,-16384);
zlTexCoord2x(2*4096, 13*4096);zlVertex3x(16384,     0, 16384);
zlTexCoord2x(2*4096, 11*4096);zlVertex3x(16384, 32178, 16384);

//top
zlTexCoord2x( 2*4096, 5*4096);zlVertex3x(16384, 32178,-16384);
zlTexCoord2x( 2*4096, 7*4096);zlVertex3x(-16384, 32178,-16384);
zlTexCoord2x(4*4096, 7*4096);zlVertex3x(-16384, 32178, 16384);
zlTexCoord2x(4*4096, 5*4096);zlVertex3x(16384, 32178, 16384);

//bottom
zlTexCoord2x( 2*4096, 11*4096); zlVertex3x(16384, 0,-16384);
zlTexCoord2x( 2*4096, 9*4096);zlVertex3x(-16384, 0,-16384);
zlTexCoord2x(4*4096, 9*4096);zlVertex3x(-16384, 0, 16384);
zlTexCoord2x(4*4096, 11*4096); zlVertex3x(16384, 0, 16384);

//right
zlTexCoord2x(2*4096, 7*4096);zlVertex3x(-16384, 32178,-16384);
zlTexCoord2x(2*4096, 9*4096);zlVertex3x(-16384,     0,-16384);
zlTexCoord2x(0*4096, 9*4096);zlVertex3x( 16384,     0,-16384);
zlTexCoord2x(0*4096, 7*4096);zlVertex3x( 16384, 32178,-16384);
//left
zlTexCoord2x(4*4096, 7*4096);zlVertex3x(-16384, 32178,16384);
zlTexCoord2x(4*4096, 9*4096);zlVertex3x(-16384,     0,16384);
zlTexCoord2x(6*4096, 9*4096);zlVertex3x( 16384,     0,16384);
zlTexCoord2x(6*4096, 7*4096);zlVertex3x( 16384, 32178,16384);

zlEndQuads();
}

void rendermoblhand(void)
{
zlBeginQuads();
//front
zlTexCoord2x( 1*4096, 1*4096);zlVertex3x(-8192, 8192,-8192);
zlTexCoord2x( 1*4096, 4*4096);zlVertex3x(-8192,-40960,-8192);
zlTexCoord2x( 2*4096, 4*4096);zlVertex3x(-8192,-40960, 8192);
zlTexCoord2x( 2*4096, 1*4096);zlVertex3x(-8192, 8192, 8192);
//back
zlTexCoord2x( 4*4096, 1*4096);zlVertex3x(8192, 8192,-8192);
zlTexCoord2x( 4*4096, 4*4096);zlVertex3x(8192,-40960,-8192);
zlTexCoord2x( 3*4096, 4*4096);zlVertex3x(8192,-40960, 8192);
zlTexCoord2x( 3*4096, 1*4096);zlVertex3x(8192, 8192, 8192);

//top
zlTexCoord2x( 1*4096, 0*4096);zlVertex3x(8192, 8192,-8192);
zlTexCoord2x( 1*4096, 1*4096);zlVertex3x(-8192,8192,-8192);
zlTexCoord2x( 2*4096, 1*4096);zlVertex3x(-8192,8192, 8192);
zlTexCoord2x( 2*4096, 0*4096);zlVertex3x(8192, 8192, 8192);

//bottom
zlTexCoord2x( 1*4096, 5*4096);zlVertex3x(8192, -40960,-8192);
zlTexCoord2x( 1*4096, 4*4096);zlVertex3x(-8192,-40960,-8192);
zlTexCoord2x( 2*4096, 4*4096);zlVertex3x(-8192,-40960, 8192);
zlTexCoord2x( 2*4096, 5*4096);zlVertex3x(8192, -40960, 8192);

//right
zlTexCoord2x(1*4096, 1*4096);zlVertex3x(-8192, 8192,-8192);
zlTexCoord2x(1*4096, 4*4096);zlVertex3x(-8192,-40960,-8192);
zlTexCoord2x(0*4096, 4*4096);zlVertex3x( 8192,-40960,-8192);
zlTexCoord2x(0*4096, 1*4096);zlVertex3x( 8192, 8192,-8192);

//left
zlTexCoord2x(2*4096, 1*4096);zlVertex3x(-8192, 8192,8192);
zlTexCoord2x(2*4096, 4*4096);zlVertex3x(-8192,-40960,8192);
zlTexCoord2x(3*4096, 4*4096);zlVertex3x( 8192,-40960,8192);
zlTexCoord2x(3*4096, 1*4096);zlVertex3x( 8192, 8192,8192);
zlEndQuads();
}

void rendermobrhand(void)
{
zlBeginQuads();
//front
zlTexCoord2x( 5*4096, 1*4096);zlVertex3x(-8192, 8192,-8192);
zlTexCoord2x( 5*4096, 4*4096);zlVertex3x(-8192,-40960,-8192);
zlTexCoord2x( 6*4096, 4*4096);zlVertex3x(-8192,-40960, 8192);
zlTexCoord2x( 6*4096, 1*4096);zlVertex3x(-8192, 8192, 8192);
//back
zlTexCoord2x( 8*4096, 1*4096);zlVertex3x(8192, 8192,-8192);
zlTexCoord2x( 8*4096, 4*4096);zlVertex3x(8192,-40960,-8192);
zlTexCoord2x( 7*4096, 4*4096);zlVertex3x(8192,-40960, 8192);
zlTexCoord2x( 7*4096, 1*4096);zlVertex3x(8192, 8192, 8192);

//top
zlTexCoord2x( 5*4096, 0*4096);zlVertex3x(8192, 8192,-8192);
zlTexCoord2x( 5*4096, 1*4096);zlVertex3x(-8192,8192,-8192);
zlTexCoord2x( 6*4096, 1*4096);zlVertex3x(-8192,8192, 8192);
zlTexCoord2x( 6*4096, 0*4096);zlVertex3x(8192, 8192, 8192);

//bottom
zlTexCoord2x( 5*4096, 5*4096);zlVertex3x(8192, -40960,-8192);
zlTexCoord2x( 5*4096, 4*4096);zlVertex3x(-8192,-40960,-8192);
zlTexCoord2x( 6*4096, 4*4096);zlVertex3x(-8192,-40960, 8192);
zlTexCoord2x( 6*4096, 5*4096);zlVertex3x(8192, -40960, 8192);

//right
zlTexCoord2x(5*4096, 1*4096);zlVertex3x(-8192, 8192,-8192);
zlTexCoord2x(5*4096, 4*4096);zlVertex3x(-8192,-40960,-8192);
zlTexCoord2x(4*4096, 4*4096);zlVertex3x( 8192,-40960,-8192);
zlTexCoord2x(4*4096, 1*4096);zlVertex3x( 8192, 8192,-8192);

//left
zlTexCoord2x(6*4096, 1*4096);zlVertex3x(-8192, 8192,8192);
zlTexCoord2x(6*4096, 4*4096);zlVertex3x(-8192,-40960,8192);
zlTexCoord2x(7*4096, 4*4096);zlVertex3x( 8192,-40960,8192);
zlTexCoord2x(7*4096, 1*4096);zlVertex3x( 8192, 8192,8192);
zlEndQuads();
}

void rendermoblleg(void)
{
zlBeginQuads();
//front
zlTexCoord2x( 9*4096, 1*4096);zlVertex3x(-8192, 0,-8192);
zlTexCoord2x( 9*4096, 4*4096);zlVertex3x(-8192,-49152,-8192);
zlTexCoord2x( 10*4096, 4*4096);zlVertex3x(-8192,-49152, 8192);
zlTexCoord2x( 10*4096, 1*4096);zlVertex3x(-8192, 0, 8192);
//back
zlTexCoord2x( 12*4096, 1*4096);zlVertex3x(8192, 0,-8192);
zlTexCoord2x( 12*4096, 4*4096);zlVertex3x(8192,-49152,-8192);
zlTexCoord2x( 11*4096, 4*4096);zlVertex3x(8192,-49152, 8192);
zlTexCoord2x( 11*4096, 1*4096);zlVertex3x(8192, 0, 8192);

//top
zlTexCoord2x( 9*4096, 0*4096);zlVertex3x(8192, 0,-8192);
zlTexCoord2x( 9*4096, 1*4096);zlVertex3x(-8192,0,-8192);
zlTexCoord2x( 10*4096, 1*4096);zlVertex3x(-8192,0, 8192);
zlTexCoord2x( 10*4096, 0*4096);zlVertex3x(8192, 0, 8192);

//bottom
zlTexCoord2x( 9*4096, 5*4096);zlVertex3x(8192, -49152,-8192);
zlTexCoord2x( 9*4096, 4*4096);zlVertex3x(-8192,-49152,-8192);
zlTexCoord2x(10*4096, 4*4096);zlVertex3x(-8192,-49152, 8192);
zlTexCoord2x(10*4096, 5*4096);zlVertex3x(8192, -49152, 8192);

//right
zlTexCoord2x(9*4096, 1*4096);zlVertex3x(-8192, 0,-8192);
zlTexCoord2x(9*4096, 4*4096);zlVertex3x(-8192,-49152,-8192);
zlTexCoord2x(8*4096, 4*4096);zlVertex3x( 8192,-49152,-8192);
zlTexCoord2x(8*4096, 1*4096);zlVertex3x( 8192, 0,-8192);

//left
zlTexCoord2x(10*4096, 1*4096);zlVertex3x(-8192, 0,8192);
zlTexCoord2x(10*4096, 4*4096);zlVertex3x(-8192,-49152,8192);
zlTexCoord2x(11*4096, 4*4096);zlVertex3x( 8192,-49152,8192);
zlTexCoord2x(11*4096, 1*4096);zlVertex3x( 8192, 0,8192);
zlEndQuads();
}
void rendermobrleg(void)
{
zlBeginQuads();
//front
zlTexCoord2x( 13*4096, 1*4096);zlVertex3x(-8192, 0,-8192);
zlTexCoord2x( 13*4096, 4*4096);zlVertex3x(-8192,-49152,-8192);
zlTexCoord2x( 14*4096, 4*4096);zlVertex3x(-8192,-49152, 8192);
zlTexCoord2x( 14*4096, 1*4096);zlVertex3x(-8192, 0, 8192);
//back
zlTexCoord2x( 16*4096, 1*4096);zlVertex3x(8192, 0,-8192);
zlTexCoord2x( 16*4096, 4*4096);zlVertex3x(8192,-49152,-8192);
zlTexCoord2x( 15*4096, 4*4096);zlVertex3x(8192,-49152, 8192);
zlTexCoord2x( 15*4096, 1*4096);zlVertex3x(8192, 0, 8192);

//top
zlTexCoord2x( 13*4096, 0*4096);zlVertex3x(8192, 0,-8192);
zlTexCoord2x( 13*4096, 1*4096);zlVertex3x(-8192,0,-8192);
zlTexCoord2x( 14*4096, 1*4096);zlVertex3x(-8192,0, 8192);
zlTexCoord2x( 14*4096, 0*4096);zlVertex3x(8192, 0, 8192);

//bottom
zlTexCoord2x(13*4096, 5*4096);zlVertex3x(8192, -49152,-8192);
zlTexCoord2x(13*4096, 4*4096);zlVertex3x(-8192,-49152,-8192);
zlTexCoord2x(14*4096, 4*4096);zlVertex3x(-8192,-49152, 8192);
zlTexCoord2x(14*4096, 5*4096);zlVertex3x(8192, -49152, 8192);

//right
zlTexCoord2x(13*4096, 1*4096);zlVertex3x(-8192, 0,-8192);
zlTexCoord2x(13*4096, 4*4096);zlVertex3x(-8192,-49152,-8192);
zlTexCoord2x(12*4096, 4*4096);zlVertex3x( 8192,-49152,-8192);
zlTexCoord2x(12*4096, 1*4096);zlVertex3x( 8192, 0,-8192);

//left
zlTexCoord2x(14*4096, 1*4096);zlVertex3x(-8192, 0,8192);
zlTexCoord2x(14*4096, 4*4096);zlVertex3x(-8192,-49152,8192);
zlTexCoord2x(15*4096, 4*4096);zlVertex3x( 8192,-49152,8192);
zlTexCoord2x(15*4096, 1*4096);zlVertex3x( 8192, 0,8192);
zlEndQuads();
}

void rendermobgun(void)
{
zlBeginQuads();
//front
zlTexCoord2x(13*4096, 12*4096);zlVertex3x(-8192, 8192,-8192);
zlTexCoord2x(13*4096, 15*4096);zlVertex3x(-8192,-40960,-8192);
zlTexCoord2x(14*4096, 15*4096);zlVertex3x(-8192,-40960, 8192);
zlTexCoord2x(14*4096, 12*4096);zlVertex3x(-8192, 8192, 8192);
//back
zlTexCoord2x(16*4096, 12*4096);zlVertex3x(8192, 8192,-8192);
zlTexCoord2x(16*4096, 15*4096);zlVertex3x(8192,-40960,-8192);
zlTexCoord2x(15*4096, 15*4096);zlVertex3x(8192,-40960, 8192);
zlTexCoord2x(15*4096, 12*4096);zlVertex3x(8192, 8192, 8192);

//top
zlTexCoord2x(13*4096, 11*4096);zlVertex3x(8192, 8192,-8192);
zlTexCoord2x(13*4096, 12*4096);zlVertex3x(-8192,8192,-8192);
zlTexCoord2x(14*4096, 12*4096);zlVertex3x(-8192,8192, 8192);
zlTexCoord2x(14*4096, 11*4096);zlVertex3x(8192, 8192, 8192);

//bottom
zlTexCoord2x(13*4096, 16*4096);zlVertex3x(8192, -40960,-8192);
zlTexCoord2x(13*4096, 15*4096);zlVertex3x(-8192,-40960,-8192);
zlTexCoord2x(14*4096, 15*4096);zlVertex3x(-8192,-40960, 8192);
zlTexCoord2x(14*4096, 16*4096);zlVertex3x(8192, -40960, 8192);

//right
zlTexCoord2x(13*4096, 12*4096);zlVertex3x(-8192, 8192,-8192);
zlTexCoord2x(13*4096, 15*4096);zlVertex3x(-8192,-40960,-8192);
zlTexCoord2x(12*4096, 15*4096);zlVertex3x( 8192,-40960,-8192);
zlTexCoord2x(12*4096, 12*4096);zlVertex3x( 8192, 8192,-8192);

//left
zlTexCoord2x(14*4096, 12*4096);zlVertex3x(-8192, 8192,8192);
zlTexCoord2x(14*4096, 15*4096);zlVertex3x(-8192,-40960,8192);
zlTexCoord2x(15*4096, 15*4096);zlVertex3x( 8192,-40960,8192);
zlTexCoord2x(15*4096, 12*4096);zlVertex3x( 8192, 8192,8192);
zlEndQuads();
}

void rendermobsword(void)
{
zlBeginQuads();
//front
zlTexCoord2x(14*4096, 6*4096);zlVertex3x(-8192, 8192,-8192);
zlTexCoord2x(14*4096, 10*4096);zlVertex3x(-8192,-65536-8192,-8192);
zlTexCoord2x(15*4096, 10*4096);zlVertex3x(-8192,-65536-8192, 8192);
zlTexCoord2x(15*4096, 6*4096);zlVertex3x(-8192, 8192, 8192);
zlEndQuads();
}

s32 bone[8][3];

s32 x,y,z,shw,cx,cy,cz,scale,idle,range,ddx,mcount,walkdata,flydata,tm,attackdata;

void drawhero(unsigned char i)
{

walkdata=FPML(f_sin[mcount*32%4096],mob[i][9]);
flydata=FPML(f_sin[mcount*4%4096],mob[i][6])/10;
attackdata=((f_sin[mob[i][36]*32])>>8);
zlPush();
zlTranslate(mob[i][1],mob[i][3],mob[i][2]);
zlRotatey(mob[i][7]);
zlColor4x(r,g,b,255);


zlBindTexture(100+secretskin);

scale=65536*3/4;
zlScale(scale,scale,scale);
zlTranslate(0,16384*3-8192,0);

idle=f_sin[mcount*11%4096]/600;
bone[0][0]=-mob[i][9]/5+flydata+attackdata;

if (mob[i][11])
bone[0][2]=-walkdata/10; else bone[0][2]=-flydata;


if (flydata<0) flydata=-flydata;

zlRotatez(bone[0][0]);
zlRotatex(bone[0][2]);


rendermobbody();
if (secretskin==0)
{
zlColor4x(255,255,255,255);
zlBeginQuads();
zlTexCoord2x(6*4096, 11*4096);zlVertex3x(8492, 49152,-16384);
zlTexCoord2x(6*4096, 12*4096);zlVertex3x(8492,32768,-16384);
zlTexCoord2x(7*4096, 12*4096);zlVertex3x(8492,32768,0);
zlTexCoord2x(7*4096, 11*4096);zlVertex3x(8492, 49152,0);
zlEndQuads();
zlColor4x(r,g,b,255);
}
else
if (secretskin==1)
{
zlBeginQuads();
//left
zlTexCoord2x(13*4096, 5*4096);zlVertex3x(8192, 69152,0);
zlTexCoord2x(13*4096, 9*4096);zlVertex3x(8192,     0,0);
zlTexCoord2x(16*4096, 9*4096);zlVertex3x(52178,     0,0);
zlTexCoord2x(16*4096, 5*4096);zlVertex3x(52178, 69152,0);
zlEndQuads();
}
bone[1][0]=mob[i][12]-bone[0][0];


bone[1][1]=mob[i][13];
if (playeraim<15)
bone[1][1]+=idle;

if (mob[i][40]==0)
{
zlPush();
zlTranslate(17000,54000,16000);
zlRotatex(128+walkdata/30);

zlBindTexture(100);

zlRotatey(2048);
rendermobgun();

zlColor4x(255,255,255,255);
zlBeginQuads();
zlTexCoord2x(5*4096, 10*4096);zlVertex3x(-8392, 8192,-8192);
zlTexCoord2x(5*4096, 11*4096);zlVertex3x(-8392,-8192,-8192);
zlTexCoord2x(6*4096, 11*4096);zlVertex3x(-8392,-8192,8192);
zlTexCoord2x(6*4096, 10*4096);zlVertex3x(-8392, 8192,8192);

zlTexCoord2x(5*4096, 11*4096);zlVertex3x(-8192, -24576,8392);
zlTexCoord2x(5*4096, 12*4096);zlVertex3x(-8192,-40960,8392);
zlTexCoord2x(6*4096, 12*4096);zlVertex3x(8192,-40960,8392);
zlTexCoord2x(6*4096, 11*4096);zlVertex3x(8192, -24576,8392);
zlEndQuads();
zlBindTexture(100+secretskin);
zlColor4x(r,g,b,255);
zlPop();
}

if (mob[i][39]==0)
{
zlPush();
zlTranslate(18000,35000,-16000);
zlRotatex(-618+walkdata/6);
zlColor4x(255,255,255,255);
zlBindTexture(100);
rendermobsword();
zlBindTexture(100+secretskin);
zlPop();
zlColor4x(r,g,b,255);
}
zlPush();

zlTranslate(0,48000,0);
zlRotatez(bone[1][0]);
zlRotatey(bone[1][1]);

scale=65536*3/4;
zlScale(scale,scale,scale);
rendermobhead();
zlColor4x(255,255,255,255);
if (secretskin==0)
{
zlBeginQuads();
zlTexCoord2x(10*4096, 11*4096);zlVertex3x(-16584,32768,-16584);
zlTexCoord2x(10*4096, 12*4096);zlVertex3x(-16584,16384,-16584);
zlTexCoord2x(11*4096, 12*4096);zlVertex3x(0,16384,-16584);
zlTexCoord2x(11*4096, 11*4096);zlVertex3x(0,32768,-16584);

zlTexCoord2x(10*4096, 11*4096);zlVertex3x(-16584,32768,16584);
zlTexCoord2x(10*4096, 12*4096);zlVertex3x(-16584,16384,16584);
zlTexCoord2x(11*4096, 12*4096);zlVertex3x(0,16384,16584);
zlTexCoord2x(11*4096, 11*4096);zlVertex3x(0,32768,16584);

//eyes
zlTexCoord2x(10*4096, 11*4096);zlVertex3x(-16584,32768,16584);
zlTexCoord2x(10*4096, 12*4096);zlVertex3x(-16584,16384,16584);
zlTexCoord2x(8*4096, 12*4096);zlVertex3x(-16584,16384,-16584);
zlTexCoord2x(8*4096, 11*4096);zlVertex3x(-16584,32768,-16584);
zlEndQuads();
}
if (playeraim>15 & secretskin==0)
{
//laser
zlBindTexture(100);

zlBeginQuads();
zlTexCoord2x(10*4096, 13*4096);zlVertex3x(-16960,16000,-8192);
zlTexCoord2x(10*4096, 14*4096);zlVertex3x(-409600,16000,-8192);
zlTexCoord2x(8*4096, 14*4096);zlVertex3x(-409600,8192,-8192);
zlTexCoord2x(8*4096, 13*4096);zlVertex3x(-16960,8192,-8192);
zlEndQuads();
zlBindTexture(100+secretskin);

}
zlColor4x(r,g,b,255);
if (secretskin==1)
{
zlBeginQuads();
//front
zlTexCoord2x( 2*4096, 4*4096);zlVertex3x(-9383, 44178,-22384);
zlTexCoord2x( 2*4096, 5*4096);zlVertex3x(-9384, 32178,-22384);
zlTexCoord2x(5*4096, 5*4096);zlVertex3x(-9384,  32178, 22384);
zlTexCoord2x(5*4096, 4*4096);zlVertex3x(-9384, 44178, 22384);
zlEndQuads();
}
zlPop();

bone[2][0]=walkdata/2;
bone[2][2]=-212+idle-4*flydata;
if (playeraim)
{
bone[2][0]+=((-1024-bone[0][0]+mob[i][12])-bone[2][0])*playeraim/16;
bone[2][2]+=((0-mob[i][13])-bone[2][2])*playeraim/16;
}

if (playeraim==0)if (mob[i][40]>0) bone[2][2]-=256;

if (mob[i][38]>0)
{
if (mob[i][38]<32)
{
bone[2][0]+=((-1024-256-bone[0][0]+mob[i][12])-bone[2][0])*mob[i][38]/32;
bone[2][2]+=((0-mob[i][13])-bone[2][2])*mob[i][38]/32;
}
else
{
bone[2][0]=-1024-bone[0][0]+mob[i][12]+(mob[i][38]-64)*8;
bone[2][2]=0-mob[i][13];
}
}

zlPush();
zlTranslate(0,40000,26000);
zlRotatez(bone[2][0]);
zlRotatex(bone[2][2]);
rendermoblhand();

if (mob[i][40]>0)
{
zlPush();
zlTranslate(-10292,-32000,-3192);
if (mob[i][40]<64)
zlRotatez((64-mob[i][40])*22);

zlBindTexture(100);
rendermobgun();
zlBindTexture(100+secretskin);
zlColor4x(255,255,255,255);
if (playeraim>13)
{
//laser
zlBindTexture(100);
zlBeginQuads();
zlTexCoord2x(10*4096, 13*4096);zlVertex3x(8192,-40960,0);
zlTexCoord2x(10*4096, 14*4096);zlVertex3x(8192,-409600,0);
zlTexCoord2x(8*4096, 14*4096);zlVertex3x(0,-40960,0);
zlTexCoord2x(8*4096, 13*4096);zlVertex3x(0,-40960,0);
zlEndQuads();
zlBindTexture(100+secretskin);
}
if (secretskin==0)
{
zlBeginQuads();
zlTexCoord2x(5*4096, 10*4096);zlVertex3x(-8392, 8192,-8192);
zlTexCoord2x(5*4096, 11*4096);zlVertex3x(-8392,-8192,-8192);
zlTexCoord2x(6*4096, 11*4096);zlVertex3x(-8392,-8192,8192);
zlTexCoord2x(6*4096, 10*4096);zlVertex3x(-8392, 8192,8192);

zlTexCoord2x(5*4096, 11*4096);zlVertex3x(-8192, -24576,8392);
zlTexCoord2x(5*4096, 12*4096);zlVertex3x(-8192,-40960,8392);
zlTexCoord2x(6*4096, 12*4096);zlVertex3x(8192,-40960,8392);
zlTexCoord2x(6*4096, 11*4096);zlVertex3x(8192, -24576,8392);
zlEndQuads();
}
zlColor4x(r,g,b,255);
zlPop();
}
if (secretskin==0)
{
zlColor4x(255,255,255,255);
zlBeginQuads();
zlTexCoord2x(6*4096, 10*4096);zlVertex3x(-8192, 8192,8392);
zlTexCoord2x(6*4096, 11*4096);zlVertex3x(-8192,-8192,8392);
zlTexCoord2x(7*4096, 11*4096);zlVertex3x( 8192,-8192,8392);
zlTexCoord2x(7*4096, 10*4096);zlVertex3x( 8192, 8192,8392);
zlEndQuads();
zlColor4x(r,g,b,255);
}
zlPop();

bone[3][0]=-walkdata/2;
bone[3][2]=212-idle+4*flydata;

if (mob[i][36])
{
tm=attackdata;

//if (mob[i]>32)
//{
//bone[3][0]=-1200+(((-512-bone[3][0])*tm)>>8);
//bone[3][2]=1000+(((-1300-bone[3][2])*tm)>>8);
//}
//else
{
bone[3][0]+=(((-1024-bone[3][0])*tm)>>8);
bone[3][2]+=(((-600-bone[3][2])*tm)>>8);
}
}


if (mob[i][37])
{
tm=((f_sin[mob[i][37]*32]))/256;
bone[3][0]+=(((-1810-bone[3][0])*tm)>>8);
bone[3][2]+=(((100-bone[3][2])*tm)>>8);
}

zlPush();
zlTranslate(0,40000,-26000);
zlRotatez(bone[3][0]);
zlRotatex(bone[3][2]);
rendermobrhand();

if (mob[i][39]>0)
{
zlPush();
zlTranslate(8192,-32000,0);
if (mob[i][39]<64)
zlRotatex(256+128+walkdata/4+(64-mob[i][39])*22);
else
zlRotatex(256+128+walkdata/4+-((f_sin[mob[i][36]*32]))/64);

zlColor4x(255,255,255,255);
zlBindTexture(100);
rendermobsword();
zlBindTexture(100+secretskin);
zlPop();
zlColor4x(r,g,b,255);
}
if (secretskin==0)
{
zlColor4x(255,255,255,255);
zlBeginQuads();
zlTexCoord2x(6*4096, 10*4096);zlVertex3x(-8192, 8192,-8392);
zlTexCoord2x(6*4096, 11*4096);zlVertex3x(-8192,-8192,-8392);
zlTexCoord2x(7*4096, 11*4096);zlVertex3x( 8192,-8192,-8392);
zlTexCoord2x(7*4096, 10*4096);zlVertex3x( 8192, 8192,-8392);
zlEndQuads();
zlColor4x(r,g,b,255);
}
zlPop();
bone[4][0]=-walkdata;
bone[4][2]=-flydata;
zlPush();
zlTranslate(400,8192,8292);
zlRotatez(bone[4][0]);
zlRotatex(bone[4][2]);
rendermoblleg();
zlPop();

bone[5][0]=walkdata+attackdata;
bone[5][2]=flydata;
zlPush();
zlTranslate(400,8192,-8292);
zlRotatez(bone[5][0]);
zlRotatex(bone[5][2]);
rendermobrleg();
zlPop();

zlPop();

}//hero

void drawnekotail(void)
{
zlBeginQuads();
//left
zlTexCoord2x(13*4096, 5*4096);zlVertex3x(8192, 69152,0);
zlTexCoord2x(13*4096, 9*4096);zlVertex3x(8192,     0,0);
zlTexCoord2x(16*4096, 9*4096);zlVertex3x(52178,     0,0);
zlTexCoord2x(16*4096, 5*4096);zlVertex3x(52178, 69152,0);

zlEndQuads();
}

void drawnekoears(void)
{
zlBeginQuads();
//front
zlTexCoord2x( 2*4096, 4*4096);zlVertex3x(-9383, 44178,-22384);
zlTexCoord2x( 2*4096, 5*4096);zlVertex3x(-9384, 32178,-22384);
zlTexCoord2x(5*4096, 5*4096);zlVertex3x(-9384,  32178, 22384);
zlTexCoord2x(5*4096, 4*4096);zlVertex3x(-9384, 44178, 22384);
zlEndQuads();
}

void drawneko(unsigned char i)
{
walkdata=FPML(f_sin[mcount*32%4096],mob[i][9]);
flydata=FPML(f_sin[mcount*4%4096],mob[i][6])/10;
attackdata=((f_sin[mob[i][36]*32])>>8);

zlPush();
zlTranslate(mob[i][1],mob[i][3],mob[i][2]);
zlRotatey(mob[i][7]);
zlColor4x(r,g,b,255);
zlBindTexture(101);
scale=65536*3/4;
zlScale(scale,scale,scale);
zlTranslate(0,16384*3-8192,0);

idle=f_sin[mcount*11%4096]/600;
bone[0][0]=-mob[i][9]/5+flydata+attackdata*2;

if (mob[i][11])
bone[0][2]=-walkdata/10; else bone[0][2]=-flydata;


if (flydata<0) flydata=-flydata;

zlRotatez(bone[0][0]);
zlRotatex(bone[0][2]);


rendermobbody();
drawnekotail();
bone[1][0]=mob[i][12]-bone[0][0];
bone[1][1]=mob[i][13]+idle;

zlPush();
zlTranslate(0,48000,0);
zlRotatez(bone[1][0]);
zlRotatey(bone[1][1]);

scale=65536*3/4;
zlScale(scale,scale,scale);
rendermobhead();
drawnekoears();
zlPop();

bone[2][0]=walkdata/2;
bone[2][2]=-212+idle-6*flydata;
if (mob[i][36])
{
bone[2][0]+=(((-1810-bone[2][0])*attackdata)>>8);
bone[2][2]+=(((100-bone[2][2])*attackdata)>>8);
}

zlPush();
zlTranslate(0,40000,26000);
zlRotatez(bone[2][0]);
zlRotatex(bone[2][2]);
rendermoblhand();
zlPop();
bone[3][0]=-walkdata/2;
bone[3][2]=212-idle+6*flydata;

if (mob[i][36])
{
bone[3][0]+=(((-1810-bone[3][0])*attackdata)>>8);
bone[3][2]+=(((100-bone[3][2])*attackdata)>>8);
}
zlPush();
zlTranslate(0,40000,-26000);
zlRotatez(bone[3][0]);
zlRotatex(bone[3][2]);
rendermobrhand();
zlPop();
bone[4][0]=-walkdata;
bone[4][2]=-flydata;
zlPush();
zlTranslate(400,8192,8292);
zlRotatez(bone[4][0]);
zlRotatex(bone[4][2]);
rendermoblleg();
zlPop();

bone[5][0]=walkdata;
bone[5][2]=flydata;
zlPush();
zlTranslate(400,8192,-8292);
zlRotatez(bone[5][0]);
zlRotatex(bone[5][2]);
rendermobrleg();
zlPop();

zlPop();

}//neko

void drawsoldier(unsigned char i)
{
walkdata=FPML(f_sin[mcount*32%4096],mob[i][9]);
flydata=FPML(f_sin[mcount*4%4096],mob[i][6])/10;

zlPush();
zlTranslate(mob[i][1],mob[i][3],mob[i][2]);
zlRotatey(mob[i][7]);
zlColor4x(r,g,b,255);
zlBindTexture(103);
scale=65536*3/4;
zlScale(scale,scale,scale);
zlTranslate(0,16384*3-8192,0);

idle=f_sin[mcount*11%4096]/600;
bone[0][0]=-mob[i][9]/5+flydata;

if (mob[i][11])
bone[0][2]=-walkdata/10; else bone[0][2]=-flydata;


if (flydata<0) flydata=-flydata;

zlRotatez(bone[0][0]);
zlRotatex(bone[0][2]);


rendermobbody();

bone[1][0]=mob[i][12]-bone[0][0];
bone[1][1]=mob[i][13]+idle;

zlPush();
zlTranslate(0,48000,0);
zlRotatez(bone[1][0]);
zlRotatey(bone[1][1]);

scale=65536*3/4;
zlScale(scale,scale,scale);
rendermobhead();

zlPop();

bone[2][0]=walkdata/2;
bone[2][2]=-212+idle-6*flydata;
zlPush();
zlTranslate(0,40000,26000);
zlRotatez(bone[2][0]);
zlRotatex(bone[2][2]);
rendermoblhand();
zlPop();
bone[3][0]=-walkdata/2;
bone[3][2]=212-idle+6*flydata;

if (mob[i][38]>0)
{
if (mob[i][38]<32)
{
bone[3][0]+=((-1024-256-bone[0][0]+mob[i][12])-bone[3][0])*mob[i][38]/32;
bone[3][2]+=((0-mob[i][13])-bone[3][2])*mob[i][38]/32;
}
else
{
bone[3][0]=-1024-bone[0][0]+mob[i][12]+(mob[i][38]-64)*8;
bone[3][2]=0-mob[i][13];
}
}

zlPush();
zlTranslate(0,40000,-26000);
zlRotatez(bone[3][0]);
zlRotatex(bone[3][2]);
rendermobrhand();


zlTranslate(-10292,-32000,3192);
rendermobgun();

zlPop();
bone[4][0]=-walkdata;
bone[4][2]=-flydata;
zlPush();
zlTranslate(400,8192,8292);
zlRotatez(bone[4][0]);
zlRotatex(bone[4][2]);
rendermoblleg();
zlPop();

bone[5][0]=walkdata;
bone[5][2]=flydata;
zlPush();
zlTranslate(400,8192,-8292);
zlRotatez(bone[5][0]);
zlRotatex(bone[5][2]);
rendermobrleg();
zlPop();

zlPop();

}//soldier

void drawslime(unsigned char i)
{
walkdata=FPML(f_sin[mcount*64%4096],mob[i][9]);
flydata=mob[i][6];

zlPush();
zlTranslate(mob[i][1],mob[i][3],mob[i][2]);
zlRotatey(mob[i][7]);
zlColor4x(r,g,b,255);
zlBindTexture(102);
scale=65536*2;
zlScale(scale+walkdata*40,scale+flydata*15,scale);
//zlTranslate(0,16384*3-8192,0);

rendermobhead();
zlPop();

}//slime

void drawzombie(unsigned char i)
{
walkdata=FPML(f_sin[mcount*32%4096],mob[i][9]);
flydata=FPML(f_sin[mcount*4%4096],mob[i][6])/10;
attackdata=((f_sin[mob[i][36]*32])>>8);

zlPush();
zlTranslate(mob[i][1],mob[i][3],mob[i][2]);
zlRotatey(mob[i][7]);
zlColor4x(r,g,b,255);
zlBindTexture(104);
scale=65536*3/4;
zlScale(scale,scale,scale);
zlTranslate(0,16384*3-8192,0);

idle=f_sin[mcount*11%4096]/600;
bone[0][0]=-mob[i][9]/5+flydata;

if (mob[i][11])
bone[0][2]=-walkdata/10; else bone[0][2]=-flydata;

bone[0][0]+=attackdata*2;

if (mob[i][42]>0) bone[0][0]+=256;


if (flydata<0) flydata=-flydata;

zlRotatez(bone[0][0]);
zlRotatex(bone[0][2]);

rendermobbody();

bone[1][0]=mob[i][12]-bone[0][0];
bone[1][1]=mob[i][13]+idle;

zlPush();
zlTranslate(0,48000,0);
zlRotatez(bone[1][0]);
zlRotatey(bone[1][1]);

scale=65536*3/4;
zlScale(scale,scale,scale);
rendermobhead();
zlBlend(1);
zlColor4x(255,255,255,255-(r+g+b)/3);
zlBeginQuads();

//eyes
zlTexCoord2x(10*4096,11*4096);zlVertex3x(-16584,32768-4096,16584);
zlTexCoord2x(10*4096,12*4096);zlVertex3x(-16584,16384-4096,16584);
zlTexCoord2x( 8*4096,12*4096);zlVertex3x(-16584,16384-4096,-16584);
zlTexCoord2x( 8*4096,11*4096);zlVertex3x(-16584,32768-4096,-16584);
zlEndQuads();
zlPop();
zlBlend(0);
zlColor4x(r,g,b,255);

bone[2][0]=-1024-walkdata/4;
bone[2][2]=0;

if (mob[i][36])
{
bone[2][0]+=(((-1810-bone[2][0])*attackdata)>>8);
bone[2][2]+=(((100-bone[2][2])*attackdata)>>8);
}

zlPush();
zlTranslate(0,40000,25000);
zlRotatez(bone[2][0]);
zlRotatex(bone[2][2]);
rendermoblhand();
zlPop();
bone[3][0]=-1024-walkdata/4;
bone[3][2]=0;
if (mob[i][36])
{
bone[3][0]+=(((-1810-bone[3][0])*attackdata)>>8);
bone[3][2]+=(((100-bone[3][2])*attackdata)>>8);
}

zlPush();
zlTranslate(0,40000,-25000);
zlRotatez(bone[3][0]);
zlRotatex(bone[3][2]);
rendermobrhand();
zlPop();
bone[4][0]=-walkdata;
bone[4][2]=-flydata;
zlPush();
zlTranslate(400,8192,8292);
zlRotatez(bone[4][0]);
zlRotatex(bone[4][2]);
rendermoblleg();
zlPop();

bone[5][0]=walkdata;
bone[5][2]=flydata;
zlPush();
zlTranslate(400,8192,-8292);
zlRotatez(bone[5][0]);
zlRotatex(bone[5][2]);
rendermobrleg();
zlPop();

zlPop();

}//zombie

void drawghoul(unsigned char i)
{
i_probe[0]=camera[0];
i_probe[1]=camera[2];
i_probe[2]=camera[1];
i_probe[3]=mob[i][1];
i_probe[4]=mob[i][2];
i_probe[5]=mob[i][3];
if (i_probe_act())
{
if (mob[i][30]==AI_ATTACK)
{
tension[3]=244;
tension[0]=255;
tension[1]=64;
tension[2]=64;
}
else
{
tension[3]=64;
tension[0]=255;
tension[1]=255;
tension[2]=255;
}
}
walkdata=FPML(f_sin[mcount*32%4096],mob[i][9]);
flydata=FPML(f_sin[mcount*4%4096],mob[i][6])/10;
attackdata=((f_sin[mob[i][36]*32])>>8);

zlPush();
zlTranslate(mob[i][1],mob[i][3],mob[i][2]);
zlRotatey(mob[i][7]);
zlColor4x(r,g,b,255);
zlBindTexture(105);
scale=65536*3/4;
zlScale(scale,scale,scale);
zlTranslate(0,16384*3-8192,0);

idle=f_sin[mcount*11%4096]/600;
bone[0][0]=-mob[i][9]/5+flydata;

if (mob[i][11])
bone[0][2]=-walkdata/10; else bone[0][2]=-flydata;

bone[0][0]+=attackdata*2;
if (mob[i][42]>0) bone[0][0]+=mob[i][42]*64;

if (flydata<0) flydata=-flydata;

zlRotatez(bone[0][0]);
zlRotatex(bone[0][2]);

rendermobbody();

bone[1][0]=mob[i][12]-bone[0][0]-128+zlrand();
bone[1][1]=mob[i][13]+idle-128+zlrand();

zlPush();
zlTranslate(0,48000,0);
zlRotatez(bone[1][0]);
zlRotatey(bone[1][1]);

scale=65536*3/4;
zlScale(scale,scale,scale);
rendermobhead();
zlColor4x(255,255,255,255);
zlBeginQuads();

//eyes
zlTexCoord2x(10*4096,11*4096);zlVertex3x(-16584,32768,16584);
zlTexCoord2x(10*4096,12*4096);zlVertex3x(-16584,16384,16584);
zlTexCoord2x( 8*4096,12*4096);zlVertex3x(-16584,16384,-16584);
zlTexCoord2x( 8*4096,11*4096);zlVertex3x(-16584,32768,-16584);
zlEndQuads();
zlColor4x(r,g,b,255);
zlPop();

bone[2][0]=-1024-walkdata/4;
bone[2][2]=0;

if (mob[i][36])
{
bone[2][0]+=(((-1810-bone[2][0])*attackdata)>>8);
bone[2][2]+=(((100-bone[2][2])*attackdata)>>8);
}

zlPush();
zlTranslate(0,40000,25000);
zlRotatez(bone[2][0]);
zlRotatex(bone[2][2]);
rendermoblhand();
zlPop();
bone[3][0]=-1024-walkdata/4;
bone[3][2]=0;
if (mob[i][36])
{
bone[3][0]+=(((-1810-bone[3][0])*attackdata)>>8);
bone[3][2]+=(((100-bone[3][2])*attackdata)>>8);
}

zlPush();
zlTranslate(0,40000,-25000);
zlRotatez(bone[3][0]);
zlRotatex(bone[3][2]);
rendermobrhand();
zlPop();
bone[4][0]=-walkdata;
bone[4][2]=-flydata;
zlPush();
zlTranslate(400,8192,8292);
zlRotatez(bone[4][0]);
zlRotatex(bone[4][2]);
rendermoblleg();
zlPop();

bone[5][0]=walkdata;
bone[5][2]=flydata;
zlPush();
zlTranslate(400,8192,-8292);
zlRotatez(bone[5][0]);
zlRotatex(bone[5][2]);
rendermobrleg();
zlPop();

zlPop();

}//ghoul

void drawscientist(unsigned char i)
{
walkdata=FPML(f_sin[mcount*32%4096],mob[i][9]);
flydata=FPML(f_sin[mcount*4%4096],mob[i][6])/10;

zlPush();
zlTranslate(mob[i][1],mob[i][3],mob[i][2]);
zlRotatey(mob[i][7]);
zlColor4x(r,g,b,255);
zlBindTexture(106);
scale=65536*3/4;
zlScale(scale,scale,scale);
zlTranslate(0,16384*3-8192,0);

idle=f_sin[mcount*11%4096]/600;
bone[0][0]=-mob[i][9]/5+flydata;

if (mob[i][11])
bone[0][2]=-walkdata/10; else bone[0][2]=-flydata;


if (flydata<0) flydata=-flydata;

zlRotatez(bone[0][0]);
zlRotatex(bone[0][2]);


rendermobbody();

bone[1][0]=mob[i][12]-bone[0][0];
bone[1][1]=mob[i][13]+idle;

zlPush();
zlTranslate(0,48000,0);
zlRotatez(bone[1][0]);
zlRotatey(bone[1][1]);

scale=65536*3/4;
zlScale(scale,scale,scale);
rendermobhead();

zlPop();

bone[2][0]=walkdata/2;
bone[2][2]=-212+idle-6*flydata;
zlPush();
zlTranslate(0,40000,26000);
zlRotatez(bone[2][0]);
zlRotatex(bone[2][2]);
rendermoblhand();
zlPop();
bone[3][0]=-walkdata/2;
bone[3][2]=212-idle+6*flydata;

zlPush();
zlTranslate(0,40000,-26000);
zlRotatez(bone[3][0]);
zlRotatex(bone[3][2]);
rendermobrhand();

zlPop();
bone[4][0]=-walkdata;
bone[4][2]=-flydata;
zlPush();
zlTranslate(400,8192,8292);
zlRotatez(bone[4][0]);
zlRotatex(bone[4][2]);
rendermoblleg();
zlPop();

bone[5][0]=walkdata;
bone[5][2]=flydata;
zlPush();
zlTranslate(400,8192,-8292);
zlRotatez(bone[5][0]);
zlRotatex(bone[5][2]);
rendermobrleg();
zlPop();

zlPop();

}//scientis

void drawraptor(unsigned char i)
{
walkdata=FPML(f_sin[mcount*64%4096],mob[i][9]);
flydata=FPML(f_sin[mcount*4%4096],mob[i][6])/10;
attackdata=((f_sin[mob[i][36]*32])>>8);

zlPush();
zlTranslate(mob[i][1],mob[i][3],mob[i][2]);
zlRotatey(mob[i][7]+FPML(f_sin[mcount*8%4096],mob[i][9]));

zlColor4x(r,g,b,255);
zlBindTexture(107);
scale=65536;
zlScale(scale,scale,scale);
zlTranslate(0,16384*3-8192,0);

idle=f_sin[mcount*11%4096]/600;
bone[0][0]=-mob[i][9]/5+flydata;

if (mob[i][11])
bone[0][2]=-walkdata/10; else bone[0][2]=-flydata;

bone[0][0]+=400+attackdata*2;;

if (flydata<0) flydata=-flydata;

zlRotatez(bone[0][0]);
zlRotatex(bone[0][2]);

rendermobbody();

bone[1][0]=mob[i][12]-bone[0][0]-1024-zabs(walkdata)/3;
bone[1][1]=mob[i][13]+idle;

zlPush();
zlTranslate(-8000,48000,0);
zlRotatez(bone[1][0]);
zlRotatey(bone[1][1]);

rendermoblhand();

zlPop();
bone[2][0]=mob[i][12]-bone[0][0]-1024+zabs(walkdata)/3;
bone[2][1]=mob[i][13]+idle;

zlPush();
zlTranslate(8000,52000,0);
zlRotatez(bone[2][0]);
zlRotatey(bone[2][1]);

rendermobrhand();

zlPop();

bone[3][0]=mob[i][12]-bone[0][0]+1024-walkdata/2;
bone[3][1]=mob[i][13]+idle;

zlPush();
zlTranslate(8000,0,0);
zlRotatez(bone[3][0]);
zlRotatey(bone[3][1]);

rendermobgun();//RAPTORH HAZ AH GUNH

zlPop();

bone[4][0]=-walkdata-bone[0][0];
bone[4][2]=-flydata-200;
zlPush();
zlTranslate(400,8192,8292);
zlRotatez(bone[4][0]);
zlRotatex(bone[4][2]);
rendermoblleg();
zlPop();

bone[5][0]=walkdata-bone[0][0];
bone[5][2]=flydata+200;
zlPush();
zlTranslate(400,8192,-8292);
zlRotatez(bone[5][0]);
zlRotatex(bone[5][2]);
rendermobrleg();
zlPop();

zlPop();

}//raptor

void drawdoctorzombie(unsigned char i)
{
walkdata=FPML(f_sin[mcount*32%4096],mob[i][9]);
flydata=FPML(f_sin[mcount*4%4096],mob[i][6])/10;
attackdata=((f_sin[mob[i][36]*32])>>8);

zlPush();
zlTranslate(mob[i][1],mob[i][3],mob[i][2]);
zlRotatey(mob[i][7]);
zlColor4x(r,g,b,255);
zlBindTexture(108);
scale=65536*3/4;
zlScale(scale,scale,scale);
zlTranslate(0,16384*3-8192,0);

idle=f_sin[mcount*11%4096]/600;
bone[0][0]=-mob[i][9]/5+flydata;

if (mob[i][11])
bone[0][2]=-walkdata/10; else bone[0][2]=-flydata;

bone[0][0]+=attackdata*2;

if (mob[i][42]>0) bone[0][0]+=256;


if (flydata<0) flydata=-flydata;

zlRotatez(bone[0][0]);
zlRotatex(bone[0][2]);

rendermobbody();

bone[1][0]=mob[i][12]-bone[0][0];
bone[1][1]=mob[i][13]+idle;

zlPush();
zlTranslate(0,48000,0);
zlRotatez(bone[1][0]);
zlRotatey(bone[1][1]);

scale=65536*3/4;
zlScale(scale,scale,scale);
rendermobhead();
zlBlend(1);
zlColor4x(255,255,255,255-(r+g+b)/3);
zlBeginQuads();

//eyes
zlTexCoord2x(10*4096,11*4096);zlVertex3x(-16584,32768-4096,16584);
zlTexCoord2x(10*4096,12*4096);zlVertex3x(-16584,16384-4096,16584);
zlTexCoord2x( 8*4096,12*4096);zlVertex3x(-16584,16384-4096,-16584);
zlTexCoord2x( 8*4096,11*4096);zlVertex3x(-16584,32768-4096,-16584);
zlEndQuads();
zlPop();
zlBlend(0);
zlColor4x(r,g,b,255);

bone[2][0]=-1024-walkdata/4;
bone[2][2]=0;

if (mob[i][36])
{
bone[2][0]+=(((-1810-bone[2][0])*attackdata)>>8);
bone[2][2]+=(((100-bone[2][2])*attackdata)>>8);
}

zlPush();
zlTranslate(0,40000,25000);
zlRotatez(bone[2][0]);
zlRotatex(bone[2][2]);
rendermoblhand();
zlPop();
bone[3][0]=-1024-walkdata/4;
bone[3][2]=0;
if (mob[i][36])
{
bone[3][0]+=(((-1810-bone[3][0])*attackdata)>>8);
bone[3][2]+=(((100-bone[3][2])*attackdata)>>8);
}

zlPush();
zlTranslate(0,40000,-25000);
zlRotatez(bone[3][0]);
zlRotatex(bone[3][2]);
rendermobrhand();
zlPop();
bone[4][0]=-walkdata;
bone[4][2]=-flydata;
zlPush();
zlTranslate(400,8192,8292);
zlRotatez(bone[4][0]);
zlRotatex(bone[4][2]);
rendermoblleg();
zlPop();

bone[5][0]=walkdata;
bone[5][2]=flydata;
zlPush();
zlTranslate(400,8192,-8292);
zlRotatez(bone[5][0]);
zlRotatex(bone[5][2]);
rendermobrleg();
zlPop();

zlPop();

}//zombie

void  drawspritemob(u8 i,u8 textid)
{
s32 tx,ty,t,ii;
zlPush();
zlTranslate(mob[i][1],mob[i][3],mob[i][2]);
zlRotatey(-camera[4]);
zlColor4x(r,g,b,255);
zlBindTexture(textid);
tx=0;
ty=0;
t=65536;
if (mob[i][30]==AI_ATTACK) ii=mcount>>3; else ii=mcount>>4;
if (ii%2==0) tx=32768;
if (ii/2%2==1) ty=32768;
zlBeginQuads();
zlTexCoord2x(tx,ty);zlVertex3x(-t,2*t,0);
zlTexCoord2x(tx+32768,ty);zlVertex3x(t,2*t,0);
zlTexCoord2x(tx+32768,ty+32768);zlVertex3x(t,0,0);
zlTexCoord2x(tx,ty+32768);zlVertex3x(-t,0,0);
zlEndQuads();

zlPop();
}


void drawmob(unsigned char i)
{
u8 drawflag=0;

if (isinlight(mob[i][1],mob[i][3]+25000,mob[i][2]))
{r=lightg[3];g=lightg[4];b=lightg[5];}
else
{r=lightg[0];g=lightg[1];b=lightg[2];}

iii_index=i;

//if (i==mobcontrol)



lcuberead(mob[i][1],mob[i][2],mob[i][3]);
r+=lcuber[0];
g+=lcuber[1];
b+=lcuber[2];
if (r>255) r=255;
if (g>255) g=255;
if (b>255) b=255;

mob[i][33]+=((r-mob[i][33])>>3);
mob[i][34]+=((g-mob[i][34])>>3);
mob[i][35]+=((b-mob[i][35])>>3);

mob[i][28]=mob[i][33]+mob[i][34]+mob[i][35];

r=mob[i][33];
g=mob[i][34];
b=mob[i][35];


x=mob[i][1];
y=mob[i][2];
z=mob[i][3];

range=viszscreen(x,z,y);
ddx=visxscreen(x,z,y);
if (ddx<0) ddx=-ddx;

ddx=ddx*6;
ddx=ddx>>3;mob[i][41]=0;


if (ddx<range+62000)
if (range>00000)
if (range<65536*8)
drawflag=1;
if (i==mobcontrol) if (firstperson>0) drawflag=0;

if (drawflag)
{
mob[i][41]=1;//WAS DRAWN
mcount=mob[i][19];
cx=x>>16;
cy=y>>16;
cz=z>>16;

while ((cz>1)&(mp[cx][cy][cz-1][0]==0)) cz--;
if (cz==1)
if (mp[cx][cy][0][0]==0) cz--;
z=cz*65536+1000+20*i;


if (playmode!=ZPM_ZVERYLE | i==mobcontrol)
if (camera[1]>z)
if (range<65536*4)
{
if (range<65536*3)
newblendsprite(0,255,x,z,y);
else
newblendsprite(0,255-(range-3*65536)/256,x,z,y);

}

switch (mob[i][10])
{
case 0:if (playmode==ZPM_AAA)drawhero(i);break;

case 1:drawneko(i);break;
case 2:drawslime(i);break;
case 3:drawsoldier(i);break;
case 4:drawzombie(i);break;
case 5:drawghoul(i);break;
case 6:drawscientist(i);break;
case 7:drawraptor(i);break;
case 8:drawdoctorzombie(i);break;

case 9:drawspritemob(i,176);break;
case 10:drawspritemob(i,177);break;
case 11:drawspritemob(i,178);break;
case 12:drawspritemob(i,179);break;

}


}
}
