#pragma once
#include "IObject.h"

class CSprite;
class CCTV;
class Player;
class SoundMgr;

class cctvCom:public IObject {
public:
	cctvCom(CCTV *cctv,Player *player,SoundMgr *sound,int x,int y,int direction);
	~cctvCom();

	CSprite *com[2];
	CCTV *cctv;
	Player *player;
	SoundMgr *sound;

	int on;
	int x, y, direction;
	int ps;
	double cl;
	RECT cRect[4]; //0 = ╩С 1 = го 2 = аб 3 = ©Л

	void Update(float eTime);
	void Render(D3DXMATRIX *pmat);
};