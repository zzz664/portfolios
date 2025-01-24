#include "raserCom.h"
#include "CSprite.h"
#include "Raser_pointMgr.h"
#include "Player.h"
#include "myFunction.h"
#include "SoundMgr.h"
#include <time.h>

raserCom::raserCom(Raser_pointMgr *raserPoint,SoundMgr *sound,float angle,Player *player,int x,int y,int direction) {
	com[0] = new CSprite("image/Obstacle/Computer/computer_off.png");
	com[1] = new CSprite("image/Obstacle/Computer/computer_on.png");

	this->raserPoint = raserPoint;
	this->player = player;
	this->sound = sound;
	
	this->x = x;
	this->y = y;
	this->direction = direction; // 0 = ╩С 1 = го 2 = аб 3 = ©Л  3.14f = ╩С 0.f = го -1.57f = аб 1.57f = ©Л
	
	for(int i = 0;i < 2;i++) {
		com[i]->pos.x = this->x;
		com[i]->pos.y = this->y;
		com[i]->rotationCenter = com[i]->GetCenter();
	}

	on = 0;
	a_rotation = 0;
	ps = 0;
	rRot = angle;
	cl = clock();
}
raserCom::~raserCom() {
	for(int i = 0;i < 2;i++) delete[] com[i];
}
void raserCom::Update(float eTime) {
	RECT tempRect;

	cRect[0] = Rect(com[0]->pos.x,com[0]->pos.y-40,com[0]->pos.x+40,com[0]->pos.y);
	cRect[1] = Rect(com[0]->pos.x,com[0]->pos.y+40,com[0]->pos.x+40,com[0]->pos.y+80);
	cRect[2] = Rect(com[0]->pos.x+40,com[0]->pos.y,com[0]->pos.x+80,com[0]->pos.y+40);
	cRect[3] = Rect(com[0]->pos.x-40,com[0]->pos.y,com[0]->pos.x,com[0]->pos.y+40);

	if(direction == 0) { 
		rect = cRect[0];
		for(int i = 0;i < 2;i++)
			com[i]->rot = 3.14f;
	}else if(direction == 1) {
		rect = cRect[1];
		for(int i = 0;i < 2;i++)
			com[i]->rot = 0.f;
	}else if(direction == 2) {
		rect = cRect[2];
		for(int i = 0;i < 2;i++)
			com[i]->rot = -1.57f;
	}else if(direction == 3) {
		rect = cRect[3];
		for(int i = 0;i < 2;i++)
			com[i]->rot = 1.57f;
	}

	if((IntersectRect(&tempRect,&rect,&player->rect) && MyKeyState('E') == 1) || a_rotation) {
		if(ps == 0) {
			sound->Playis(COM_BGM);
			ps = 1;
		}
		on = 1;
		a_rotation = 1;
		if(raserPoint->raser->Raser_body->rot <= rRot+0.785)
			raserPoint->raser->Raser_body->rot += eTime/3;
		else {
			a_rotation = 0;
			ps = 0;
		}
	}
	if(clock() - cl > 1500) {
		on = 0;
		cl = clock();
	}
}
void raserCom::Render(D3DXMATRIX *pmat) {
	if(on) com[1]->Render(&this->mat);
	else com[0]->Render(&this->mat);
}