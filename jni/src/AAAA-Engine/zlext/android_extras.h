#ifndef ANDROID_EXTRAS_H

extern void doVibrateFromJNI(int duration);
extern char *getObbMountedPath();
extern void readJavaConfigurationFromJNI();
extern void writeJavaConfigurationFromJNI();
extern void readOtherJavaSettingsFromJNI();

#endif // ANDROID_EXTRAS_H
