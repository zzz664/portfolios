#include "key.h"
#include "Player.h"
#include "UI.h"
#include "CSprite.h"
#include "myFunction.h"

key::key(Player *player,UI *ui,int x,int y) {
	this->player = player;
	this->ui = ui;

	Key = new CSprite("image/Item/key.png");
	Key->pos.x = x;
	Key->pos.y = y;
}
key::~key() {
	delete Key;
}
void key::Update(float eTime) {
	RECT tempRect;
	kRect = Rect(Key->pos.x,Key->pos.y,Key->pos.x+Key->width,Key->pos.y+Key->height);
	if(MyKeyState('E') == 1 &&
		IntersectRect(&tempRect,&kRect,&player->rect)) {
			Key = new CSprite("image/Item/dump.jpg");
			Key->opacity = 0;
			player->Key++;
			ui->k_num++;
	}

}
void key::Render(D3DXMATRIX *pmat) {
	IObject::Render(pmat);
	Key->Render(&this->mat);
}