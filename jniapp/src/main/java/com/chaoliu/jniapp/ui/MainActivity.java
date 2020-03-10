package com.chaoliu.jniapp.ui;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

import com.chaoliu.jniapp.NativeLib;
import com.chaoliu.jniapp.R;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate( savedInstanceState );
        setContentView( R.layout.activity_main );
        NativeLib.getNativeString( "sasas" );
    }
}
