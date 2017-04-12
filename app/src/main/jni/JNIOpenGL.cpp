#include <jni.h>
#include "OpenGL/VelGLES.h"
extern "C" {


    /*JNIEXPORT jint JNICALL Java_com_example_t_velengestest_GameLibJNIWrapper_Test(JNIEnv* env, jobject obj)
    {
        return 1;
    }*/

    JNIEXPORT void JNICALL Java_com_example_t_velengestest_VelRenderer_Init(JNIEnv* env, jobject obj)
    {
        Vel::OnSurfaceCreated();
    }
    JNIEXPORT void JNICALL Java_com_example_t_velengestest_VelRenderer_Draw(JNIEnv* env, jobject obj)
    {
		Vel::OnDrawFrame();
    }
    JNIEXPORT void JNICALL Java_com_example_t_velengestest_VelRenderer_Resize(JNIEnv* env, jobject obj)
    {
    }
};


