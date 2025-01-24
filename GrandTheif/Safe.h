#pragma once
#include "IObject.h"

class CSprite;

class Safe:public IObject {
public:
	Safe(int x,int y);
	~Safe();

	CSprite *safe;
	RECT sRect;

	void Update(float eTime);
	void Render(D3DXMATRIX *pmat);
};