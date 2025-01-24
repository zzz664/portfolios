#include "Raser_point.h"
#include "Raser.h"
#include "CSprite.h"
#include "myFunction.h"

Raser_point::Raser_point(Raser *raser) {
	pRaser = new CSprite("image/Obstacle/Raser/Raser.png");
	this->raser = raser;
	isErase = false;
	pRaser->pos.x = this->raser->Raser_body->pos.x + (raser->Raser_body->width/2-pRaser->width/2);
	pRaser->pos.y = this->raser->Raser_body->pos.y + (raser->Raser_body->width/2-pRaser->width/2);
	pRaser->rotationCenter = pRaser->GetCenter();
	w = cos(this->raser->Raser_body->rot);
	h = sin(this->raser->Raser_body->rot);
	range = 0;
	pRaser->blue = 200;
	pRaser->scalingCenter = D3DXVECTOR2(pRaser->width/2,pRaser->height);
}
Raser_point::~Raser_point() {
	delete pRaser;
}
void Raser_point::Update(float eTime) {
	pRaser->Update(eTime);
	range += 15*eTime;
	pRaser->scale.y += 0.03f;
	pRaser->rot = atan2(h,w);
	pRaser->pos.x += range*sin(raser->Raser_body->rot);
	pRaser->pos.y -= range*cos(raser->Raser_body->rot);
}
void Raser_point::Render(D3DXMATRIX *pmat) {
	IObject::Render(pmat);
	pRaser->Render(&this->mat);
}