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

public class AAAALauncherActivity extends Activity {

	private String obbFilePathName = "/storage/sdcard0/main.1.ru.exlmoto.aaaa.obb";
	// private final String obbKey = "aaaa";
	private ObbInfo mObbInfo = null;
	// JNI-access
	public static String obbMountedPath = "";
	private StorageManager mStorageManager = null;
	AAAALauncherActivity aaaaLauncherActivity = this;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		mStorageManager = (StorageManager) getApplicationContext().getSystemService(STORAGE_SERVICE);

		setContentView(R.layout.aaaa_launcher);

		Button buttonRun = (Button) findViewById(R.id.buttonRun);
		buttonRun.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View v) {
				checkObbMount();
			}
		});
	}

	private void checkObbMount() {
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
}