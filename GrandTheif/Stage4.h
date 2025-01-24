#pragma once
#include "StartScene.h"

class CSprite;
class Player;
class UI;
class Vision;
class Raser_pointMgr;
class raserCom;
class CCTV;
class cctvCom;
class coin;
class key;
class trap;
class Diamond;
class Police;
class Safe;
class SoundMgr;

class Stage4 : public IScene {
public:
	Stage4();
	~Stage4();

	CSprite *stage;
	CSprite *fence;
	CSprite *diaon;
	Player *player;
	UI *ui;
	Vision *vision;
	Raser_pointMgr *raser[4];
	raserCom *rasercom[4];
	CCTV *cctv;
	cctvCom *cctvcom;
	coin *Coin[5];
	trap *Trap;
	Police *police;
	Safe *safe;
	Diamond *dia;
	SoundMgr *sound;

	int ps;

	void Update(float eTime);
	void Render();
};