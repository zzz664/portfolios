#include "Vision.h"
#include "Player.h"
#include "CSprite.h"

Vision::Vision(Player *player) {
	this->player = player;
	vision = new CSprite("image/Player/vision/vision.png");
	vision->pos.x = (this->player->pos.x + this->player->pSprite->width/2) - 1000;
	vision->pos.y = (this->player->pos.y + this->player->pSprite->height/2) - 760;
}
Vision::~Vision() {
	delete vision;
}
void Vision::Update(float eTime) {
	vision->pos.x = (player->pos.x + player->pSprite->width/2) - 1000;
	vision->pos.y = (player->pos.y + player->pSprite->height/2) - 760;
}
void Vision::Render(D3DXMATRIX *pmat) {
	IObject::Render(pmat);
	vision->Render(&this->mat);
}