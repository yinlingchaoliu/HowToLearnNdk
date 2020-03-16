package com.chaoliu.jniapp.utils;

import android.util.Log;


public class LogUtil {

    private static String TAG = "LogUtil";

    public static void d(String msg){
        Log.d( TAG, msg );
    }

    public static void e(String msg){
        Log.e( TAG, msg );
    }

    public static void d(String tag ,String msg){
        Log.d( tag, msg );
    }

    public static void e(String tag ,String msg){
        Log.e( tag, msg );
    }

}
