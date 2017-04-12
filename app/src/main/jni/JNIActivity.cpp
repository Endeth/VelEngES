#include <jni.h>
#include "OpenGL/VelGLES.h"
extern "C" {


    /*JNIEXPORT jint JNICALL Java_com_example_t_velengestest_GameLibJNIWrapper_Test(JNIEnv* env, jobject obj)
    {
        return 1;
    }*/

    JNIEXPORT void JNICALL Java_com_example_t_velengestest_OpenGLActivity_JNIInit(JNIEnv* env, jobject obj, jobject assetManager, jstring pathToInternalDir)
    {

    }
	JNIEXPORT void JNICALL Java_com_example_t_velengestest_OpenGLActivity_JNICleanUp(JNIEnv* env, jobject obj)
    {

    }

};


