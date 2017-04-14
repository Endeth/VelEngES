#include "VelGLES.h"
#include "VRenderer.h"




namespace Vel {

    using namespace std;

    VelEngES* VelEngES::_instance = nullptr;

    VelEngES::VelEngES()
    {

        InitCamera();

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glDepthFunc(GL_LEQUAL);
    }

    bool VelEngES::AddShaderProgram(const string & Name, const shared_ptr<VGLSLShader> &shaderPtr)
    {
        _shaderPrograms.emplace(Name, shaderPtr);
        return true;
    }

    bool VelEngES::AddShaderProgram(const string & Name, const string & VertFilename, const string & FragFilename)
    {
        std::string vertexShader = LoadAsset(VertFilename.c_str());
        std::string fragmentShader = LoadAsset(FragFilename.c_str());
        while(vertexShader.back() != '}') //TODO erase hack?
            vertexShader.pop_back();
        while(fragmentShader.back() != '}')
            fragmentShader.pop_back();

        auto shader = _shaderPrograms.emplace(Name, make_shared<VGLSLShader>()).first->second;
        shader->LoadFromString(GL_VERTEX_SHADER, vertexShader.c_str());
        shader->LoadFromString(GL_FRAGMENT_SHADER, fragmentShader.c_str());
        shader->CreateAndLinkProgram();

        __android_log_print(ANDROID_LOG_INFO, "OpenGL", "Shader:\n%s\n", vertexShader.c_str());
        __android_log_print(ANDROID_LOG_INFO, "OpenGL", "Shader:\n%s\n", fragmentShader.c_str());

        //delete[] vertexShader;
        //delete[] fragmentShader;

        return true;
    }


    const shared_ptr<VGLSLShader>& VelEngES::GetShader(const string & name)
    {
        return _shaderPrograms[name];
    }

    void VelEngES::CreateScene(const string& Name)
    {
        unique_ptr<VScene> scene(new VScene());
        _scenes.emplace(Name, std::move(scene));
    }

    void VelEngES::AddModelToScene(const string & sceneName, const shared_ptr<VModel>& modelPtr)
    {
        _scenes[sceneName]->AddModel(modelPtr);
    }

    void VelEngES::AddLightSourceToScene(const string & sceneName, const shared_ptr<VLightSource>& lightSourcePtr)
    {
        _scenes[sceneName]->AddLightSource(lightSourcePtr);
    }

    void VelEngES::HandleInput()
    {

    }

    void VelEngES::RenderScenes()
    {
        _scenes["TestScene"]->DrawSceneWithImposedShader(GetShader("BasicShader"));
    }

    void VelEngES::RenderFrame()
    {
        glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        RenderScenes();
        //GLint err = glGetError();
        //__android_log_print(ANDROID_LOG_INFO, "OpenGL", "Error:%d\n", err); //FRAME ERROR CHECK
    }





    void VelEngES::InitCamera()
    {
        _mainCamera = std::make_shared<VFreeCamera>();
        _mainCamera->SetupProjection(60, (GLfloat)(720 / 1280));
        _mainCamera->Update();
    }

    void VelEngES::InitAssetManager(JNIEnv* env, jobject &assetManager, std::string &&internalPath)
    {
        _assetManager = std::unique_ptr<VAssetManager>(new VAssetManager(AAssetManager_fromJava(env, assetManager), std::move(internalPath)));
    }

    char* VelEngES::LoadAsset(const char *fileName) {
        return _assetManager->LoadAsset(fileName);
    }



//--------------------------------------------------------------------------------------------------

    static const string VERTEX_SHD =
    "#version 300 es\n"
    "layout(location = 0) in vec3 vVertex;\n"
    "layout(location = 1) in vec3 vNormal;\n"
    "layout(location = 2) in vec2 vUV;\n"
    "out vec4 verColor;\n"
    "void main() {\n"
    "    gl_Position = vec4(vVertex, 1.0);\n"
    "    verColor = vec4(vNormal, 1.0);\n"
    "}\n";

    static const string FRAGMENT_SHD =
    "#version 300 es\n"
    "precision mediump float;\n"
    "in vec4 verColor;\n"
    "out vec4 FragColor;\n"
    "void main() {\n"
    "    FragColor = verColor;\n"
    "}\n";


    void OnSurfaceCreated()
    {
        __android_log_print(ANDROID_LOG_INFO, "OpenGL", "SurfaceCreated");
        VelEngES::Instance()->AddShaderProgram("BasicShader", "TestShader.vert", "TestShader.frag");
        auto TestShader = VelEngES::Instance()->GetShader("BasicShader");
        TestShader->SetAttributes({ "vVertex", "vNormal", "vUV"}); //TODO fix vUV attribute

        std::shared_ptr<VTriangleMesh> triangleMeshTest = std::make_shared<VTriangleMesh>();
        triangleMeshTest->LoadVerticesOnly();
        triangleMeshTest->SetShader(TestShader);
        shared_ptr<VModel> modelTest = std::make_shared<VModel>();
        modelTest->AddMesh(triangleMeshTest);

        GLint err = glGetError();
        //__android_log_print(ANDROID_LOG_INFO, "OpenGL", "ASSETLOADING%x\n", testAsset.size());

        VelEngES::Instance()->CreateScene("TestScene");
        VelEngES::Instance()->AddModelToScene("TestScene", modelTest);

    }

    void OnSurfaceChanged() {

    }

    void OnDrawFrame() {
        if (VelEngES::Instance()->ShouldRun())
        {
            VelEngES::Instance()->RenderFrame();
        }
    }
}