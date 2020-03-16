//
// Created by 陈桐 on 2020/3/12.
//
#include <android/log.h>
#ifndef HOWTOLEARNNDK_LOGUTIL_H
#define HOWTOLEARNNDK_LOGUTIL_H

#define LOG_TAG "NativeMethod"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__);
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__);

#endif //HOWTOLEARNNDK_LOGUTIL_H
