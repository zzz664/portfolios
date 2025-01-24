#include "Raser_pointMgr.h"
#include "SoundMgr.h"
#include "Player.h"
#include "UI.h"
#include "myFunction.h"
#include "Def.h"
#include <time.h>

Raser_pointMgr::Raser_pointMgr(UI *ui,Player *player,SoundMgr *sound,int x,int y,float angle,RECT Stage_Col[],int stage_max,int stage) {

	raser = new Raser();
	raser->Raser_body->pos.x = x;
	raser->Raser_body->pos.y = y;
	raser->Raser_body->rot = angle;

	this->player = player;
	this->ui = ui;
	this->sound = sound;

	this->raser->Raser_body->rotationCenter = raser->Raser_body->GetCenter();
	this->Stage_Max = stage_max;
	this->stage = stage;
	cl = clock();
	if(this->stage == 1)
		for(int i = 0;i < Stage_Max;i++) Stage1[i] = Stage_Col[i];
	else if(this->stage == 2)
		for(int i = 0;i < Stage_Max;i++) Stage2[i] = Stage_Col[i];
	else if(this->stage == 3)
		for(int i = 0;i < Stage_Max;i++) Stage3[i] = Stage_Col[i];
	else if(this->stage == 4)
		for(int i = 0;i < Stage_Max;i++) Stage4[i] = Stage_Col[i];
}
Raser_pointMgr::~Raser_pointMgr() {
	RASERLIST::iterator iter;
	for(iter = raserList.begin();iter != raserList.end();iter++)
		delete (*iter);
	raserList.clear();
}
void Raser_pointMgr::PushRaser(Raser_point *r) {
	raserList.push_back(r);
}
void Raser_pointMgr::Update(float eTime) {
	PushRaser(new Raser_point(raser));

	RASERLIST::iterator iter;
	raser->Update(eTime);

	RECT tmpRect;
	for(iter = raserList.begin();iter != raserList.end();iter++) {
		(*iter)->Update(eTime);
		(*iter)->rect = Rect((*iter)->pRaser->pos.x,(*iter)->pRaser->pos.y,
			(*iter)->pRaser->pos.x+(*iter)->pRaser->width,(*iter)->pRaser->pos.y+(*iter)->pRaser->height*(*iter)->scale.y);
		if((*iter)->pRaser->pos.x < 0 || (*iter)->pRaser->pos.y < 0 || (*iter)->pRaser->pos.x > 1000 || (*iter)->pRaser->pos.y > 760)
			(*iter)->isErase = true;

		for(int i = 0;i < Stage_Max;i++) {
			if(IntersectRect(&tmpRect,&Stage1[i],&(*iter)->rect) && stage == 1) { //스테이지1 일때의 충돌체크
				if(((*iter)->pRaser->pos.x+(*iter)->pRaser->width >= Stage1[i].left ||
					(*iter)->pRaser->pos.x <= Stage1[i].right) && (*iter)->rect.top < Stage1[i].bottom) {
						(*iter)->isErase = true;
				} else if(((*iter)->pRaser->pos.x+(*iter)->pRaser->width >= Stage1[i].left ||
					(*iter)->pRaser->pos.x <= Stage1[i].right) && (*iter)->rect.bottom > Stage1[i].top) {
						(*iter)->isErase = true;
				} if(((*iter)->pRaser->pos.y+(*iter)->pRaser->height >= Stage1[i].top ||
					(*iter)->pRaser->pos.y <= Stage1[i].bottom) && (*iter)->rect.left < Stage1[i].right) {
						(*iter)->isErase = true;
				} else if(((*iter)->pRaser->pos.y+(*iter)->pRaser->height >= Stage1[i].top ||
					(*iter)->pRaser->pos.y <= Stage1[i].bottom) && (*iter)->rect.right > Stage1[i].left) {
						(*iter)->isErase = true;
				}
			} 
			if(IntersectRect(&tmpRect,&Stage2[i],&(*iter)->rect) && stage == 2) { //스테이지2 일때의 충돌체크
				if(((*iter)->pRaser->pos.x+(*iter)->pRaser->width >= Stage2[i].left || (*iter)->pRaser->pos.x <= Stage2[i].right) && (*iter)->rect.top < Stage2[i].bottom)
					(*iter)->isErase = true;
				else if(((*iter)->pRaser->pos.x+(*iter)->pRaser->width >= Stage2[i].left || (*iter)->pRaser->pos.x <= Stage2[i].right) && (*iter)->rect.bottom > Stage2[i].top)
					(*iter)->isErase = true;
				if(((*iter)->pRaser->pos.y+(*iter)->pRaser->height >= Stage2[i].top || (*iter)->pRaser->pos.y <= Stage2[i].bottom) && (*iter)->rect.left < Stage2[i].right)
					(*iter)->isErase = true;
				else if(((*iter)->pRaser->pos.y+(*iter)->pRaser->height >= Stage2[i].top || (*iter)->pRaser->pos.y <= Stage2[i].bottom) && (*iter)->rect.right > Stage2[i].left)
					(*iter)->isErase = true;
			} 
			if(IntersectRect(&tmpRect,&Stage3[i],&(*iter)->rect) && stage == 3) {//스테이지3 일때의 충돌체크
				if(((*iter)->pRaser->pos.x+(*iter)->pRaser->width >= Stage3[i].left || (*iter)->pRaser->pos.x <= Stage3[i].right) && (*iter)->rect.top < Stage3[i].bottom)
					(*iter)->isErase = true;
				else if(((*iter)->pRaser->pos.x+(*iter)->pRaser->width >= Stage3[i].left || (*iter)->pRaser->pos.x <= Stage3[i].right) && (*iter)->rect.bottom > Stage3[i].top)
					(*iter)->isErase = true;
				if(((*iter)->pRaser->pos.y+(*iter)->pRaser->height >= Stage3[i].top || (*iter)->pRaser->pos.y <= Stage3[i].bottom) && (*iter)->rect.left < Stage3[i].right)
					(*iter)->isErase = true;
				else if(((*iter)->pRaser->pos.y+(*iter)->pRaser->height >= Stage3[i].top || (*iter)->pRaser->pos.y <= Stage3[i].bottom) && (*iter)->rect.right > Stage3[i].left)
					(*iter)->isErase = true;
			} 
			if(IntersectRect(&tmpRect,&Stage4[i],&(*iter)->rect) && stage == 4) {//스테이지4 일때의 충돌체크
				if(((*iter)->pRaser->pos.x+(*iter)->pRaser->width >= Stage4[i].left || (*iter)->pRaser->pos.x <= Stage4[i].right) && (*iter)->rect.top < Stage4[i].bottom)
					(*iter)->isErase = true;
				else if(((*iter)->pRaser->pos.x+(*iter)->pRaser->width >= Stage4[i].left || (*iter)->pRaser->pos.x <= Stage4[i].right) && (*iter)->rect.bottom > Stage4[i].top)
					(*iter)->isErase = true;
				if(((*iter)->pRaser->pos.y+(*iter)->pRaser->height >= Stage4[i].top || (*iter)->pRaser->pos.y <= Stage4[i].bottom) && (*iter)->rect.left < Stage4[i].right)
					(*iter)->isErase = true;
				else if(((*iter)->pRaser->pos.y+(*iter)->pRaser->height >= Stage4[i].top || (*iter)->pRaser->pos.y <= Stage4[i].bottom) && (*iter)->rect.right > Stage4[i].left)
					(*iter)->isErase = true;
			}
			if(IntersectRect(&tmpRect,&(*iter)->rect,&player->rect)) {
				(*iter)->isErase = true;
				if(clock() - cl > 1000) {
					if(ui->l_num != 0)
						ui->l_num--;
					cl = clock();
				}
			}
		}
		if((*iter)->isErase) {
			delete (*iter);
			iter = raserList.erase(iter);
			if(iter == raserList.end())
				break;
		}
	}
}
void Raser_pointMgr::Render(D3DXMATRIX *pmat) {
	IObject::Render(pmat);
	RASERLIST::iterator iter;
	for(iter = raserList.begin();iter != raserList.end();iter++) {
		(*iter)->Render(&this->mat);
	}
	raser->Render(&this->mat);
}