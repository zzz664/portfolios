#pragma once

#include "Game2D.h"
#include "Player.h"
#include "Monster.h"

using namespace jm;

class EndlessShooting : public Game2D
{
private:
	Player* player;
	Monster* m;
public:

	EndlessShooting();
	~EndlessShooting();

	void update() override;
};