#pragma once

#include "Vector2.h"

using namespace jm;

class DotSystem
{
private:
	int data[16][16];

	int w;
	int h;

	float dot_size;

public:
	DotSystem(int (*data)[16], float dot_size);
	~DotSystem();

	void render();

	Vector2<float> getCenter() { return Vector2<float>(((w * dot_size / 2.f) + (dot_size / 2.f)), -((h * dot_size / 2.f) - (dot_size / 2.f))); }
	float getDotSize() { return dot_size; }
	int getDotImageWidth() { return w; }
	int getDotImageHeight() { return h; }
};