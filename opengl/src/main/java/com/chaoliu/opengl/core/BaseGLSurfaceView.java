package com.chaoliu.opengl.core;

import android.annotation.SuppressLint;
import android.content.Context;
import android.opengl.GLSurfaceView;
import android.view.SurfaceHolder;

/**
 * 基础类
 */
@SuppressLint("ViewConstructor")
public class BaseGLSurfaceView extends GLSurfaceView {

    private BaseGLRenderer baseRenderer;

    public BaseGLSurfaceView(Context context, BaseGLRenderer renderer) {
        super( context );
        setEGLContextClientVersion( 2 );
        this.baseRenderer = renderer;
        this.setRenderer( baseRenderer );
        setRenderMode( GLSurfaceView.RENDERMODE_WHEN_DIRTY );
    }

    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        super.surfaceCreated( holder );
    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int w, int h) {
        super.surfaceChanged( holder, format, w, h );
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {
        super.surfaceDestroyed( holder );
        if (baseRenderer != null) {
            baseRenderer.onSurfaceDestroyed();
        }
    }
}