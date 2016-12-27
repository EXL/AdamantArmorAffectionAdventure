//system

#ifdef PC32
#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include <GL/gl.h>
#endif


#ifdef GP2XCAANOO
#include "GLES/gl.h"
#include "GLES/egl.h"
#include "GLES/glext.h"
#endif
#ifdef GP2XWIZ
#include "OpenGLES/gl.h"
#include "OpenGLES/egl.h"
#include "OpenGLES/glext.h"
#endif

//
#include "vars.h"

u8 lasttexture;

void corerenderreset(void)
{
meshcount=0;
lasttexture=255;
glViewport(0,0,screenwidth,screenheight);
glEnable(GL_TEXTURE_2D);
glEnable(GL_ALPHA_TEST);

}

GLfloat fog_color[4];



void RenderMeshii(u32 istart,u32 icount)
{
u32 kt,poly,polyneed;
u8 mytexture;

poly=istart/3;
polyneed=icount/3;

while (polyneed>0)
{
kt=1;mytexture=meshtid[poly];

while ((kt<polyneed)&(meshtid[poly+kt]==mytexture)) kt++;
if (lasttexture!=mytexture) {glBindTexture(GL_TEXTURE_2D,zc_texture[mytexture]);lasttexture=mytexture;}
glDrawArrays(GL_TRIANGLES,poly*3,kt*3);
polyneed-=kt;
poly+=kt;

}
}

void corerenderrender(void)
{



//corerenderprocess();
#ifdef PC32
/*
glAccum(GL_MULT,0.5);
glAccum(GL_ACCUM,0.5);
glAccum(GL_RETURN,1.0);
*/
#endif
}

///////////////////////

void zlClrScr(void)
{
glClearColor(fog_color[0],fog_color[1],fog_color[2],fog_color[3]);
glClear(GL_COLOR_BUFFER_BIT);
}

void zlClrDepth(void)
{glClear(GL_DEPTH_BUFFER_BIT);}

void zlTranslate(signed long x,signed long y,signed long z)
{
#ifdef GP2X
glTranslatex(x,y,z);
#endif
#ifdef PC32
glTranslatef(x/65536.0,y/65536.0,z/65536.0);
#endif
}
void zlRotatex(signed long x)
{
#ifdef GP2X
glRotatex(x*5760,65536,0,0);
#endif
#ifdef PC32
glRotatef(x/11.37778,1.0,0.0,0.0);
#endif
}
void zlRotatey(signed long y)
{
#ifdef GP2X
glRotatex(y*5760,0,65536,0);
#endif
#ifdef PC32
glRotatef(y/11.37778,0.0,1.0,0.0);
#endif
}
void zlRotatez(signed long z)
{
#ifdef GP2X
glRotatex(z*5760,0,0,65536);
#endif
#ifdef PC32
glRotatef(z/11.37778,0.0,0.0,1.0);
#endif
}
void zlScale(signed long x,signed long y,signed long z)
{
#ifdef GP2X
glScalex(x,y,z);
#endif
#ifdef PC32
glScalef(x/65536.0,y/65536.0,z/65536.0);
#endif
}
void zlFogParam(signed long fogstart,signed long fogend)
{
#ifdef PC32
glFogf(GL_FOG_START,fogstart/65536.0f);
glFogf(GL_FOG_END,fogend/65536.0f);
#endif
#ifdef GP2X
glFogx(GL_FOG_START,fogstart);
glFogx(GL_FOG_END,fogend);
#endif
fog_end=fogend;
}
void zlFogColor(unsigned char r,unsigned char g,unsigned char b)
{
fog_color[0]=r/255.0;
fog_color[1]=g/255.0;
fog_color[2]=b/255.0;
fog_color[3]=1.0;
glFogfv(GL_FOG_COLOR,fog_color);

}
void zlRender(unsigned long first,unsigned long pcount)
{
//TO DO OPTIMIZE

#ifdef PC32
u32 i;
for (i=0;i<pcount*3;i++) mesh[first*3+i]=mesh[first*3+i]/65536.0;
for (i=0;i<pcount*2;i++) mesht[first*2+i]=mesht[first*2+i]/65536.0;
#endif

RenderMeshii(first,pcount);
}

