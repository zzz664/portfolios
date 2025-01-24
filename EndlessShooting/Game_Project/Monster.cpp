#include "Monster.h"
#include "Game2D.h"

Monster::Monster(Vector2<float> player_pos)
{
	dot_datas = new DotDatas();
	dot_image = new DotSystem(dot_datas->monster_dots, 3.f);
	
	pos.x = 640.f;
	pos.y = 480.f;

	this->player_pos.x = player_pos.x;
	this->player_pos.y = player_pos.y;

	dir.x = player_pos.x - pos.x;
	dir.y = player_pos.y - pos.y;

	degree = 180.f * atan2(dir.y, dir.x) / 3.141592f + 90.f;

	vel = 300.f;
}

Monster::~Monster()
{
	delete dot_datas;
	delete dot_image;
}

void Monster::update(float dt)
{
	pos.x += vel * dt * cos(atan2(dir.y, dir.x));
	pos.y += vel * dt * sin(atan2(dir.y, dir.x));

	beginTransformation();
	{
		translate(pos);
		translate(dot_image->getCenter());
		rotate(degree);
		translate(-dot_image->getCenter());
		dot_image->render();
	}
	endTransformation();
}