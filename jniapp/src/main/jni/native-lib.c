#include <jni.h>
#include <string>
#include <memory.h>

JNIEXPORT jint JNICALL
Java_com_chaoliu_jniapp_NativeLib_plus(JNIEnv *env, jclass type, jint a, jint b) {
    jint sum = a + b;
    return sum;
}

JNIEXPORT jstring JNICALL
Java_com_chaoliu_jniapp_NativeLib_getNativeString(JNIEnv *env, jclass type, jstring str_) {

    //生成 jstring 类型的字符串
    jstring returnValue = (*env)->NewStringUTF(env, "hello native string");
    //将 jstring 类型的字符串转换为 C 风格的字符串，会额外申请内存
    const char *str = (*env)->GetStringUTFChars(env, str_, 0);
    // 释放掉申请的 C 风格字符串的内存
    (*env)->ReleaseStringUTFChars(env, str_, str);
    // 返回 jstring 类型字符串
    return (*env)->NewStringUTF(env, returnValue);
}

JNIEXPORT jstring JNICALL
Java_com_chaoliu_jniapp_NativeLib_getReturnString(JNIEnv *env, jclass type, jstring str_) {
    return (*env)->NewStringUTF(env, str_);
}


JNIEXPORT void JNICALL
Java_com_chaoliu_jniapp_NativeLib_printf(JNIEnv *env, jclass type, jstring str_) {
    //申请分配字符串
    const char *utfStr = (*env)->GetStringUTFChars(env, str_, 0);
    if (utfStr == NULL)
        return;
    //实际操作
    printf("%s", utfStr);
    //释放内存
    (*env)->ReleaseStringUTFChars(env, str_, utfStr);
}

//只获得直接指针
JNIEXPORT void JNICALL
Java_com_chaoliu_jniapp_NativeLib_printfCritical(JNIEnv *env, jclass type, jstring str_) {

    const jchar *c_str = (*env)->GetStringCritical(env, str_, NULL);

    if (c_str == NULL)
        return;

    (*env)->ReleaseStringUTFChars(env, str_, c_str);
}

JNIEXPORT jint JNICALL
Java_com_chaoliu_jniapp_NativeLib_getLength(JNIEnv *env, jclass type, jstring str_) {
    jint jlength = (*env)->GetStringLength(env, str_); //两种计算方式 1
    const char *str = (*env)->GetStringUTFChars(env, str_, 0);
    int c_len = strlen(str); //两种计算方式 2
    (*env)->ReleaseStringUTFChars(env, str_, str);
    return c_len;
}

JNIEXPORT void JNICALL
Java_com_chaoliu_jniapp_NativeLib_printfRegion(JNIEnv *env, jclass type, jstring str_) {

    jchar outbuf[128];
    memset(outbuf, 0x00, sizeof(outbuf));
    int len = (*env)->GetStringLength(env, str_);
    //获得指定范围字符串
    (*env)->GetStringUTFRegion(env, str_, 0, len, outbuf);
    printf("%s", outbuf);
}

JNIEXPORT jint JNICALL
Java_com_chaoliu_jniapp_NativeLib_intArraySum(JNIEnv *env, jclass type, jintArray intArray_,
                                              jint size) {
    jint *intArray = (*env)->GetIntArrayElements(env, intArray_, NULL);

    int sum = 0;
    if (intArray == NULL)
        return 0;

    int length = (*env)->GetArrayLength(env, intArray_);

    for (int i = 0; i < length; ++i) {
        sum += intArray[i];
    }
    (*env)->ReleaseIntArrayElements(env, intArray_, intArray, 0);
    return sum;
}


//一维数组
JNIEXPORT jintArray JNICALL
Java_com_chaoliu_jniapp_NativeLib_getIntArray(JNIEnv *env, jclass type, jint num) {

    jintArray intArray;
    intArray = (*env)->NewIntArray(env, num);

    jint buf[num];
    memset(buf, 0, sizeof(buf));

    for (int i = 0; i < num; ++i) {
        buf[i] = i * 2;
    }

    //使用 setIntArrayRegion 来赋值
    (*env)->SetIntArrayRegion(env, intArray, 0, num, buf);

    return intArray;
}

