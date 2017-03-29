package ru.exlmoto.aaaa;

import org.libsdl.app.SDLActivity;

import android.content.Context;
import android.os.Bundle;
import android.os.Vibrator;
import android.util.Log;
import android.view.ViewGroup.LayoutParams;
import android.widget.LinearLayout;

import ru.exlmoto.aaaa.AAAALauncherActivity.AAAASettings;

public class AAAAActivity extends SDLActivity {

	private static final String APP_TAG = "AAAA_App";

	private static Vibrator m_vibrator = null;

	private AAAAModernInputView aaaaModernInputView = null;

	@SuppressWarnings("deprecation")
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		toDebugLog("Start SDL Activity from AAAAActivity");

		m_vibrator = (Vibrator)getSystemService(Context.VIBRATOR_SERVICE);

		if (AAAASettings.touchControls == AAAASettings.MODERN_TOUCH_CONTROLS) {
			aaaaModernInputView = new AAAAModernInputView(this);
			addContentView(aaaaModernInputView,
					new LinearLayout.LayoutParams(
							LayoutParams.MATCH_PARENT,
							LayoutParams.MATCH_PARENT));
		} else if (AAAASettings.touchControls == AAAASettings.OLD_TOUCH_CONTROLS) {
			LinearLayout ll = new LinearLayout(this);
			ll.setBackgroundDrawable(getResources().getDrawable(R.drawable.overlay_controls));
			addContentView(ll, new LinearLayout.LayoutParams(
					LayoutParams.MATCH_PARENT,
					LayoutParams.MATCH_PARENT));
		}
	}

	public static void toDebugLog(String debugMessage) {
		Log.d(APP_TAG, "=== " + debugMessage);
	}

	// JNI-method
	public static void doVibrate(int duration, int fromJNI) {
		// From JNI: 1 -- yes, 0 -- no
		// TODO: Delays?
		if ((fromJNI == 1) && (AAAASettings.configuration[10] == 1)) {
			// AAAASettings.configuration[10] -- Vibrohaptics
			m_vibrator.vibrate(duration);
		}

		if ((fromJNI == 0) && (AAAASettings.touchVibration)) {
			m_vibrator.vibrate(duration);
		}
	}

	// JNI-method
	public static void writeConfiguration(int[] cfg) {

		for (int i = 0; i < AAAASettings.CFG_CNT; ++i) {
			AAAAActivity.toDebugLog("" + cfg[i]);
		}

		for (int i = 0; i < AAAASettings.CFG_CNT; ++i) {
			AAAASettings.configuration[i] = cfg[i];
		}
		// TODO: Write settings
	}
}
