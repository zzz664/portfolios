#include "trap.h"
#include "Player.h"
#include "UI.h"
#include "CSprite.h"
#include "myFunction.h"

trap::trap(Player *player,UI *ui,int x,int y) {
	this->player = player;
	this->ui = ui;

	Trap = new CSprite("image/Item/trap.png");
	Trap->pos.x = x;
	Trap->pos.y = y;
}
trap::~trap() {
	delete Trap;
}
void trap::Update(float eTime) {
	RECT tempRect;
	tRect = Rect(Trap->pos.x,Trap->pos.y,Trap->pos.x+Trap->width,Trap->pos.y+Trap->height);
	if(MyKeyState('E') == 1 &&
		IntersectRect(&tempRect,&tRect,&player->rect)) {
			Trap = new CSprite("image/Item/dump.jpg");
			Trap->opacity = 0;
			ui->l_num--;
	}

}
void trap::Render(D3DXMATRIX *pmat) {
	IObject::Render(pmat);
	Trap->Render(&this->mat);
}