/*
 * AAAANativeLibProxy.cpp
 *
 *  Created on: Jan 12, 2017
 *      Author: exl
 */

#include "ru_exlmoto_aaaa_AAAANativeLibProxy.h" // JNI Header

extern "C" {
#include "src/AAAA-Engine/vars.h"
#include "src/AAAA-Engine/zcore.h"
#include "src/AAAA-Engine/zresm.h"
}

static int appRunning = 0;

// Init
void JNICALL Java_ru_exlmoto_aaaa_AAAANativeLibProxy_AAAANativeInit
  (JNIEnv *env, jclass c) {
	if (appRunning == 0) {

		zresminit();
		zcoreinit();

		appRunning = 1;
	}
}

// Deinit
void JNICALL Java_ru_exlmoto_aaaa_AAAANativeLibProxy_AAAANativeDeinit
  (JNIEnv *env, jclass c) {
	if (appRunning == 1) {

		zresmdown();
		zcoredown();

		appRunning = 0;
	}
}

// Surface Changed
void JNICALL Java_ru_exlmoto_aaaa_AAAANativeLibProxy_AAAANativeSurfaceChanged
  (JNIEnv *env, jclass c, jint w, jint h) {
	if (appRunning == 1) {
		screenwidth = w;
		screenheight = h;
	}
}

// Draw step
void JNICALL Java_ru_exlmoto_aaaa_AAAANativeLibProxy_AAANativeDrawStep
  (JNIEnv *env, jclass c) {
	if (appRunning == 1) {
		zcoreloop();
	}
}

void JNICALL Java_ru_exlmoto_aaaa_AAAANativeLibProxy_SpoutInitilizeGlobalJavaEnvPointer
  (JNIEnv *env, jclass c) {

}
