#include <jni.h>
#include <string>
#include <memory.h>

JNIEXPORT jint JNICALL
Java_com_chaoliu_jniapp_NativeLib_plus(JNIEnv *env, jclass type, jint a, jint b) {
    jint sum = a+b;
    return sum;
}

JNIEXPORT jstring JNICALL
Java_com_chaoliu_jniapp_NativeLib_getNativeString(JNIEnv *env, jclass type, jstring str_) {

    //生成 jstring 类型的字符串
    jstring returnValue = (*env)->NewStringUTF(env,"hello native string");
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
    if(utfStr == NULL)
        return;
    //实际操作
    printf("%s",utfStr);
    //释放内存
    (*env)->ReleaseStringUTFChars(env, str_, utfStr);
}

//只获得直接指针
JNIEXPORT void JNICALL
Java_com_chaoliu_jniapp_NativeLib_printfCritical(JNIEnv *env, jclass type, jstring str_) {

    const jchar * c_str = (*env)->GetStringCritical(env ,str_,NULL);

    if (c_str == NULL)
        return;

    (*env)->ReleaseStringUTFChars(env, str_, c_str);
}

JNIEXPORT jint JNICALL
Java_com_chaoliu_jniapp_NativeLib_getLength(JNIEnv *env, jclass type, jstring str_) {
    jint jlength = (*env)->GetStringLength(env,str_); //两种计算方式 1
    const char *str = (*env)->GetStringUTFChars(env, str_, 0);
    int c_len =  strlen(str); //两种计算方式 2
    (*env)->ReleaseStringUTFChars(env, str_, str);
    return c_len;
}

JNIEXPORT void JNICALL
Java_com_chaoliu_jniapp_NativeLib_printfRegion(JNIEnv *env, jclass type, jstring str_) {

    jchar outbuf[128];
    memset(outbuf,0x00, sizeof(outbuf));
    int len = (*env)->GetStringLength(env,str_);
    //获得指定范围字符串
    (*env)->GetStringUTFRegion(env,str_,0,len,outbuf);
    printf("%s",outbuf);
}

JNIEXPORT jint JNICALL
Java_com_chaoliu_jniapp_NativeLib_intArraySum(JNIEnv *env, jclass type, jintArray intArray_,
                                              jint size) {
    jint *intArray = (*env)->GetIntArrayElements(env, intArray_, NULL);

    int sum = 0;
    if (intArray == NULL)
        return 0;

    int length = (*env)->GetArrayLength(env,intArray_);

    for(int i= 0 ; i < length; ++i){
        sum += intArray[i];
    }
    (*env)->ReleaseIntArrayElements(env, intArray_, intArray, 0);
    return sum;
}


//一维数组
JNIEXPORT jintArray JNICALL
Java_com_chaoliu_jniapp_NativeLib_getIntArray(JNIEnv *env, jclass type, jint num) {

    jintArray intArray;
    intArray = (*env)->NewIntArray(env,num);

    jint buf[num];
    memset(buf,0, sizeof(buf));

    for (int i = 0; i < num ; ++i) {
        buf[i] = i *2;
    }

    //使用 setIntArrayRegion 来赋值
    (*env)->SetIntArrayRegion(env,intArray,0,num,buf);

    return intArray;
}

//二维数组
JNIEXPORT jobjectArray JNICALL
Java_com_chaoliu_jniapp_NativeLib_getTwoDimensionalArray(JNIEnv *env, jclass type, jint size) {

    jobjectArray result;
    //找到对象数组中具体的对象类型,[I 指的就是数组类型
    jclass intArrayCls = (*env)->FindClass(env,"[I");

    if(intArrayCls == NULL) return NULL;

    result = (*env)->NewObjectArray(env,size,intArrayCls,NULL);

    if (result == NULL) return NULL;

    for (int i = 0; i < size ; ++i) {
        jint tmp[256];
        memset(tmp,0, sizeof(tmp));
        jintArray iarr = (*env)->NewIntArray(env,size);
        if (iarr == NULL) return NULL;

        for (int j = 0; j < size ; ++j) {
            tmp[j] = i+j;
        }

        //填充数据
        (*env)->SetIntArrayRegion(env,iarr,0,size,tmp);
        //给二维数组指定位置填充数据
        (*env)->SetObjectArrayElement(env,result,i,iarr);
        //释放局部引用
        (*env)->DeleteLocalRef(env,iarr);
    }
    return result;
}

