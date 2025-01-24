#pragma once
#include "CSprite.h"

class CAnimation : public IObject
{
public:
	CAnimation();
	CAnimation(int maxFrame,float speed);
	~CAnimation();

	int maxFrame;
	float nowFrame;
	float speed;
	CSprite **frame;

	void PushFrame(char *path,int prior);
	void Update(float eTime);
	void Render(D3DXMATRIX *pmat);
};