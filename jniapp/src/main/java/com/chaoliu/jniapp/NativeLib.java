package com.chaoliu.jniapp;

import com.chaoliu.jniapp.model.Animal;

/**
 * jni代码编写 通过env特定转化函数
 * 建议jni调用用C封装好的函数，细节不要暴露在里面
 * 标准示例 包含各种写法
 */
public class NativeLib {

    static {
        System.loadLibrary( "native-lib" );
    }

    //示例demo
    public static native int plus(int a, int b);

    //字符串操作 hello world
    public static native String getNativeString(String str);

    //返回字符串
    public static native String getReturnString(String str);

    //打印字符串
    public static native void printf(String str);

    //获得源字符串的指针 只获得指针 用于读取 中间不能有阻塞操作
    public static native void printfCritical(String str);

    public static native int getLength(String str);

    public static native void printfRegion(String str);

    //操作数组
    public static native int intArraySum(int[] intArray, int size);

    //返回数组
    public static native int[] getIntArray(int num);

    //对象数组
    public static native int[][] getTwoDimensionalArray(int size);

    //java c++ 互相调用
    public static native void printAnimalsName(Animal[] animals);

    //访问类实例字段 set方法
    public static native void setAnimalName(Animal animal,String name);

    //访问静态字段
    public static native int getAnimalNum(Animal animal);

    //调用实例方法
    public static native void callInstanceMethod(Animal animal);

    //调用静态方法
    public static native String callStaticMethod(Animal animal);

    //构造方法 public String(char value[]) // Java String 类的其中一个构造方法
    public static native String newStringInstance();

    //构造方法 Animal(String name)
    public static native Animal invokeAnimalConstructor(String name);

    //构造方法 Animal(String name)  延迟初始化 AllocObject
    public static native Animal allocAnimalConstructor(String name);

    //调用父类方法
    public static native void callSuperMethod();

    //调用缓存字段 避免 FindClass GetFieldID ,GetMethodID重复调用

    //使用时缓存
    public static native void staticCacheField(Animal animal);

    //初始化缓存
    static {
        initCacheMethodId();
    }
    public static native void initCacheMethodId(); // 静态代码块中进行缓存

    public static native void callCacheMethod(Animal animal);

    // FindClass 是局部引用，不能static缓存
    //(*env)->DeleteLocalRef(env, jstr);

    //局部引用
    public static native void localRef();

    //全局引用
    public static native void gloablRef(Animal animal);

    //弱引用
    public static native void weakRef(Animal animal);

    //native 处理java异常
    public static native void nativeInvokeJavaException();

    //native 抛出java异常
    public static native void nativeThrowException() throws IllegalArgumentException;

}
