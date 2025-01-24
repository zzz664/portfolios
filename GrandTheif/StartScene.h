#pragma once
#include "IScene.h"

class CSprite;
class SoundMgr;

class StartScene : public IScene {
public:
	StartScene();
	~StartScene();

	CSprite *bg;
	CSprite *start;
	CSprite *easy;
	CSprite *hard;
	CSprite *maker;
	CSprite *help;

	CSprite *mup;
	CSprite *hup;

	SoundMgr *sound;

	bool start_on,easy_on,hard_on,help_on,maker_on,m_up,h_up;

	void Update(float eTime);
	void Render();
};