void zlScreen(signed long x,signed long y,signed long zoom)
{
#ifdef GP2X
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glFrustumx(-x,x,-y,y,zoom,fog_end);
glMatrixMode(GL_MODELVIEW);
#endif
#ifdef PC32
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glFrustum(-x/65536.0,x/65536.0,-y/65536.0,y/65536.0,zoom/65536.0,fog_end/65536.0);
glMatrixMode(GL_MODELVIEW);
#endif
}
extern void zlPush(void)
{glPushMatrix();}

extern void zlPop(void)
{glPopMatrix();}

extern void zlFog(unsigned char value)
{
if (value==1) glEnable(GL_FOG); else glDisable(GL_FOG);
}
extern void zlDepthTest(unsigned char value)
{
if (value==1) glEnable(GL_DEPTH_TEST); else glDisable(GL_DEPTH_TEST);
}
extern void zlBlend(unsigned char value)
{
if (value==1)
{
glEnable(GL_BLEND);

#ifdef GP2X
glAlphaFuncx(GL_GREATER,65);
#endif
#ifdef PC32
glAlphaFunc(GL_GREATER,0.01f);
#endif
}
else
{
glDisable(GL_BLEND);
#ifdef GP2X
glAlphaFuncx(GL_GREATER,31728);
#endif
#ifdef PC32
glAlphaFunc(GL_GREATER,0.50f);
#endif
}
}



s32 zlr_tx,zlr_ty;
u32 zlr_mi,zlr_ci,zlr_ti,zlr_tid,zlr_count,zlr_texture;
u8 zlr_r,zlr_g,zlr_b,zlr_a;

void zlBeginQuads(void)
{
zlr_count=0;
zlr_mi=meshcount*3;
zlr_ci=meshcount*4;
zlr_ti=meshcount*2;
zlr_tid=meshcount/3;
}
void zlBindTexture(unsigned char i)
{
zlr_texture=i;
}

void zlForceBindTexture(unsigned char i)
{
glBindTexture(GL_TEXTURE_2D,zc_texture[i]);
}

void zlColor4x(unsigned char r,unsigned char g,unsigned char b,unsigned char a)
{
zlr_r=r;
zlr_g=g;
zlr_b=b;
zlr_a=a;
}
void zlTexCoord2x(signed long x,signed long y)
{
zlr_tx=x;
zlr_ty=y;
}
void zlVertex3x(signed long x,signed long y,signed long z)
{
mesh[zlr_mi++]=x;
mesh[zlr_mi++]=y;
mesh[zlr_mi++]=z;

meshc[zlr_ci++]=zlr_r;
meshc[zlr_ci++]=zlr_g;
meshc[zlr_ci++]=zlr_b;
meshc[zlr_ci++]=zlr_a;

mesht[zlr_ti++]=zlr_tx;
mesht[zlr_ti++]=zlr_ty;


if ((zlr_count&3)==2)
{
mesh[zlr_mi]=mesh[zlr_mi-3];zlr_mi++;
mesh[zlr_mi]=mesh[zlr_mi-3];zlr_mi++;
mesh[zlr_mi]=mesh[zlr_mi-3];zlr_mi++;

mesh[zlr_mi]=mesh[zlr_mi-12];zlr_mi++;
mesh[zlr_mi]=mesh[zlr_mi-12];zlr_mi++;
mesh[zlr_mi]=mesh[zlr_mi-12];zlr_mi++;

meshc[zlr_ci]=meshc[zlr_ci-4];zlr_ci++;
meshc[zlr_ci]=meshc[zlr_ci-4];zlr_ci++;
meshc[zlr_ci]=meshc[zlr_ci-4];zlr_ci++;
meshc[zlr_ci]=meshc[zlr_ci-4];zlr_ci++;

meshc[zlr_ci]=meshc[zlr_ci-16];zlr_ci++;
meshc[zlr_ci]=meshc[zlr_ci-16];zlr_ci++;
meshc[zlr_ci]=meshc[zlr_ci-16];zlr_ci++;
meshc[zlr_ci]=meshc[zlr_ci-16];zlr_ci++;

mesht[zlr_ti]=mesht[zlr_ti-2];zlr_ti++;
mesht[zlr_ti]=mesht[zlr_ti-2];zlr_ti++;
mesht[zlr_ti]=mesht[zlr_ti-8];zlr_ti++;
mesht[zlr_ti]=mesht[zlr_ti-8];zlr_ti++;

meshtid[zlr_tid++]=zlr_texture;
meshtid[zlr_tid++]=zlr_texture;

}

zlr_count++;
}
void zlEndQuads(void)
{
zlRender(meshcount,(zlr_count/4)*6);
meshcount+=(zlr_count/4)*6;
}

