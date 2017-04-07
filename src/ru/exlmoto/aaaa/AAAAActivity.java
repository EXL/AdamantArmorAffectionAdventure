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
		// AAAASettings.configuration[10] is vibro haptics in game config
		// 30 is default scale for vibration
		if ((fromJNI == 1) && (AAAASettings.configuration[10] == 1)) {
			m_vibrator.vibrate(duration + (AAAASettings.vibroScale - 30));
		}

		if ((fromJNI == 0) && (AAAASettings.touchVibration)) {
			m_vibrator.vibrate(duration + (AAAASettings.vibroScale - 30));
		}
	}

	// JNI-method
	public static void writeConfiguration(int[] cfg) {
		for (int i = 0; i < AAAASettings.CFG_CNT; ++i) {
			AAAASettings.configuration[i] = cfg[i];
		}
		AAAALauncherActivity.writeConfig();
	}
}
