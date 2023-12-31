# Introduction

Sometimes we need to rewrite core method with C++ to improve performance. For example, hive UDF. We can use [JNI](https://docs.oracle.com/javase/8/docs/technotes/guides/jni/spec/intro.html#java_native_interface_overview) to call C++ method in Java. Here is a simple example.

# The Java Part
First We need to create a Java class and declare a native method. The native method will be implemented in C++.

We create a Java file `com/foo/Bar.java` with the following content.

```java
package com.foo;

public class Bar {
    public native static String pong(String arg);

    static {
        System.loadLibrary("ping_pong");
    }

    public static void main(String[] args) {
        System.out.println(pong("ping") + " from c++...");
    }
}
```

Then we need to compile the Java class and generate a header file.

```bash
javac com/foo/Bar.java
javah -jni com.foo.Bar
```

We will get a C++ header file `com_foo_Bar.h` like this.

```c
/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_foo_Bar */

#ifndef _Included_com_foo_Bar
#define _Included_com_foo_Bar
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_foo_Bar
 * Method:    pong
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_foo_Bar_pong
  (JNIEnv *, jclass, jstring);

#ifdef __cplusplus
}
#endif
#endif
```

# The C++ Part

We create a C++ file `com_foo_Bar.cpp` with the following content to implement the method declared in the header file.

Before we start coding C++, we can define a make files. In this tutorial, we use cmake to manage the project. We create a `CMakeLists.txt` file with the following content.

```cmake
cmake_minimum_required(VERSION 3.15)
project(ping_pong)
set(CMAKE_BUILD_TYPE Release)

# add JNI dependency
find_package(JNI REQUIRED)
include_directories(${JNI_INCLUDE_DIRS})

set(SOURCE_FILES com_foo_Bar.cpp com_foo_Bar.h)

# add library, the library name should be the same as the library name in Java
add_library(ping_pong SHARED ${SOURCE_FILES})
```

Then we can start coding C++.

```c++
#include "com_foo_Bar.h"
#include <string>
#include <iostream>


JNIEXPORT jstring JNICALL Java_com_foo_Bar_pong
        (JNIEnv *jEnv, jclass jClass, jstring jStr) {
    std::string str = jEnv->GetStringUTFChars(jStr, nullptr);
    std::cout << str << " from java..." << std::endl;
    return jEnv->NewStringUTF("pong");
}
```

# Build and Run

We can use cmake to build the project.

```bash
mkdir build
cd build
cmake ..
make
```

Then we can run the Java class.

```bash
cd ..
java -Djava.library.path=./build com.foo.Bar
```

We will get the following output.

```bash
ping from java...
pong from c++...
```

# Reference

- [JNI](https://docs.oracle.com/javase/8/docs/technotes/guides/jni/spec/intro.html#java_native_interface_overview)
- [cmake](https://cmake.org/cmake/help/latest/guide/tutorial/index.html)
