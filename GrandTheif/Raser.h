#pragma once
#include "IObject.h"

class CSprite;

class Raser : public IObject {
public:
	Raser();
	~Raser();

	CSprite *Raser_body;

	void Update(float eTime);
	void Render(D3DXMATRIX *pmat);
};