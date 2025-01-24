#pragma once
#include "IScene.h"

class CSprite;

class EndScene : public IScene {
public:
	EndScene(int wl);
	~EndScene();

	CSprite *lose;
	CSprite *win;

	int wl;

	void Update(float eTime);
	void Render();
};