#include "Player.h"
#include "CAnimation.h"
#include "myFunction.h"
#include "StartScene.h"
#include "SoundMgr.h"
#include "UI.h"

Player::Player(int Stage_arr[][100],UI *ui,SoundMgr *sound,int x,int y) {
	this->sound = sound;
	this->ui = ui;
	pSprite = new CSprite("image/Player/player.png");
	safe = new CSprite("image/Player/safe.png");
	pAni = new CAnimation(2,7.0f);
	uAni = new CAnimation(2,7.0f);
	dAni = new CAnimation(2,7.0f);

	pAni->PushFrame("image/Player/pAni/pAni1.png",0);
	pAni->PushFrame("image/Player/pAni/pAni2.png",1);
	uAni->PushFrame("Image/Player/pAni/uAni1.png",0);
	uAni->PushFrame("image/Player/pAni/uAni2.png",1);
	dAni->PushFrame("image/Player/pAni/dAni1.png",0);
	dAni->PushFrame("image/Player/pAni/dAni2.png",1);

	pos.x = x;
	pos.y = y;

	box = sf = 0;

	Uw = Dw = 0;

	Key = 0; Stage_key = 0;
	left_c = right_c = top_c = bottom_c = FALSE;

	for(int i = 0;i < 76;i++) {
		for(int j = 0;j < 100;j++) {
			this->Stage_arr[i][j] = Stage_arr[i][j];
		}
	}
	scalingCenter = pSprite->GetCenter();
	change = 0;
	die = 0;
}
Player::~Player() {
	delete pSprite;
	delete pAni;
	delete uAni;
	delete dAni;
	delete safe;
}
void Player::Update(float eTime) {
	pAni->Update(eTime);
	uAni->Update(eTime);
	dAni->Update(eTime);
	safe->Update(eTime);
	rect = Rect(pos.x,pos.y,pos.x+pSprite->width,pos.y+pSprite->height);
	px_mid = rect.left + pSprite->width/2;
	py_mid = rect.top + pSprite->height/2;

	walking = FALSE;
	Uw = Dw = 0;
	if((MyKeyState(VK_LEFT) > 0) && (left_c == FALSE)) {
		walking = TRUE;
		Uw = Dw = 0;
		scale = D3DXVECTOR2(-1,1);
		pos.x -= 150*eTime;
	}
	if((MyKeyState(VK_RIGHT) > 0) && (right_c == FALSE)) {
		walking = TRUE;
		Uw = Dw = 0;
		scale = D3DXVECTOR2(1,1);
		pos.x += 150*eTime;
	}
	if((MyKeyState(VK_UP) > 0) && (top_c == FALSE)) {
		walking = FALSE;
		Uw = 1;
		Dw = 0;
		pos.y -= 150*eTime;
	}
	if((MyKeyState(VK_DOWN) > 0 && (bottom_c == FALSE))) {
		walking = FALSE;
		Uw = 0;
		Dw = 1;
		pos.y += 150*eTime;
	}

	Collision();
	Door_Open();
	Stage_Open();
}
void Player::Render(D3DXMATRIX *pmat) {
	IObject::Render(pmat);
	if(walking)
		pAni->Render(&this->mat);
	else if(Uw)
		uAni->Render(&this->mat);
	else if(Dw)
		dAni->Render(&this->mat);
	else if(box)
		safe->Render(&this->mat);
	else
		pSprite->Render(&this->mat);
}
void Player::Collision() {
	save_pos = Rect(pos.x,pos.y,pos.x+pSprite->width,pos.y+pSprite->height);

	if ((Stage_arr[save_pos.top / 10][(save_pos.left) / 10] >= 5 && Stage_arr[save_pos.bottom / 10][(save_pos.left) / 10] >= 5))
		left_c = FALSE;
	if (Stage_arr[save_pos.top / 10][(save_pos.right) / 10] >= 5 && Stage_arr[save_pos.bottom / 10][(save_pos.right) / 10] >= 5)
		right_c = FALSE;
	if (Stage_arr[(save_pos.top-3) / 10][(save_pos.left) / 10] >= 5 && Stage_arr[(save_pos.top-3) / 10][(save_pos.right) / 10] >= 5)
		top_c = FALSE;
	if (Stage_arr[(save_pos.bottom+3) / 10][save_pos.left / 10] >= 5 && Stage_arr[(save_pos.bottom+3) / 10][save_pos.right / 10] >= 5)
		bottom_c = FALSE;

	if ((Stage_arr[save_pos.top / 10][(save_pos.left) / 10] < 5 ||
		Stage_arr[save_pos.bottom / 10][(save_pos.left) / 10] < 5) && MyKeyState(VK_LEFT) > 0) {
			pos.x = rect.left;
			left_c = TRUE;
	} else if (Stage_arr[save_pos.top / 10][(save_pos.right) / 10] < 5 ||
		Stage_arr[save_pos.bottom / 10][(save_pos.right) / 10] < 5 && MyKeyState(VK_RIGHT) > 0) {
			pos.x = rect.left;
			right_c = TRUE;
	}

	save_pos = Rect(pos.x,pos.y,pos.x+pSprite->width,pos.y+pSprite->height);

	if ((Stage_arr[(save_pos.top) / 10][(save_pos.left) / 10] < 5 ||
		Stage_arr[(save_pos.top) / 10][(save_pos.right) / 10] < 5) && MyKeyState(VK_UP) > 0) {
			pos.y = rect.top;
			top_c = TRUE;
	}
	else if (Stage_arr[(save_pos.bottom) / 10][(save_pos.left) / 10] < 5 ||
		Stage_arr[(save_pos.bottom) / 10][(save_pos.right) / 10] < 5 && MyKeyState(VK_DOWN) > 0) {
			pos.y = rect.top;
			bottom_c = TRUE;
	}
}
void Player::Door_Open() {
	if (MyKeyState('E') == 1 && Key >= 1 && Stage_arr[py_mid / 10][(rect.right + 3) / 10] == 3) {
		for (int i = py_mid / 40 * 4; i < py_mid / 40 * 4 + 4; i++)
			for (int j = (rect.right + 3) / 40 * 4; j < (rect.right + 3) / 40 * 4 + 4; j++)
				Stage_arr[i][j] = 5;
		Key--;
		ui->k_num--;
		sound->Playis(OPENDOOR_BGM);
	} if (MyKeyState('E') == 1 && Key >= 1 && Stage_arr[py_mid / 10][(rect.left - 3) / 10] == 3) {
		for (int i = py_mid / 40 * 4; i < py_mid / 40 * 4 + 4; i++)
			for (int j = (rect.left - 3) / 40 * 4; j < (rect.left - 3) / 40 * 4 + 4; j++)
				Stage_arr[i][j] = 5;
		Key--;
		ui->k_num--;
		sound->Playis(OPENDOOR_BGM);
	} if (MyKeyState('E') == 1 && Key >= 1 && Stage_arr[(rect.top - 5) / 10][px_mid / 10] == 3) {
		for (int i = (rect.top - 5) / 40 * 4; i<(rect.top - 5) / 40 * 4 + 4; i++)
			for (int j = px_mid / 40 * 4; j<px_mid / 40 * 4 + 4; j++)
				Stage_arr[i][j] = 5;
		Key--;
		ui->k_num--;
		sound->Playis(OPENDOOR_BGM);
	} if (MyKeyState('E') == 1 && Key >= 1 && Stage_arr[(rect.bottom + 5) / 10][px_mid / 10] == 3) {
		for (int i = (rect.bottom + 5) / 40 * 4; i < (rect.bottom + 5) / 40 * 4 + 4; i++)
			for (int j = px_mid / 40 * 4; j<px_mid / 40 * 4 + 4; j++)
				Stage_arr[i][j] = 5;
		Key--;
		ui->k_num--;
		sound->Playis(OPENDOOR_BGM);
	}
}
void Player::Stage_Open() {
	if (MyKeyState('E') == 1 && Stage_key >= 1 && Stage_arr[py_mid / 10][(rect.right + 3) / 10] == 4) {
		for (int i = py_mid / 40 * 4; i < py_mid / 40 * 4 + 4; i++)
			for (int j = (rect.right + 3) / 40 * 4; j < (rect.right + 3) / 40 * 4 + 4; j++)
				Stage_arr[i][j] = 5;
		ui->sk_num--;
		change = 1;
	} if (MyKeyState('E') == 1 && Stage_key >= 1 && Stage_arr[py_mid / 10][(rect.left - 3) / 10] == 4) {
		for (int i = py_mid / 40 * 4; i < py_mid / 40 * 4 + 4; i++)
			for (int j = (rect.left - 3) / 40 * 4; j < (rect.left - 3) / 40 * 4 + 4; j++)
				Stage_arr[i][j] = 5;
		ui->sk_num--;
		change = 1;
	} if (MyKeyState('E') == 1 && Stage_key >= 1 && Stage_arr[(rect.top - 5) / 10][px_mid / 10] == 4) {
		for (int i = (rect.top - 5) / 40 * 4; i < (rect.top - 5) / 40 * 4 + 4; i++)
			for (int j = px_mid / 40 * 4; j < px_mid / 40 * 4 + 4; j++)
				Stage_arr[i][j] = 5;
		ui->sk_num--;
		change = 1;
	} if (MyKeyState('E') == 1 && Stage_key >= 1 && Stage_arr[(rect.bottom + 5) / 10][px_mid / 10] == 4) {
		for (int i = (rect.bottom + 5) / 40 * 4; i < (rect.bottom + 5) / 40 * 4 + 4; i++)
			for (int j = px_mid / 40 * 4; j < px_mid / 40 * 4 + 4; j++)
				Stage_arr[i][j] = 5;
		ui->sk_num--;
		change = 1;
	}
}