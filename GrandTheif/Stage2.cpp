#include "Stage2.h"
#include "Player.h"
#include "Raser_pointMgr.h"
#include "CCTV.h"
#include "cctvCom.h"
#include "raserCom.h"
#include "Vision.h"
#include "UI.h"
#include "coin.h"
#include "key.h"
#include "stage_key.h"
#include "trap.h"
#include "Police.h"
#include "Safe.h"
#include "Stage2_RECT.h"
#include "Stage2_arr.h"
#include "CSprite.h"
#include "myFunction.h"
#include "SoundMgr.h"
#include "EndScene.h"

Stage2::Stage2() {
	this->sound = new SoundMgr();
	ui = new UI(this->sound);
	player = new Player(stage2,ui,this->sound,50,100);
	vision = new Vision(player);
	safe = new Safe(320,600);
	raser[0] = new Raser_pointMgr(ui,player,NULL,200,23,3.14f,Stage2_Col,Stage2_Max,2);
	raser[1] = new Raser_pointMgr(ui,player,NULL,63,440,1.57f,Stage2_Col,Stage2_Max,2);
	raser[2] = new Raser_pointMgr(ui,player,NULL,935,200,-1.57f,Stage2_Col,Stage2_Max,2);
	raser[3] = new Raser_pointMgr(ui,player,NULL,480,575,0.f,Stage2_Col,Stage2_Max,2);
	cctv[0] = new CCTV(player,80,520,2);
	cctv[1] = new CCTV(player,520,40,1);
	cctv[2] = new CCTV(player,600,600,2);
	cctv[3] = new CCTV(player,920,440,1);
	cctvcom[0] = new cctvCom(cctv[0],player,this->sound,360,400,1);
	cctvcom[1] = new cctvCom(cctv[1],player,this->sound,680,120,3);
	cctvcom[2] = new cctvCom(cctv[3],player,this->sound,800,560,2);
	rasercom[0] = new raserCom(raser[0],this->sound,3.14f,player,40,320,2);
	rasercom[1] = new raserCom(raser[1],this->sound,1.57f,player,200,600,0);
	rasercom[2] = new raserCom(raser[3],this->sound,0.f,player,400,280,3);
	rasercom[3] = new raserCom(raser[2],this->sound,-1.57f,player,680,400,1);
	Coin[0] = new coin(player,ui,this->sound,902,103);
	Coin[1] = new coin(player,ui,this->sound,488,61);
	Coin[2] = new coin(player,ui,this->sound,709,625);
	Coin[3] = new coin(player,ui,this->sound,488,539);
	Coin[4] = new coin(player,ui,this->sound,99,273);
	Key[0] = new key(player,ui,262,327);
	Key[1] = new key(player,ui,509,348);
	Key[2] = new key(player,ui,187,539);
	Trap[0] = new trap(player,ui,300,531);
	Trap[1] = new trap(player,ui,882,476);
	s_Key = new stage_key(player,ui,438,658);
	police[0] = new Police(player,safe,cctv[0],stage2,80,520);
	police[1] = new Police(player,safe,cctv[0],stage2,400,640);
	police[2] = new Police(player,safe,cctv[0],stage2,520,40);
	stage = new CSprite("image/Stage/stage2.jpg");
	ps = 0;
	this->sound->Playis(MAIN_BGM);
}
Stage2::~Stage2() {
	for(int i = 0;i < 4;i++) {
		delete raser[i];
		delete cctv[i];
		delete rasercom[i];
	}
	for(int i = 0;i < 3;i++) {
		delete cctvcom[i];
	}
	for(int i = 0;i < 5;i++) delete Coin[i];
	for(int i = 0;i < 3;i++) delete Key[i];
	for(int i = 0;i < 2;i++) delete Trap[i];
	for(int i = 0;i < 3;i++) delete police[i];
	delete s_Key;
	delete player;
	delete ui;
	delete vision;
	delete stage;
	delete safe;
}
void Stage2::Update(float eTime) {
	RECT tempRect;
	sound->Update();
	player->Update(eTime);
	vision->Update(eTime);
	ui->Update(eTime);
	for(int i = 0;i < 4;i++) {
		raser[i]->Update(eTime);
		cctv[i]->Update(eTime);
		rasercom[i]->Update(eTime);
	}
	for(int i = 0;i < 3;i++) {
		cctvcom[i]->Update(eTime);
	}
	for(int i = 0;i < 5;i++) Coin[i]->Update(eTime);
	for(int i = 0;i < 3;i++) Key[i]->Update(eTime);
	for(int i = 0;i < 2;i++) Trap[i]->Update(eTime);
	if(ui->c_num == 5) s_Key->Update(eTime);
	for(int i = 0;i < 3;i++) police[i]->Update(eTime);
	for(int i = 0;i < 3;i++) {
	if(police[0]->stock || police[1]->stock || police[2]->stock || cctv[1]->police_ch) {
		sound->Stop(MAIN_BGM);
		sound->Playis(EMERGENCY_BGM);
		ui->s_on = 1;
		if(ps == 0) {
			sound->Playis(WHISTLE_BGM);
			ps++;
		}
	} else {
		sound->Stop(EMERGENCY_BGM);
		sound->Playis(MAIN_BGM);
		ui->s_on = 0;
		ps = 0;
	}
	}
	if(ui->l_num == 0) 
		ChangeScene(new Stage2());
	else if(player->change) {
		sound->Stop(EMERGENCY_BGM);
		sound->Stop(MAIN_BGM);
		ChangeScene(new Stage3());
	}
	else if(player->die == 1) {
		sound->Stop(EMERGENCY_BGM);
		sound->Stop(MAIN_BGM);
		sound->Stop(SIREN_BGM);
		ChangeScene(new EndScene(0));
	}
}
void Stage2::Render() {
	stage->Render(NULL);
	for(int i = 0;i < 5;i++) Coin[i]->Render(NULL);
	for(int i = 0;i < 3;i++) Key[i]->Render(NULL);
	for(int i = 0;i < 2;i++) Trap[i]->Render(NULL);
	if(ui->c_num == 5) s_Key->Render(NULL);
	safe->Render(NULL);
	player->Render(NULL);
	for(int i = 0;i < 3;i++) police[i]->Render(NULL);
	for(int i = 0;i < 4;i++) {
		raser[i]->Render(NULL);
		cctv[i]->Render(NULL);
		rasercom[i]->Render(NULL);
	}
	for(int i = 0;i < 3;i++) {
		cctvcom[i]->Render(NULL);
	}
	//vision->Render(NULL);
	ui->Render(NULL);
}
