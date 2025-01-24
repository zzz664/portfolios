#pragma once
#include <d3dx9.h>

class IObject
{
public:
	IObject();
	virtual ~IObject();

	D3DXMATRIX mat;
	D3DXVECTOR2 pos,scale,rotationCenter,scalingCenter;
	float rot;

	RECT rect;

	virtual void Update(float eTime) = 0;
	virtual void Render(D3DXMATRIX *pmat);
};