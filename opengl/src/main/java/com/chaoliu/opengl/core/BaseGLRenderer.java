package com.chaoliu.opengl.core;

import android.content.Context;
import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 *
 *  封装opengl渲染接口
 *  GLSurfaceView.Renderer
 *
 */
public abstract class BaseGLRenderer implements GLSurfaceView.Renderer {

    protected Context mContext;

    public BaseGLRenderer(Context mContext) {
        this.mContext = mContext;
    }

    /**
     * 初始化创建
     * @param gl
     * @param config
     */
    public abstract void onSurfaceCreated(GL10 gl, EGLConfig config);

    /**
     * Surface 刚创建的时候，它的 size 是 0，也就是说在画第一次图之前它会被调用一次
     *
     * @param gl
     * @param width
     * @param height
     */
    public abstract void onSurfaceChanged(GL10 gl, int width, int height);

    public abstract void onDrawFrame(GL10 gl);

    /**
     * 内存清理
     */
    public abstract void onSurfaceDestroyed();

}
