#ifndef ANDROID_EXTRAS_H

extern void doVibrateFromJNI(int duration);
extern char *getObbMountedPath();
extern void readJavaConfigurationFromJni();
extern void writeJavaConfigurationFromJni();
extern void readOtherJavaSettingsFromJNI();

#endif // ANDROID_EXTRAS_H
