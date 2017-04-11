Adamant Armor Affection Adventure
=================================

Adamant Armor Affection Adventure by quasist and Don Miguel is a 3D stealth-action platform game participated in the [RIOT Tag-Team Coding Competition](http://www.riotdigital.com/ttcc2011/?page=Blog) event in 2011 and took the second place. It was originally released on the gaming console GP2X Caanoo and GP2X Wiz, and later ported to Pandora and GCW Zero.

![Adamant Armor Affection Adventure running on Motorola Droid 2](https://raw.github.com/EXL/AdamantArmorAffectionAdventure/master/images/aaaa_motorola_droid_2.jpg)

This is my port of Adamant Armor Affection Adventure to Android OS with using SDL2 and SDL2_mixer libraries and rendering the videocontext of the game with using OpenGL ES. I added simple touch controls and some other improvements to the game engine.

![Adamant Armor Affection Adventure Android Screen 1](https://raw.github.com/EXL/AdamantArmorAffectionAdventure/master/images/aaaa_android_screen1.jpg)

![Adamant Armor Affection Adventure Android Screen 2](https://raw.github.com/EXL/AdamantArmorAffectionAdventure/master/images/aaaa_android_screen2.jpg)

![Adamant Armor Affection Adventure Android Screen 3](https://raw.github.com/EXL/AdamantArmorAffectionAdventure/master/images/aaaa_android_screen3.jpg)

[Adamant Armor Affection Adventure port on Motorola Photon Q video on YouTube](http://youtu.be/vnNax1uNLfo)

## Build instructions

For example, GNU/Linux:

* Install the latest [Android SDK](https://developer.android.com/sdk/) and [Android NDK](https://developer.android.com/ndk/);

* Clone repository into deploy directory;

```sh
cd ~/Deploy/
git clone https://github.com/EXL/AdamantArmorAffectionAdventure AdamantArmorAffectionAdventureAndroid
```

* Edit "project.properties" file and set the installed Android API SDK version here, for example:

```sh
# Project target.
target=android-23
```

* Build the APK-package into deploy directory;

```sh
cd ~/Deploy/AdamantArmorAffectionAdventureAndroid/
/opt/android/android-sdk-linux/tools/android update project -n AdamantArmorAffectionAdventure -p .
/opt/android/android-ndk-r10d/ndk-build V=1
/opt/android/apache-ant-1.9.4/bin/ant debug
```

* Install AdamantArmorAffectionAdventure APK-package on your Android device via adb;

```sh
cd ~/Deploy/AdamantArmorAffectionAdventureAndroid/
/opt/android/android-sdk-linux/platform-tools/adb install -r bin/AdamantArmorAffectionAdventure-debug.apk
```

* Run and enjoy!

You can also import this project in your favorite IDE: Eclipse or Android Studio and build the APK-package by using these programs.

## More information

Please read [Porting Guide (In Russian)](http://exlmoto.ru/adamant-armor-affection-adventure-droid) for more info about porting AdamantArmorAffectionAdventure to Android OS.
