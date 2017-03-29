package ru.exlmoto.aaaa;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import android.annotation.SuppressLint;
import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.view.MotionEvent;
import android.view.View;

import org.libsdl.app.SDLActivity;

public class AAAAModernInputView extends View {

	private Paint paint = null;

	private int width = 0;
	private int height = 0;

	private int radius = 0;
	private static int[] pid = new int[16];

	private Bitmap button_a = null;
	private Bitmap button_b = null;
	private Bitmap button_x = null;
	private Bitmap button_y = null;
	private Bitmap button_l = null;
	private Bitmap button_r = null;
	private Bitmap button_s = null;

	private int b_wh = 0;

	private int col1_w = 0;
	private int col2_w = 0;
	private int row1_h = 0;
	private int row2_h = 0;
	private int row3_h = 0;
	private int rad_d2 = 0;

	private static final int VIBRO_OFFSET = 20;

	// --- Game Keycodes Table
	// Joystick
	private static final int KC_GAME_UP = 2;
	private static final int KC_GAME_DOWN = 6;
	private static final int KC_GAME_RIGHT = 0;
	private static final int KC_GAME_LEFT = 4;
	private static final int KC_GAME_UPRIGHT = 3;
	private static final int KC_GAME_UPLEFT = 1;
	private static final int KC_GAME_DOWNLEFT = 5;
	private static final int KC_GAME_DOWNRIGHT = 7;
	// Buttons
	private static final int KC_GAME_X = 8;
	private static final int KC_GAME_A = 9;
	private static final int KC_GAME_L = 10;
	private static final int KC_GAME_B = 11;
	private static final int KC_GAME_R = 12;
	private static final int KC_GAME_Y = 13;
	private static final int KC_GAME_SELECT = 14;
	private static final int KC_GAME_START = 15;

	// Send To AAAA-Engine
	// Joystick
	private static final int TJ_GAME_UP = 0;
	private static final int TJ_GAME_LEFT = 1;
	private static final int TJ_GAME_DOWN = 2;
	private static final int TJ_GAME_RIGHT = 3;
	private static final int TJ_GAME_UPRIGHT = 4;
	private static final int TJ_GAME_UPLEFT = 5;
	private static final int TJ_GAME_DOWNRIGHT = 6;
	private static final int TJ_GAME_DOWNLEFT = 7;
	// Buttons
	private static final int KC_SDL_X = 62;      // Space
	private static final int KC_SDL_A = 67;      // Backspace
	private static final int KC_SDL_L = 59;      // Shift
	private static final int KC_SDL_B = 66;      // Enter
	private static final int KC_SDL_Y = 54;      // Z
	private static final int KC_SDL_R = 52;      // X
	private static final int KC_SDL_SELECT = 31; // C
	private static final int KC_SDL_START = 7;   // 0 - Zero Digit
	private static final int KC_SDL_UP = 51;     // W
	private static final int KC_SDL_DOWN = 47;   // S
	private static final int KC_SDL_LEFT = 29;   // A
	private static final int KC_SDL_RIGHT = 32;  // D
	// D-Pad
	private static final int DPAD_UP = 19;
	private static final int DPAD_DOWN = 20;
	private static final int DPAD_LEFT = 21;
	private static final int DPAD_RIGHT = 22;
	private static final int DPAD_OK = 23;

	// --- SDL Patch Functions
	public static void pressOrReleaseKey(int keyCode, boolean press) {
		if (press) {
			SDLActivity.onNativeKeyDown(keyCode);
		} else {
			SDLActivity.onNativeKeyUp(keyCode);
		}
	}

