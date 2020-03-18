package com.glumes.openglbasicshape;

import android.content.Context;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;

import com.glumes.openglbasicshape.magiccube.views.ViewAutoMode;

public class MagicCubeActivity extends AppCompatActivity {

    Context mContext;

    ViewAutoMode glView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.activity_magic_cube);
        glView = (ViewAutoMode) findViewById(R.id.viewAutoMode);
    }
}
