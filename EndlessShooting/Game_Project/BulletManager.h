#pragma once

#include <list>
#include "Bullet.h"

class BulletManager
{
private:

	std::list<Bullet*> bullet_list;

public:

	BulletManager();
	~BulletManager();

	void update(float dt);

	void push(Bullet* bullet);
};