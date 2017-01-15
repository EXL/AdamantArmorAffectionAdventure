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
