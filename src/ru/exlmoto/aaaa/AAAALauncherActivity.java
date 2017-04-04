package ru.exlmoto.aaaa;

import java.io.File;
import java.io.IOException;

import android.app.Activity;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.res.ObbInfo;
import android.content.res.ObbScanner;
import android.os.Bundle;
import android.os.storage.OnObbStateChangeListener;
import android.os.storage.StorageManager;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.RadioButton;

public class AAAALauncherActivity extends Activity {

	private static final int AC_FILE_PICKER_CODE = 1;

	public static class AAAASettings {

		// GLOBALS
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
		public static boolean openAllLevels = false;
		public static boolean frameLimit = false; // Access from JNI
		public static boolean aiDisable = false;  // Access from JNI
		public static boolean showFps = false;    // Access from JNI
		public static int gSensorScale = 1000;    // Access from JNI
		public static int vibroScale = 30;
		public static String obbSavedPath = "";
	}

	private String obbFilePathName = "";
	// private final String obbKey = "aaaa";
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
	private CheckBox checkBoxOpenAllLevels = null;
	private RadioButton radioButtonModernTouchControls = null;
	private RadioButton radioButtonSimpleTouchControls = null;
	private RadioButton radioButtonNoTouchControls = null;

	// JNI-access
	public static String obbMountedPath = "";

	public static SharedPreferences mSharedPreferences = null;
	public StorageManager mStorageManager = null;
	AAAALauncherActivity aaaaLauncherActivity = this;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		mSharedPreferences = getSharedPreferences("ru.exlmoto.aaaa", MODE_PRIVATE);
		// Check the first run
		if (mSharedPreferences.getBoolean("firstrun", true)) {
			// The first run, fill GUI layout with default values
			mSharedPreferences.edit().putBoolean("firstrun", false).commit();
		} else {
			// Read settings from Shared Preferences
			readConfig();
		}

		mStorageManager = (StorageManager) getApplicationContext().getSystemService(STORAGE_SERVICE);

		setContentView(R.layout.aaaa_launcher);

		initWidgets();

		Button buttonRun = (Button) findViewById(R.id.buttonRun);
		buttonRun.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View v) {
				checkObbMount();
			}
		});

		Button buttonBrowse = (Button) findViewById(R.id.buttonObbBrowse);
		buttonBrowse.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View v) {
				runFilePicker();
			}
		});
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
					AAAAActivity.toDebugLog("The OBB file could not be found!");
				} catch (IOException e) {
					e.printStackTrace();
					AAAAActivity.toDebugLog("The OBB file could not be read!");
				}
				if (mStorageManager.mountObb(obbFilePathName, null, mObbEventListener)) {
					AAAAActivity.toDebugLog("Mount OBB file...");
				} else {
					AAAAActivity.toDebugLog("Failed to start OBB mounting!");
				}
			} catch (IllegalArgumentException e) {
				e.printStackTrace();
				AAAAActivity.toDebugLog("The OBB file already mounted!");
			}
		} else {
			AAAAActivity.toDebugLog("OBB file isn't exist or it's a directory!");
		}

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
					AAAAActivity.toDebugLog("Error access to mounted files!");
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
				editTextObbPath.setText(data.getStringExtra("ObbPath"));
			}
			break;
		default:
			break;
		}
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
		AAAASettings.obbSavedPath = editTextObbPath.getEditableText().toString();
		AAAASettings.vibroScale = Integer.parseInt(editTextHaptics.getEditableText().toString());
		AAAASettings.gSensorScale = Integer.parseInt(editTextGSensorScale.getEditableText().toString());
		AAAASettings.configuration[12] = Integer.parseInt(editTextFrameSkip.getEditableText().toString());
		AAAASettings.configuration[8] = checkBoxSound.isChecked() ? 1 : 0;
		AAAASettings.configuration[9] = checkBoxMusic.isChecked() ? 1 : 0;
		AAAASettings.configuration[11] = checkBoxGSensor.isChecked() ? 1 : 0;
		AAAASettings.configuration[13] = checkBoxFilmGrain.isChecked() ? 1 : 0;
		AAAASettings.showFps = checkBoxShowFps.isChecked();
		AAAASettings.frameLimit = checkBoxFramelimit.isChecked();
		AAAASettings.touchVibration = checkBoxVibrationOnTouch.isChecked();
		AAAASettings.configuration[10] = checkBoxVibrationInGame.isChecked() ? 1 : 0;
		AAAASettings.aiDisable = checkBoxDisableAiAttack.isChecked();
		AAAASettings.openAllLevels = checkBoxOpenAllLevels.isChecked();
		if (radioButtonModernTouchControls.isChecked()) {
			AAAASettings.touchControls = AAAASettings.MODERN_TOUCH_CONTROLS;
		} else if (radioButtonSimpleTouchControls.isChecked()) {
			AAAASettings.touchControls = AAAASettings.OLD_TOUCH_CONTROLS;
		} else if (radioButtonNoTouchControls.isChecked()) {
			AAAASettings.touchControls = AAAASettings.NO_TOUCH_CONTROLS;
		}
	}

	private void fillWidgetsBySettings() {
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
		checkBoxOpenAllLevels.setChecked(AAAASettings.openAllLevels);
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
		checkBoxOpenAllLevels = (CheckBox) findViewById(R.id.checkBoxOpenAllLevels);
		radioButtonModernTouchControls = (RadioButton) findViewById(R.id.radioButtonModern);
		radioButtonSimpleTouchControls = (RadioButton) findViewById(R.id.radioButtonSimple);
		radioButtonNoTouchControls = (RadioButton) findViewById(R.id.radioButtonOff);
	}

	public static void writeSettings() {
		SharedPreferences.Editor editor = mSharedPreferences.edit();
		editor.putInt("touchControls", AAAASettings.touchControls);
		editor.putInt("gSensorScale", AAAASettings.gSensorScale);
		editor.putInt("vibroScale", AAAASettings.vibroScale);
		editor.putBoolean("touchVibration", AAAASettings.touchVibration);
		editor.putBoolean("frameLimit", AAAASettings.frameLimit);
		editor.putBoolean("aiDisable", AAAASettings.aiDisable);
		editor.putBoolean("showFps", AAAASettings.showFps);
		editor.putBoolean("openAllLevels", AAAASettings.openAllLevels);
		editor.putString("obbSavedPath", AAAASettings.obbSavedPath);
		editor.commit();
	}

	public static void readSettings() {
		AAAASettings.touchControls = mSharedPreferences.getInt("touchControls", 0);
		AAAASettings.gSensorScale = mSharedPreferences.getInt("gSensorScale", 1000);
		AAAASettings.vibroScale = mSharedPreferences.getInt("vibroScale", 30);
		AAAASettings.touchVibration = mSharedPreferences.getBoolean("touchVibration", true);
		AAAASettings.frameLimit = mSharedPreferences.getBoolean("frameLimit", false);
		AAAASettings.aiDisable = mSharedPreferences.getBoolean("aiDisable", false);
		AAAASettings.showFps = mSharedPreferences.getBoolean("showFps", false);
		AAAASettings.openAllLevels = mSharedPreferences.getBoolean("openAllLevels", false);
		AAAASettings.obbSavedPath = mSharedPreferences.getString("obbSavedPath", "");
	}
}
