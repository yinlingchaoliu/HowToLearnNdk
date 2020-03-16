
cmake_minimum_required(VERSION 3.4.1)

add_library( # Sets the name of the library.
        native-lib

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        src/main/jni/native-lib.c
        src/main/jni/bitmap/bitmapops.cpp
        src/main/jni/thread/jvmthread.cpp
        )

include_directories(src/main/jni/util)
include_directories(src/main/jni/bitmap)
include_directories(src/main/jni/thread)

find_library(
        log-lib
        log)


target_link_libraries( # Specifies the target library.
        native-lib
        jnigraphics  # bitmap处理库
        # included in the NDK.
        ${log-lib})