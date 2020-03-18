package com.chaoliu.app;

import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.FrameLayout;

import com.chaoliu.opengl.core.BaseGLSurfaceView;
import com.chaoliu.opengl.Circle;


public class MainActivity extends AppCompatActivity {

    FrameLayout mContainer;
    BaseGLSurfaceView baseGLSurfaceView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate( savedInstanceState );
        setContentView( R.layout.activity_main );
        mContainer = findViewById( R.id.baseContainer );

        Circle circle = new Circle( this );
        baseGLSurfaceView = new BaseGLSurfaceView( this,circle );
        baseGLSurfaceView.setRenderMode( GLSurfaceView.RENDERMODE_CONTINUOUSLY );
        setView( baseGLSurfaceView );
    }

    void setView(View view) {
        mContainer.removeAllViews();
        mContainer.addView(view);
    }

    @Override
    protected void onResume() {
        super.onResume();
        baseGLSurfaceView.onResume();
    }

    @Override
    protected void onPause() {
        super.onPause();
        baseGLSurfaceView.onPause();
    }
}