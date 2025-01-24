#pragma once

#include "Vector2.h"

using namespace jm;

class Object
{
protected:
	Vector2<float> pos;

	float vel;
	float acc;

	float degree;

public:

	Object() {}
	~Object() {}

	virtual void update(float dt) = 0;

	void SetPos(float x, float y) { pos.x = x; pos.y = y; }
	Vector2<float>  GetPos() { return pos; }

	void SetDeg(float degree) { this->degree = degree; }
	float GetDeg() { return degree; }
};