#include <jni.h>
#include "VelEngEs/VelGLES.h"
extern "C" {


    /*JNIEXPORT jint JNICALL Java_com_example_t_velengestest_GameLibJNIWrapper_Test(JNIEnv* env, jobject obj)
    {
        return 1;
    }*/

    JNIEXPORT void JNICALL Java_com_example_t_velengestest_OpenGLActivity_JNIInit(JNIEnv* env, jobject obj, jobject assetManager, jstring pathToInternalDir)
    {
        std::string internalDir{env->GetStringUTFChars(pathToInternalDir, nullptr)};
        Vel::VelEngES::Instance()->InitAssetManager(env, assetManager, std::move(internalDir));
    }
	JNIEXPORT void JNICALL Java_com_example_t_velengestest_OpenGLActivity_JNICleanUp(JNIEnv* env, jobject obj)
    {

    }

};


