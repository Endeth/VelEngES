package com.example.t.perc;

import android.app.ActivityManager;
import android.content.Context;
import android.content.pm.ConfigurationInfo;
import android.opengl.GLSurfaceView;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import static android.opengl.GLES10.*;

class VelRenderer implements GLSurfaceView.Renderer
{
    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config)
    {
        GameLibJNIWrapper.Init();
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height)
    {
        GameLibJNIWrapper.Resize(width, height);
    }
    @Override
    public void onDrawFrame(GL10 gl)
    {
        GameLibJNIWrapper.Draw();
    }
}

public class OpenGLActivity extends AppCompatActivity
{

    private GLSurfaceView glSurfaceView;
    private boolean rendererSet;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_open_gl);

        ActivityManager actManager = (ActivityManager) getSystemService(Context.ACTIVITY_SERVICE);
        ConfigurationInfo confInfo = actManager.getDeviceConfigurationInfo();
        final boolean supportsEGL2 = confInfo.reqGlEsVersion >= 0x20000;
        if(supportsEGL2)
        {
            glSurfaceView = new GLSurfaceView(this);
            glSurfaceView.setEGLConfigChooser(8, 8, 8, 0, 16, 0);
            glSurfaceView.setEGLContextClientVersion(2);
            glSurfaceView.setRenderer(new VelRenderer());
            rendererSet = true;
            setContentView(glSurfaceView);
        }
    }

    @Override
    protected void onPause()
    {
        super.onPause();

        if(rendererSet)
        {
            glSurfaceView.onPause();
        }
    }

    @Override
    protected void onResume()
    {
        super.onResume();

        if(rendererSet)
        {
            glSurfaceView.onResume();
        }
    }


}
