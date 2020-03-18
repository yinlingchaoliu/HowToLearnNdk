package com.chaoliu.opengl.util;

import android.opengl.GLES20;

/**
 *  常用函数
 * @author chentong
 *
 */
public class OpenglUtil {

    public static final String RENDERER_TYPE = "renderer_type";

    public static final int BYTES_PRE_FLOAT = 4;

    public static final int BYTES_PRE_BYTE = 1;

    //常用量
    //位置
    private static final String A_POSITION = "a_Position";
    //颜色
    private static final String U_COLOR = "u_Color";

    //矩阵
    private static final String U_MATRIX = "u_Matrix";
    //矩阵
    private static final String U_MODEL_MATRIX = "u_ModelMatrix";
    private static final String U_PRO_MATRIX = "u_ProMatrix";
    private static final String U_VIEW_MATRIX = "u_ViewMatrix";

    /**
     * 获得位置顶点
     *
     * @param program
     * @return
     */
    public static int getAttrPostionLocation(int program) {
        return GLES20.glGetAttribLocation( program, A_POSITION );
    }

    /**
     * 获得颜色
     *
     * @param program
     * @return
     */
    public static int getUColorLocation(int program) {
        return GLES20.glGetUniformLocation( program, U_COLOR );
    }

    /**
     * 获得矩阵变量
     *
     * @param program
     * @return
     */
    public static int getUMatrixLocation(int program) {
        return GLES20.glGetUniformLocation( program, U_MATRIX );
    }

    public static int getUProMatrixLocation(int program) {
        return GLES20.glGetUniformLocation( program, U_PRO_MATRIX );
    }

    public static int getUModelMatrixLocation(int program) {
        return GLES20.glGetUniformLocation( program, U_MODEL_MATRIX );
    }

    public static int getUViewMatrixLocation(int program) {
        return GLES20.glGetUniformLocation( program, U_VIEW_MATRIX );
    }

    /**
     * opengl 颜色清理
     */
    public static void glClear() {
        GLES20.glClearColor( 0f, 0f, 0f, 1f );
        GLES20.glClear( GLES20.GL_DEPTH_BUFFER_BIT | GLES20.GL_COLOR_BUFFER_BIT );
    }

    /**
     * @param program
     * @param name
     * @return   glsl语法
     * @desc 获得uniform变量   ==> uniform vec4  颜色
     *                        ==> uniform mat4  矩阵
     */
    public static int glGetUniformLocation(int program, String name) {
        return GLES20.glGetUniformLocation( program, name );
    }

    /**
     * @param program
     * @param name
     * @return
     * @desc 获得attr变量 ==> attribute vec4
     */
    public static int glGetAttribLocation(int program, String name) {
        return GLES20.glGetAttribLocation( program, name );
    }

}
