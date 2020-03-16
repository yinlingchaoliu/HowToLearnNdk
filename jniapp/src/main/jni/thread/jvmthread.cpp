//
// Created by 陈桐 on 2020/3/12.
//

#include <stdio.h>
#include <jni.h>
#include <pthread.h>
#include "../util/logutil.h"
#include "jvmthread.h"

void posixThreads(JNIEnv *env, jobject runObj, jint threadnum);

//c语言run 方法
void *run(void *args);

jmethodID getRunableMethod(JNIEnv *env, jobject runObj);

void printNativeMsg(JNIEnv *env, jstring msg);

//释放内存
void  nativeFree(JNIEnv *env);

//异常抛出
void throwByName(JNIEnv *env, const char *name, const char *msg) ;

static jmethodID printMsgMid;

static jclass nativeThreadCls = NULL;

//jvm
static JavaVM *gVm = NULL;
//互斥锁
static pthread_mutex_t mutex;
//运行时异常
static const char *runtimeException = "java/lang/RuntimeException";


//初始化挂载
JNIEXPORT int JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }

    gVm = vm;

    return JNI_VERSION_1_6;
}


JNIEXPORT void JNICALL
Java_com_chaoliu_jniapp_NativeThread_nativeInit(JNIEnv *env, jclass type) {

    jclass threadCls = env->FindClass("com/chaoliu/jniapp/NativeThread");
    if(threadCls == NULL){
        throwByName(env, runtimeException, "Unable to get nativeThreadCls");
        return;
    }

    //局部引用转换为全局引用
    nativeThreadCls = static_cast<jclass>(env->NewGlobalRef(threadCls));
    env->DeleteLocalRef(threadCls);

    printMsgMid = env->GetMethodID(nativeThreadCls, "printNativeMsg", "(Ljava/lang/String;)V");

    //    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    if (pthread_mutex_init(&mutex, NULL) != 0) {
        throwByName(env, runtimeException, "Unable to initialize mutex");
    }
}


JNIEXPORT void JNICALL
Java_com_chaoliu_jniapp_NativeThread_createNativeThread(JNIEnv *env, jclass type, jobject obj) {
    posixThreads(env,obj,1);
}

JNIEXPORT void JNICALL
Java_com_chaoliu_jniapp_NativeThread_posixThreads(JNIEnv *env, jclass type, jobject runObj, jint threadnum) {
    posixThreads(env,runObj,threadnum);
}

JNIEXPORT void JNICALL
Java_com_chaoliu_jniapp_NativeThread_nativeFree(JNIEnv *env, jclass type) {
    nativeFree(env);
}

//挂载销毁
JNIEXPORT void JNI_OnUnload(JavaVM* vm, void* reserved){
    LOGD("JNI_OnUnload");
    JNIEnv *env;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return ;
    }
    nativeFree(env);
}

//创建线程执行
void posixThreads(JNIEnv *env, jobject runObj, jint threadnum) {

    pthread_t *handles = new pthread_t[threadnum];

    jmethodID runMid = getRunableMethod(env,runObj);

    for (int i = 0; i < threadnum; ++i) {

        ThreadRunArgs *threadRunArgs = new ThreadRunArgs();
        threadRunArgs->id = i;
        threadRunArgs->result = i * i;
        threadRunArgs->runMid = runMid;
        threadRunArgs->runObj = runObj;
        threadRunArgs->env = env;

        // 创建一个线程，
        int result = pthread_create(&handles[i], NULL, run, (void *) threadRunArgs);
        if (result != 0) {
            throwByName(env, runtimeException, "Unable to create thread");
        }
    }

    for (int i = 0; i < threadnum; ++i) {
        void * result = NULL;
        if (pthread_join(handles[i], &result) != 0) {
            throwByName(env, runtimeException, "Unable to join thread");
        } else {
            LOGD("return value is %li", (long)result);
            char message[26];
            sprintf(message, "Worker %d returned %li", i, (long)result);
            jstring msg = env->NewStringUTF(message);
            //打印native信息
            printNativeMsg(env,msg);
            if (env->ExceptionOccurred() != NULL) {
                return;
            }
        }
    }

}

void throwByName(JNIEnv *env, const char *name, const char *msg) {
    jclass cls = env->FindClass(name);
    if (cls != NULL) {
        env->ThrowNew(cls, msg);
        env->DeleteLocalRef(cls);
    }
}

//运行方法
void *run(void *args) {

    //获得参数
    ThreadRunArgs *threadRunArgs = (ThreadRunArgs *) args;
    jobject runObj = (*threadRunArgs).runObj;
    JNIEnv *env = threadRunArgs->env;

    // 将当前线程添加到 Java 虚拟机上
    if (gVm->AttachCurrentThread(&env, NULL) == 0) {

        if (pthread_mutex_lock(&mutex) != 0) {
            throwByName(env, runtimeException, "Unable to lock mutex");
        }

        env->CallVoidMethod(runObj, threadRunArgs->runMid);

        //异常避免崩溃
        jthrowable exe = env->ExceptionOccurred();
        if(exe){
            env->ExceptionDescribe();
            env->ExceptionClear();
        }

        if (pthread_mutex_unlock(&mutex)) {
            throwByName(env, runtimeException, "Unable to unlock mutex");
        }
        // 从 Java 虚拟机上分离当前线程
        gVm->DetachCurrentThread();
    }
    return & threadRunArgs->result;
}

//获得runnable方法
jmethodID getRunableMethod(JNIEnv *env, jobject runObj){
    jclass runCls = (*env).GetObjectClass(runObj);
    if (runCls == NULL) return NULL;
    return (*env).GetMethodID(runCls,"run","()V");
}

//调用java打印方法 打印native信息
void printNativeMsg(JNIEnv *env, jstring msg){
    env->CallStaticVoidMethod(nativeThreadCls,printMsgMid,msg);
}

void nativeFree(JNIEnv *env) {

    jboolean isGC = env->IsSameObject(nativeThreadCls, NULL);
    if(!isGC){
        env->DeleteGlobalRef(nativeThreadCls);
        nativeThreadCls = NULL;
    }

    if (pthread_mutex_destroy(&mutex) != 0) {
        throwByName(env, runtimeException, "Unable to destroy mutex");
    }

}