//二维数组
JNIEXPORT jobjectArray JNICALL
Java_com_chaoliu_jniapp_NativeLib_getTwoDimensionalArray(JNIEnv *env, jclass type, jint size) {

    jobjectArray result;
    //找到对象数组中具体的对象类型,[I 指的就是数组类型
    jclass intArrayCls = (*env)->FindClass(env, "[I");

    if (intArrayCls == NULL) return NULL;

    result = (*env)->NewObjectArray(env, size, intArrayCls, NULL);

    if (result == NULL) return NULL;

    for (int i = 0; i < size; ++i) {
        jint tmp[256];
        memset(tmp, 0, sizeof(tmp));
        jintArray iarr = (*env)->NewIntArray(env, size);
        if (iarr == NULL) return NULL;

        for (int j = 0; j < size; ++j) {
            tmp[j] = i + j;
        }

        //填充数据
        (*env)->SetIntArrayRegion(env, iarr, 0, size, tmp);
        //给二维数组指定位置填充数据
        (*env)->SetObjectArrayElement(env, result, i, iarr);
        //释放局部引用
        (*env)->DeleteLocalRef(env, iarr);
    }
    return result;
}

// java对象 C++ 互相调用
JNIEXPORT void JNICALL
Java_com_chaoliu_jniapp_NativeLib_printAnimalsName(JNIEnv *env, jclass type, jobjectArray animals) {

    //数组长度
    int size = (*env)->GetArrayLength(env, animals);
    //获得对应java数据类
    jclass animalCls = (*env)->FindClass(env, "com/chaoliu/jniapp/model/Animal");
    //类对应字段
    jfieldID nameFid = (*env)->GetFieldID(env, animalCls, "name", "Ljava/lang/String;");

    for (int i = 0; i < size; ++i) {
        //获得当前元素对象
        jobject animal = (*env)->GetObjectArrayElement(env, animals, i);
        //获得当前字段
        jstring jstr = (jstring) (*env)->GetObjectField(env, animal, nameFid);
        //jstring 转 char
        const char *str = (*env)->GetStringUTFChars(env, jstr, NULL);
        if (str == NULL) continue;
        printf("%s\n", str);
        //内存释放
        (*env)->ReleaseStringUTFChars(env, jstr, str);
    }
}

JNIEXPORT void JNICALL
Java_com_chaoliu_jniapp_NativeLib_setAnimalName(JNIEnv *env, jclass type, jobject animal,
                                                jstring name_) {
    //获取java对象类
//    jclass animalCls = (*env)->FindClass(env,"com/chaoliu/jniapp/model/Animal");
    //获得java对象
    jclass animalCls = (*env)->GetObjectClass(env, animal);
    //获取name字段
    jfieldID nameFid = (*env)->GetFieldID(env, animalCls, "name", "Ljava/lang/String;");
    if (nameFid == NULL) return;

    //获取name字段值 打印name字符串
    jstring jstr = (*env)->GetObjectField(env, animal, nameFid);
    const char *name = (*env)->GetStringUTFChars(env, jstr, NULL);
    printf("%s\n", name);
    (*env)->ReleaseStringUTFChars(env, name_, name);

    //设置值 默认值
    if (name_ == NULL) {
        jstring jname = (*env)->NewStringUTF(env, "name");
        if (jname == NULL) return;
        (*env)->SetObjectField(env, animal, nameFid, jname);
        return;
    }

    //设置name值
    (*env)->SetObjectField(env, animal, nameFid, name_);
}


JNIEXPORT jint JNICALL
Java_com_chaoliu_jniapp_NativeLib_getAnimalNum(JNIEnv *env, jclass type, jobject animal) {

    jclass animalCls = (*env)->GetObjectClass(env, animal);
    jfieldID numFid = (*env)->GetFieldID(env, animalCls, "num", "I");
    if (numFid == NULL) return 0;
    //获得num值
    jint num = (*env)->GetStaticIntField(env, animalCls, numFid);
    printf("%d\n", num);
    //设置num值
    (*env)->SetStaticIntField(env, animalCls, numFid, ++num);
    //返回值
    return (*env)->GetStaticIntField(env, animalCls, numFid);
}

JNIEXPORT void JNICALL
Java_com_chaoliu_jniapp_NativeLib_callInstanceMethod(JNIEnv *env, jclass type,
                                                     jobject animal) {
    jclass animalCls = (*env)->GetObjectClass(env, animal);

    jmethodID mid = (*env)->GetMethodID(env, animalCls, "callInstanceMethod", "(I)V");

    if (mid == NULL) return;

    (*env)->CallVoidMethod(animal, mid, 2);
}

JNIEXPORT jstring JNICALL
Java_com_chaoliu_jniapp_NativeLib_callStaticMethod(JNIEnv *env, jclass type, jobject animal) {
    jclass animalCls = (*env)->GetObjectClass(env, animal);
    jmethodID mid = (*env)->GetStaticMethodID(env, animalCls, "callStaticMethod",
                                              "(Ljava/lang/String;)Ljava/lang/String;");
    if (mid == NULL)
        return NULL;
    jstring jstr = (*env)->NewStringUTF(env, "callStaticMethod");
    jstring jvalue = (*env)->CallStaticObjectMethod(env, animalCls, mid, jstr);
    return jvalue;
}

