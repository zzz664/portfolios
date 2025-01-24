#pragma once
#include "Stage4.h"

class CSprite;
class Player;
class UI;
class Raser_pointMgr;
class raserCom;
class CCTV;
class cctvCom;
class Vision;
class coin;
class key;
class stage_key;
class trap;
class Police;
class Safe;
class SoundMgr;

class Stage3 : public IScene {
public:
	Stage3();
	~Stage3();

	CSprite *stage;
	Player *player;
	UI *ui;
	Raser_pointMgr *raser[2];
	raserCom *rasercom[2];
	CCTV *cctv[3];
	cctvCom *cctvcom[3];
	Vision *vision;
	coin *Coin[5];
	key *Key[3];
	trap *Trap[2];
	stage_key *s_Key;
	Police *police[3];
	Safe *safe;
	SoundMgr *sound;

	int ps;

	void Update(float eTime);
	void Render();
};