LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := AAAA-Engine

SDL_PATH := ../SDL2
SDL_MIXER_PATH := ../SDL2_mixer

DEFINES := -DSDL2_PORT -DANDROID_NDK

LOCAL_CFLAGS += -O3 -ffast-math -fomit-frame-pointer $(DEFINES)

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include $(LOCAL_PATH)/$(SDL_MIXER_PATH) $(LOCAL_PATH)

# Add your application source files here...
LOCAL_SRC_FILES := $(SDL_PATH)/src/main/android/SDL_android_main.c \
		zlext/android_extras.c \
		bullets.c \
		camera.c \
		drawmob.c \
		game.c \
		gamemenu.c \
		gamescene.c \
		intro.c \
		main.c \
		mobai.c \
		mobs.c \
		narrator.c \
		particles.c \
		/playcontrol.c \
		/render.c \
		/sprites.c \
		/vars.c \
		/veryblend.c \
		/wlight.c \
		/wmapgen.c \
		/wmapload.c \
		/zcore.c \
		/zcsound.c \
		/zctables.c \
		/zeditmode.c \
		/zgui.c \
		/zlext.c \
		/zlmath.c \
		/zresm.c


LOCAL_SHARED_LIBRARIES := SDL2 SDL2_mixer

LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog

include $(BUILD_SHARED_LIBRARY)
