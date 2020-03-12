package com.chaoliu.jniapp;

import android.util.Log;

/**
 * 编写一个通用库 用作示例
 * 使用传入方法必须实现run方法
 */
public class NativeThread {

    static {
        System.loadLibrary( "native-lib" );
        nativeInit();
    }

    //初始化资源
    private static native void nativeInit();

    //创建线程 用native执行java方法
    public static native void createNativeThread(Runnable runObj);

    //创建多线程
    public static native void posixThreads(Runnable runObj,int threadnum);

    //释放内存
    private static native void nativeFree();

    /**
     * Native 回到到 Java 的方法，打印当前线程名字
     *
     * @param msg
     */
    public static void printNativeMsg(String msg) {
        Log.d("NativeThread", "native msg is " + msg);
        Log.d("NativeThread","print native msg current thread name is " + Thread.currentThread().getName());
    }

}
