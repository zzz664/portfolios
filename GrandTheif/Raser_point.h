#pragma once
#include "IObject.h"

class CSprite;
class Raser;

class Raser_point : public IObject {
public:
	Raser_point(Raser *raser);
	~Raser_point();

	CSprite *pRaser;
	Raser *raser;

	float w,h;
	float range;

	bool isErase;

	void Update(float eTime);
	void Render(D3DXMATRIX *pmat);
};