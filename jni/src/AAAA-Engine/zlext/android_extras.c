/************************************************************************************
** The MIT License (MIT)
**
** Copyright (c) 2017 EXL
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in all
** copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
** SOFTWARE.
************************************************************************************/

#include "../../../ru_exlmoto_aaaa_AAAANativeLibProxy.h" // JNI Header

#include "../vars.h"

#include "android_extras.h"

void JNICALL Java_ru_exlmoto_aaaa_AAAANativeLibProxy_AAAAJoystickButtonDown
	(JNIEnv *env, jclass c, jint keyCode)
{
	// TO_DEBUG_LOG("Pushed: %d\n", keyCode);
	tjoy_b[keyCode] = 1;
}

void JNICALL Java_ru_exlmoto_aaaa_AAAANativeLibProxy_AAAAJoystickButtonUp
	(JNIEnv *env, jclass c, jint keyCode)
{
	// TO_DEBUG_LOG("Released: %d\n", keyCode);
	tjoy_b[keyCode] = 0;
}

void doVibrateFromJNI(int duration) {
	if (javaEnviron != NULL) {
		jclass clazz = (*javaEnviron)->FindClass(javaEnviron, "ru/exlmoto/aaaa/AAAAActivity");
		if (clazz == 0) {
			TO_DEBUG_LOG("Error JNI: Class ru/exlmoto/aaaa/AAAAActivity not found!");
			return;
		}

		jmethodID methodId = (*javaEnviron)->GetStaticMethodID(javaEnviron, clazz, "doVibrate", "(II)V");
		if (methodId == 0) {
			TO_DEBUG_LOG("Error JNI: methodId is 0, method doVibrate (II)V not found!");
			return;
		}

		// Call Java-method
		(*javaEnviron)->CallStaticVoidMethod(javaEnviron, clazz, methodId, (jint)duration, 1);

		// Delete Ref
		(*javaEnviron)->DeleteLocalRef(javaEnviron, clazz);
	}
}

char *getObbMountedPath() {
	if (javaEnviron != NULL) {
		jclass clazz = (*javaEnviron)->FindClass(javaEnviron, "ru/exlmoto/aaaa/AAAALauncherActivity");
		if (clazz == 0) {
			TO_DEBUG_LOG("Error JNI: Class ru/exlmoto/aaaa/AAAALauncherActivity not found!");
			return NULL;
		}

		// Get Field ID
		jfieldID fieldID = (*javaEnviron)->GetStaticFieldID(javaEnviron, clazz, "obbMountedPath", "Ljava/lang/String;");
		if (fieldID == 0) {
			TO_DEBUG_LOG("Error JNI: fieldID is 0, field String obbMountedPath not found!");
			return NULL;
		}

		// Get String from Java and convert to char*
		jstring javaString = (*javaEnviron)->GetStaticObjectField(javaEnviron, clazz, fieldID);
		if (javaString == 0) {
			return NULL;
		}
		const char *nativeString = (*javaEnviron)->GetStringUTFChars(javaEnviron, javaString, 0);
		char *stringToAAAAEngine = strdup(nativeString);

		// Destroy string
		(*javaEnviron)->ReleaseStringUTFChars(javaEnviron, javaString, nativeString);

		// Delete Ref
		(*javaEnviron)->DeleteLocalRef(javaEnviron, clazz);

		// Return copy of string to Engine
		return stringToAAAAEngine;
	} else {
		return NULL;
	}
}

void readJavaConfigurationFromJNI() {
	if (javaEnviron != NULL) {
		jclass clazz = (*javaEnviron)->FindClass(javaEnviron, "ru/exlmoto/aaaa/AAAALauncherActivity$AAAASettings");
		if (clazz == 0) {
			TO_DEBUG_LOG("Error JNI: Class ru/exlmoto/aaaa/AAAALauncherActivity$AAAASettings not found!");
			return;
		}

		// Get configuration Field ID
		jfieldID fieldID = (*javaEnviron)->GetStaticFieldID(javaEnviron, clazz, "configuration", "[I");
		if (fieldID == 0) {
			TO_DEBUG_LOG("Error JNI: fieldID is 0, field int[] configuration not found!");
			return;
		}

		// Get array of integers
		jintArray intArray = (jintArray) (*javaEnviron)->GetStaticObjectField(javaEnviron, clazz, fieldID);
		if (intArray == 0) {
			TO_DEBUG_LOG("Error JNI: intArray is 0, field int[] configuration do not available!");
			return;
		}

		// http://docs.oracle.com/javase/7/docs/technotes/guides/jni/spec/functions.html
		// Get<PrimitiveType>ArrayElements Routines
		// If isCopy is not NULL, then *isCopy is set to JNI_TRUE if a copy is made;
		// or it is set to JNI_FALSE if no copy is made.
		jint *cfg_array = (*javaEnviron)->GetIntArrayElements(javaEnviron, intArray, 0);
		int i, size = sizeof(configdata) / sizeof(configdata[0]);
		for (i = 0; i < size; ++i) {
			configdata[i] = cfg_array[i];
		}

		// Destroy Int Array
		(*javaEnviron)->ReleaseIntArrayElements(javaEnviron, intArray, cfg_array, JNI_ABORT);

		// Delete Ref
		(*javaEnviron)->DeleteLocalRef(javaEnviron, clazz);
	}
}

