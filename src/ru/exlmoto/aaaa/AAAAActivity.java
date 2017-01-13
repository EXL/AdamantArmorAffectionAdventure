package ru.exlmoto.aaaa;

import org.libsdl.app.SDLActivity;

import android.content.Context;
import android.os.Bundle;
import android.os.Vibrator;
import android.util.Log;
import android.view.ViewGroup.LayoutParams;
import android.widget.LinearLayout;

public class AAAAActivity extends SDLActivity {

	private static final String APP_TAG = "AAAA_App";

	private static Vibrator m_vibrator = null;

	private AAAAModernInputView aaaaModernInputView = null;

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		toDebugLog("Start SDL Activity from AAAAActivity");

		m_vibrator = (Vibrator)getSystemService(Context.VIBRATOR_SERVICE);

		aaaaModernInputView = new AAAAModernInputView(this);

		addContentView(aaaaModernInputView,
				new LinearLayout.LayoutParams(
						LayoutParams.MATCH_PARENT,
						LayoutParams.MATCH_PARENT));
	}

	public static void toDebugLog(String debugMessage) {
		Log.d(APP_TAG, "=== " + debugMessage);
	}

	// JNI-method
	public static void doVibrate(int duration) {
		if (true) { // AAAASettings
			m_vibrator.vibrate(duration);
		}
	}
}
