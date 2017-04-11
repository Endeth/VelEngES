#pragma once
#include <GLES3/gl3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "VGLSLShader.h"
#include "VFramebuffer.h"
#include "VModel.h"
#include <memory>
#include <list>
#include <string>


namespace Vel
{
	class VLightSource //TODO make a generic class GEOMETRY OBJECT or something like that
	{
	protected:
		using ShaderPtr = std::shared_ptr<VGLSLShader>;
		using ShadowMapFBOPtr = std::unique_ptr<VShadowMap2D>;
	public:
		class VLightColor
		{

		public:
			VLightColor(const glm::vec3& diffuse, const glm::vec3& specular);
			const glm::vec3& GetDiffuse() const { return _diffuse; }
			const glm::vec3& GetSpecular() const { return _specular; }
		private:
			glm::vec3 _diffuse;
			glm::vec3 _specular;
		};

		VLightSource(const glm::vec3& diffuse, const glm::vec3& specular); 
		VLightSource(const VLightColor& color);
		void ActivateShader() { _depthShader->Activate(); }
		void DeactivateShader() { _depthShader->Deactivate(); }

		/*Sets uniforms in light using shader
		Pass iterator from VSceneLights to uniformID when setting uniforms*/
		virtual void SetLPassLightUniforms(GLuint program, GLuint uniformID) = 0;
		//Sets uniforms in shadow map generating shader
		virtual void SetShadowUniforms();

		virtual void SetTextureUnit(GLuint textureUnit);
		virtual void BindShadowMapForWriting();
		virtual void UnbindShadowMapForWriting(); 
		virtual void BindShadowMapForReading();
		virtual void UnbindShadowMapForReading();

		void SetShader(const ShaderPtr& shader) { _depthShader = shader; }
		const VLightColor& GetColor() const { return _color; }
		const ShaderPtr& GetShader() const { return _depthShader; }
		const glm::ivec2& GetShadowResolution() const { return _shadowResolution; }
	protected:
		VLightColor _color;
		ShaderPtr _depthShader;
		ShadowMapFBOPtr _shadowMap;
		glm::mat4 _lightSpaceMatrix;
		glm::ivec2 _shadowResolution;
	};

	class VPointLight : public VLightSource
	{
	public:
		VPointLight(const glm::vec3& position, const glm::vec3& diffuse, const glm::vec3& specular); //no reason to keep ambient
		VPointLight(const glm::vec3& position, const VLightColor& colors);
		

		virtual void SetLPassLightUniforms(GLuint program, GLuint uniformID) override;
		virtual void SetShadowUniforms() override;

		//sets position and recalculates shadow transforms matrices - might want to set those apart
		void SetPosition(const glm::vec3 &pos);
		const glm::vec3& GetPosition() const { return _position; }

		virtual void SetTextureUnit(GLuint textureUnit) override { _shadowMap->SetTextureUnit(textureUnit); }
		virtual void BindShadowMapForWriting() override { _shadowMap->BindFBOWriting(); }
		virtual void UnbindShadowMapForWriting() override { _shadowMap->UnbindFBOWriting(); }
		virtual void BindShadowMapForReading() override { _shadowMap->BindTexturesReading(); }
		virtual void UnbindShadowMapForReading() override { _shadowMap->UnbindTexturesReading(); }
		
	protected:
		glm::vec3 _position;
		GLfloat _constant;
		GLfloat _linear;
		GLfloat _quadratic;
		
	private:
		std::vector<glm::mat4> _shadowTransforms;
		std::unique_ptr<VShadowMapCube> _shadowMap;
		void UpdateShadowTransforms();
	};

	class VDirectionalLight : public VLightSource
	{
	public:
		VDirectionalLight(const glm::vec3& direction, const glm::vec3& diffuse, const glm::vec3& specular);
		VDirectionalLight(const glm::vec3& direction, const VLightColor& colors);

		virtual void SetLPassLightUniforms(GLuint program);
		virtual void SetShadowUniforms() override;

		//sets direction and recalculates shadow transforms matrices - might want to set those apart
		void SetDirection(const glm::vec3 &dir);
		const glm::vec3& GetDirection() const { return _direction; }

		void SetCameraPosition(const glm::vec3 &pos);
	protected:
		glm::vec3 _direction;
	private:
		glm::vec3 _camPosition;
		glm::vec3 _shadowCastingPosition;
		virtual void SetLPassLightUniforms(GLuint program, GLuint uniformID) override {}; //not needed
		void UpdateShadowTransforms(); //TODO - implement directional light following camera
	};

	//not yet implemented
	class VSpotLight : public VLightSource
	{
	public:
		VSpotLight(const glm::vec3& direction, const glm::vec3& diffuse, const glm::vec3& specular);
		VSpotLight(const glm::vec3& direction, const VLightColor& colors);

		virtual void SetLPassLightUniforms(GLuint program, GLuint uniformID) override;
		virtual void SetShadowUniforms() override;

		//sets direction and recalculates shadow transforms matrices - might want to set those apart
		void SetDirection(const glm::vec3 &dir) { _direction = dir; }
		const glm::vec3& GetDirection() const { return _direction; }
	protected:
		glm::vec3 _position;
		glm::vec3 _direction;
		GLfloat _constant;
		GLfloat _linear;
		GLfloat _quadratic;
	private:
		void UpdateShadowTransforms();
	};

	class VSceneLighting
	{
	/*
		maybe light sorting? then calculating first X lights, same principle with shadows?
	*/
	public:

		void CleanUpLights() {}; //TODO
		void AddLight(const std::shared_ptr<VLightSource>& lightSource);
		void CreateDirectionalLight(const glm::vec3 &dir, const VLightSource::VLightColor &color);
		void CreateDirectionalLight(std::unique_ptr<VDirectionalLight> &&light);

		//creates shadowmap where camera position is center
		void DrawDirectionalLightShadowMap(const glm::vec3 &cameraPosition);
		//Draws MAX 4 shadow maps
		void DrawSceneShadows(const std::vector<std::shared_ptr<VModel>>& models);

		/*Activates first 4 (or less if there aren't that many textures) unit textures
		from GL_TEXTURE4 to GL_TEXTURE7 and binds appropriate textures*/
		void ActivateShadowMaps();

		//requires active shader
		void SetLPassLightUniforms(GLuint lPassProgram);
		void SetAmbientLight(const glm::vec3 &amb) { _ambientLight = amb; }
		void SetCameraPosition(const glm::vec3 &pos);
	private:
		glm::vec3 _cameraPosition; //TODO change to pointer
		glm::vec3 _ambientLight{0.1,0.1,0.1};
		std::unique_ptr<VDirectionalLight> _directionalLight;
		std::list<std::shared_ptr<VLightSource>> _sceneLights;
	};
}