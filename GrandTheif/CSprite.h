#pragma once
#include "IObject.h"
typedef LPDIRECT3DTEXTURE9 LPTEXT;

class CSprite : public IObject
{
public:
	CSprite();
	CSprite(char *path);
	~CSprite();

	LPTEXT pTexture;
	int width, height;
	int opacity,red,green,blue;
	bool blendMode;
	RECT rect;

	void Update(float eTime);
	void Render(D3DXMATRIX *pmat);
	D3DXVECTOR2 GetCenter();
	D3DXVECTOR2 GetCenterToClient();
};