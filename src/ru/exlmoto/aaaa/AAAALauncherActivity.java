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

import java.io.File;
import java.io.IOException;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.Dialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.res.ObbInfo;
import android.content.res.ObbScanner;
import android.os.Bundle;
import android.os.storage.OnObbStateChangeListener;
import android.os.storage.StorageManager;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.CompoundButton.OnCheckedChangeListener;
import android.widget.EditText;
import android.widget.RadioButton;
import android.widget.Toast;

public class AAAALauncherActivity extends Activity {

	private static final int AC_FILE_PICKER_CODE = 1;

	private static final int DIALOG_WRONG_HAPTIC = 0;
	private static final int DIALOG_WRONG_FRAMESKIP = 1;
	private static final int DIALOG_WRONG_GSENSOR = 2;
	private static final int DIALOG_QUESTION_OPEN_LEVELS = 3;
	private static final int DIALOG_QUESTION_RESET_SETTINGS = 4;

	public static class AAAASettings {

		public static final int CFG_CNT = 32;
		public static final int MODERN_TOUCH_CONTROLS = 0;
		public static final int OLD_TOUCH_CONTROLS = 1;
		public static final int NO_TOUCH_CONTROLS = 2;

		// GAME CONFIG
		public static int[] configuration = {
				1, 0, 0, 0, 0, 0, 1, 1, // 0-7: Menu Items
				128, 48,                // 8-9: Sound and Music Volume
				1, 1, 2, 1, 0, 0,       // 10-15: Vibrohaptics, G-Sensor, Frameskip, Noise, Reserve?, Reserve?
				99, 59, 199, 59, 199, 59, 199, 59, 199, 59, 199, 59, 199, 59, 199, 59 // 16-31: Levels and Time
		};

		// GAME SETTINGS
		public static int touchControls = MODERN_TOUCH_CONTROLS;
		public static boolean touchVibration = true;
		public static boolean frameLimit = false; // Access from JNI
		public static boolean aiDisable = false;  // Access from JNI
		public static boolean showFps = false;    // Access from JNI
		public static int gSensorScale = 1000;    // Access from JNI
		public static int vibroScale = 30;
		public static String obbSavedPath = "";
	}

	private boolean firstRun = false;

	private String obbFilePathName = "";
	// Unfortunately, the crypted OBB files do not work
	// private final String obbKey = "aaaa";
	@SuppressWarnings("unused")
	private ObbInfo mObbInfo = null;

	private EditText editTextObbPath = null;
	private EditText editTextHaptics = null;
	private EditText editTextGSensorScale = null;
	private EditText editTextFrameSkip = null;
	private CheckBox checkBoxSound = null;
	private CheckBox checkBoxMusic = null;
	private CheckBox checkBoxGSensor = null;
	private CheckBox checkBoxFilmGrain = null;
	private CheckBox checkBoxShowFps = null;
	private CheckBox checkBoxFramelimit = null;
	private CheckBox checkBoxVibrationOnTouch = null;
	private CheckBox checkBoxVibrationInGame = null;
	private CheckBox checkBoxDisableAiAttack = null;
	private RadioButton radioButtonModernTouchControls = null;
	private RadioButton radioButtonSimpleTouchControls = null;
	private RadioButton radioButtonNoTouchControls = null;

	private AlertDialog aboutDialog = null;

	// JNI-access
	public static String obbMountedPath = "";

	public static SharedPreferences mSharedPreferences = null;
	public StorageManager mStorageManager = null;
	AAAALauncherActivity aaaaLauncherActivity = this;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		if (mSharedPreferences == null) {
			mSharedPreferences = getSharedPreferences("ru.exlmoto.aaaa", MODE_PRIVATE);
		}

		// Check the first run
		if (mSharedPreferences.getBoolean("firstrun", true)) {
			// The first run, fill GUI layout with default values
			mSharedPreferences.edit().putBoolean("firstrun", false).commit();
			firstRun = true;
		} else {
			firstRun = false;
			// Read settings from Shared Preferences
			// Move to onResume()
			// readConfig();
			// readSettings();
		}