	public static boolean convertJoyDpadToKeysFilter(int keyCode, boolean press) {
		switch (keyCode) {
		case DPAD_UP:
			pressOrReleaseKey(KC_SDL_UP, press);
			return true;
		case DPAD_DOWN:
			pressOrReleaseKey(KC_SDL_DOWN, press);
			return true;
		case DPAD_LEFT:
			pressOrReleaseKey(KC_SDL_LEFT, press);
			return true;
		case DPAD_RIGHT:
			pressOrReleaseKey(KC_SDL_RIGHT, press);
			return true;
		case DPAD_OK:
			pressOrReleaseKey(KC_SDL_A, press);
			return true;
		default:
			return false;
		}
	}
	// ---

	public AAAAModernInputView(Context context) {
		super(context);

		button_a = BitmapFactory.decodeResource(context.getResources(), R.drawable.button_a);
		button_b = BitmapFactory.decodeResource(context.getResources(), R.drawable.button_b);
		button_x = BitmapFactory.decodeResource(context.getResources(), R.drawable.button_x);
		button_y = BitmapFactory.decodeResource(context.getResources(), R.drawable.button_y);
		button_r = BitmapFactory.decodeResource(context.getResources(), R.drawable.button_r);
		button_l = BitmapFactory.decodeResource(context.getResources(), R.drawable.button_l);
		button_s = BitmapFactory.decodeResource(context.getResources(), R.drawable.button_s);

		b_wh = button_a.getWidth();

		AAAAActivity.toDebugLog("Touch buttons size: " + b_wh + "x" + b_wh);

		paint = new Paint();
	}

	@Override
	protected void onDraw(Canvas canvas) {
		paint.setARGB(128, 255, 255, 255);

		paint.setFilterBitmap(true);
		paint.setAntiAlias(true);

		// Joystick
		if (p0id >= 0) {
			paint.setARGB(16, 255, 255, 255);
			canvas.drawCircle(p0x, p0y, radius << 1, paint);
			for (int i = 0; i < 8; ++i) {
				paint.setARGB(i == p1b ? 96 : 32, 255, 128, 128);
				canvas.drawCircle((float) (p0x + 7 * radius * Math.cos(i * Math.PI / 4) / 4),
						(float) (p0y - 7 * radius * Math.sin(i * Math.PI / 4) / 4),
						radius / 4, paint);
			}
			paint.setARGB(128, 255, 255, 255);
			canvas.drawCircle(p0x, p0y, radius / 3, paint);
			canvas.drawCircle(p1x, p1y, radius, paint);
		}

		// buttons
		paint.setARGB(pid[KC_GAME_X] < 0 ? 64 : 160, 255, 255, 255);
		canvas.drawBitmap(button_x, col1_w, row1_h, paint);
		//canvas.drawCircle(width - radius - radius / 3, height - radius - radius / 3, radius, paint);
		paint.setARGB(pid[KC_GAME_L] < 0 ? 64 : 160, 255, 255, 255);
		canvas.drawBitmap(button_l, col1_w, row2_h, paint);
		//canvas.drawCircle(width - radius - radius / 3, radius + radius / 3, radius, paint);
		paint.setARGB(pid[KC_GAME_A] < 0 ? 64 : 160, 255, 255, 255);
		canvas.drawBitmap(button_a, col1_w, row3_h, paint);
		//canvas.drawCircle(width - radius - radius / 3, height / 2, radius, paint);
		paint.setARGB(pid[KC_GAME_B] < 0 ? 64 : 160, 255, 255, 255);
		canvas.drawBitmap(button_b, col2_w, row1_h, paint);
		//canvas.drawCircle(width - radius * 5, height - radius - radius / 3, radius, paint);
		paint.setARGB(pid[KC_GAME_Y] < 0 ? 64 : 160, 255, 255, 255);
		canvas.drawBitmap(button_y, col2_w, row2_h, paint);
		//canvas.drawCircle(width - radius * 5, radius + radius / 3, radius, paint);
		paint.setARGB(pid[KC_GAME_SELECT] < 0 ? 64 : 160, 255, 255, 255);
		canvas.drawBitmap(button_s, col2_w, row3_h, paint);
		//canvas.drawCircle(width - radius * 5, height / 2, radius, paint);
		paint.setARGB(pid[KC_GAME_R] < 0 ? 64 : 160, 255, 255, 255);
		//canvas.drawRect(0, 0, radius * 3, radius, paint);
		canvas.drawBitmap(button_r, rad_d2, rad_d2, paint);

		invalidate();

		super.onDraw(canvas);
	}