// java对象 C++ 互相调用
JNIEXPORT void JNICALL
Java_com_chaoliu_jniapp_NativeLib_printAnimalsName(JNIEnv *env, jclass type, jobjectArray animals) {

    //数组长度
    int size = (*env)->GetArrayLength(env,animals);
    //获得对应java数据类
    jclass animalCls = (*env)->FindClass(env,"com/chaoliu/jniapp/model/Animal");
    //类对应字段
    jfieldID nameFid = (*env)->GetFieldID(env,animalCls,"name","Ljava/lang/String;");

    for (int i = 0; i < size; ++i) {
        //获得当前元素对象
        jobject animal = (*env)->GetObjectArrayElement(env,animals,i);
        //获得当前字段
        jstring jstr = (jstring)(*env)->GetObjectField(env,animal,nameFid);
        //jstring 转 char
        const char * str = (*env)->GetStringUTFChars(env,jstr,NULL);
        if (str ==NULL) continue;
        printf("%s\n",str);
        //内存释放
        (*env)->ReleaseStringUTFChars(env,jstr,str);
    }
}

JNIEXPORT void JNICALL
Java_com_chaoliu_jniapp_NativeLib_setAnimalName(JNIEnv *env, jclass type, jobject animal,
                                                jstring name_) {
    //获取java对象类
//    jclass animalCls = (*env)->FindClass(env,"com/chaoliu/jniapp/model/Animal");
    //获得java对象
    jclass animalCls = (*env)->GetObjectClass(env,animal);
    //获取name字段
    jfieldID nameFid = (*env)->GetFieldID(env,animalCls,"name","Ljava/lang/String;");
    if (nameFid == NULL) return;

    //获取name字段值 打印name字符串
    jstring jstr = (*env)->GetObjectField(env,animal,nameFid);
    const char *name = (*env)->GetStringUTFChars(env, jstr, NULL);
    printf("%s\n",name);
    (*env)->ReleaseStringUTFChars(env, name_, name);

    //设置值 默认值
    if(name_ == NULL) {
        jstring jname = (*env)->NewStringUTF(env,"name");
        if (jname == NULL) return;
        (*env)->SetObjectField(env,animal,nameFid,jname);
        return;
    }

    //设置name值
    (*env)->SetObjectField(env,animal,nameFid,name_);
}


JNIEXPORT jint JNICALL
Java_com_chaoliu_jniapp_NativeLib_getAnimalNum(JNIEnv *env, jclass type, jobject animal) {

    jclass animalCls = (*env)->GetObjectClass(env,animal);
    jfieldID numFid = (*env)->GetFieldID(env,animalCls,"num","I");
    if(numFid == NULL)  return 0;
    //获得num值
    jint num =  (*env)->GetStaticIntField(env,animalCls,numFid);
    printf("%d\n",num);
    //设置num值
    (*env)->SetStaticIntField(env,animalCls,numFid,++num);
    //返回值
    return (*env)->GetStaticIntField(env,animalCls,numFid);
}

JNIEXPORT void JNICALL
Java_com_chaoliu_jniapp_NativeLib_callInstanceMethod(JNIEnv *env, jobject instance,
                                                         jobject animal) {
    jclass animalCls = (*env)->GetObjectClass(env,animal);

    jmethodID mid = (*env)->GetMethodID(env,animalCls,"callInstanceMethod","(I)V");

    if (mid == NULL) return;

    (*env)->CallVoidMethod(animal,mid,2);
}

JNIEXPORT jstring JNICALL
Java_com_chaoliu_jniapp_NativeLib_callStaticMethod(JNIEnv *env, jobject instance, jobject animal) {
    jclass animalCls = (*env)->GetObjectClass(env,animal);
    jmethodID mid = (*env)->GetStaticMethodID(env,animalCls,"callStaticMethod","(Ljava/lang/String;)Ljava/lang/String;");
    if (mid == NULL)
        return NULL;
    jstring jstr = (*env)->NewStringUTF(env,"callStaticMethod");
    jstring jvalue = (*env)->CallStaticObjectMethod(env,animalCls,mid,jstr);
    return jvalue;
}