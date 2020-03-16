package com.chaoliu.jniapp.model;


import com.chaoliu.jniapp.utils.LogUtil;

/**
 * @Author glumes
 */

public class Animal {


    protected String name;

    public static int num = 0;

    public Animal(String name) {
        this.name = name;
    }


    public String getName() {
        LogUtil.d("call getName method");
        return this.name;
    }

    public int getNum() {
        return num;
    }

    // C++ 调用 Java 的实例方法
    public void callInstanceMethod(int num) {
        LogUtil.d("call instance method and num is " + num);
    }

    // C++ 调用 Java 的类方法
    public static String callStaticMethod(String str) {

        if (str != null) {
            LogUtil.d("call static method with " + str);
        } else {
            LogUtil.d("call static method str is null");
        }
        return str;
    }

    public static String callStaticMethod(String[] strs, int num) {
        LogUtil.d("call static method with string array");
        if (strs != null) {
            for (String str : strs) {
                LogUtil.d("str in array is " + str);
            }
        }
        return "";
    }

    public static void callStaticVoidMethod() {
        LogUtil.d("call static void method");
    }
}
