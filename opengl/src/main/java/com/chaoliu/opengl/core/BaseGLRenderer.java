package com.chaoliu.opengl.core;

import android.content.Context;
import android.opengl.GLSurfaceView;

import com.chaoliu.opengl.util.ShaderHelper;
import com.chaoliu.opengl.util.VertexArray;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;


/**
 * 封装opengl渲染接口
 * GLSurfaceView.Renderer
 * @author chentong
 *
 * 存放一些冗余变量，因为glsl脚本常用，便于快速开发
 *
 */
public abstract class BaseGLRenderer implements GLSurfaceView.Renderer {

    protected Context mContext;

    protected int POSITION_COMPONENT_COUNT;

    //预读顶点位置
    protected VertexArray vertexArray;

    //常用变量
    protected int mProgram;

    protected int aColorLocation;
    protected int aPositionLocation;

    protected int uMatrixLocation;
    protected int uProMatrixLocation;
    protected int uViewMatrixLocation;
    protected int uModelMatrixLocation;

    public BaseGLRenderer(Context mContext) {
        this.mContext = mContext;
    }

    /**
     * 初始化创建
     * todo opengl创建必须在onSurfaceCreated中
     * @param gl
     * @param config
     * 不容许重写
     */
    public final void onSurfaceCreated(GL10 gl, EGLConfig config){
        mProgram = buildOpenGLProgram();
        ShaderHelper.glUseProgram( mProgram );
        onCreate( gl, config );
    }

    /**
     * 创建opengl
     * @return
     */
    public abstract int buildOpenGLProgram();

    /**
     * 初始化
     * @param gl
     * @param config
     */
    public abstract void onCreate(GL10 gl, EGLConfig config);

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
