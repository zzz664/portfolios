#include "Safe.h"
#include "CSprite.h"
#include "myFunction.h"

Safe::Safe(int x,int y) {
	safe = new CSprite("image/Safe/safe.png");
	safe->pos.x = x;
	safe->pos.y = y;
	sRect = Rect(safe->pos.x,safe->pos.y,safe->pos.x+safe->width,safe->pos.y+safe->height);
}
Safe::~Safe() {
	delete safe;
}
void Safe::Update(float eTime) {}
void Safe::Render(D3DXMATRIX *pmat) {
	IObject::Render(pmat);
	safe->Render(&this->mat);
}