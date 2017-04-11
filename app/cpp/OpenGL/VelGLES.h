#ifndef VELGLES_H
#define VELGLES_H

#include <unordered_map>
#include <android/log.h>
#include <map>
#include <memory>
#include <string>

#include <android/log.h>
#include <GLES3/gl3.h>
#include "glm/glm.hpp"

#include "VGLSLShader.h"
#include "VScene.h"
#include "VModel.h"
#include "VSky.h"
#include "VCamera.h"
#include "VTexture.h"
#include "VRenderer.h"
#include "VFramebuffer.h"
#include "VLight.h"
#include "VelEngUti.h"


namespace Vel {
    class VelEngES
    {
        using RendererPtr = std::shared_ptr<VDefferedRenderer>;
        using ScenePtr = std::shared_ptr<VScene>;
    public:
        static VelEngES* Instance()
        {
            if (!_instance)
                _instance = new VelEngES;
            return _instance;
        }
        VelEngES(const VelEngES&) = delete;
        VelEngES(const VelEngES&&) = delete;

        const bool ShouldRun() const { return _shouldRun; }
        void SetRenderer(const RendererPtr& renderer) { _renderer = renderer; }
        bool AddShaderProgram(const std::string& name, const std::shared_ptr<VGLSLShader> &shaderPtr);
        bool AddShaderProgram(const std::string& name, const std::string& vertFilename, const std::string& fragFilename);

        const std::shared_ptr<VGLSLShader>& GetShader(const std::string& name);
        std::shared_ptr<VFreeCamera>& GetMainCamera() { return _mainCamera; }

        void CreateScene(const std::string& name);
        ScenePtr& GetScene(const std::string& name) { return _scenes[name]; }
        void AddModelToScene(const std::string & sceneName, const std::shared_ptr<VModel>& modelPtr);
        void AddLightSourceToScene(const std::string & sceneName, const std::shared_ptr<VLightSource>& lightSourcePtr);

        void InitCamera();

        void HandleInput();
        void RenderScenes();
        void RenderFrame();

    private:
        VelEngES();

        std::unordered_map<std::string, std::shared_ptr<VGLSLShader>> _shaderPrograms;
        std::map<std::string, std::shared_ptr<VScene>> _scenes;

        std::shared_ptr<VFreeCamera> _mainCamera;

        static VelEngES* _instance;

        RendererPtr _renderer;
        VFrameClock _frameClock;
        bool _shouldRun{ true };
    };

    void OnSurfaceCreated();

    void OnSurfaceChanged();

    void OnDrawFrame();
}
#endif // VELGLES_H