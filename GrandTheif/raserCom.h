#pragma once
#include "IObject.h"

class CSprite;
class Raser_pointMgr;
class Player;
class SoundMgr;

class raserCom:public IObject {
public:
	raserCom(Raser_pointMgr *raserPoint,SoundMgr *sound,float angle,Player *player,int x,int y,int direction);
	~raserCom();

	CSprite *com[2];
	Raser_pointMgr *raserPoint;
	Player *player;
	SoundMgr *sound;

	int on;
	int a_rotation;
	int x, y, direction;
	int ps;
	float rRot;
	double cl;
	RECT cRect[4]; //0 = ╩С 1 = го 2 = аб 3 = ©Л

	void Update(float eTime);
	void Render(D3DXMATRIX *pmat);
};