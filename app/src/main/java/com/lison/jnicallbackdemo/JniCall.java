package com.lison.jnicallbackdemo;

import android.util.Log;

public class JniCall {

    public static final String TAG = "JniCall";
    static {
        System.loadLibrary("lison");
    }
    public native void start();
    public native void setJNIEnv();
    public native void mainThread();

    public void callMethod01(){
        Log.e(TAG, "callMethod01: 已执行" );
    }

    public int callMethod02(String para1,String para2,int para3){
        Log.e(TAG, "callMethod02: 已执行 ---->"+para1+"  "+para2+"   "+para3 );
        return 0;
    }

    public void ReceiveCallback(byte[] buffer,int len){
        Log.e(TAG, "ReceiveCallback:  buffer=== "+new String(buffer)+"    len =  "+len );
    }

    public static void fromJNI(int i){
        Log.e(TAG, "fromJNI: "+i );
    }
}
