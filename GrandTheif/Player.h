#pragma once
#include "IObject.h"

class CAnimation;
class CSprite;
class SoundMgr;
class UI;

class Player : public IObject {
public:
	Player(int Stage_arr[][100],UI *ui,SoundMgr *sound,int x,int y);
	~Player();

	CSprite *pSprite;
	CSprite *safe;
	CAnimation *pAni;
	CAnimation *uAni;
	CAnimation *dAni;
	SoundMgr *sound;
	UI *ui;

	RECT save_pos;

	bool walking;

	int Stage_arr[76][100];
	int Key, Stage_key;
	int px_mid,py_mid;
	int left_c,right_c,top_c,bottom_c;
	int die;
	int box,sf;
	int Uw,Dw;
	int change;

	void Collision();
	void Door_Open();
	void Stage_Open();

	void Update(float eTime);
	void Render(D3DXMATRIX *pmat);
};