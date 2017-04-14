
#include "VelEngUti.h"

void Vel::VFrameClock::Tick()
{
	_prevTime = _currentTime;
	//_currentTime = GETCURRENTTIME; //TODO get current time
	_tick += _frameRate;
}

const GLfloat Vel::VFrameClock::CalculateRenderTime()
{
	_prevTime = _currentTime;
	//_currentTime = GETCURRENTTIME; //TODO get current time
	return _currentTime - _prevTime;
}

 