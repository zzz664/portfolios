#pragma once
#include "Stage2.h"

class CSprite;
class Player;
class Vision;
class Police;
class Raser_pointMgr;
class CCTV;
class cctvCom;
class raserCom;
class UI;
class coin;
class stage_key;
class trap;
class Safe;
class SoundMgr;

class Stage1 : public IScene {
public:
	Stage1();
	~Stage1();

	Player *player;
	CCTV *cctv;
	Police *police;
	CSprite *stage;
	Vision *vision;
	Raser_pointMgr *raserMgr;
	cctvCom *cctvcom;
	raserCom *rasercom;
	UI *ui;
	coin *Coin[5];
	trap *Trap;
	stage_key *s_Key;
	Safe *safe;
	SoundMgr *sound;

	int sk;
	int ps;

	void Update(float eTime);
	void Render();
};