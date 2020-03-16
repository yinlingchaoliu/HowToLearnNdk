//
// Created by 陈桐 on 2020/3/12.
//

#include <jni.h>
#include <android/bitmap.h>

#ifndef HOWTOLEARNNDK_BITMAPOPS_H
#define HOWTOLEARNNDK_BITMAPOPS_H

#ifdef __cplusplus
extern "C" {
#endif


JNIEXPORT jobject JNICALL
Java_com_chaoliu_jniapp_NativeBitmap_rotateBitmap(JNIEnv *env, jobject instance, jobject bitmap);

JNIEXPORT jobject JNICALL
Java_com_chaoliu_jniapp_NativeBitmap_convertBitmap(JNIEnv *env, jobject instance, jobject bitmap);

JNIEXPORT jobject JNICALL
Java_com_chaoliu_jniapp_NativeBitmap_mirrorBitmap(JNIEnv *env, jobject instance, jobject bitmap);


#ifdef __cplusplus
}
#endif
#endif //HOWTOLEARNNDK_BITMAPOPS_H
