#ifndef WLIGHT_H
#define WLIGHT_H

extern void newlight(signed long x, signed long y, signed long z, unsigned long lightdata);

extern unsigned char isinlight(signed long x, signed long y, signed long z);

extern void clearlightcube(void);

extern void lcuberead(signed long x, signed long y, signed long z);

#endif // WLIGHT_H