		mStorageManager = (StorageManager) getApplicationContext().getSystemService(STORAGE_SERVICE);

		initAboutDialog();

		setContentView(R.layout.aaaa_launcher);

		initWidgets();

		// Move to onResume()
		// fillWidgetsBySettings();

		checkBoxSound.setOnCheckedChangeListener(new OnCheckedChangeListener() {

			@Override
			public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
				AAAASettings.configuration[8] = (isChecked) ? 128 : 0;
			}
		});

		checkBoxMusic.setOnCheckedChangeListener(new OnCheckedChangeListener() {

			@Override
			public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
				AAAASettings.configuration[9] = (isChecked) ? 48 : 0;
			}
		});

		checkBoxGSensor.setOnCheckedChangeListener(new OnCheckedChangeListener() {

			@Override
			public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
				AAAASettings.configuration[11] = (isChecked) ? 1 : 0;
				if (!isChecked) {
					editTextGSensorScale.setText(String.valueOf(1000));
				}
				editTextGSensorScale.setEnabled(isChecked);
			}
		});

		checkBoxFilmGrain.setOnCheckedChangeListener(new OnCheckedChangeListener() {

			@Override
			public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
				AAAASettings.configuration[13] = (isChecked) ? 1 : 0;
			}
		});

		checkBoxShowFps.setOnCheckedChangeListener(new OnCheckedChangeListener() {

			@Override
			public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
				AAAASettings.showFps = isChecked;
			}
		});

		checkBoxFramelimit.setOnCheckedChangeListener(new OnCheckedChangeListener() {

			@Override
			public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
				AAAASettings.frameLimit = isChecked;
			}
		});

		radioButtonModernTouchControls.setOnCheckedChangeListener(new OnCheckedChangeListener() {

			@Override
			public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
				AAAASettings.touchControls = AAAASettings.MODERN_TOUCH_CONTROLS;
			}
		});

		radioButtonSimpleTouchControls.setOnCheckedChangeListener(new OnCheckedChangeListener() {

			@Override
			public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
				AAAASettings.touchControls = AAAASettings.OLD_TOUCH_CONTROLS;
			}
		});

		radioButtonNoTouchControls.setOnCheckedChangeListener(new OnCheckedChangeListener() {

			@Override
			public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
				AAAASettings.touchControls = AAAASettings.NO_TOUCH_CONTROLS;
			}
		});

		checkBoxVibrationOnTouch.setOnCheckedChangeListener(new OnCheckedChangeListener() {

			@Override
			public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
				AAAASettings.touchVibration = isChecked;
				if (!isChecked && !checkBoxVibrationInGame.isChecked()) {
					editTextHaptics.setText(String.valueOf(30));
					editTextHaptics.setEnabled(false);
				} else {
					editTextHaptics.setEnabled(true);
				}
			}
		});

		checkBoxVibrationInGame.setOnCheckedChangeListener(new OnCheckedChangeListener() {

			@Override
			public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
				AAAASettings.configuration[10] = (isChecked) ? 1 : 0;
				if (!isChecked && !checkBoxVibrationOnTouch.isChecked()) {
					editTextHaptics.setText(String.valueOf(30));
					editTextHaptics.setEnabled(false);
				} else {
					editTextHaptics.setEnabled(true);
				}
			}
		});

		checkBoxDisableAiAttack.setOnCheckedChangeListener(new OnCheckedChangeListener() {

			@Override
			public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
				AAAASettings.aiDisable = isChecked;
			}
		});

		Button buttonRun = (Button) findViewById(R.id.buttonRun);
		buttonRun.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View v) {
				if (testAllRanges()) {
					writeAll();

					checkObbMount();
				}
			}
		});

		Button buttonBrowse = (Button) findViewById(R.id.buttonObbBrowse);
		buttonBrowse.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View v) {
				runFilePicker();
			}
		});

		Button buttonResetAllSettings = (Button) findViewById(R.id.buttonResetSettings);
		buttonResetAllSettings.setOnClickListener(new OnClickListener() {

			@SuppressWarnings("deprecation")
			@Override
			public void onClick(View v) {
				showDialog(DIALOG_QUESTION_RESET_SETTINGS);
			}
		});

		Button buttonOpenAllChaptters = (Button) findViewById(R.id.buttonOpenAllChapters);
		buttonOpenAllChaptters.setOnClickListener(new OnClickListener() {

			@SuppressWarnings("deprecation")
			@Override
			public void onClick(View v) {
				showDialog(DIALOG_QUESTION_OPEN_LEVELS);
			}
		});

		Button buttonAbout = (Button) findViewById(R.id.buttonAbout);
		buttonAbout.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View v) {
				showMyDialog(aboutDialog);
			}
		});
	}

	@Override
	protected void onResume() {
		if (!firstRun) {
			readConfig();
			readSettings();
		}
		fillWidgetsBySettings();
		super.onResume();
	}

	@SuppressWarnings("deprecation")
	private boolean testAllRanges() {
		int haptics = Integer.parseInt(editTextHaptics.getEditableText().toString());
		int frameskip = Integer.parseInt(editTextFrameSkip.getEditableText().toString());
		int gsensor = Integer.parseInt(editTextGSensorScale.getEditableText().toString());
		if (haptics < 5 || haptics > 200) {
			showDialog(DIALOG_WRONG_HAPTIC);
			return false;
		}
		if (frameskip < 0 || frameskip > 20) {
			showDialog(DIALOG_WRONG_FRAMESKIP);
			return false;
		}
		if (gsensor < 100 || gsensor > 9000) {
			showDialog(DIALOG_WRONG_GSENSOR);
			return false;
		}
		return true;
	}

	private void openAllLevelsCheat() {
		for (int i = 1; i <= 5; ++i) {
			AAAASettings.configuration[i] = 1;
		}
		for (int i = 0; i < 8; i++) {
			AAAASettings.configuration[16 + i * 2] = 99;
			AAAASettings.configuration[17 + i * 2] = 59;
		}
		showToast(R.string.open_all_levels_toast, Toast.LENGTH_SHORT);
	}

	private void resetAllSettingsToDefaultValues() {
		AAAASettings.configuration[0] = 1;    AAAASettings.configuration[8] = 128;
		AAAASettings.configuration[1] = 0;    AAAASettings.configuration[9] =  48;
		AAAASettings.configuration[2] = 0;    AAAASettings.configuration[10] =  1;
		AAAASettings.configuration[3] = 0;    AAAASettings.configuration[11] =  1;
		AAAASettings.configuration[4] = 0;    AAAASettings.configuration[12] =  2;
		AAAASettings.configuration[5] = 0;    AAAASettings.configuration[13] =  1;
		AAAASettings.configuration[6] = 1;    AAAASettings.configuration[14] =  0;
		AAAASettings.configuration[7] = 1;    AAAASettings.configuration[15] =  0;

		AAAASettings.configuration[16] =  99; AAAASettings.configuration[24] = 199;
		AAAASettings.configuration[17] =  59; AAAASettings.configuration[25] =  59;
		AAAASettings.configuration[18] = 199; AAAASettings.configuration[26] = 199;
		AAAASettings.configuration[19] =  59; AAAASettings.configuration[27] =  59;
		AAAASettings.configuration[20] = 199; AAAASettings.configuration[28] = 199;
		AAAASettings.configuration[21] =  59; AAAASettings.configuration[29] =  59;
		AAAASettings.configuration[22] = 199; AAAASettings.configuration[30] = 199;
		AAAASettings.configuration[23] =  59; AAAASettings.configuration[31] =  59;

		AAAASettings.touchControls = AAAASettings.MODERN_TOUCH_CONTROLS;
		AAAASettings.touchVibration = true;
		AAAASettings.frameLimit = false;
		AAAASettings.aiDisable = false;
		AAAASettings.showFps = false;
		AAAASettings.gSensorScale = 1000;
		AAAASettings.vibroScale = 30;
		AAAASettings.obbSavedPath = "";

		fillWidgetsBySettings();

		showToast(R.string.reset_all_settings_toast, Toast.LENGTH_SHORT);
	}

	private void showToast(int stringId, int length) {
		Toast.makeText(aaaaLauncherActivity,
				getResources().getString(stringId),
				length).show();
	}

	private void runFilePicker() {
		Intent intent = new Intent(this, AAAAFilePickerActivity.class);
		startActivityForResult(intent, AC_FILE_PICKER_CODE);
	}

	private void checkObbMount() {
		obbFilePathName = editTextObbPath.getEditableText().toString();
		File obbFile = new File(obbFilePathName);
		if (obbFile.exists() && obbFile.isFile()) {
			try {
				try {
					mObbInfo = ObbScanner.getObbInfo(obbFilePathName);
				} catch (IllegalArgumentException e) {
					e.printStackTrace();
					showToast(R.string.obb_file_not_found, Toast.LENGTH_LONG);
				} catch (IOException e) {
					e.printStackTrace();
					showToast(R.string.obb_file_not_read, Toast.LENGTH_LONG);
				}
				if (mStorageManager.mountObb(obbFilePathName, null, mObbEventListener)) {
					AAAAActivity.toDebugLog("Mount OBB file...");
				} else {
					showToast(R.string.obb_mount_start_fail, Toast.LENGTH_LONG);
				}
			} catch (IllegalArgumentException e) {
				e.printStackTrace();
				AAAAActivity.toDebugLog("The OBB file already mounted!");
			}
		} else {
			showToast(R.string.obb_fail, Toast.LENGTH_LONG);
		}
		mObbInfo = null;
		obbFile = null;
		System.gc();
	}

	OnObbStateChangeListener mObbEventListener = new OnObbStateChangeListener() {

		@Override
		public void onObbStateChange(String path, int state) {
			AAAAActivity.toDebugLog("ObbStateChanged, path: " + path + ", state: " + state);
			switch (state) {
			case OnObbStateChangeListener.ERROR_ALREADY_MOUNTED:
				AAAAActivity.toDebugLog("Obb File Already Mounted! Unmounting... #2");
				mStorageManager.unmountObb(obbFilePathName, true, mObbEventListener);
				break;
			case OnObbStateChangeListener.MOUNTED:
				obbMountedPath = mStorageManager.getMountedObbPath(obbFilePathName);
				AAAAActivity.toDebugLog("Obb Mounted! Path: " + obbMountedPath);

				// Attempt to read the random file
				File readMeFile = new File(obbMountedPath + "/AAAA-Data/DONOTREAD.ME");
				if (readMeFile.exists() && readMeFile.isFile()) {
					Intent intent = new Intent(aaaaLauncherActivity, AAAAActivity.class);
					startActivity(intent);
				} else {
					showToast(R.string.obb_files_read_error, Toast.LENGTH_LONG);
				}

				break;
			case OnObbStateChangeListener.UNMOUNTED:
				AAAAActivity.toDebugLog("Obb File Unmounted!");
				break;
			default:
				break;
			}
		}
	};

	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		if (data == null) {
			return;
		}
		switch (requestCode) {
		case AC_FILE_PICKER_CODE:
			if (resultCode == RESULT_OK) {
				AAAASettings.obbSavedPath = data.getStringExtra("ObbPath");
				editTextObbPath.setText(AAAASettings.obbSavedPath);
				writeAll();
				showToast(R.string.obb_file_c, Toast.LENGTH_SHORT);
			}
			break;
		default:
			break;
		}
	}

	@Override
	protected void onDestroy() {
		writeAll();

		super.onDestroy();
	}

	@Override
	protected Dialog onCreateDialog(int id) {
		AlertDialog.Builder builder = new AlertDialog.Builder(this);
		switch (id) {
		case DIALOG_WRONG_HAPTIC:
			builder.setTitle(getString(R.string.wrong_haptic_title));
			builder.setMessage(getString(R.string.wrong_haptic_body) +
					"\nMin: " + 5 + "\nMax: " + 200 + "\n" +
					getString(R.string.wrong_body_general));
			builder.setPositiveButton(getString(R.string.button_ok), new DialogInterface.OnClickListener() {

				@Override
				public void onClick(DialogInterface dialog, int id) {
					AAAASettings.vibroScale = 30;
					editTextHaptics.setText(String.valueOf(AAAASettings.vibroScale));
					dialog.cancel();
				}
			});
			break;
		case DIALOG_WRONG_FRAMESKIP:
			builder.setTitle(getString(R.string.wrong_frameskip_title));
			builder.setMessage(getString(R.string.wrong_frameskip_body) +
					"\nMin: " + 0 + "\nMax: " + 20 + "\n" +
					getString(R.string.wrong_body_general));
			builder.setPositiveButton(getString(R.string.button_ok), new DialogInterface.OnClickListener() {

				@Override
				public void onClick(DialogInterface dialog, int id) {
					AAAASettings.configuration[12] = 2;
					editTextFrameSkip.setText(String.valueOf(AAAASettings.configuration[12]));
					dialog.cancel();
				}
			});
			break;
		case DIALOG_WRONG_GSENSOR:
			builder.setTitle(getString(R.string.wrong_gsensor_title));
			builder.setMessage(getString(R.string.wrong_gsensor_body) +
					"\nMin: " + 100 + "\nMax: " + 9000 + "\n" +
					getString(R.string.wrong_body_general));
			builder.setPositiveButton(getString(R.string.button_ok), new DialogInterface.OnClickListener() {

				@Override
				public void onClick(DialogInterface dialog, int id) {
					AAAASettings.gSensorScale = 1000;
					editTextGSensorScale.setText(String.valueOf(AAAASettings.gSensorScale));
					dialog.cancel();
				}
			});
			break;
		case DIALOG_QUESTION_OPEN_LEVELS:
			builder.setTitle(getString(R.string.question_title_general));
			builder.setMessage(getString(R.string.question_open_body));
			builder.setPositiveButton(getString(R.string.button_ok), new DialogInterface.OnClickListener() {

				@Override
				public void onClick(DialogInterface dialog, int id) {
					openAllLevelsCheat();
					dialog.cancel();
				}
			});
			builder.setNegativeButton(getString(R.string.button_cancel), new DialogInterface.OnClickListener() {

				@Override
				public void onClick(DialogInterface dialog, int id) {
					dialog.cancel();
				}
			});
			break;
		case DIALOG_QUESTION_RESET_SETTINGS:
			builder.setTitle(getString(R.string.question_title_general));
			builder.setMessage(getString(R.string.question_reset_body));
			builder.setPositiveButton(getString(R.string.button_ok), new DialogInterface.OnClickListener() {

				@Override
				public void onClick(DialogInterface dialog, int id) {
					resetAllSettingsToDefaultValues();
					dialog.cancel();
				}
			});
			builder.setNegativeButton(getString(R.string.button_cancel), new DialogInterface.OnClickListener() {

				@Override
				public void onClick(DialogInterface dialog, int id) {
					dialog.cancel();
				}
			});
			break;
		default:
			break;
		}
		return builder.create();
	}

	private void initAboutDialog() {
		AlertDialog.Builder builder = new AlertDialog.Builder(this);
		LayoutInflater inflater = this.getLayoutInflater();
		final ViewGroup nullParentVG = null;
		View dialogView = inflater.inflate(R.layout.aaaa_dialog_about, nullParentVG);
		builder.setView(dialogView);
		builder.setTitle(R.string.app_name_short);
		builder.setPositiveButton(R.string.button_ok, null);
		aboutDialog = builder.create();
	}

	// Prevent dialog dismiss when orientation changes
	// http://stackoverflow.com/a/27311231/2467443
	private static void doKeepDialog(AlertDialog dialog) {
		WindowManager.LayoutParams lp = new WindowManager.LayoutParams();
		lp.copyFrom(dialog.getWindow().getAttributes());
		lp.width = WindowManager.LayoutParams.WRAP_CONTENT;
		lp.height = WindowManager.LayoutParams.WRAP_CONTENT;
		dialog.getWindow().setAttributes(lp);
	}

	private void showMyDialog(AlertDialog dialog) {
		dialog.show();
		doKeepDialog(dialog);
	}

	public static void writeConfig() {
		AAAAActivity.toDebugLog("Write Config!");
		SharedPreferences.Editor editor = mSharedPreferences.edit();
		int count = 0;
		for (int i: AAAASettings.configuration) {
			editor.putInt("cfg_" + count++, i);
		}
		editor.commit();
	}

	public static void readConfig() {
		AAAAActivity.toDebugLog("Read Config!");
		for (int i = 0; i < AAAASettings.CFG_CNT; ++i) {
			AAAASettings.configuration[i] = mSharedPreferences.getInt("cfg_" + i, 0);
		}
	}

	private void fillSettingsByWidgets() {
		AAAAActivity.toDebugLog("FSBW!");
		AAAASettings.obbSavedPath = editTextObbPath.getEditableText().toString();
		AAAASettings.vibroScale = Integer.parseInt(editTextHaptics.getEditableText().toString());
		AAAASettings.gSensorScale = Integer.parseInt(editTextGSensorScale.getEditableText().toString());
		AAAASettings.configuration[12] = Integer.parseInt(editTextFrameSkip.getEditableText().toString());
		AAAASettings.configuration[8] = checkBoxSound.isChecked() ? AAAASettings.configuration[8] : 0;
		AAAASettings.configuration[9] = checkBoxMusic.isChecked() ? AAAASettings.configuration[9] : 0;
		AAAASettings.configuration[11] = checkBoxGSensor.isChecked() ? 1 : 0;
		AAAASettings.configuration[13] = checkBoxFilmGrain.isChecked() ? 1 : 0;
		AAAASettings.showFps = checkBoxShowFps.isChecked();
		AAAASettings.frameLimit = checkBoxFramelimit.isChecked();
		AAAASettings.touchVibration = checkBoxVibrationOnTouch.isChecked();
		AAAASettings.configuration[10] = checkBoxVibrationInGame.isChecked() ? 1 : 0;
		AAAASettings.aiDisable = checkBoxDisableAiAttack.isChecked();
		if (radioButtonModernTouchControls.isChecked()) {
			AAAASettings.touchControls = AAAASettings.MODERN_TOUCH_CONTROLS;
		} else if (radioButtonSimpleTouchControls.isChecked()) {
			AAAASettings.touchControls = AAAASettings.OLD_TOUCH_CONTROLS;
		} else if (radioButtonNoTouchControls.isChecked()) {
			AAAASettings.touchControls = AAAASettings.NO_TOUCH_CONTROLS;
		}
	}

	private void fillWidgetsBySettings() {
		AAAAActivity.toDebugLog("FWBS!");
		editTextObbPath.setText(AAAASettings.obbSavedPath);
		editTextHaptics.setText(String.valueOf(AAAASettings.vibroScale));
		editTextGSensorScale.setText(String.valueOf(AAAASettings.gSensorScale));
		editTextFrameSkip.setText(String.valueOf(AAAASettings.configuration[12]));
		checkBoxSound.setChecked(AAAASettings.configuration[8] > 0);
		checkBoxMusic.setChecked(AAAASettings.configuration[9] > 0);
		checkBoxGSensor.setChecked(AAAASettings.configuration[11] > 0);
		checkBoxFilmGrain.setChecked(AAAASettings.configuration[13] > 0);
		checkBoxShowFps.setChecked(AAAASettings.showFps);
		checkBoxFramelimit.setChecked(AAAASettings.frameLimit);
		checkBoxVibrationOnTouch.setChecked(AAAASettings.touchVibration);
		checkBoxVibrationInGame.setChecked(AAAASettings.configuration[10] > 0);
		checkBoxDisableAiAttack.setChecked(AAAASettings.aiDisable);
		switch (AAAASettings.touchControls) {
		case AAAASettings.MODERN_TOUCH_CONTROLS:
			radioButtonModernTouchControls.setChecked(true);
			break;
		case AAAASettings.OLD_TOUCH_CONTROLS:
			radioButtonSimpleTouchControls.setChecked(true);
			break;
		case AAAASettings.NO_TOUCH_CONTROLS:
			radioButtonNoTouchControls.setChecked(true);
			break;
		default:
			break;
		}
		if (!checkBoxGSensor.isChecked()) {
			editTextGSensorScale.setEnabled(false);
		}
		if (!checkBoxVibrationInGame.isChecked() && !checkBoxVibrationOnTouch.isChecked()) {
			editTextHaptics.setEnabled(false);
		}
	}

	private void initWidgets() {
		editTextObbPath = (EditText) findViewById(R.id.editTextObbPath);
		editTextHaptics = (EditText) findViewById(R.id.editTextVibroScale);
		editTextGSensorScale = (EditText) findViewById(R.id.editTextGSensorScale);
		editTextFrameSkip = (EditText) findViewById(R.id.editTextFrameSkip);
		checkBoxSound = (CheckBox) findViewById(R.id.checkBoxSound);
		checkBoxMusic = (CheckBox) findViewById(R.id.checkBoxMusic);
		checkBoxGSensor = (CheckBox) findViewById(R.id.checkBoxGSensor);
		checkBoxFilmGrain = (CheckBox) findViewById(R.id.checkBoxFilmGrain);
		checkBoxShowFps = (CheckBox) findViewById(R.id.checkBoxFps);
		checkBoxFramelimit = (CheckBox) findViewById(R.id.checkBoxFrameLimit);
		checkBoxVibrationOnTouch = (CheckBox) findViewById(R.id.checkBoxVibroOnTouch);
		checkBoxVibrationInGame = (CheckBox) findViewById(R.id.checkBoxVibtoInGame);
		checkBoxDisableAiAttack = (CheckBox) findViewById(R.id.checkBoxDisableAiAttack);
		radioButtonModernTouchControls = (RadioButton) findViewById(R.id.radioButtonModern);
		radioButtonSimpleTouchControls = (RadioButton) findViewById(R.id.radioButtonSimple);
		radioButtonNoTouchControls = (RadioButton) findViewById(R.id.radioButtonOff);
	}

	public void writeSettings() {
		fillSettingsByWidgets();

		SharedPreferences.Editor editor = mSharedPreferences.edit();
		editor.putInt("touchControls", AAAASettings.touchControls);
		editor.putInt("gSensorScale", AAAASettings.gSensorScale);
		editor.putInt("vibroScale", AAAASettings.vibroScale);
		editor.putBoolean("touchVibration", AAAASettings.touchVibration);
		editor.putBoolean("frameLimit", AAAASettings.frameLimit);
		editor.putBoolean("aiDisable", AAAASettings.aiDisable);
		editor.putBoolean("showFps", AAAASettings.showFps);
		editor.putString("obbSavedPath", AAAASettings.obbSavedPath);
		editor.commit();
	}

	public static void readSettings() {
		AAAAActivity.toDebugLog("Read Settings!");
		AAAASettings.touchControls = mSharedPreferences.getInt("touchControls", 0);
		AAAASettings.gSensorScale = mSharedPreferences.getInt("gSensorScale", 1000);
		AAAASettings.vibroScale = mSharedPreferences.getInt("vibroScale", 30);
		AAAASettings.touchVibration = mSharedPreferences.getBoolean("touchVibration", true);
		AAAASettings.frameLimit = mSharedPreferences.getBoolean("frameLimit", false);
		AAAASettings.aiDisable = mSharedPreferences.getBoolean("aiDisable", false);
		AAAASettings.showFps = mSharedPreferences.getBoolean("showFps", false);
		AAAASettings.obbSavedPath = mSharedPreferences.getString("obbSavedPath", "");
	}

	void writeAll() {
		writeConfig();
		writeSettings();
	}
}
