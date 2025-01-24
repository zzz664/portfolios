#include "CCTV.h"
#include "Player.h"
#include "CSprite.h"
#include "myFunction.h"
#include <time.h>

CCTV::CCTV(Player *player,int x,int y,int direction) {
	this->player = player;
	this->direction = direction;

	excl = new CSprite("image/UI/excl/excl.png");
	cctv = new CSprite("image/Obstacle/CCTV/cctv.png");
	vision = new CSprite("image/Obstacle/CCTV/vision.png");

	cctv->pos.x = x;
	cctv->pos.y = y;
	cctv->scalingCenter = cctv->GetCenter();

	check  = ch = police_ch = 0;
	on = 1;
	cl = clock();
	if(this->direction == 1) {
		cctv->scale = D3DXVECTOR2(1,1);
		vision->scale = D3DXVECTOR2(-1,1);
		Check = Rect(cctv->pos.x-160,cctv->pos.y,cctv->pos.x,cctv->pos.y+80);
		vision->pos = D3DXVECTOR2(Check.right,Check.top);
	} else if(this->direction == 2) {
		cctv->scale = D3DXVECTOR2(-1,1);
		vision->scale = D3DXVECTOR2(1,1);
		Check = Rect(cctv->pos.x+cctv->width,cctv->pos.y,cctv->pos.x+cctv->width+160,cctv->pos.y+80);
		vision->pos = D3DXVECTOR2(Check.left,Check.top);
	}
}
CCTV::~CCTV() {
	delete excl;
	delete cctv;
	delete vision;
}
void CCTV::Update(float eTime) {
	RECT tmp;
	if(on) {
		excl->pos = D3DXVECTOR2(player->pos.x-6,player->pos.y-excl->height);
		if(IntersectRect(&tmp,&player->rect,&Check)) {
			if(clock() - cl > 1000) {
				ch = 1;
				police_ch = 1;
			}
		} else {
			ch = 0;
			cl = clock();
		}
	}
}
void CCTV::Render(D3DXMATRIX *pmat) {
	IObject::Render(pmat);
	if(ch)
		excl->Render(&this->mat);
	cctv->Render(&this->mat);
	if(on)
		vision->Render(&this->mat);
}