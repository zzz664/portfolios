#include "Stage4.h"
#include "Stage4_RECT.h"
#include "Stage4_arr.h"
#include "CSprite.h"
#include "Player.h"
#include "UI.h"
#include "Vision.h"
#include "Raser_pointMgr.h"
#include "raserCom.h"
#include "CCTV.h"
#include "cctvCom.h"
#include "coin.h"
#include "key.h"
#include "stage_key.h"
#include "trap.h"
#include "Police.h"
#include "Safe.h"
#include "Diamond.h"
#include "myFunction.h"
#include "SoundMgr.h"
#include "EndScene.h"

Stage4::Stage4() {
	this->sound = new SoundMgr();
	ui = new UI(this->sound);
	player = new Player(stage4,ui,this->sound,720,10);
	vision = new Vision(player);
	safe = new Safe(630,360);
	raser[0] = new Raser_pointMgr(ui,player,NULL,80,30,3.14f,Stage4_Col,Stage4_Max,4);
	raser[1] = new Raser_pointMgr(ui,player,NULL,410,80,-1.57f,Stage4_Col,Stage4_Max,4);
	raser[2] = new Raser_pointMgr(ui,player,NULL,360,692,0.f,Stage4_Col,Stage4_Max,4);
	raser[3] = new Raser_pointMgr(ui,player,NULL,25,670,1.57f,Stage4_Col,Stage4_Max,4);
	rasercom[0] = new raserCom(raser[0],this->sound,3.14f,player,200,0,1);
	rasercom[1] = new raserCom(raser[1],this->sound,-1.57f,player,440,500,3);
	rasercom[2] = new raserCom(raser[2],this->sound,0.f,player,440,200,2);
	rasercom[3] = new raserCom(raser[3],this->sound,1.57f,player,0,240,3);
	cctv = new CCTV(player,480,240,2);
	cctvcom = new cctvCom(cctv,player,this->sound,722,371,1);
	Coin[0] = new coin(player,ui,this->sound,206,73);
	Coin[1] = new coin(player,ui,this->sound,360,205);
	Coin[2] = new coin(player,ui,this->sound,100,480);
	Coin[3] = new coin(player,ui,this->sound,237,648);
	Coin[4] = new coin(player,ui,this->sound,510,520);
	Trap = new trap(player,ui,712,214);
	dia = new Diamond(player,ui,230,360);
	police = new Police(player,safe,cctv,stage4,800,240);
	stage = new CSprite("image/Stage/stage4.png");
	fence = new CSprite("image/Stage/fence.png");
	diaon = new CSprite("image/Stage/diaon.png");
	diaon->pos.x = 212;
	diaon->pos.y = 337;
	ps = 0;
	this->sound->Playis(MAIN_BGM);
}
Stage4::~Stage4() {
	delete stage;
	delete fence;
	delete player;
	delete ui;
	delete cctv;
	delete cctvcom;
	delete Trap;
	delete vision;
	delete police;
	delete dia;
	delete diaon;
	delete safe;
	for(int i = 0;i < 5;i++) {
		delete Coin[i];
	}
	for(int i = 0;i < 4;i++) {
		delete raser[i];
		delete rasercom[i];
	}
}
void Stage4::Update(float eTime) {
	RECT tempRect;
	RECT fr[3];
	fr[0] = Rect(480,480,556,715);
	fr[1] = Rect(560,640,880,715);
	fr[2] = Rect(877,41,957,715);
	sound->Update();
	fence->Update(eTime);
	player->Update(eTime);
	ui->Update(eTime);
	cctv->Update(eTime);
	cctvcom->Update(eTime);
	Trap->Update(eTime);
	dia->Update(eTime);
	vision->Update(eTime);
	for(int i = 0;i < 5;i++) {
		Coin[i]->Update(eTime);
	}
	for(int i = 0;i < 4;i++) {
		raser[i]->Update(eTime);
		rasercom[i]->Update(eTime);
	}
	police->Update(eTime);
	if(IntersectRect(&tempRect,&fr[0],&player->rect) ||
		IntersectRect(&tempRect,&fr[1],&player->rect) ||
		IntersectRect(&tempRect,&fr[2],&player->rect)) {
		fence->opacity = 100;
	} else
		fence->opacity = 255;
	if(police->stock || cctv->police_ch) {
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
		ChangeScene(new Stage4());
	else if(player->change == 1) {
		sound->Stop(EMERGENCY_BGM);
		sound->Stop(MAIN_BGM);
		ChangeScene(new EndScene(1));
	}
	else if(player->die == 1) {
		sound->Stop(EMERGENCY_BGM);
		sound->Stop(MAIN_BGM);
		sound->Stop(SIREN_BGM);
		ChangeScene(new EndScene(0));
	}
}
void Stage4::Render() {
	stage->Render(NULL);
	for(int i = 0;i < 5;i++) Coin[i]->Render(NULL);
	Trap->Render(NULL);
	diaon->Render(NULL);
	dia->Render(NULL);
	safe->Render(NULL);
	player->Render(NULL);
	police->Render(NULL);
	fence->Render(NULL);
	cctv->Render(NULL);
	cctvcom->Render(NULL);
	for(int i = 0;i < 4;i++) {
		raser[i]->Render(NULL);
		rasercom[i]->Render(NULL);
	}
	//vision->Render(NULL);
	ui->Render(NULL);
}
