#pragma once

#include <GLES3/gl3.h>
#include "glm/glm.hpp"
#include <chrono>

namespace Vel
{
	class VFrameClock
	{
	public:
		void Tick();
		void SetCurrentTime(GLfloat currentTime) { _currentTime = currentTime;}
		const GLfloat GetTime() const { return _currentTime; }
		const GLfloat GetSimulationTime() const { return _tick; }
		const GLfloat GetFrameRate() const { return _frameRate; }
		const GLfloat GetTimeDifferance() const { return _currentTime - _prevTime; }
		//void CapFPS();
	private:
		const GLfloat CalculateRenderTime();

		GLfloat _prevTime{ 0.0 };
		GLfloat _tick{ 0.0 };
		GLfloat _currentTime{ 0.0 };
		GLfloat _frameRate{ 1.0f / 30.0f };
	};
}