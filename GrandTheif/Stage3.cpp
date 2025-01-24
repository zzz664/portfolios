#include "Stage3.h"
#include "Stage3_RECT.h"
#include "Stage3_arr.h"
#include "CSprite.h"
#include "Player.h"
#include "UI.h"
#include "Raser_pointMgr.h"
#include "raserCom.h"
#include "CCTV.h"
#include "cctvCom.h"
#include "Vision.h"
#include "coin.h"
#include "key.h"
#include "stage_key.h"
#include "trap.h"
#include "Police.h"
#include "Safe.h"
#include "myFunction.h"
#include "SoundMgr.h"
#include "EndScene.h"

Stage3::Stage3() {
	this->sound = new SoundMgr();
	ui = new UI(this->sound);
	player = new Player(stage3,ui,this->sound,20,50);
	vision = new Vision(player);
	safe = new Safe(500,680);
	raser[0] = new Raser_pointMgr(ui,player,NULL,25,215,1.57f,Stage3_Col,Stage3_Max,3);
	raser[1] = new Raser_pointMgr(ui,player,NULL,440,930,0.f,Stage3_Col,Stage3_Max,3);
	rasercom[0] = new raserCom(raser[0],this->sound,1.57f,player,160,120,3);
	rasercom[1] = new raserCom(raser[1],this->sound,0.f,player,600,560,2);
	cctv[0] = new CCTV(player,40,520,2);
	cctv[1] = new CCTV(player,920,200,1);
	cctv[2] = new CCTV(player,920,520,1);
	cctvcom[0] = new cctvCom(cctv[0],player,this->sound,200,450,2);
	cctvcom[1] = new cctvCom(cctv[1],player,this->sound,645,160,1);
	cctvcom[2] = new cctvCom(cctv[2],player,this->sound,850,320,2);
	Coin[0] = new coin(player,ui,this->sound,439,87);
	Coin[1] = new coin(player,ui,this->sound,280,573);
	Coin[2] = new coin(player,ui,this->sound,711,413);
	Coin[3] = new coin(player,ui,this->sound,580,87);
	Coin[4] = new coin(player,ui,this->sound,909,612);
	Key[0] = new key(player,ui,84,667);
	Key[1] = new key(player,ui,301,374);
	Key[2] = new key(player,ui,648,222);
	Trap[0] = new trap(player,ui,479,313);
	Trap[1] = new trap(player,ui,85,453);
	s_Key = new stage_key(player,ui,485,576);
	police[0] = new Police(player,safe,cctv[1],stage3,40,240);
	police[1] = new Police(player,safe,cctv[1],stage3,520,280);
	police[2] = new Police(player,safe,cctv[1],stage3,920,280);
	stage = new CSprite("image/Stage/stage3.jpg");
	ps = 0;
	this->sound->Playis(MAIN_BGM);
}
Stage3::~Stage3() {
	delete stage;
	delete player;
	delete ui;
	delete vision;
	for(int i = 0;i < 2;i++) {
		delete raser[i];
		delete rasercom[i];
	}
	for(int i = 0;i < 3;i++) {
		delete cctv[i];
		delete cctvcom[i];
	}
	for(int i = 0;i < 5;i++) delete Coin[i];
	for(int i = 0;i < 3;i++) delete Key[i];
	for(int i = 0;i < 2;i++) delete Trap[i];
	delete s_Key;
}
void Stage3::Update(float eTime) {
	sound->Update();
	ui->Update(eTime);
	player->Update(eTime);
	vision->Update(eTime);
	for(int i = 0;i < 3;i++) police[i]->Render(NULL);
	for(int i = 0;i < 2;i++) {
		raser[i]->Update(eTime);
		rasercom[i]->Update(eTime);
	}
	for(int i = 0;i < 3;i++) {
		cctv[i]->Update(eTime);
		cctvcom[i]->Update(eTime);
	}
	for(int i = 0;i < 5;i++) Coin[i]->Update(eTime);
	for(int i = 0;i < 3;i++) Key[i]->Update(eTime);
	for(int i = 0;i < 2;i++) Trap[i]->Update(eTime);
	if(ui->c_num == 5) s_Key->Update(eTime);
	for(int i = 0;i < 3;i++) police[i]->Update(eTime);
	if(police[0]->stock || police[1]->stock || police[2]->stock || cctv[1]->police_ch) {
		sound->Stop(MAIN_BGM);
		sound->Playis(EMERGENCY_BGM);
		ui->s_on = 1;
		if(ps == 0) {
			sound->Play(WHISTLE_BGM);
			ps = 1;
		}
	} else {
		sound->Stop(EMERGENCY_BGM);
		sound->Playis(MAIN_BGM);
		ui->s_on = 0;
		ps = 0;
	}

	if(ui->l_num == 0) 
		ChangeScene(new Stage3());
	else if(player->change) {
		sound->Stop(EMERGENCY_BGM);
		sound->Stop(MAIN_BGM);
		ChangeScene(new Stage4());
	}
	else if(player->die == 1) {
		sound->Stop(EMERGENCY_BGM);
		sound->Stop(MAIN_BGM);
		sound->Stop(SIREN_BGM);
		ChangeScene(new EndScene(0));
	}
}
void Stage3::Render() {
	stage->Render(NULL);
	for(int i = 0;i < 5;i++) Coin[i]->Render(NULL);
	for(int i = 0;i < 3;i++) Key[i]->Render(NULL);
	for(int i = 0;i < 2;i++) Trap[i]->Render(NULL);
	if(ui->c_num == 5) s_Key->Render(NULL);
	safe->Render(NULL);
	player->Render(NULL);
	for(int i = 0;i < 3;i++) police[i]->Render(NULL);
	for(int i = 0;i < 2;i++) {
		raser[i]->Render(NULL);
		rasercom[i]->Render(NULL);
	}
	for(int i = 0;i < 3;i++) {
		cctv[i]->Render(NULL);
		cctvcom[i]->Render(NULL);
	}
	//vision->Render(NULL);
	ui->Render(NULL);
}