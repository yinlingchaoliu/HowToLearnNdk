package com.chaoliu.opengl;

import android.content.Context;

import com.chaoliu.app.R;
import com.chaoliu.opengl.core.BaseGLRenderer;
import com.chaoliu.opengl.util.OpenglUtil;
import com.chaoliu.opengl.util.ShaderHelper;
import com.chaoliu.opengl.util.VertexArray;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import static android.opengl.GLES20.GL_LINE_LOOP;
import static android.opengl.GLES20.glDrawArrays;
import static android.opengl.GLES20.glUniform4f;


/**
 * Created by glumes on 2017/8/6.
 */

public class Circle extends BaseGLRenderer {

    // 圆形分割的数量，可由 360 个直线组成空心圆，也可以由 360 个三角形组成实心圆
    // 把 数量改变就可以绘制对应的正多边形了，毕竟圆形也是由正多边形趋近的
    public static final int VERTEX_DATA_NUM = 360;

    // 360 个顶点的位置，因为有 x 和 y 坐标，所以 double 一下，再加上中心点 和 闭合的点
    float[] circleVertex = new float[VERTEX_DATA_NUM * 2 + 4];

    // 分成 360 份，每一份的弧度
    float radian = (float) (2 * Math.PI / VERTEX_DATA_NUM);

    // 绘制的半径
    float radius = 0.8f;

    public Circle(Context context) {
        super(context);
    }

    @Override
    public int buildOpenGLProgram() {
        return ShaderHelper.buildProgram(mContext, R.raw.circle_vertex_shader, R.raw.circle_fragment_shader);
    }

    @Override
    public void onCreate(GL10 gl, EGLConfig config) {
        initVertexData();
        vertexArray = new VertexArray(circleVertex);
        POSITION_COMPONENT_COUNT = 2;
        aColorLocation = OpenglUtil.getUColorLocation(mProgram);
        aPositionLocation = OpenglUtil.getAttrPostionLocation( mProgram );
        vertexArray.setVertexAttribPointer(0, aPositionLocation, POSITION_COMPONENT_COUNT, 0);
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {

    }

    @Override
    public void onSurfaceDestroyed() {

    }

    @Override
    public void onDrawFrame(GL10 gl) {
        glUniform4f(aColorLocation, 0.0f, 1.0f, 0.0f, 0.0f);
        // 绘制实心的圆形
//        glDrawArrays(GL_TRIANGLE_FAN, 0, VERTEX_DATA_NUM + 2);

        // 绘制空心的圆形
        glDrawArrays(GL_LINE_LOOP, 1, VERTEX_DATA_NUM);
    }

    // 初始化圆形的顶点数据
    private void initVertexData() {
        // 中心点
        circleVertex[0] = 0f;
        circleVertex[1] = 0f;
        // 圆的 360 份的顶点数据
        for (int i = 0; i < VERTEX_DATA_NUM; i++) {
            circleVertex[2 * i + 2] = (float) (radius * Math.cos(radian * i));
            circleVertex[2 * i + 1 + 2] = (float) (radius * Math.sin(radian * i));
        }
        // 闭合点
        circleVertex[VERTEX_DATA_NUM * 2 + 2] = (float) (radius * Math.cos(radian));
        circleVertex[VERTEX_DATA_NUM * 2 + 3] = (float) (radius * Math.sin(radian));
    }

}
