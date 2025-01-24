#pragma once

#include "DotSystem.h"
#include "DotDatas.h"
#include "Object.h"

class Monster : public Object
{
private:
	Vector2<float> player_pos;
	Vector2<float> dir;

	DotDatas* dot_datas;
	DotSystem* dot_image;

public:
	Monster(Vector2<float> player_pos);
	~Monster();

	void update(float dt);
};
