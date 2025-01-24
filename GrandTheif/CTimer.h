#pragma once
class CTimer
{
public:
	float duration;
	float elapsedTime;
	bool running;

	CTimer(float duration,bool running = true);

	bool Elapsed();
	void Reset(bool running = true);
	void Update(float eTime);
};