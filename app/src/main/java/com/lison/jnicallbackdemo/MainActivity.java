package com.lison.jnicallbackdemo;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;

public class MainActivity extends AppCompatActivity {

    public static final String TAG = "MainActivity";
    private JniCall jniCall;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        jniCall = new JniCall();
        jniCall.start();

        jniCall.setJNIEnv();  //

    }

    public void startThread(View view) {
        jniCall.mainThread();
    }
}
