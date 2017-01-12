LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := AAAA-Engine

SDL_PATH := ../SDL2-2.0.5
SDL_MIXER_PATH := ../SDL2_mixer-2.0.1

AAAA_PATH := AAAA-Engine

DEFINES := -DSDL2_PORT -DANDROID_NDK

LOCAL_CFLAGS += -O3 -ffast-math -fomit-frame-pointer $(DEFINES)

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include $(LOCAL_PATH)/$(SDL_MIXER_PATH) $(LOCAL_PATH)/$(AAAA_PATH)

# Add your application source files here...
LOCAL_SRC_FILES := $(SDL_PATH)/src/main/android/SDL_android_main.c \
	$(AAAA_PATH)/zlext/android_extras.c \
	$(AAAA_PATH)/bullets.c \
	$(AAAA_PATH)/camera.c \
	$(AAAA_PATH)/drawmob.c \
	$(AAAA_PATH)/game.c \
	$(AAAA_PATH)/gamemenu.c \
	$(AAAA_PATH)/gamescene.c \
	$(AAAA_PATH)/intro.c \
	$(AAAA_PATH)/main.c \
	$(AAAA_PATH)/mobai.c \
	$(AAAA_PATH)/mobs.c \
	$(AAAA_PATH)/narrator.c \
	$(AAAA_PATH)/particles.c \
	$(AAAA_PATH)/playcontrol.c \
	$(AAAA_PATH)/render.c \
	$(AAAA_PATH)/sprites.c \
	$(AAAA_PATH)/vars.c \
	$(AAAA_PATH)/veryblend.c \
	$(AAAA_PATH)/wlight.c \
	$(AAAA_PATH)/wmapgen.c \
	$(AAAA_PATH)/wmapload.c \
	$(AAAA_PATH)/zcore.c \
	$(AAAA_PATH)/zcsound.c \
	$(AAAA_PATH)/zctables.c \
	$(AAAA_PATH)/zeditmode.c \
	$(AAAA_PATH)/zgui.c \
	$(AAAA_PATH)/zlext.c \
	$(AAAA_PATH)/zlmath.c \
	$(AAAA_PATH)/zresm.c


LOCAL_SHARED_LIBRARIES := SDL2 SDL2_mixer

LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog

include $(BUILD_SHARED_LIBRARY)
