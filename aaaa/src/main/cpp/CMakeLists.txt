##########################################################################################
## The MIT License (MIT)
##
## Copyright (c) 2017 EXL
##
## Permission is hereby granted, free of charge, to any person obtaining a copy
## of this software and associated documentation files (the "Software"), to deal
## in the Software without restriction, including without limitation the rights
## to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
## copies of the Software, and to permit persons to whom the Software is
## furnished to do so, subject to the following conditions:
##
## The above copyright notice and this permission notice shall be included in all
## copies or substantial portions of the Software.
##
## THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
## IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
## FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
## AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
## LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
## OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
## SOFTWARE.
##########################################################################################

cmake_minimum_required(VERSION 3.4.1)
project("AAAA-Engine")

option(ANDROID "Enable Android Build instead Desktop" ON)

include_directories(${PROJECT_NAME})

set(HEADERS AAAA-Engine/bullets.h
            AAAA-Engine/camera.h
            AAAA-Engine/drawmob.h
            AAAA-Engine/game.h
            AAAA-Engine/gamemenu.h
            AAAA-Engine/gamescene.h
            AAAA-Engine/intro.h
            AAAA-Engine/mobai.h
            AAAA-Engine/mobs.h
            AAAA-Engine/narrator.h
            AAAA-Engine/particles.h
            AAAA-Engine/playcontrol.h
            AAAA-Engine/render.h
            AAAA-Engine/sprites.h
            AAAA-Engine/vars.h
            AAAA-Engine/veryblend.h
            AAAA-Engine/wlight.h
            AAAA-Engine/wmapgen.h
            AAAA-Engine/wmapload.h
            AAAA-Engine/zcore.h
            AAAA-Engine/zcsound.h
            AAAA-Engine/zctables.h
            AAAA-Engine/zeditmode.h
            AAAA-Engine/zgui.h
            AAAA-Engine/zlext.h
            AAAA-Engine/zlmath.h
            AAAA-Engine/zresm.h
            AAAA-Engine/ztypes.h)

set(SOURCES AAAA-Engine/bullets.c
            AAAA-Engine/camera.c
            AAAA-Engine/drawmob.c
            AAAA-Engine/game.c
            AAAA-Engine/gamemenu.c
            AAAA-Engine/gamescene.c
            AAAA-Engine/intro.c
            AAAA-Engine/main.c
            AAAA-Engine/mobai.c
            AAAA-Engine/mobs.c
            AAAA-Engine/narrator.c
            AAAA-Engine/particles.c
            AAAA-Engine/playcontrol.c
            AAAA-Engine/render.c
            AAAA-Engine/sprites.c
            AAAA-Engine/vars.c
            AAAA-Engine/veryblend.c
            AAAA-Engine/wlight.c
            AAAA-Engine/wmapgen.c
            AAAA-Engine/wmapload.c
            AAAA-Engine/zcore.c
            AAAA-Engine/zcsound.c
            AAAA-Engine/zctables.c
            AAAA-Engine/zeditmode.c
            AAAA-Engine/zgui.c
            AAAA-Engine/zlext.c
            AAAA-Engine/zlmath.c
            AAAA-Engine/zresm.c)

