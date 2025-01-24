#include "Stage1.h"
#include "Player.h"
#include "Vision.h"
#include "Police.h"
#include "CCTV.h"
#include "Raser_pointMgr.h"
#include "cctvCom.h"
#include "raserCom.h"
#include "CSprite.h"
#include "UI.h"
#include "coin.h"
#include "stage_key.h"
#include "trap.h"
#include "Safe.h"
#include "SoundMgr.h"
#include "EndScene.h"
#include "Stage1_RECT.h"
#include "Stage1_arr.h"

Stage1::Stage1() {
	this->sound = new SoundMgr();
	ui = new UI(this->sound);
	player = new Player(stage1,ui,this->sound,950,350);
	vision = new Vision(player);
	safe = new Safe(40,200);
	Coin[0] = new coin(player,ui,this->sound,95,173);
	Coin[1] = new coin(player,ui,this->sound,436,153);
	Coin[2] = new coin(player,ui,this->sound,134,544);
	Coin[3] = new coin(player,ui,this->sound,369,631);
	Coin[4] = new coin(player,ui,this->sound,789,354);
	Trap = new trap(player,ui,278,271);
	s_Key = new stage_key(player,ui,209,60);
	cctv = new CCTV(player,40,280,2);
	raserMgr = new Raser_pointMgr(ui,player,NULL,360,183,3.14f,Stage1_Col,Stage1_Max,1);
	cctvcom = new cctvCom(cctv,player,sound,60,240,0);
	rasercom = new raserCom(raserMgr,this->sound,3.14f,player,360,100,2);
	police = new Police(player,safe,cctv,stage1,90,280);
	stage = new CSprite("image/Stage/stage1.jpg");
	sk = 0;
	ps = 0;
	this->sound->Playis(MAIN_BGM);
}
Stage1::~Stage1() {
	delete player;
	delete cctv;  
	delete cctvcom;
	delete rasercom;
	delete police;
	delete stage;
	delete vision;
	delete raserMgr;
	delete ui;
	delete s_Key;
	delete Trap;
	delete safe;
	for(int i = 0;i < 5;i++) delete Coin[i];
}
void Stage1::Update(float eTime) {
	sound->Update();
	player->Update(eTime);
	cctv->Update(eTime);
	cctvcom->Update(eTime);
	rasercom->Update(eTime);
	police->Update(eTime);
	vision->Update(eTime);
	raserMgr->Update(eTime);
	ui->Update(eTime);
	if(ui->c_num == 5) s_Key->Update(eTime);
	for(int i = 0;i < 5;i++) Coin[i]->Update(eTime);
	Trap->Update(eTime);
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
	if(ui->l_num == 0) {
		ChangeScene(new Stage1());
	}
	else if(player->change == 1) {
		sound->Stop(EMERGENCY_BGM);
		sound->Stop(MAIN_BGM);
		ChangeScene(new Stage2());
	}
	else if(player->die == 1) {
		sound->Stop(EMERGENCY_BGM);
		sound->Stop(MAIN_BGM);
		sound->Stop(SIREN_BGM);
		ChangeScene(new EndScene(0));
	}
}
void Stage1::Render() {
	stage->Render(NULL);
	for(int i = 0;i < 5;i++) Coin[i]->Render(NULL);
	if(ui->c_num == 5) s_Key->Render(NULL);
	Trap->Render(NULL);
	safe->Render(NULL);
	player->Render(NULL);
	police->Render(NULL);
	cctvcom->Render(NULL);
	rasercom->Render(NULL);
	cctv->Render(NULL);
	raserMgr->Render(NULL);
	//vision->Render(NULL);
	ui->Render(NULL);
}