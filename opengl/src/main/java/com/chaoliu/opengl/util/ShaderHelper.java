package com.chaoliu.opengl.util;

import android.content.Context;
import android.opengl.GLES20;

import static android.opengl.GLES20.GL_COMPILE_STATUS;
import static android.opengl.GLES20.GL_FRAGMENT_SHADER;
import static android.opengl.GLES20.GL_LINK_STATUS;
import static android.opengl.GLES20.GL_VALIDATE_STATUS;
import static android.opengl.GLES20.GL_VERTEX_SHADER;
import static android.opengl.GLES20.glAttachShader;
import static android.opengl.GLES20.glCompileShader;
import static android.opengl.GLES20.glCreateProgram;
import static android.opengl.GLES20.glCreateShader;
import static android.opengl.GLES20.glDeleteProgram;
import static android.opengl.GLES20.glDeleteShader;
import static android.opengl.GLES20.glGetProgramInfoLog;
import static android.opengl.GLES20.glGetProgramiv;
import static android.opengl.GLES20.glGetShaderiv;
import static android.opengl.GLES20.glLinkProgram;
import static android.opengl.GLES20.glShaderSource;
import static android.opengl.GLES20.glValidateProgram;


/**
 * 创建一个 OpenGL 程序的通用步骤
 * 只提供opengl基本操作，便于整体性理解，提高通用扩展性
 *
 * @author chentong
 * @desc 进行二次抽象，便于开发者快速使用
 * @date 2020-3-16
 */
public class ShaderHelper {

    private static final String TAG = "ShaderHelper";

    //todo 完整编译opengl
    public static int buildProgram(String vertexShaderSource, String fragmentShaderSource) {
        int program;
        LogUtil.d( "vertex is " + vertexShaderSource + " frag is " + fragmentShaderSource );
        int vertexShader = compileVertexShader( vertexShaderSource );
        int fragmentShader = compleFragmentShader( fragmentShaderSource );
        program = linkProgram( vertexShader, fragmentShader );
        validateProgram( program );
        return program;
    }

    public static int buildProgram(Context context, int vertexShaderSource, int fragmentShaderSource) {
        String vertexString = TextResourceReader.readTextFileFromResource( context, vertexShaderSource );
        String textureString = TextResourceReader.readTextFileFromResource( context, fragmentShaderSource );
        return buildProgram( vertexString, textureString );
    }

    public static int buildProgramFromAssetFile(Context context, String vertexFileName, String fragmentFileName) {
        String vertexString = TextResourceReader.readTextFileFromAsset( context, vertexFileName );
        String fragmentString = TextResourceReader.readTextFileFromAsset( context, fragmentFileName );
        LogUtil.d( "vertex is " + vertexString + " frag is " + fragmentString );
        return buildProgram( vertexString, fragmentString );
    }

    // 编译顶点着色器
    public static int compileVertexShader(String shaderCode) {
        return compileShader( GL_VERTEX_SHADER, shaderCode );
    }

    // 编译片段着色器
    public static int compleFragmentShader(String shaderCode) {
        return compileShader( GL_FRAGMENT_SHADER, shaderCode );
    }

    // todo 根据类型编译着色器
    private static int compileShader(int type, String shaderCode) {
        final int shaderObjectId = glCreateShader( type );
        if (shaderObjectId == 0) {
            LogUtil.d( "could not create new shader" );
            return 0;
        }
        glShaderSource( shaderObjectId, shaderCode );
        glCompileShader( shaderObjectId );
        final int[] compileStatsu = new int[1];
        glGetShaderiv( shaderObjectId, GL_COMPILE_STATUS, compileStatsu, 0 );
//        LogUtil.d("Result of compiling source:" + "\n" + shaderCode + "\n:"
//                + glGetShaderInfoLog(shaderObjectId));

        if ((compileStatsu[0] == 0)) {
            glDeleteShader( shaderObjectId );
            LogUtil.d( "Compilation of shader failed" );
            return 0;
        }
        return shaderObjectId;
    }

    //todo 创建opengl程序和着色器链接
    public static int linkProgram(int vertexShaderId, int fragmentShaderId) {
        final int programObjectId = glCreateProgram();
        if (programObjectId == 0) {
            LogUtil.d( "Could not create new program" );
            return 0;
        }
        glAttachShader( programObjectId, vertexShaderId );
        glAttachShader( programObjectId, fragmentShaderId );
        glLinkProgram( programObjectId );

        final int[] linkStatus = new int[1];
        glGetProgramiv( programObjectId, GL_LINK_STATUS, linkStatus, 0 );

        LogUtil.d( "Result of linking program:\n" + glGetProgramInfoLog( programObjectId ) );

        if (linkStatus[0] == 0) {
            glDeleteProgram( programObjectId );
            LogUtil.d( "Linking of program failed" );
            return 0;
        }
        return programObjectId;
    }

    //todo 验证OpenGL程序
    public static boolean validateProgram(int programObjectId) {
        glValidateProgram( programObjectId );
        final int[] validateStatus = new int[1];
        glGetProgramiv( programObjectId, GL_VALIDATE_STATUS, validateStatus, 0 );
        LogUtil.d( "Result of validating program: " + validateStatus[0] + "\nLog:" + glGetProgramInfoLog( programObjectId ) );
        return validateStatus[0] != 0;
    }

    //todo 验证错误
    public static void checkGlError(String glOperation) {
        int error;
        while ((error = GLES20.glGetError()) != GLES20.GL_NO_ERROR) {
            LogUtil.e( glOperation + ": glError " + error );
            throw new RuntimeException( glOperation + ": glError " + error );
        }
    }
}