if(ANDROID)
    add_definitions(-DSDL2_PORT -DANDROID_NDK -DGL_GLEXT_PROTOTYPES -DWAV_MUSIC -DOGG_MUSIC -DOGG_USE_TREMOR -DOGG_HEADER="<ivorbisfile.h>" -D_ARM_ASSEM_)

    ## SDL2
    set(SDL2 "SDL2")
    set(SDL2_HEADERS ${SDL2}/src/events/scancodes_linux.h
                ${SDL2}/src/events/SDL_sysevents.h
                ${SDL2}/src/events/SDL_clipboardevents_c.h
                ${SDL2}/src/events/SDL_touch_c.h
                ${SDL2}/src/events/SDL_events_c.h
                ${SDL2}/src/events/blank_cursor.h
                ${SDL2}/src/events/scancodes_darwin.h
                ${SDL2}/src/events/SDL_dropevents_c.h
                ${SDL2}/src/events/SDL_gesture_c.h
                ${SDL2}/src/events/SDL_windowevents_c.h
                ${SDL2}/src/events/default_cursor.h
                ${SDL2}/src/events/scancodes_xfree86.h
                ${SDL2}/src/events/SDL_keyboard_c.h
                ${SDL2}/src/events/SDL_mouse_c.h
                ${SDL2}/src/events/scancodes_windows.h
                ${SDL2}/src/SDL_assert_c.h
                ${SDL2}/src/thread/SDL_thread_c.h
                ${SDL2}/src/thread/pthread/SDL_sysmutex_c.h
                ${SDL2}/src/thread/pthread/SDL_systhread_c.h
                ${SDL2}/src/thread/SDL_systhread.h
                ${SDL2}/src/dynapi/SDL_dynapi_procs.h
                ${SDL2}/src/dynapi/SDL_dynapi.h
                ${SDL2}/src/dynapi/SDL_dynapi_overrides.h
                ${SDL2}/src/SDL_internal.h
                ${SDL2}/src/video/SDL_sysvideo.h
                ${SDL2}/src/video/SDL_rect_c.h
                ${SDL2}/src/video/SDL_RLEaccel_c.h
                ${SDL2}/src/video/SDL_pixels_c.h
                ${SDL2}/src/video/SDL_shape_internals.h
                ${SDL2}/src/video/SDL_blit.h
                ${SDL2}/src/video/SDL_blit_slow.h
                ${SDL2}/src/video/SDL_blit_auto.h
                ${SDL2}/src/video/android/SDL_androidmessagebox.h
                ${SDL2}/src/video/android/SDL_androidwindow.h
                ${SDL2}/src/video/android/SDL_androidclipboard.h
                ${SDL2}/src/video/android/SDL_androidtouch.h
                ${SDL2}/src/video/android/SDL_androidevents.h
                ${SDL2}/src/video/android/SDL_androidvideo.h
                ${SDL2}/src/video/android/SDL_androidmouse.h
                ${SDL2}/src/video/android/SDL_androidkeyboard.h
                ${SDL2}/src/video/SDL_egl_c.h
                ${SDL2}/src/video/SDL_blit_copy.h
                ${SDL2}/src/libm/math_private.h
                ${SDL2}/src/libm/math_libm.h
                ${SDL2}/src/audio/SDL_wave.h
                ${SDL2}/src/audio/SDL_audio_c.h
                ${SDL2}/src/audio/SDL_audiodev_c.h
                ${SDL2}/src/audio/android/SDL_androidaudio.h
                ${SDL2}/src/audio/SDL_sysaudio.h
                ${SDL2}/src/core/android/SDL_android.h
                ${SDL2}/src/timer/SDL_timer_c.h
                ${SDL2}/src/haptic/SDL_syshaptic.h
                ${SDL2}/src/haptic/SDL_haptic_c.h
                ${SDL2}/src/joystick/SDL_joystick_c.h
                ${SDL2}/src/joystick/SDL_sysjoystick.h
                ${SDL2}/src/joystick/SDL_gamecontrollerdb.h
                ${SDL2}/src/joystick/android/SDL_sysjoystick_c.h
                ${SDL2}/src/SDL_error_c.h
                ${SDL2}/src/render/SDL_sysrender.h
                ${SDL2}/src/render/SDL_yuv_sw_c.h
                ${SDL2}/src/render/software/SDL_blendpoint.h
                ${SDL2}/src/render/software/SDL_drawline.h
                ${SDL2}/src/render/software/SDL_blendfillrect.h
                ${SDL2}/src/render/software/SDL_render_sw_c.h
                ${SDL2}/src/render/software/SDL_rotate.h
                ${SDL2}/src/render/software/SDL_draw.h
                ${SDL2}/src/render/software/SDL_drawpoint.h
                ${SDL2}/src/render/software/SDL_blendline.h
                ${SDL2}/src/render/opengles/SDL_glesfuncs.h
                ${SDL2}/include/SDL_platform.h
                ${SDL2}/include/SDL_gesture.h
                ${SDL2}/include/SDL_config_wiz.h
                ${SDL2}/include/SDL_opengles2.h
                ${SDL2}/include/close_code.h
                ${SDL2}/include/SDL_keycode.h
                ${SDL2}/include/SDL_config_iphoneos.h
                ${SDL2}/include/SDL.h
                ${SDL2}/include/SDL_error.h
                ${SDL2}/include/SDL_revision.h
                ${SDL2}/include/SDL_config_pandora.h
                ${SDL2}/include/SDL_filesystem.h
                ${SDL2}/include/SDL_surface.h
                ${SDL2}/include/SDL_audio.h
                ${SDL2}/include/SDL_types.h
                ${SDL2}/include/SDL_assert.h
                ${SDL2}/include/SDL_events.h
                ${SDL2}/include/SDL_stdinc.h
                ${SDL2}/include/SDL_test_log.h
                ${SDL2}/include/SDL_messagebox.h
                ${SDL2}/include/SDL_test_fuzzer.h
                ${SDL2}/include/SDL_loadso.h
                ${SDL2}/include/SDL_blendmode.h
                ${SDL2}/include/SDL_atomic.h
                ${SDL2}/include/SDL_opengles.h
                ${SDL2}/include/SDL_opengles2_gl2.h
                ${SDL2}/include/SDL_copying.h
                ${SDL2}/include/SDL_name.h
                ${SDL2}/include/SDL_config_psp.h
                ${SDL2}/include/SDL_rect.h
                ${SDL2}/include/begin_code.h
                ${SDL2}/include/SDL_test_harness.h
                ${SDL2}/include/SDL_cpuinfo.h
                ${SDL2}/include/SDL_touch.h
                ${SDL2}/include/SDL_mutex.h
                ${SDL2}/include/SDL_test.h
                ${SDL2}/include/SDL_power.h
                ${SDL2}/include/SDL_pixels.h
                ${SDL2}/include/SDL_config.h
                ${SDL2}/include/SDL_opengles2_gl2ext.h
                ${SDL2}/include/SDL_config_winrt.h
                ${SDL2}/include/SDL_test_crc32.h
                ${SDL2}/include/SDL_test_images.h
                ${SDL2}/include/SDL_scancode.h
                ${SDL2}/include/SDL_egl.h
                ${SDL2}/include/SDL_version.h
                ${SDL2}/include/SDL_config_android.h
                ${SDL2}/include/SDL_test_font.h
                ${SDL2}/include/SDL_bits.h
                ${SDL2}/include/SDL_endian.h
                ${SDL2}/include/SDL_quit.h
                ${SDL2}/include/SDL_mouse.h
                ${SDL2}/include/SDL_hints.h
                ${SDL2}/include/SDL_log.h
                ${SDL2}/include/SDL_haptic.h
                ${SDL2}/include/SDL_main.h
                ${SDL2}/include/SDL_system.h
                ${SDL2}/include/SDL_test_assert.h
                ${SDL2}/include/SDL_syswm.h
                ${SDL2}/include/SDL_test_random.h
                ${SDL2}/include/SDL_opengl_glext.h
                ${SDL2}/include/SDL_joystick.h
                ${SDL2}/include/SDL_render.h
                ${SDL2}/include/SDL_clipboard.h
                ${SDL2}/include/SDL_keyboard.h
                ${SDL2}/include/SDL_thread.h
                ${SDL2}/include/SDL_video.h
                ${SDL2}/include/SDL_gamecontroller.h
                ${SDL2}/include/SDL_config_windows.h
                ${SDL2}/include/SDL_config_minimal.h
                ${SDL2}/include/SDL_opengl.h
                ${SDL2}/include/SDL_test_compare.h
                ${SDL2}/include/SDL_opengles2_gl2platform.h
                ${SDL2}/include/SDL_config_macosx.h
                ${SDL2}/include/SDL_timer.h
                ${SDL2}/include/SDL_opengles2_khrplatform.h
                ${SDL2}/include/SDL_shape.h
                ${SDL2}/include/SDL_test_common.h
                ${SDL2}/include/SDL_rwops.h
                ${SDL2}/include/SDL_test_md5.h)
    set(SDL2_SOURCES ${SDL2}/src/SDL_assert.c
                ${SDL2}/src/events/SDL_gesture.c
                ${SDL2}/src/events/SDL_keyboard.c
                ${SDL2}/src/events/SDL_mouse.c
                ${SDL2}/src/events/SDL_events.c
                ${SDL2}/src/events/SDL_touch.c
                ${SDL2}/src/events/SDL_quit.c
                ${SDL2}/src/events/SDL_clipboardevents.c
                ${SDL2}/src/events/SDL_windowevents.c
                ${SDL2}/src/events/SDL_dropevents.c
                ${SDL2}/src/loadso/dlopen/SDL_sysloadso.c
                ${SDL2}/src/atomic/SDL_atomic.c
                ${SDL2}/src/atomic/SDL_spinlock.c
                ${SDL2}/src/filesystem/android/SDL_sysfilesystem.c
                ${SDL2}/src/thread/pthread/SDL_syscond.c
                ${SDL2}/src/thread/pthread/SDL_systhread.c
                ${SDL2}/src/thread/pthread/SDL_syssem.c
                ${SDL2}/src/thread/pthread/SDL_sysmutex.c
                ${SDL2}/src/thread/pthread/SDL_systls.c
                ${SDL2}/src/thread/SDL_thread.c
                ${SDL2}/src/SDL_log.c
                ${SDL2}/src/dynapi/SDL_dynapi.c
                ${SDL2}/src/SDL_hints.c
                ${SDL2}/src/video/SDL_blit.c
                ${SDL2}/src/video/SDL_clipboard.c
                ${SDL2}/src/video/SDL_egl.c
                ${SDL2}/src/video/SDL_blit_auto.c
                ${SDL2}/src/video/SDL_blit_N.c
                ${SDL2}/src/video/SDL_blit_1.c
                ${SDL2}/src/video/SDL_pixels.c
                ${SDL2}/src/video/SDL_bmp.c
                ${SDL2}/src/video/SDL_blit_copy.c
                ${SDL2}/src/video/SDL_RLEaccel.c
                ${SDL2}/src/video/SDL_blit_slow.c
                ${SDL2}/src/video/SDL_shape.c
                ${SDL2}/src/video/SDL_blit_0.c
                ${SDL2}/src/video/SDL_surface.c
                ${SDL2}/src/video/SDL_stretch.c
                ${SDL2}/src/video/SDL_video.c
                ${SDL2}/src/video/SDL_fillrect.c
                ${SDL2}/src/video/SDL_blit_A.c
                ${SDL2}/src/video/android/SDL_androidkeyboard.c
                ${SDL2}/src/video/android/SDL_androidvideo.c
                ${SDL2}/src/video/android/SDL_androidevents.c
                ${SDL2}/src/video/android/SDL_androidmouse.c
                ${SDL2}/src/video/android/SDL_androidgl.c
                ${SDL2}/src/video/android/SDL_androidmessagebox.c
                ${SDL2}/src/video/android/SDL_androidwindow.c
                ${SDL2}/src/video/android/SDL_androidtouch.c
                ${SDL2}/src/video/android/SDL_androidclipboard.c
                ${SDL2}/src/video/SDL_rect.c
                ${SDL2}/src/SDL_error.c
                ${SDL2}/src/audio/SDL_mixer.c
                ${SDL2}/src/audio/SDL_audio.c
                ${SDL2}/src/audio/SDL_audiotypecvt.c
                ${SDL2}/src/audio/SDL_audiodev.c
                ${SDL2}/src/audio/SDL_wave.c
                ${SDL2}/src/audio/SDL_audiocvt.c
                ${SDL2}/src/audio/android/SDL_androidaudio.c
                ${SDL2}/src/core/android/SDL_android.c
                ${SDL2}/src/timer/unix/SDL_systimer.c
                ${SDL2}/src/timer/SDL_timer.c
                ${SDL2}/src/SDL.c
                ${SDL2}/src/haptic/SDL_haptic.c
                ${SDL2}/src/stdlib/SDL_iconv.c
                ${SDL2}/src/stdlib/SDL_malloc.c
                ${SDL2}/src/stdlib/SDL_string.c
                ${SDL2}/src/stdlib/SDL_stdlib.c
                ${SDL2}/src/stdlib/SDL_getenv.c
                ${SDL2}/src/stdlib/SDL_qsort.c
                ${SDL2}/src/joystick/SDL_gamecontroller.c
                ${SDL2}/src/joystick/SDL_joystick.c
                ${SDL2}/src/joystick/android/SDL_sysjoystick.c
                ${SDL2}/src/cpuinfo/SDL_cpuinfo.c
                ${SDL2}/src/render/SDL_render.c
                ${SDL2}/src/render/software/SDL_blendpoint.c
                ${SDL2}/src/render/software/SDL_drawpoint.c
                ${SDL2}/src/render/software/SDL_blendfillrect.c
                ${SDL2}/src/render/software/SDL_drawline.c
                ${SDL2}/src/render/software/SDL_render_sw.c
                ${SDL2}/src/render/software/SDL_blendline.c
                ${SDL2}/src/render/software/SDL_rotate.c
                ${SDL2}/src/render/opengles/SDL_render_gles.c
                ${SDL2}/src/render/SDL_yuv_sw.c
                ${SDL2}/src/file/SDL_rwops.c)
    add_library(${SDL2} SHARED ${SDL2_SOURCES} ${SDL2_HEADERS})
    target_link_libraries(${SDL2} dl GLESv1_CM GLESv2 log android)

    ## SDL2_mixer
    set(SDL2_MIXER "SDL2_mixer")
    set(SDL2_MIXER_HEADERS ${SDL2_MIXER}/dynamic_ogg.h
                ${SDL2_MIXER}/SDL_mixer.h
                ${SDL2_MIXER}/load_ogg.h
                ${SDL2_MIXER}/music_ogg.h
                ${SDL2_MIXER}/music_mod.h
                ${SDL2_MIXER}/music_mad.h
                ${SDL2_MIXER}/dynamic_mp3.h
                ${SDL2_MIXER}/music_modplug.h
                ${SDL2_MIXER}/fluidsynth.h
                ${SDL2_MIXER}/load_voc.h
                ${SDL2_MIXER}/external/libogg-1.3.1/include/ogg/os_types.h
                ${SDL2_MIXER}/external/libogg-1.3.1/include/ogg/config_types.h
                ${SDL2_MIXER}/external/libogg-1.3.1/include/ogg/ogg.h
                ${SDL2_MIXER}/external/libvorbisidec-1.2.1/codec_internal.h
                ${SDL2_MIXER}/external/libvorbisidec-1.2.1/ivorbisfile.h
                ${SDL2_MIXER}/external/libvorbisidec-1.2.1/ivorbiscodec.h
                ${SDL2_MIXER}/external/libvorbisidec-1.2.1/window_lookup.h
                ${SDL2_MIXER}/external/libvorbisidec-1.2.1/lsp_lookup.h
                ${SDL2_MIXER}/external/libvorbisidec-1.2.1/mdct.h
                ${SDL2_MIXER}/external/libvorbisidec-1.2.1/os.h
                ${SDL2_MIXER}/external/libvorbisidec-1.2.1/misc.h
                ${SDL2_MIXER}/external/libvorbisidec-1.2.1/mdct_lookup.h
                ${SDL2_MIXER}/external/libvorbisidec-1.2.1/block.h
                ${SDL2_MIXER}/external/libvorbisidec-1.2.1/codebook.h
                ${SDL2_MIXER}/external/libvorbisidec-1.2.1/registry.h
                ${SDL2_MIXER}/external/libvorbisidec-1.2.1/asm_arm.h
                ${SDL2_MIXER}/external/libvorbisidec-1.2.1/config_types.h
                ${SDL2_MIXER}/external/libvorbisidec-1.2.1/window.h
                ${SDL2_MIXER}/external/libvorbisidec-1.2.1/backends.h
                ${SDL2_MIXER}/load_mp3.h
                ${SDL2_MIXER}/wavestream.h
                ${SDL2_MIXER}/music_cmd.h
                ${SDL2_MIXER}/music_flac.h
                ${SDL2_MIXER}/dynamic_modplug.h
                ${SDL2_MIXER}/dynamic_flac.h
                ${SDL2_MIXER}/dynamic_mod.h
                ${SDL2_MIXER}/dynamic_fluidsynth.h
                ${SDL2_MIXER}/effects_internal.h
                ${SDL2_MIXER}/load_flac.h
                ${SDL2_MIXER}/load_aiff.h)
    set(SDL2_MIXER_SOURCES ${SDL2_MIXER}/music_mad.c
                ${SDL2_MIXER}/effects_internal.c
                ${SDL2_MIXER}/dynamic_mod.c
                ${SDL2_MIXER}/load_ogg.c
                ${SDL2_MIXER}/music_flac.c
                ${SDL2_MIXER}/load_flac.c
                ${SDL2_MIXER}/load_mp3.c
                ${SDL2_MIXER}/effect_position.c
                ${SDL2_MIXER}/music_modplug.c
                ${SDL2_MIXER}/wavestream.c
                ${SDL2_MIXER}/dynamic_modplug.c
                ${SDL2_MIXER}/music_ogg.c
                ${SDL2_MIXER}/load_voc.c
                ${SDL2_MIXER}/effect_stereoreverse.c
                ${SDL2_MIXER}/music.c
                ${SDL2_MIXER}/fluidsynth.c
                ${SDL2_MIXER}/playmus.c
                ${SDL2_MIXER}/external/libogg-1.3.1/src/bitwise.c
                ${SDL2_MIXER}/external/libogg-1.3.1/src/framing.c
                ${SDL2_MIXER}/external/libvorbisidec-1.2.1/codebook.c
                ${SDL2_MIXER}/external/libvorbisidec-1.2.1/info.c
                ${SDL2_MIXER}/external/libvorbisidec-1.2.1/window.c
                ${SDL2_MIXER}/external/libvorbisidec-1.2.1/vorbisfile.c
                ${SDL2_MIXER}/external/libvorbisidec-1.2.1/res012.c
                ${SDL2_MIXER}/external/libvorbisidec-1.2.1/registry.c
                ${SDL2_MIXER}/external/libvorbisidec-1.2.1/ivorbisfile_example.c
                ${SDL2_MIXER}/external/libvorbisidec-1.2.1/synthesis.c
                ${SDL2_MIXER}/external/libvorbisidec-1.2.1/iseeking_example.c
                ${SDL2_MIXER}/external/libvorbisidec-1.2.1/floor0.c
                ${SDL2_MIXER}/external/libvorbisidec-1.2.1/mdct.c
                ${SDL2_MIXER}/external/libvorbisidec-1.2.1/floor1.c
                ${SDL2_MIXER}/external/libvorbisidec-1.2.1/sharedbook.c
                ${SDL2_MIXER}/external/libvorbisidec-1.2.1/block.c
                ${SDL2_MIXER}/external/libvorbisidec-1.2.1/mapping0.c
                ${SDL2_MIXER}/dynamic_mp3.c
                ${SDL2_MIXER}/music_cmd.c
                ${SDL2_MIXER}/music_mod.c
                ${SDL2_MIXER}/mixer.c
                ${SDL2_MIXER}/load_aiff.c
                ${SDL2_MIXER}/dynamic_flac.c
                ${SDL2_MIXER}/dynamic_ogg.c
                ${SDL2_MIXER}/dynamic_fluidsynth.c
                ${SDL2_MIXER}/playwave.c)
    add_library(${SDL2_MIXER} SHARED ${SDL2_MIXER_SOURCES} ${SDL2_MIXER_HEADERS})
    target_link_libraries(${SDL2_MIXER} ${SDL2})

    include_directories(${INCLUDE_DIRECTORIES}
                ${SDL2}/include ${SDL2_MIXER}
                ${SDL2_MIXER}/external/libogg-1.3.1 ${SDL2_MIXER}/external/libvorbisidec-1.2.1/)
    set(HEADERS ${HEADERS} ru_exlmoto_aaaa_AAAANativeLibProxy.h
                ${PROJECT_NAME}/zlext/android_extras.h)
    set(SOURCES ${PROJECT_NAME}/zlext/android_extras.c
                ${SDL2}/src/main/android/SDL_android_main.c)
    add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})
    target_link_libraries(${PROJECT_NAME} ${SDL2} ${SDL2_MIXER} log GLESv1_CM)