s32 if_tx=65536/16,if_ty=-65536/4;
void zlRenderText(void)
{
u8 i,c;
s32 ttx,tty,xx;
zlBindTexture(8);
zlBeginQuads();
xx=0;
for (i=0;i<l_text;i++)
{
c=s_text[i];
if (c>33)
{
c=c-32;
ttx=(c % 16)*65536/16;
tty=((c/16)+1)*65536/4;

zlTexCoord2x(ttx,tty);zlVertex3x(xx,0,0);
zlTexCoord2x(ttx+if_tx,tty);zlVertex3x(xx+65536,0,0);
zlTexCoord2x(ttx+if_tx,tty+if_ty);zlVertex3x(xx+65536,65536,0);
zlTexCoord2x(ttx,tty+if_ty);zlVertex3x(xx,65536,0);

}
xx+=65536;

//zlTranslate(65536,0,0);
}
zlEndQuads();
}

void zlRenderScreen(unsigned char index)
{
s32 x,y,wwx,wwy;

wwx=65536*320/384;
wwy=65536*256/240;
for (x=0;x<3;x++)
for (y=0;y<2;y++)
{
zlBindTexture(index+x+y*3);
zlBeginQuads();
zlTexCoord2x(0,0);
zlVertex3x(-65536+(x)*wwx,65536-(y)*wwy,0);
zlTexCoord2x(65535,0);
zlVertex3x(-65536+(x+1)*wwx,65536-(y)*wwy,0);

zlTexCoord2x(65535,65535);
zlVertex3x(-65536+(x+1)*wwx,65536-(y+1)*wwy,0);
zlTexCoord2x(0,65535);
zlVertex3x(-65536+(x)*wwx,65536-(y+1)*wwy,0);

zlEndQuads();
}
}

void zlRenderQuad(void)
{
zlBeginQuads();
zlTexCoord2x(0,0);zlVertex3x(-65536,65536,0);
zlTexCoord2x(65535,0);zlVertex3x(65536,65536,0);
zlTexCoord2x(65535,65535);zlVertex3x(65536,-65536,0);
zlTexCoord2x(0,65535);zlVertex3x(-65536,-65536,0);
zlEndQuads();

}

s32 rr=0,gg=0,bb=0;
void zlDrawTransmask(unsigned char r,unsigned char g,unsigned char b)
{
s32 a;
s32 tx,ty;
rr=r+(rr-r)*15/16;
gg=g+(gg-g)*15/16;
bb=b+(bb-b)*15/16;
a=gameswitchdelay;
if (a<0) a=100+a;
a=a*42/20;
if (a>255) a=255;

ty=((count/6)&255)*256*16;;
tx=(count&255)*256*16;

zlBlend(1);
zlColor4x(rr,gg,bb,a);
zlBindTexture(200);
zlBeginQuads();
zlTexCoord2x(tx,ty);zlVertex3x(-65536,65536,0);
zlTexCoord2x(tx+65535+32768,ty);zlVertex3x(65536,65536,0);
zlTexCoord2x(tx+65535+32768,ty+65535);zlVertex3x(65536,-65536,0);
zlTexCoord2x(tx,ty+65535);zlVertex3x(-65536,-65536,0);
zlEndQuads();
zlBlend(0);
}

void zlForceRender(unsigned short i_start,unsigned short i_end)
{
glDrawArrays(GL_TRIANGLES,i_start,i_end);
}
