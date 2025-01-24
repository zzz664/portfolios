#pragma once
#include "IObject.h"

class CSprite;
class Player;
class UI;

class stage_key:public IObject {
public:
	stage_key(Player *player,UI *ui,int x,int y);
	~stage_key();

	Player *player;
	UI *ui;
	CSprite *Stage_key;

	RECT skRect;

	void Update(float eTime);
	void Render(D3DXMATRIX *pmat);
};