void writeJavaConfigurationFromJNI() {
	if (javaEnviron != NULL) {
		jclass clazz = (*javaEnviron)->FindClass(javaEnviron, "ru/exlmoto/aaaa/AAAAActivity");
		if (clazz == 0) {
			TO_DEBUG_LOG("Error JNI: Class ru/exlmoto/aaaa/AAAAActivity not found!");
			return;
		}

		jmethodID methodId = (*javaEnviron)->GetStaticMethodID(javaEnviron, clazz, "writeConfiguration", "([I)V");
		if (methodId == 0) {
			TO_DEBUG_LOG("Error JNI: methodId is 0, method writeConfiguration ([I)V not found!");
			return;
		}

		// Create Int Array
		int i, size = sizeof(configdata) / sizeof(configdata[0]);
		jintArray cfg_array = (*javaEnviron)->NewIntArray(javaEnviron, size);

		// Copy Data from configdata to cfg_array
		jint *body_array = (*javaEnviron)->GetIntArrayElements(javaEnviron, cfg_array, 0);
		for (i = 0; i < size; ++i) {
			body_array[i] = configdata[i];
		}

		// Set Region Array
		// On Dalvik works without calling this function, but for ART it is necessary
		// Otherwise, the array will be reset to zeros
		(*javaEnviron)->SetIntArrayRegion(javaEnviron, cfg_array, 0, size, body_array);

		// Call Java-method
		(*javaEnviron)->CallStaticVoidMethod(javaEnviron, clazz, methodId, cfg_array);

		// Destroy Int Array
		(*javaEnviron)->ReleaseIntArrayElements(javaEnviron, cfg_array, body_array, 0);

		// Delete Ref
		(*javaEnviron)->DeleteLocalRef(javaEnviron, clazz);
	}
}

void readOtherJavaSettingsFromJNI() {
	if (javaEnviron != NULL) {
		jclass clazz = (*javaEnviron)->FindClass(javaEnviron, "ru/exlmoto/aaaa/AAAALauncherActivity$AAAASettings");
		if (clazz == 0) {
			TO_DEBUG_LOG("Error JNI: Class ru/exlmoto/aaaa/AAAALauncherActivity$AAAASettings not found!");
			return;
		}

		// Get frameLimit Field ID
		jfieldID fieldID = (*javaEnviron)->GetStaticFieldID(javaEnviron, clazz, "frameLimit", "Z");
		if (fieldID == 0) {
			TO_DEBUG_LOG("Error JNI: fieldID is 0, field boolean frameLimit not found!");
			return;
		}

		jboolean frameLimit = (*javaEnviron)->GetStaticBooleanField(javaEnviron, clazz, fieldID);
		frame_limit = (int)frameLimit;

		// Get AI Disable Field ID
		fieldID = (*javaEnviron)->GetStaticFieldID(javaEnviron, clazz, "aiDisable", "Z");
		if (fieldID == 0) {
			TO_DEBUG_LOG("Error JNI: fieldID is 0, field boolean aiDisable not found!");
			return;
		}

		jboolean aiDisable = (*javaEnviron)->GetStaticBooleanField(javaEnviron, clazz, fieldID);
		ai_attack_disable_cheat = (int)aiDisable;

		// Get showFps Field ID
		fieldID = (*javaEnviron)->GetStaticFieldID(javaEnviron, clazz, "showFps", "Z");
		if (fieldID == 0) {
			TO_DEBUG_LOG("Error JNI: fieldID is 0, field boolean showFps not found!");
			return;
		}

		jboolean showFps = (*javaEnviron)->GetStaticBooleanField(javaEnviron, clazz, fieldID);
		fpsdisplay = (int)showFps;

		// Get gSensorScale Field ID
		fieldID = (*javaEnviron)->GetStaticFieldID(javaEnviron, clazz, "gSensorScale", "I");
		if (fieldID == 0) {
			TO_DEBUG_LOG("Error JNI: fieldID is 0, field int gSensorScale not found!");
			return;
		}

		jint gSensorScale = (*javaEnviron)->GetStaticIntField(javaEnviron, clazz, fieldID);
		gsensor_scale = (int)gSensorScale;

		// Delete Ref
		(*javaEnviron)->DeleteLocalRef(javaEnviron, clazz);
	}
}
