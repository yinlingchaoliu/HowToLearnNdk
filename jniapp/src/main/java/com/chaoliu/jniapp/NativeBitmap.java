package com.chaoliu.jniapp;

import android.graphics.Bitmap;

public class NativeBitmap {

    static {
        System.loadLibrary( "native-lib" );
    }

    // 顺时针旋转 90° 的操作
    public native Bitmap rotateBitmap(Bitmap bitmap);

    public native Bitmap convertBitmap(Bitmap bitmap);

    public native Bitmap mirrorBitmap(Bitmap bitmap);
}
