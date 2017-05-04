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
    add_definitions(-DSDL2_PORT -DANDROID_NDK -DGL_GLEXT_PROTOTYPES
            -DWAV_MUSIC -DOGG_MUSIC -DOGG_USE_TREMOR -DOGG_HEADER=<ivorbisfile.h>)

    if(ANDROID_ABI MATCHES "armeabi")
        add_definitions(-D_ARM_ASSEM_)
    endif()

    # SDL2
    set(SDL2 "SDL2")
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
    add_library(${SDL2} SHARED ${SDL2_SOURCES})
    target_link_libraries(${SDL2} dl GLESv1_CM GLESv2 log android)

    # SDL2_mixer
    set(SDL2_MIXER "SDL2_mixer")
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
                ${SDL2_MIXER}/external/libvorbisidec-1.2.1/synthesis.c
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
                ${SDL2_MIXER}/dynamic_fluidsynth.c)
    add_library(${SDL2_MIXER} SHARED ${SDL2_MIXER_SOURCES})
    target_link_libraries(${SDL2_MIXER} ${SDL2})

    include_directories(${INCLUDE_DIRECTORIES}
                ${SDL2}/include ${SDL2_MIXER}
                ${SDL2_MIXER}/external/libogg-1.3.1/include ${SDL2_MIXER}/external/libvorbisidec-1.2.1/)
    set(SOURCES ${SOURCES} ${PROJECT_NAME}/zlext/android_extras.c
                ${SDL2}/src/main/android/SDL_android_main.c)

    add_library(${PROJECT_NAME} SHARED ${SOURCES})
    target_link_libraries(${PROJECT_NAME} ${SDL2} ${SDL2_MIXER} log GLESv1_CM)
else()
    option(GLES "Enable OpenGL ES instead OpenGL" OFF)

    # Deploy Game Files and Executable.
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../../../../assets_obb/AAAA-Data/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE})

    # Add Cmake path with additional modules.
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

    find_package(OpenGL REQUIRED)
    find_package(SDL2 REQUIRED)
    find_package(SDL2_mixer REQUIRED)

    include_directories(${PROJECT_NAME} ${OPENGL_INCLUDE_DIRS} ${SDL2_INCLUDE_DIR} ${SDL2_MIXER_INCLUDE_DIR})

    if(GLES)
        message(STATUS "Build w/ using OpenGLES libraries!")
        set(TARGET_NAME "AAAA-Engine-gles")
        find_package(OpenGLES REQUIRED)
        add_definitions(-DPC_GLES -DSDL2_PORT)
        include_directories(${INCLUDE_DIRECTORIES} ${OPENGLES_INCLUDE_DIR})
    else()
        message(STATUS "Build w/ using OpenGL libraries!")
        set(TARGET_NAME ${PROJECT_NAME})
        add_definitions(-DPC_GL -DSDL2_PORT)
    endif()

    add_executable(${TARGET_NAME} ${SOURCES})
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
