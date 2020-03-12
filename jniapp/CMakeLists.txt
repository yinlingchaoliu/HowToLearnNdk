
cmake_minimum_required(VERSION 3.4.1)

add_library( # Sets the name of the library.
        native-lib

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        src/main/cpp/native-lib.cpp
        src/main/cpp/bitmap/bitmapops.c
        src/main/cpp/thread/jvmthread.c

        )

include_directories(src/main/cpp/bitmap)
include_directories(src/main/cpp/thread)


find_library(
        log-lib
        log)


target_link_libraries( # Specifies the target library.
        native-lib
        # included in the NDK.
        ${log-lib})