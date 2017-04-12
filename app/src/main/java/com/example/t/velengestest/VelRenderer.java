package com.example.t.velengestest;

import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

class VelRenderer implements GLSurfaceView.Renderer
{
    public static native void Init();
    public static native void Resize(int width, int height);
    public static native void Draw();

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config)
    {
        Init();
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height)
    {
        Resize(width, height);
    }
    @Override
    public void onDrawFrame(GL10 gl)
    {
        Draw();
    }
}