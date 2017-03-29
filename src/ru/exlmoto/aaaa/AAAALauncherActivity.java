package ru.exlmoto.aaaa;

import java.io.File;
import java.io.IOException;

import android.app.Activity;
import android.content.Intent;
import android.content.res.ObbInfo;
import android.content.res.ObbScanner;
import android.os.Bundle;
import android.os.storage.OnObbStateChangeListener;
import android.os.storage.StorageManager;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;

public class AAAALauncherActivity extends Activity {

	private static final int AC_FILE_PICKER_CODE = 1;

	public static class AAAASettings {

		// GLOBALS
		public static final int CFG_CNT = 32;
		public static final int MODERN_TOUCH_CONTROLS = 0;
		public static final int OLD_TOUCH_CONTROLS = 1;
		public static final int NO_TOUCH_CONTROLS = 2;

		public static int[] configuration = {
				1, 0, 0, 0, 0, 0, 1, 1, // 0-7: Menu Items
				128, 48,                // 8-9: Sound and Music Volume
				1, 1, 2, 1, 0, 0,       // 10-15: Vibrohaptics, G-Sensor, Frameskip, Noise, Hz ?
				99, 59, 199, 59, 199, 59, 199, 59, 199, 59, 199, 59, 199, 59, 199, 59 // 16-31: Levels and Time
		};

		public static int touchControls = MODERN_TOUCH_CONTROLS;
		public static boolean touchVibration = true;
	}

	private String obbFilePathName;
	private EditText editTextObbPath = null;
	// private final String obbKey = "aaaa";
	private ObbInfo mObbInfo = null;

	// JNI-access
	public static String obbMountedPath = "";

	public static StorageManager mStorageManager = null;
	AAAALauncherActivity aaaaLauncherActivity = this;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		for (int i = 0; i < AAAASettings.CFG_CNT; ++i) {
			AAAAActivity.toDebugLog("Act: " + AAAASettings.configuration[i]);
		}

		mStorageManager = (StorageManager) getApplicationContext().getSystemService(STORAGE_SERVICE);

		setContentView(R.layout.aaaa_launcher);

		editTextObbPath = (EditText) findViewById(R.id.editTextObbPath);
		editTextObbPath.setText(obbFilePathName);

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
}
