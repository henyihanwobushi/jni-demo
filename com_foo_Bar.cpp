#include "com_foo_Bar.h"
#include <string>
#include <iostream>


JNIEXPORT jstring JNICALL Java_com_foo_Bar_pong
        (JNIEnv *jEnv, jclass jClass, jstring jStr) {
    std::string str = jEnv->GetStringUTFChars(jStr, nullptr);
    std::cout << str << " from java..." << std::endl;
    return jEnv->NewStringUTF("pong");
}