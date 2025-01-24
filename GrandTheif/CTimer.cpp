#include "CTimer.h"

CTimer::CTimer(float duration,bool running)
{
	this->duration = duration;
	this->running = running;
}
bool CTimer::Elapsed()
{
	return elapsedTime >= duration;;
}
void CTimer::Reset(bool running)
{
	if(running)
		elapsedTime = 0.f;
}
void CTimer::Update(float eTime)
{
	elapsedTime+=eTime;
}