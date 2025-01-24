#pragma once
#include "IObject.h"

class Player;
class UI;
class CSprite;

class key:public IObject {
public:
	key(Player *player,UI *ui,int x,int y);
	~key();

	Player *player;
	UI *ui;
	CSprite *Key;

	RECT kRect;

	int x,y;

	void Update(float eTime);
	void Render(D3DXMATRIX *pmat);
};