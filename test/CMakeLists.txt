cmake_minimum_required(VERSION 3.7 FATAL_ERROR)
project(test)

option(DOKUN_USE_GLFW "Build dokun-ui with GLFW" ON)
option(DOKUN_USE_OPENGL "Build dokun-ui with OpenGL" ON)
option(DOKUN_USE_VULKAN "Build dokun-ui with Vulkan" OFF)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ../build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../build)


include_directories(../include)

include_directories(../external/lua/lua-5.4.1/src) # lua
include_directories(../external/glew/include)
include_directories(../external/png ../external/zlib)
include_directories(../external/freetype/include                   # public headers - ft2build.h
   ../external/freetype/include/freetype           # public headers
   ../external/freetype/include/freetype/config    # public config headers
   ../external/freetype/include/freetype/internal) # private headers - added 2019-07-29
include_directories(../external/ogg/include)
include_directories(../external/vorbis/include
   ../external/vorbis/lib)
include_directories(../external/theora/include)
#include_directories(../external/utf8/source)
include_directories(../external/openal/include
   ../external/openal-soft/include)
include_directories(../external/jpeg
   ../external/jpeg/jpeg-6b)
include_directories(../external/tiff/libtiff)
include_directories(../external/gif/lib)
include_directories(#[[../external/flac]] # config.h
   ../external/flac/include
   ../external/flac/src/libFLAC/include) # for "private/cpu.h"
include_directories(../external/glm)

link_directories(../src)


set(test_main "main")
add_executable(${test_main} main.cpp)
#target_link_directories(${test_main} PUBLIC ../src)
#target_include_directories(${test_main} PUBLIC ../include)
set(dokun_ui_src libdokun-ui.a) # includes definitions: DOKUN_BUILD_LIBRARY, DOKUN_USE_GLFW, DOKUN_USE_OPENGL #target_compile_definitions(${test_main} PUBLIC DOKUN_BUILD_LIBRARY)
target_link_libraries(${test_main} ${dokun_ui_src})


if(WIN32) # -lglfw3 -lgdi32 -lopengl32 -limm32
endif()
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(posix_src libpthread.so libdl.so libm.so   )
    target_link_libraries(${test_main} ${posix_src})
    find_package(X11 REQUIRED)
    if(X11_FOUND)
	    target_link_libraries(${test_main} ${X11_LIBRARIES})
    endif()
endif()
set(OpenGL_GL_PREFERENCE "LEGACY")
find_package(OpenGL REQUIRED)
if(OPENGL_FOUND)
if(DOKUN_USE_OPENGL) # -DDOKUN_USE_OPENGL=1
    message(STATUS "Using OpenGL: ${OPENGL_LIBRARIES}")
    target_compile_definitions(${test_main} PRIVATE DOKUN_USE_OPENGL)
	target_link_libraries(${test_main} ${OPENGL_LIBRARIES})
endif()
endif()
find_package(Vulkan) # optional - requires cmake version 3.7
if(Vulkan_FOUND)
if(DOKUN_USE_VULKAN) # -DDOKUN_USE_VULKAN=1
	message(STATUS "Using Vulkan: ${Vulkan_LIBRARIES}")# at ${Vulkan_INCLUDE_DIRS} (v${Vulkan_VERSION})") # Vulkan_VERSION requires cmake version 3.23
	target_compile_definitions(${test_main} PRIVATE DOKUN_USE_VULKAN) # should be defined when building libdokun-ui.a instead
	target_link_libraries(${test_main} ${Vulkan_LIBRARIES})
endif()
endif()
find_package(GLFW3)# REQUIRED)
if(GLFW3_FOUND)
if(DOKUN_USE_GLFW) # -DDOKUN_USE_GLFW=1
    message(STATUS "Using GLFW3: ${GLFW3_LIBRARY}")
	target_compile_definitions(${test_main} PRIVATE DOKUN_USE_GLFW) # already defined in libdokun-ui.a
    target_link_libraries(${test_main} ${GLFW3_LIBRARY})
endif()
endif()
