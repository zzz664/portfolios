#pragma once
#include "IObject.h"

class CSprite;
class CAnimation;
class SoundMgr;

class UI:public IObject {
public:
	UI(SoundMgr *sound);
	~UI();

	CSprite *coin[5];
	CSprite *life[3];
	CSprite *key[3];
	CSprite *stage_key;
	CSprite *diamond;
	CAnimation *Siren;
	SoundMgr *sound;

	int c_num,l_num,k_num,sk_num,d_num;
	int s_on;

	void Update(float eTime);
	void Render(D3DXMATRIX *pmat);
};