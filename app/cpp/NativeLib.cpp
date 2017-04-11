#include <jni.h>
#include "OpenGL/VelGLES.h"
extern "C" {


    JNIEXPORT jint JNICALL Java_com_example_t_perc_GameLibJNIWrapper_Test(JNIEnv* env, jobject obj)
    {
        return 1;
    }


//OpenGL -------------------------------------------------------------------------------------------
    JNIEXPORT void JNICALL Java_com_example_t_perc_GameLibJNIWrapper_Init(JNIEnv* env, jobject obj)
    {
        Vel::OnSurfaceCreated();
    }
    JNIEXPORT void JNICALL Java_com_example_t_perc_GameLibJNIWrapper_Draw(JNIEnv* env, jobject obj)
    {
		Vel::OnDrawFrame();
    }
    JNIEXPORT void JNICALL Java_com_example_t_perc_GameLibJNIWrapper_Resize(JNIEnv* env, jobject obj)
    {
    }
};