//构造方法 String(char value[])
JNIEXPORT jstring JNICALL
Java_com_chaoliu_jniapp_NativeLib_newStringInstance(JNIEnv *env, jclass type) {

    //查找类
    jclass stringCls = (*env)->FindClass(env, "java/lang/String");
    if (stringCls == NULL) return NULL;

    //String(char value[])
    jmethodID initMethodId = (*env)->GetMethodID(env, stringCls, "<init>", "([C)V");
    if (initMethodId == NULL)return NULL;

    jstring jstr = (*env)->NewStringUTF(env, "this is char array");
    //给java对象传值 Unicode编码
    const jchar *chars = (*env)->GetStringChars(env, jstr, NULL);
    int len = (*env)->GetStringLength(env, jstr);

    //创建数组
    jcharArray charArr = (*env)->NewCharArray(env, len);
    if (charArr == NULL)return NULL;

    //拷贝字符串
    (*env)->SetCharArrayRegion(env, charArr, 0, len, chars);
    //创建实例
    jstring result = (*env)->NewObject(env, stringCls, initMethodId, charArr);

    //清理内存
    (*env)->DeleteLocalRef(env, charArr);
    (*env)->DeleteLocalRef(env, stringCls);
    (*env)->ReleaseStringUTFChars(env, jstr, chars);

    return result;
}

/**
 *
 * 建议采用goto方式解决内存泄漏问题
 */
JNIEXPORT jobject JNICALL
Java_com_chaoliu_jniapp_NativeLib_invokeAnimalConstructor(JNIEnv *env, jclass type, jstring name_) {

    jclass animalCls = (*env)->FindClass(env, "com/chaoliu/jniapp/model/Animal");
    if (animalCls == NULL)return NULL;

    jmethodID nameMid = (*env)->GetMethodID(env, animalCls, "<init>", "(Ljava/lang/String;)V");
    if (nameMid == NULL) goto clear;

    //创建实例
    jobject animal = (*env)->NewObject(env, animalCls, nameMid, name_);
    (*env)->DeleteLocalRef(env, animalCls);
    return animal;

    clear:
    if (animalCls != NULL)
        (*env)->DeleteLocalRef(env, animalCls);
    return NULL;
}

JNIEXPORT jobject JNICALL
Java_com_chaoliu_jniapp_NativeLib_allocAnimalConstructor(JNIEnv *env, jclass type, jstring name_) {

    jclass animalCls = (*env)->FindClass(env, "com/chaoliu/jniapp/model/Animal");
    if (animalCls == NULL)return NULL;

    jmethodID nameMid = (*env)->GetMethodID(env, animalCls, "<init>", "(Ljava/lang/String;)V");
    if (nameMid == NULL) goto clear;

    //未初始化实例
    jobject animal = (*env)->AllocObject(env, animalCls);
    if (animal == NULL)
        return NULL;

    //延迟初始化
    (*env)->CallNonvirtualVoidMethod(env, animal, nameMid, name_);
    if ((*env)->ExceptionCheck(env)) {
        (*env)->DeleteLocalRef(env, animal);
    }
    (*env)->DeleteLocalRef(env, animalCls);

    return animal;

    clear:
    if (animalCls != NULL)
        (*env)->DeleteLocalRef(env, animalCls);
    return NULL;
}

//调用父类方法
JNIEXPORT void JNICALL
Java_com_chaoliu_jniapp_NativeLib_callSuperMethod(JNIEnv *env, jclass type) {

    jclass catCls = (*env)->FindClass(env, "com/chaoliu/jniapp/model/Cat");

    if (catCls == NULL) return;

    jmethodID catInitMid = (*env)->GetFieldID(env, catCls, "<init>", "(Ljava/lang/String;)V");

    if (catInitMid == NULL)
        return;

    jstring jstr = (*env)->NewStringUTF(env, "I am a cat! miao~~~");
    if (jstr == NULL)
        return;

    jobject cat = (*env)->NewObject(env, catCls, catInitMid, jstr);
    if (jstr == NULL) return;

    jclass animalCls = (*env)->FindClass(env, "com/chaoliu/jniapp/model/Animal");

    jmethodID getNameMid = (*env)->GetMethodID(env, animalCls, "getName", "()Ljava/lang/String;");
    //调用父类方法 callInstanceMethod
    jstring name = (*env)->CallNonvirtualObjectMethod(env, cat, animalCls, getNameMid);

    int num = 3;

    jmethodID callInstanceMethodId = (*env)->GetMethodID(env, animalCls, "callInstanceMethod",
                                                         "(I)V");
    //调用父类方法 callInstanceMethod
    (*env)->CallNonvirtualVoidMethod(env, cat, animalCls, callInstanceMethodId, num);
}

