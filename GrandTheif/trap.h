#pragma once
#include "IObject.h"

class Player;
class UI;
class CSprite;

class trap:public IObject {
public:
	trap(Player *player,UI *ui,int x,int y);
	~trap();

	Player *player;
	UI *ui;
	CSprite *Trap;

	RECT tRect;

	int x,y;

	void Update(float eTime);
	void Render(D3DXMATRIX *pmat);
};