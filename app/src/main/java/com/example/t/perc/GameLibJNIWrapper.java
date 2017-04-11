package com.example.t.perc;

/**
 * Created by T on 2017-03-30.
 */

public class GameLibJNIWrapper
{
    public static native void Init();
    public static native void Resize(int width, int height);
    public static native void Draw();
    public static native int Test();
    static
    {
        System.loadLibrary("NativeLib");
    }
}
