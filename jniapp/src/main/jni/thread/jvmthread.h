//
// Created by glumes on 2018/5/29.
//
#include <jni.h>
#include <pthread.h>

#ifndef ANDROIDCPPSOLIB_THREAD_OPERATION_H
#define ANDROIDCPPSOLIB_THREAD_OPERATION_H


struct ThreadRunArgs {
    JNIEnv *env;
    jint id;
    jint result;
    jobject runObj;
    jmethodID runMid;
};


#ifdef __cplusplus
extern "C" {
#endif

//初始化挂载
JNIEXPORT int JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) ;

JNIEXPORT void JNICALL
Java_com_chaoliu_jniapp_NativeThread_nativeInit(JNIEnv *env, jclass type) ;

JNIEXPORT void JNICALL
Java_com_chaoliu_jniapp_NativeThread_createNativeThread(JNIEnv *env, jclass type, jobject obj) ;

JNIEXPORT void JNICALL
Java_com_chaoliu_jniapp_NativeThread_posixThreads(JNIEnv *env, jclass type, jobject runObj, jint threadnum) ;
JNIEXPORT void JNICALL
Java_com_chaoliu_jniapp_NativeThread_nativeFree(JNIEnv *env, jclass type) ;

//挂载销毁
JNIEXPORT void JNI_OnUnload(JavaVM* vm, void* reserved);

#ifdef __cplusplus
}
#endif
#endif //ANDROIDCPPSOLIB_THREAD_OPERATION_H
