#include "StartScene.h"
#include "Stage1.h"
#include "CSprite.h"
#include "SoundMgr.h"
#include "myFunction.h"

StartScene::StartScene() {
	bg = new CSprite("image/start/bg.jpg");
	start = new CSprite("image/start/start.png");
	maker = new CSprite("image/start/maker.png");
	help = new CSprite("image/start/help.png");
	mup = new CSprite("image/start/makerup.png");
	hup = new CSprite("image/start/helpup.jpg");
	sound = new SoundMgr();

	sound->addSound(OPENING_BGM,"Sound/opening.mp3");
	sound->addSound(MAIN_BGM,"Sound/main_bgm.mp3");
	sound->addSound(EMERGENCY_BGM,"Sound/chase_bgm.mp3");
	sound->addSound(COM_BGM,"Sound/com_on.wav");
	sound->addSound(MOVE_BGM,"Sound/moving.mp3");
	sound->addSound(PICK_COIN_BGM,"Sound/pick_coin.wav");
	sound->addSound(WHISTLE_BGM,"Sound/whistle.wav");
	sound->addSound(OPENDOOR_BGM,"Sound/Open_Door.wav");
	sound->addSound(SIREN_BGM,"Sound/Siren.mp3");
	sound->Stop(MAIN_BGM);
	
	start_on = help_on = maker_on = FALSE;
	h_up = m_up = FALSE;
}
StartScene::~StartScene() {
	delete bg;
	delete mup;
	delete hup;
	delete start;
	delete help;
	delete maker;
}
void StartScene::Update(float eTime) {
	start->Update(eTime);
	help->Update(eTime);
	maker->Update(eTime);
	sound->Playis(OPENING_BGM);

	RECT startR,helpR,makerR;

	start->pos = D3DXVECTOR2(650,430);
	help->pos = D3DXVECTOR2(650,530);
	maker->pos = D3DXVECTOR2(650,630);
	startR = Rect(start->pos.x,start->pos.y,start->pos.x+start->width,start->pos.y+start->height);
	helpR = Rect(help->pos.x,help->pos.y,help->pos.x+help->width,help->pos.y+help->height);
	makerR = Rect(maker->pos.x,maker->pos.y,maker->pos.x+maker->width,maker->pos.y+maker->height);
	
	D3DXVECTOR2 mPos = D3DXVECTOR2(MyGetCursorPos().x,MyGetCursorPos().y);
	if(mPos.x >= startR.left && mPos.x <= startR.right && mPos.y >= startR.top && mPos.y <= startR.bottom &&
		maker_on == FALSE && help_on == FALSE) {
		start->pos = D3DXVECTOR2(650,420);
		start->green = 0;
		start->blue = 0;
		start_on = TRUE;
	} else {
		start_on = FALSE;
		start->green = 255;
		start->blue = 255;
	} if(mPos.x >= helpR.left && mPos.x <= helpR.right && mPos.y >= helpR.top && mPos.y <= helpR.bottom &&
		maker_on == FALSE && start_on == FALSE) {
		help->pos = D3DXVECTOR2(650,520);
		help->green = 0;
		help->blue = 0;
		help_on = TRUE;
	} else {
		help_on = FALSE;
		help->green = 255;
		help->blue = 255;
	} if(mPos.x >= makerR.left && mPos.x <= makerR.right && mPos.y >= makerR.top && mPos.y <= makerR.bottom &&
		help_on == FALSE && start_on == FALSE) {
		maker->pos = D3DXVECTOR2(650,620);
		maker->green = 0;
		maker->blue = 0;
		maker_on = TRUE;
	} else {
		maker_on = FALSE;
		maker->green = 255;
		maker->blue = 255;
	}
	if(start_on && MyKeyState(MK_LBUTTON) == 1 && h_up == FALSE && m_up == FALSE) {
		sound->Stop(OPENING_BGM);
		ChangeScene(new Stage1());
	}
	if(maker_on && h_up == FALSE && MyKeyState(MK_LBUTTON) == 1) 
		m_up = TRUE;
	else if(MyKeyState(VK_ESCAPE) == 1 && m_up)
		m_up = FALSE;
	if(help_on && m_up == FALSE && MyKeyState(MK_LBUTTON) == 1 )
		h_up = TRUE;
	else if(MyKeyState(VK_ESCAPE) == 1 && h_up)
		h_up = FALSE;

	
}
void StartScene::Render() {
	bg->Render(NULL);
	start->Render(NULL);
	help->Render(NULL);
	maker->Render(NULL);
	if(m_up)
		mup->Render(NULL);
	if(h_up)
		hup->Render(NULL);
}