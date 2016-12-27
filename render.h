extern void corerenderreset(void);
extern void corerenderrender(void);

extern void zlClrScr(void);
extern void zlClrDepth(void);
extern void zlTranslate(signed long x,signed long y,signed long z);
extern void zlRotatex(signed long x);
extern void zlRotatey(signed long y);
extern void zlRotatez(signed long z);
extern void zlScale(signed long x,signed long y,signed long z);
extern void zlFogParam(signed long fogstart,signed long fogend);
extern void zlFogColor(unsigned char r,unsigned char g,unsigned char b);
extern void zlRender(unsigned long first,unsigned long pcount);
extern void zlScreen(signed long x,signed long y,signed long zoom);
extern void zlPush(void);
extern void zlPop(void);
extern void zlFog(unsigned char value);
extern void zlDepthTest(unsigned char value);
extern void zlBlend(unsigned char value);


extern void zlBeginQuads(void);
extern void zlBindTexture(unsigned char i);
extern void zlForceBindTexture(unsigned char i);
extern void zlForceRender(unsigned short i_start,unsigned short i_end);

extern void zlColor4x(unsigned char r,unsigned char g,unsigned char b,unsigned char a);
extern void zlTexCoord2x(signed long x,signed long y);
extern void zlVertex3x(signed long x,signed long y,signed long z);
extern void zlEndQuads(void);

extern void zlRenderText(void);

extern void zlRenderScreen(unsigned char index);
extern void zlRenderQuad(void);
extern void zlDrawTransmask(unsigned char r,unsigned char g,unsigned char b);

