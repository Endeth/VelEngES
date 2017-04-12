cmake_minimum_required(VERSION 3.6.0)
project (NativeLib)


set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fno-rtti -fno-exceptions -Wall")


set(OPENGL_LIB GLESv3)

add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/OpenGL)

set(SOURCE ${SOURCE} ${CMAKE_CURRENT_SOURCE_DIR}/JNIOpenGL.cpp ${CMAKE_CURRENT_SOURCE_DIR}/JNIGesture.cpp ${CMAKE_CURRENT_SOURCE_DIR}/JNIActivity.cpp)
add_library(NativeLib SHARED
            ${SOURCE} ${HEADERS})
			
# Include libraries needed for gles3jni lib
target_link_libraries(NativeLib
                      ${OPENGL_LIB}
                      android
                      EGL
                      log
                      m)