	private static List<MotionEvent> events = new ArrayList<MotionEvent>();

	public static void addEvent(MotionEvent event) {
		synchronized (events) {
			events.add(event);
		}
	}

	@SuppressLint({ "Recycle", "ClickableViewAccessibility" })
	@Override
	public boolean onTouchEvent(MotionEvent event) {
		addEvent(MotionEvent.obtainNoHistory(event));
		checkInput();
		// event.recycle();
		return true;
	}

	@Override
	public void onWindowFocusChanged(boolean hasFocus) {
		super.onWindowFocusChanged(hasFocus);

		width = getWidth();
		height = getHeight();

		radius = Math.min(width, height) / 11;
		Arrays.fill(pid, -1);

		// Some optimizations
		col1_w = width - b_wh - b_wh / 4;
		col2_w = width - b_wh * 3;
		row1_h = height - b_wh - b_wh / 4;
		row2_h = b_wh / 4;
		row3_h = height / 2 - b_wh / 2;
		rad_d2 = radius / 3;

		AAAAActivity.toDebugLog("Set Resolution of Input layer as: " + width + "x" + height);
	}

	private int p0x, p0y, p1x, p1y, p1b, p0id = -1;

	public void checkInput() {
		List<MotionEvent> copy;
		synchronized (events) {
			copy = new ArrayList<MotionEvent>(events);
			events.clear();
		}
		int[] npid = Arrays.copyOf(pid, pid.length);
		int id, index, b, x, y;
		int sector_move, sector_button_r;
		for (MotionEvent e : copy) {
			sector_move = 2 * width / 3;
			sector_button_r = radius * 3;
			switch(e.getActionMasked()) {
			case MotionEvent.ACTION_MOVE:
				int len = e.getPointerCount();
				Arrays.fill(npid, -1);
				p1b = -1;
				for (index = 0; index < len; ++index) {
					id = e.getPointerId(index);
					x = (int) e.getX(index);
					y = (int) e.getY(index);
					if (x < sector_move) {
						if (x < sector_button_r && y < radius) {
							b = getButton(x, y);
						} else {
							b = getDirection(x, y);
						}
					} else {
						b = getButton(x, y);
					}
					if (b >= 0) {
						npid[b] = id;
					}
				}
				break;
			case MotionEvent.ACTION_DOWN:
				index = e.getActionIndex();
				id = e.getPointerId(index);
				cleanPointer(npid, id);
				x = (int) e.getX(index);
				y = (int) e.getY(index);
				if (x < sector_move) {
					if (x < sector_button_r && y < radius) {
						b = getButton(x, y);
						if (b >= 0) {
							npid[b] = id;
							AAAAActivity.doVibrate(50 - VIBRO_OFFSET, 0);
						}
						break;
					}
					p1b = -1;
					p0x = x;
					p0y = y;
					p1x = p0x;
					p1y = p0y;
					p0id = id;
				} else {
					b = getButton(x, y);
					if (b >= 0) {
						npid[b] = id;
						AAAAActivity.doVibrate(50 - VIBRO_OFFSET, 0);
					}
				}
				break;
			case MotionEvent.ACTION_UP:
				id = e.getPointerId(e.getActionIndex());
				cleanPointer(npid, id);
				if (id == p0id) {
					p0id = -1;
				}
				break;
			case MotionEvent.ACTION_POINTER_DOWN:
				index = e.getActionIndex();
				id = e.getPointerId(index);
				cleanPointer(npid, id);
				x = (int) e.getX(index);
				y = (int) e.getY(index);
				if (x < sector_move) {
					if (x < sector_button_r && y < radius) {
						b = getButton(x, y);
						if (b >= 0) {
							npid[b] = id;
							AAAAActivity.doVibrate(50 - VIBRO_OFFSET, 0);
						}
						break;
					}
					if (p0id < 0) {
						p1b = -1;
						p0x = x;
						p0y = y;
						p1x = p0x;
						p1y = p0y;
						p0id = id;
					}
				} else {
					b = getButton(x, y);
					if (b >= 0) {
						npid[b] = id;
						AAAAActivity.doVibrate(50 - VIBRO_OFFSET, 0);
					}
				}
				break;
			case MotionEvent.ACTION_POINTER_UP:
				id = e.getPointerId(e.getActionIndex());
				cleanPointer(npid, id);
				if (id == p0id) {
					p0id = -1;
				}
				break;
			}
		}
		// lastKeyTyped = 0;
		// lastKey = 0;
		for (int i = 0; i < npid.length; ++i) {
			if (npid[i] < 0) {
				if (pid[i] >= 0) {
					releaseKey(i);
				}
			} else {
				pressKey(i);
			}
			pid[i] = npid[i];
		}
	}

