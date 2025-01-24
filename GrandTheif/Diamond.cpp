#include "Diamond.h"
#include "CSprite.h"
#include "Player.h"
#include "UI.h"
#include "myFunction.h"

Diamond::Diamond(Player *player,UI *ui,int x,int y) {
	this->player = player;
	this->ui = ui;
	diamond = new CSprite("image/Item/diamond.jpg");
	diamond->pos.x = x;
	diamond->pos.y = y;
	rect = Rect(207,332,295,422);
}
Diamond::~Diamond() {
	delete diamond;
}
void Diamond::Update(float eTime) {
	RECT tempRect;
	if(MyKeyState('E') == 1 && IntersectRect(&tempRect,&player->rect,&rect) && ui->c_num == 5) {
		diamond = new CSprite("image/Item/dump.jpg");
		diamond->opacity = 0;
		player->Stage_key = 1;
		ui->d_num++;
	}
}
void Diamond::Render(D3DXMATRIX *pmat) {
	IObject::Render(pmat);
	diamond->Render(&this->mat);
}