#include "stage_key.h"
#include "Player.h"
#include "UI.h"
#include "CSprite.h"
#include "myFunction.h"

stage_key::stage_key(Player *player,UI *ui,int x,int y) {
	this->player = player;
	this->ui = ui;

	Stage_key = new CSprite("image/Item/stage_key.png");
	Stage_key->pos.x = x;
	Stage_key->pos.y = y;
}
stage_key::~stage_key() {
	delete Stage_key;
}
void stage_key::Update(float eTime) {
	RECT tempRect;
	skRect = Rect(Stage_key->pos.x,Stage_key->pos.y,Stage_key->pos.x+Stage_key->width,Stage_key->pos.y+Stage_key->height);
	if(MyKeyState('E') == 1 &&
		IntersectRect(&tempRect,&skRect,&player->rect)) {
			Stage_key = new CSprite("image/Item/dump.jpg");
			Stage_key->opacity = 0;
			ui->sk_num++;
			player->Stage_key = 1;
	}
}
void stage_key::Render(D3DXMATRIX *pmat) {
	IObject::Render(pmat);
	Stage_key->Render(&this->mat);
}