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
	JNIEnv *javaEnviron = SDL_AndroidGetJNIEnv();
	if (javaEnviron != NULL) {
		jclass clazz = (*javaEnviron)->FindClass(javaEnviron, "ru/exlmoto/aaaa/AAAAActivity");
		if (clazz == 0) {
			TO_DEBUG_LOG("Error JNI: Class ru/exlmoto/aaaa/AAAAActivity not found!");
			return;
		}

		jmethodID methodId = (*javaEnviron)->GetStaticMethodID(javaEnviron, clazz, "doVibrate", "(I)V");
		if (methodId == 0) {
			LOGI("Error JNI: methodId is 0, method doVibrate (I)V not found!");
			return;
		}

		// Call Java-method
		(*javaEnviron)->CallStaticVoidMethod(javaEnviron, clazz, methodId, (jint)duration);

		// Delete Ref
		(*javaEnviron)->DeleteLocalRef(javaEnviron, clazz);
	}
}

char *getObbMountedPath() {
	JNIEnv *javaEnviron = SDL_AndroidGetJNIEnv();
	if (javaEnviron != NULL) {
		jclass clazz = (*javaEnviron)->FindClass(javaEnviron, "ru/exlmoto/aaaa/AAAALauncherActivity");
		if (clazz == 0) {
			TO_DEBUG_LOG("Error JNI: Class ru/exlmoto/aaaa/AAAALauncherActivity not found!");
			return NULL;
		}

		// Get Field ID
		jfieldID fieldID = (*javaEnviron)->GetStaticFieldID(javaEnviron, clazz, "obbMountedPath", "Ljava/lang/String;");
		if (fieldID == 0) {
			TO_DEBUG_LOG("Error JNI: fieldID is 0, field obbMountedPath String not found!");
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
