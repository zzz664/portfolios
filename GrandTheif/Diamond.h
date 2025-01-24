#pragma once
#include "IObject.h"

class CSprite;
class Player;
class UI;

class Diamond:public IObject {
public:
	Diamond(Player *player,UI *ui,int x,int y);
	~Diamond();

	CSprite *diamond;
	Player *player;
	UI *ui;

	void Update(float eTime);
	void Render(D3DXMATRIX *pmat);
};