#pragma once

#include "glm/glm.hpp"
#include <jni.h>
#include <android/asset_manager.h>
#include <pthread.h>
#include <string>
#include <memory>
#include <vector>

namespace Vel
{
	class VAssetManager
	{
	public:
        VAssetManager(AAssetManager* aManPtr, const std::string &internalPath);
		VAssetManager(AAssetManager* aManPtr, std::string &&internalPath);
        char* LoadAsset(const char* fileName);
	private:
        AAssetManager* _aManager;
		std::string _apkInternalPath;
	};

}