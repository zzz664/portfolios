#pragma once
#include "IObject.h"

class CSprite;
class Player;

class Vision : public IObject {
public:
	Vision(Player *player);
	~Vision();

	CSprite *vision;
	Player *player;

	void Update(float eTime);
	void Render(D3DXMATRIX *pmat);
};