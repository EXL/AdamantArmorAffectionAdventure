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

cmake_minimum_required(VERSION 2.8)
project("AAAA-Engine")

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
