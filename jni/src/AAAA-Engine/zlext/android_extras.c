#include "../../../ru_exlmoto_aaaa_AAAANativeLibProxy.h"

#include "../vars.h"

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
