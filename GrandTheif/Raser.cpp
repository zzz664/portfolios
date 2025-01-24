#include "Raser.h"
#include "CSprite.h"

Raser::Raser() {
	Raser_body = new CSprite("image/Obstacle/Raser/Raser_body.png");
}
Raser::~Raser() {
	delete Raser_body;
}
void Raser::Update(float eTime) {
}
void Raser::Render(D3DXMATRIX *pmat) {
	IObject::Render(pmat);
	Raser_body->Render(&this->mat);
}