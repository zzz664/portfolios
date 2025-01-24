#pragma once
#include "Game2D.h"
#include "DotSystem.h"
#include "DotDatas.h"
#include "Object.h"
#include "BulletManager.h"

class Player : public Object
{
private:
	Game2D* game;

	BulletManager* bullet_manager;
	Bullet* bullet;

	DotDatas* dot_datas;
	DotSystem* dot_image;

	float atan_dx;
	float atan_dy;

	bool is_move;

	float col_rad;

	float distance;

	float shoot_delay;
	

public:
	Player(Game2D* game);
	~Player();

	void update(float dt);
};