	public void pressKey(int keyCode) {
		// AAAAActivity.toDebugLog(keyCode + " pushed!");
		switch (keyCode) {
		case KC_GAME_X:
			SDLActivity.onNativeKeyDown(KC_SDL_X);
			break;
		case KC_GAME_A:
			SDLActivity.onNativeKeyDown(KC_SDL_A);
			break;
		case KC_GAME_L:
			SDLActivity.onNativeKeyDown(KC_SDL_L);
			break;
		case KC_GAME_B:
			SDLActivity.onNativeKeyDown(KC_SDL_B);
			break;
		case KC_GAME_R:
			SDLActivity.onNativeKeyDown(KC_SDL_R);
			break;
		case KC_GAME_Y:
			SDLActivity.onNativeKeyDown(KC_SDL_Y);
			break;
		case KC_GAME_SELECT:
			SDLActivity.onNativeKeyDown(KC_SDL_SELECT);
			break;
		case KC_GAME_START:
			SDLActivity.onNativeKeyDown(KC_SDL_START);
			break;
		case KC_GAME_UP:
			AAAANativeLibProxy.AAAAJoystickButtonDown(TJ_GAME_UP);
			break;
		case KC_GAME_DOWN:
			AAAANativeLibProxy.AAAAJoystickButtonDown(TJ_GAME_DOWN);
			break;
		case KC_GAME_RIGHT:
			AAAANativeLibProxy.AAAAJoystickButtonDown(TJ_GAME_RIGHT);
			break;
		case KC_GAME_LEFT:
			AAAANativeLibProxy.AAAAJoystickButtonDown(TJ_GAME_LEFT);
			break;
		case KC_GAME_UPRIGHT:
			AAAANativeLibProxy.AAAAJoystickButtonDown(TJ_GAME_UPRIGHT);
			break;
		case KC_GAME_UPLEFT:
			AAAANativeLibProxy.AAAAJoystickButtonDown(TJ_GAME_UPLEFT);
			break;
		case KC_GAME_DOWNRIGHT:
			AAAANativeLibProxy.AAAAJoystickButtonDown(TJ_GAME_DOWNRIGHT);
			break;
		case KC_GAME_DOWNLEFT:
			AAAANativeLibProxy.AAAAJoystickButtonDown(TJ_GAME_DOWNLEFT);
			break;
		default:
			break;
		}
	}