else()
    option(GLES "Enable OpenGL ES instead OpenGL" OFF)

    # Deploy Game Files and Executable.
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../../assets_obb/AAAA-Data/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE})

    # Add Cmake path with additional modules.
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

    find_package(OpenGL REQUIRED)
    find_package(SDL2 REQUIRED)
    find_package(SDL2_mixer REQUIRED)

    include_directories(${PROJECT_NAME} ${OPENGL_INCLUDE_DIRS} ${SDL2_INCLUDE_DIR} ${SDL2_MIXER_INCLUDE_DIR})

    if(GLES)
        message(STATUS "Build using OpenGLES libraries!")
        set(TARGET_NAME "AAAA-Engine-gles")
        find_package(OpenGLES REQUIRED)
        add_definitions(-DPC_GLES -DSDL2_PORT)
        include_directories(${INCLUDE_DIRECTORIES} ${OPENGLES_INCLUDE_DIR})
    else()
        set(TARGET_NAME ${PROJECT_NAME})
        add_definitions(-DPC_GL -DSDL2_PORT)
    endif()

    add_executable(${TARGET_NAME} ${SOURCES} ${HEADERS})
    target_link_libraries(${TARGET_NAME} ${SDL2_LIBRARY} ${SDL2_MIXER_LIBRARY} ${OPENGL_LIBRARIES} m)
    if(GLES)
        target_link_libraries(${TARGET_NAME} ${OPENGLES_LIBRARIES})
    endif()

    # Show final message when build done.
    add_custom_target(finalMessage ALL
        ${CMAKE_COMMAND} -E cmake_echo_color --green "Output directory: ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}, executable: ${TARGET_NAME}."
        COMMENT "Final Message")
    add_dependencies(finalMessage ${TARGET_NAME})
endif()
