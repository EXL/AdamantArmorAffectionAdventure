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

	//private static Vibrator m_vibrator;

	private AAAAInputView aaaaInputView = null;

	public static void toDebugLog(String debugMessage) {
		Log.d(APP_TAG, "=== " + debugMessage);
	}

	@Override
	public void onCreate(Bundle savedInstanceState) {
		toDebugLog("Start SDL Activity from AAAAActivity");
		super.onCreate(savedInstanceState);

		//toDebugLog("Setting Vibration");
		//m_vibrator = (Vibrator)getSystemService(Context.VIBRATOR_SERVICE);

		aaaaInputView = new AAAAInputView(this);

		addContentView(aaaaInputView,
				new LinearLayout.LayoutParams(
						LayoutParams.MATCH_PARENT,
						LayoutParams.MATCH_PARENT));
	}
}
