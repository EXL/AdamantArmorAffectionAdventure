#ifndef ZCSOUND_H
#define ZCSOUND_H

extern void zcsoundstep(void);

extern void zcplaysound(unsigned char index);
extern void zcplaysound3d(unsigned char index, unsigned char ssize, signed long xx, signed long yy, signed long zz);

extern void zcinitsound(void);

#endif // ZCSOUND_H
