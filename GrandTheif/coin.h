#pragma once
#include "IObject.h"

class Player;
class UI;
class CSprite;
class SoundMgr;

class coin:public IObject {
public:
	coin(Player *player,UI *ui,SoundMgr *sound,int x,int y);
	~coin();

	Player *player;
	UI *ui;
	CSprite *Coin;
	SoundMgr *sound;

	RECT cRect;

	int x,y;

	void Update(float eTime);
	void Render(D3DXMATRIX *pmat);
};