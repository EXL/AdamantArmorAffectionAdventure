package ru.exlmoto.aaaa;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.view.MotionEvent;
import android.view.View;

public class AAAAInputView extends View {

	private Paint paint;

	private boolean firstRun = true;
	private int width = 0;
	private int height = 0;

	public AAAAInputView(Context context) {

		super(context);

		paint = new Paint();
	}

	@Override
	protected void onDraw(Canvas canvas) {
		if (firstRun) {
			width = canvas.getWidth();
			height = canvas.getHeight();

			firstRun = false;
		}

		paint.setARGB(128, 255, 255, 255);
		canvas.drawCircle(200, 450, 60, paint);

		//AAAAActivity.toDebugLog("w:" + width + "h:" + height + ":" + canvas.isHardwareAccelerated());

		invalidate();
		super.onDraw(canvas);
	}

	@Override
	public boolean onTouchEvent(MotionEvent event) {
		//SDL.addEvent(MotionEvent.obtainNoHistory(event));
		AAAAActivity.toDebugLog("" + event.toString());
		return true;
	}

	private void initBitmaps() {

	}
}
