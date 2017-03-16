package ru.exlmoto.aaaa;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

public class AAAALauncherActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		setContentView(R.layout.aaaa_launcher);

		Button buttonRun = (Button) findViewById(R.id.buttonRun);
		buttonRun.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View v) {
				Intent intent = new Intent(v.getContext(), AAAAActivity.class);
				startActivity(intent);
			}
		});
	}
}
