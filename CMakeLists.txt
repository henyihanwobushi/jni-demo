cmake_minimum_required(VERSION 3.15)
project(ping_pong)
set(CMAKE_BUILD_TYPE Release)

# add JNI dependency
find_package(JNI REQUIRED)
include_directories(${JNI_INCLUDE_DIRS})

set(CMAKE_OSX_ARCHITECTURES "x86_64")

set(SOURCE_FILES com_foo_Bar.cpp com_foo_Bar.h)

# add library, the library name should be the same as the library name in Java
add_library(ping_pong SHARED ${SOURCE_FILES})
