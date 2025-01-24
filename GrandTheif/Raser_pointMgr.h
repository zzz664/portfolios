#pragma once
#include "IObject.h"
#include "Raser_point.h"
#include "Raser.h"
#include "CSprite.h"
#include <list>

using namespace std;
typedef list<Raser_point*> RASERLIST;

class Player;
class UI;
class SoundMgr;

class Raser_pointMgr : public IObject {
public:
	Raser_pointMgr(UI *ui,Player *player,SoundMgr *sound,int x,int y,float angle,RECT Stage_Col[],int stage_max,int stage);
	~Raser_pointMgr();

	Raser *raser;
	Raser_point *raser_point;
	Player *player;
	UI *ui;
	SoundMgr *sound;

	RECT Stage1[36];
	RECT Stage2[53];
	RECT Stage3[43];
	RECT Stage4[25];

	RASERLIST raserList;

	int x,y;
	int stage;
	int Stage_Max;
	float angle;
	double cl;

	void PushRaser(Raser_point *r);
	void Update(float eTime);
	void Render(D3DXMATRIX *pmat);
};