//使用时缓存
JNIEXPORT void JNICALL
Java_com_chaoliu_jniapp_NativeLib_staticCacheField(JNIEnv *env, jclass type, jobject animal) {

    static jfieldID nameFid = NULL;

    jclass animalCls = (*env)->GetObjectClass(env, animal);

    //cache field
    if (nameFid == NULL) {
        nameFid = (*env)->GetFieldID(env, animalCls, "name", "Ljava/lang/String;");
        if (nameFid == NULL)return;
    } else {
        printf("%s\n", "nameFid is cache");
    }

    jstring jstr = (*env)->GetObjectField(env, animal, nameFid);

    const char *chars = (*env)->GetStringUTFChars(env, jstr, NULL);
    if (chars == NULL)
        return;
    printf("%s/n", chars);

    (*env)->ReleaseStringUTFChars(env, jstr, chars);

    jstr = (*env)->NewStringUTF(env, "new value");

    if (jstr == NULL) return;
    (*env)->SetObjectField(env, animal, nameFid, jstr);
}


//全局缓存方法ID
jmethodID instanceMethodCache;
//初始化缓存
JNIEXPORT void JNICALL
Java_com_chaoliu_jniapp_NativeLib_initCacheMethodId(JNIEnv *env, jclass type) {
    jclass animalCls = (*env)->FindClass(env, "com/chaoliu/jniapp/model/Animal");
    instanceMethodCache = (*env)->GetMethodID(env, animalCls, "getName", "()Ljava/lang/String;");
}

JNIEXPORT void JNICALL
Java_com_chaoliu_jniapp_NativeLib_callCacheMethod(JNIEnv *env, jclass type, jobject animal) {
    jstring jstr = (*env)->CallObjectMethod(env, animal, instanceMethodCache);
    const char *chars = (*env)->GetStringUTFChars(env, jstr, NULL);
    printf("%s\n", chars);
    (*env)->ReleaseStringUTFChars(env, jstr, chars);
}

JNIEXPORT void JNICALL
Java_com_chaoliu_jniapp_NativeLib_localRef(JNIEnv *env, jclass type) {

    jclass animalCls = (*env)->FindClass(env, "com/chaoliu/jniapp/model/Animal");

    //字符串转换为char类型
    jstring jstr = (*env)->NewStringUTF(env, "LocalRef Word Test");
    int len = (*env)->GetStringUTFLength(env, jstr);
    const jchar *cstr = (*env)->GetStringUTFChars(env, jstr, NULL);

    //char数组
    jcharArray charArr = (*env)->NewCharArray(env, len);
    //拷贝
    (*env)->SetCharArrayRegion(env, charArr, 0, len, cstr);

    //局部引用释放
    (*env)->DeleteLocalRef(env, animalCls);
    (*env)->DeleteLocalRef(env, charArr);
    (*env)->ReleaseStringUTFChars(env, jstr, cstr);
    (*env)->DeleteLocalRef(env, jstr);
}


//全局引用
JNIEXPORT void JNICALL
Java_com_chaoliu_jniapp_NativeLib_gloablRef(JNIEnv *env, jclass type, jobject animal) {

    static jclass animalGlobalCls = NULL;  //引用要用全局保存

    static jfieldID nameFid = NULL;

    if (animalGlobalCls == NULL) {
        jclass animalCls = (*env)->GetObjectClass(env, animal);
        if (animalCls == NULL) return;
        //创建全局引用
        animalGlobalCls = (*env)->NewGlobalRef(env, animalCls);
        if (animalGlobalCls == NULL) return;

        //删除局部引用
        (*env)->DeleteLocalRef(env, animalCls);
    } else {
        printf("use gloabl cache");
    }

    //cache field
    if (nameFid == NULL) {
        nameFid = (*env)->GetFieldID(env, animalGlobalCls, "name", "Ljava/lang/String;");
        if (nameFid == NULL)return;
    } else {
        printf("%s\n", "nameFid is cache");
    }

    jstring jstr = (*env)->GetObjectField(env, animal, nameFid);

    const char *chars = (*env)->GetStringUTFChars(env, jstr, NULL);
    if (chars == NULL) return;
    printf("%s/n", chars);
    (*env)->ReleaseStringUTFChars(env, jstr, chars);

}


