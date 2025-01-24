#pragma once
#include "IObject.h"

class Player;
class CSprite;

class CCTV : public IObject {
public:
	CCTV(Player *player,int x,int y,int direction);
	~CCTV();
	
	Player *player;
	CSprite *excl;
	CSprite *cctv;
	CSprite *vision;

	RECT Check;

	int check;
	int direction;
	int ch,police_ch;
	bool on;
	double cl;

	void Update(float eTime);
	void Render(D3DXMATRIX *pmat);
};