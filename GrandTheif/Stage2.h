#pragma once
#include "Stage3.h"

class CSprite;
class Player;
class Raser_pointMgr;
class CCTV;
class cctvCom;
class raserCom;
class UI;
class Vision;
class SoundMgr;
class coin;
class key;
class stage_key;
class trap;
class Police;
class Safe;

class Stage2 : public IScene{
public:
	Stage2();
	~Stage2();

	CSprite *stage;
	Player *player;
	Police *police[3];
	Raser_pointMgr *raser[4];
	CCTV *cctv[4];
	cctvCom *cctvcom[3];
	raserCom *rasercom[4];
	UI *ui;
	Vision *vision;
	SoundMgr *sound;
	coin *Coin[5];
	key *Key[3];
	stage_key *s_Key;
	trap *Trap[2];
	Safe *safe;

	int ps;

	void Update(float eTime);
	void Render();
};