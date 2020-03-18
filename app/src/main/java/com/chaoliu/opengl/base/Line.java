package com.chaoliu.opengl.base;

import android.content.Context;

import com.chaoliu.opengl.core.BaseGLRenderer;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class Line extends BaseGLRenderer {

    public Line(Context mContext) {
        super( mContext );
    }

    @Override
    public int buildOpenGLProgram() {
        return 0;
    }

    @Override
    public void onCreate(GL10 gl, EGLConfig config) {

    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {

    }

    @Override
    public void onDrawFrame(GL10 gl) {

    }

    @Override
    public void onSurfaceDestroyed() {

    }
}
