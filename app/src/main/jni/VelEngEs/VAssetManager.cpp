#include "VAssetManager.h"
#include <GLES3/gl3.h>
#include <android/log.h>

namespace Vel
{
    VAssetManager::VAssetManager(AAssetManager *aManPtr, const std::string &internalPath) : _aManager(aManPtr), _apkInternalPath(internalPath)
    {
    }
    VAssetManager::VAssetManager(AAssetManager *aManPtr, std::string &&internalPath) : _aManager(aManPtr), _apkInternalPath(internalPath)
    {
    }

    char* VAssetManager::LoadAsset(const char* fileName)
    {
        char* as;
        AAsset* asset = AAssetManager_open(_aManager, fileName, AASSET_MODE_STREAMING);

        off_t srcLen = AAsset_getLength(asset);
        as = new char[srcLen];
        AAsset_seek(asset, 0, 0);
        AAsset_read(asset, as, srcLen);
        AAsset_close(asset);

        return as;
    }
}