	public void releaseKey(int keyCode) {
		// AAAAActivity.toDebugLog(keyCode + " released!");
		switch (keyCode) {
		case KC_GAME_X:
			SDLActivity.onNativeKeyUp(KC_SDL_X);
			break;
		case KC_GAME_A:
			SDLActivity.onNativeKeyUp(KC_SDL_A);
			break;
		case KC_GAME_L:
			SDLActivity.onNativeKeyUp(KC_SDL_L);
			break;
		case KC_GAME_B:
			SDLActivity.onNativeKeyUp(KC_SDL_B);
			break;
		case KC_GAME_R:
			SDLActivity.onNativeKeyUp(KC_SDL_R);
			break;
		case KC_GAME_Y:
			SDLActivity.onNativeKeyUp(KC_SDL_Y);
			break;
		case KC_GAME_SELECT:
			SDLActivity.onNativeKeyUp(KC_SDL_SELECT);
			break;
		case KC_GAME_START:
			SDLActivity.onNativeKeyUp(KC_SDL_START);
			break;
		case KC_GAME_UP:
			AAAANativeLibProxy.AAAAJoystickButtonUp(TJ_GAME_UP);
			break;
		case KC_GAME_DOWN:
			AAAANativeLibProxy.AAAAJoystickButtonUp(TJ_GAME_DOWN);
			break;
		case KC_GAME_RIGHT:
			AAAANativeLibProxy.AAAAJoystickButtonUp(TJ_GAME_RIGHT);
			break;
		case KC_GAME_LEFT:
			AAAANativeLibProxy.AAAAJoystickButtonUp(TJ_GAME_LEFT);
			break;
		case KC_GAME_UPRIGHT:
			AAAANativeLibProxy.AAAAJoystickButtonUp(TJ_GAME_UPRIGHT);
			break;
		case KC_GAME_UPLEFT:
			AAAANativeLibProxy.AAAAJoystickButtonUp(TJ_GAME_UPLEFT);
			break;
		case KC_GAME_DOWNRIGHT:
			AAAANativeLibProxy.AAAAJoystickButtonUp(TJ_GAME_DOWNRIGHT);
			break;
		case KC_GAME_DOWNLEFT:
			AAAANativeLibProxy.AAAAJoystickButtonUp(TJ_GAME_DOWNLEFT);
			break;
		default:
			break;
		}
	}

	public void cleanPointer(int[] npid, int id) {
		for (int i = 0; i < npid.length; ++i) {
			if (npid[i] == id) {
				npid[i] = -1;
				break;
			}
		}
	}

	public int getDirection(int bx, int by) {
		int abx = bx - p0x;
		int aby = p0y - by;

		double lenab = Math.sqrt(abx * abx + aby * aby);

		if (lenab > radius) {
			p1x = p0x + (int) ((bx - p0x) * (radius / lenab));
			p1y = p0y + (int) ((by - p0y) * (radius / lenab));
		} else {
			p1x = bx;
			p1y = by;
		}

		if (lenab < (radius / 3)) {
			p1b = -1;
		} else {
			double rslt = aby == 0 ? (abx > 0 ? 0 : Math.PI) : Math.acos(abx / lenab);
			if (by > p0y) {
				rslt = (Math.PI * 2) - rslt;
			}
			p1b = ((int) ((rslt + Math.PI / 16) / (Math.PI / 4))) & 0x7;
		}
		return p1b;
	}

	public int getButton(int x, int y) {
		int b = -1;
		if (x < radius * 3 && y < radius) {
			b = KC_GAME_R;
		} else if (x > (2 * width / 2.5)) {
			if (y > (height / 3) * 2) { // Down
				b = KC_GAME_X;
			} else if (y < (height / 3)) { // Up
				b = KC_GAME_L;
			} else { // Center
				b = KC_GAME_A;
			}
		} else {
			// AAAAActivity.toDebugLog("Second Buttons Column:" + x + "x" + y);
			if (y > (height / 3) * 2) { // Down
				b = KC_GAME_B;
			} else if (y < (height / 3)) { // Up
				b = KC_GAME_Y;
			} else { // Center
				b = KC_GAME_SELECT;
			}
		}
		return b;
	}
}
