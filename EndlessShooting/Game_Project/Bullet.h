#pragma once

#include "Game2D.h"
#include "DotSystem.h"
#include "DotDatas.h"
#include "Object.h"

class Bullet : public Object
{
private:
	DotDatas* dot_datas;
	DotSystem* dot_image;

	float center_x, center_y;
	float life_time;
	bool is_erase;

public:
	Bullet();
	~Bullet();

	void update(float dt);

	void SetCenter(float x, float y) { center_x = x, center_y = y; };

	bool SetErase(bool is_erase) { this->is_erase = is_erase; }
	bool IsErase() { return is_erase; }
};