JNIEXPORT void JNICALL
Java_com_chaoliu_jniapp_NativeLib_weakRef(JNIEnv *env, jclass type, jobject animal) {

    static jclass animalWeakCls = NULL;  //引用要用全局保存
    static jmethodID initMid = NULL;

    if (animalWeakCls == NULL) {
        jclass animalCls = (*env)->GetObjectClass(env, animal);
        if (animalCls == NULL) return;
        //创建全局弱引用引用
        animalWeakCls = (*env)->NewWeakGlobalRef(env, animalCls);
        if (animalWeakCls == NULL) return;
        //删除局部引用
        (*env)->DeleteLocalRef(env, animalCls);
    } else {
        printf("use gloabl cache");
    }

    //cache field
    if (initMid == NULL) {
        initMid = (*env)->GetMethodID(env, animalWeakCls, "<init>", "(Ljava/lang/String;)V");
        if (initMid == NULL)return;
    } else {
        printf("%s\n", "initMid is cache");
    }

    //判断引用是否被释放
    jboolean isGC = (*env)->IsSameObject(env, animalWeakCls, NULL);
    if (isGC) {
        printf("weak reference has been gc");
        animalWeakCls = NULL;
    } else {
        jstring jstr = (*env)->NewStringUTF(env, "this is name");
        jobject object = (*env)->NewObject(env, animalWeakCls, initMid, jstr);
        (*env)->DeleteWeakGlobalRef(env, animalWeakCls);
        animalWeakCls = NULL;
    }
}

JNIEXPORT void JNICALL
Java_com_chaoliu_jniapp_NativeLib_nativeInvokeJavaException(JNIEnv *env, jclass type) {

    jclass expCls = (*env)->FindClass(env, "com/chaoliu/jniapp/exception/ExceptionOps");
    //构造方法
    jmethodID initMid = (*env)->GetMethodID(env, expCls, "<init>", "()V");
    jobject expObj = (*env)->NewObject(env, expCls, initMid);

    jmethodID operMid = (*env)->GetMethodID(env, expCls, "operation", "()I");
    //调用函数  异常函数
    (*env)->CallIntMethod(env, expObj, operMid);


    //异常处理
    jthrowable exc = (*env)->ExceptionOccurred(env);
    // jboolean result = env->ExceptionCheck();

    if (exc) {
        //打印异常日志
        (*env)->ExceptionDescribe(env);
        //清除代码崩溃
        (*env)->ExceptionClear(env);
        //释放资源
        (*env)->DeleteLocalRef(env, expCls);
        (*env)->DeleteLocalRef(env, expObj);
    }

}

//简单封装函数
void printExceptionInfo(JNIEnv *env) {

    //异常处理
    jthrowable exc = (*env)->ExceptionOccurred(env);
    // jboolean result = env->ExceptionCheck();
    if (exc) {
        //打印异常日志
        (*env)->ExceptionDescribe(env);
        //清除代码崩溃
        (*env)->ExceptionClear(env);
    }
}

//抛出java 异常
void throwByName(JNIEnv *env, const char *throwClassName, const char *throwMsg) {
    jclass throwCls = (*env)->FindClass(env, throwClassName);
    if (throwCls != NULL) {
        (*env)->ThrowNew(env, throwCls, throwMsg);
        (*env)->DeleteLocalRef(env, throwCls);
    }
}

//抛出java异常
JNIEXPORT void JNICALL
Java_com_chaoliu_jniapp_NativeLib_nativeThrowException(JNIEnv *env, jclass type) {

    jclass expCls = (*env)->FindClass(env, "com/chaoliu/jniapp/exception/ExceptionOps");
    //构造方法
    jmethodID initMid = (*env)->GetMethodID(env, expCls, "<init>", "()V");
    jobject expObj = (*env)->NewObject(env, expCls, initMid);

    jmethodID operMid = (*env)->GetMethodID(env, expCls, "operation", "()I");
    //调用函数  异常函数
    (*env)->CallIntMethod(env, expObj, operMid);


    //异常处理
    jthrowable exc = (*env)->ExceptionOccurred(env);
    // jboolean result = env->ExceptionCheck();

    if (exc) {
        //打印异常日志
        (*env)->ExceptionDescribe(env);
        //清除代码崩溃
        (*env)->ExceptionClear(env);
        //释放资源
        (*env)->DeleteLocalRef(env, expCls);
        (*env)->DeleteLocalRef(env, expObj);
        throwByName(env, "java/lang/IllegalArgumentException", "native throw exception");
    }

}
