#include "Bullet.h"

Bullet::Bullet()
{
	dot_datas = new DotDatas();
	dot_image = new DotSystem(dot_datas->bullet_dots, 2.f);

	pos = { 0.f, 0.f };
	vel = 800.f;
	degree = 0.f;
	life_time = 0.f;
	is_erase = false;
}

Bullet::~Bullet()
{
	delete dot_datas;
	delete dot_image;
}

void Bullet::update(float dt)
{
	life_time += dt;

	if (life_time >= 1.55f)
	{
		is_erase = true;
	}

	pos.x += vel * dt * cos(3.141592f * (degree + 90.f) / 180.f);
	pos.y += vel * dt * sin(3.141592f * (degree + 90.f) / 180.f);

	beginTransformation();
	{
		translate(pos);
		translate(center_x, center_y);
		rotate(degree);
		translate(-center_x, -center_y);
		dot_image->render();
	}
	endTransformation();
}