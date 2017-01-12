package ru.exlmoto.aaaa;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.os.SystemClock;
import android.view.SurfaceHolder;

public class AAAANativeGLSurface extends GLSurfaceView
	implements android.opengl.GLSurfaceView.Renderer {

	private static final int FPS_RATE = 60;
	private long m_lastFrame = 0;

	public AAAANativeGLSurface(Context context) {
		super(context);
		setRenderer(this);

		// We wants events
		//setFocusable(true);
		//setFocusableInTouchMode(true);
		//requestFocus();

		// We wants keep on screen
		setKeepScreenOn(true);
	}

	@Override
	public void onSurfaceCreated(GL10 gl, EGLConfig config) {
		AAAANativeLibProxy.AAAANativeInit();
	}

	@Override
	public void onSurfaceChanged(GL10 gl, int width, int height) {
		AAAANativeLibProxy.AAAANativeSurfaceChanged(width, height);
	}

	@Override
	public void onDrawFrame(GL10 gl) {
		// TODO Auto-generated method stub
		long currentFrame = SystemClock.uptimeMillis();
		long diff = currentFrame - m_lastFrame;
		m_lastFrame = currentFrame;

		// Draw step
		AAAANativeLibProxy.AAANativeDrawStep();

		try {
			long sleepfor = (1000 / FPS_RATE) - diff;
			if (sleepfor > 0) {
//				SpoutActivity.toDebug("Sleep now: " + sleepfor);
				Thread.sleep(sleepfor);
			}
		} catch (InterruptedException ex) { }
	}

	@Override
	public void surfaceDestroyed(SurfaceHolder holder) {
		super.surfaceDestroyed(holder);
		AAAANativeLibProxy.AAAANativeDeinit();
		System.exit(0);
	}
}
