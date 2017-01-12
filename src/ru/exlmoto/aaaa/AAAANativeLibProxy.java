package ru.exlmoto.aaaa;

public class AAAANativeLibProxy {
	// Load native library
	static {
		System.loadLibrary("AAAA-Engine");
	}

	public native static void AAAANativeInit();
	public native static void AAAANativeDeinit();

	public native static void AAAANativeSurfaceChanged(int width, int height);
	public native static void AAANativeDrawStep();

	public native static void AAANativeKeyDown(int keycode);
	public native static void AAANativeKeyUp(int keycode);

	//public native static void SpoutNativeKeyDown(int keyCode);
	//public native static void SpoutNativeKeyUp(int keyCode);

	//public native static void SpoutFilter(boolean filterGLES);

	//public native static void SpoutNativePushScore(int height, int score);

	//public native static boolean SpoutVibrate();

	//public native static void SpoutSetSound(boolean sound);

	//public native static void SpoutSetColor(boolean color);
	//public native static void SpoutSetTail(boolean tail);

	//public native static void SpoutSet3DCube(boolean cube);

	//public native static int SpoutGetScoreScores();
	//public native static int SpoutGetScoreHeight();

	//public native static void SpoutDisplayOffsetX(int offset_x);
	//public native static void SpoutDisplayOffsetY(int offset_y);

	public native static void SpoutInitilizeGlobalJavaEnvPointer();
}
