#include "EndScene.h"
#include "CSprite.h"
#include "myFunction.h"
#include "StartScene.h"

EndScene::EndScene(int wl) {
	this->wl = wl;
	win = new CSprite("image/end/win.jpg");
	lose = new CSprite("image/end/lose.jpg");
}
EndScene::~EndScene() {
	delete win;
	delete lose;
}
void EndScene::Update(float eTime) {
	if(MyKeyState(VK_ESCAPE) == 1)
		ChangeScene(new StartScene());
}
void EndScene::Render() {
	if(wl == 0)
		lose->Render(NULL);
	else if(wl == 1)
		win->Render(NULL);
}