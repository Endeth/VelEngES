package com.example.t.velengestest;

import android.app.ActivityManager;
import android.content.Context;
import android.content.pm.ConfigurationInfo;
import android.content.res.AssetManager;
import android.opengl.GLSurfaceView;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;


public class OpenGLActivity extends AppCompatActivity
{
    private native void JNIInit(AssetManager assetManager, String pathToInternalDir);
    private native void JNICleanUp();
    private GLSurfaceView glSurfaceView;
    private boolean rendererSet;
    VelGesture gesture;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_open_gl);

        AssetManager assetManager = getAssets();
        String pathToInternalDir = getFilesDir().getAbsolutePath();

        JNIInit(assetManager, pathToInternalDir);

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

    @Override
    protected void onDestroy()
    {
        super.onDestroy();
        JNICleanUp();
    }

}
