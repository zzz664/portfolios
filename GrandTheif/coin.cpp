#include "coin.h"
#include "Player.h"
#include "UI.h"
#include "CSprite.h"
#include "SoundMgr.h"
#include "myFunction.h"

coin::coin(Player *player,UI *ui,SoundMgr *sound,int x,int y) {
	this->player = player;
	this->ui = ui;
	this->sound = sound;

	Coin = new CSprite("image/Item/coin.png");
	Coin->pos.x = x;
	Coin->pos.y = y;
}
coin::~coin() {
	delete Coin;
}
void coin::Update(float eTime) {
	RECT tempRect;
	cRect = Rect(Coin->pos.x,Coin->pos.y,Coin->pos.x+Coin->width,Coin->pos.y+Coin->height);
	if(MyKeyState('E') == 1 &&
		IntersectRect(&tempRect,&cRect,&player->rect)) {
			sound->Play(PICK_COIN_BGM);
			Coin = new CSprite("image/Item/dump.jpg");
			Coin->opacity = 0;
			ui->c_num++;
	}

}
void coin::Render(D3DXMATRIX *pmat) {
	IObject::Render(pmat);
	Coin->Render(&this->mat);
}