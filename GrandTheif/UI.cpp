#include "UI.h"
#include "CAnimation.h"
#include "Def.h"
#include "SoundMgr.h"

UI::UI(SoundMgr *sound) {
	this->sound = sound;
	coin[0] = new CSprite("image/UI/Coin/coin1.png");
	coin[1] = new CSprite("image/UI/Coin/coin2.png");
	coin[2] = new CSprite("image/UI/Coin/coin3.png");
	coin[3] = new CSprite("image/UI/Coin/coin4.png");
	coin[4] = new CSprite("image/UI/Coin/coin5.png");

	life[0] = new CSprite("image/UI/Life/life1.png");
	life[1] = new CSprite("image/UI/Life/life2.png");
	life[2] = new CSprite("image/UI/Life/life3.png");

	key[0] = new CSprite("image/UI/Key/key1.png");
	key[1] = new CSprite("image/UI/Key/key2.png");
	key[2] = new CSprite("image/UI/Key/key3.png");
	stage_key = new CSprite("image/UI/Key/stage_key.png");
	diamond = new CSprite("image/UI/Dia/diamond.jpg");

	Siren = new CAnimation(2,3.0f);
	Siren->PushFrame("image/UI/Siren/Siren1.png",0);
	Siren->PushFrame("image/UI/Siren/Siren2.png",1);

	for(int i = 0;i < 3;i++) {
		life[i]->pos = D3DXVECTOR2(WIDTH/2-100,20);
		key[i]->pos = D3DXVECTOR2(WIDTH/2+20,20);
	}
	for(int i = 0;i < 5;i++) {
		coin[i]->pos = D3DXVECTOR2(WIDTH/2+20,100);
	}
	stage_key->pos = D3DXVECTOR2(WIDTH/2+20,60);
	Siren->scale = D3DXVECTOR2(2,2);
	c_num = 0;
	k_num = 0;
	sk_num = 0;
	d_num = 0;
	l_num = 3;
	s_on = 0;
}
UI::~UI() {
	for(int i = 0;i < 3;i++) {
		delete life[i];
		delete key[i];
	}
	for(int i = 0;i < 5;i++) {
		delete coin[i];
	}
	delete stage_key;
	delete diamond;
	delete Siren;
}
void UI::Update(float eTime) {
	sound->Update();
	Siren->Update(eTime);
	for(int i = 0;i < 3;i++) {
		life[i]->pos = D3DXVECTOR2(10,700);
		key[i]->pos = D3DXVECTOR2(WIDTH-130,680);
	}
	for(int i = 0;i < 5;i++) {
		coin[i]->pos = D3DXVECTOR2(WIDTH-100,720);
	}
	stage_key->pos = D3DXVECTOR2(WIDTH-130,640);
	diamond->pos = D3DXVECTOR2(WIDTH-130,640);
	Siren->pos = D3DXVECTOR2(WIDTH/2,HEIGHT-80);
	if(s_on)
		sound->Playis(SIREN_BGM);
	else
		sound->Stop(SIREN_BGM);
}
void UI::Render(D3DXMATRIX *pmat) {
	if(c_num != 0) coin[c_num-1]->Render(&this->mat);
	if(k_num != 0) key[k_num-1]->Render(&this->mat);
	if(sk_num != 0) stage_key->Render(&this->mat);
	if(d_num != 0) diamond->Render(&this->mat);
	life[l_num-1]->Render(&this->mat);
	if(s_on) Siren->Render(NULL);
}