#include "myFunction.h"
#include "CSprite.h"
#include "StartScene.h"
#include <map>
using namespace std;

extern LPDIRECT3DDEVICE9 g_pd3dDevice; //그래픽카드를 사용하기 위함
extern LPD3DXSPRITE g_pSprite;
extern HWND g_hWnd;

LARGE_INTEGER LInterval, RInterval, Frequency;
IScene *nowScene;
bool lkey[256],rkey[256];
map<char*,LPDIRECT3DTEXTURE9> texMap;

LPDIRECT3DTEXTURE9 LoadTexture(char *path)
{
	if(texMap[path] != NULL) return texMap[path];
	D3DXCreateTextureFromFileExA(
		g_pd3dDevice,
		path,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		1,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		NULL,
		NULL,
		NULL,
		&texMap[path]);
	return texMap[path];
}
void Init()
{
	nowScene = new StartScene();
	QueryPerformanceCounter(&LInterval);
	QueryPerformanceFrequency(&Frequency);
	for(int i=0;i<256;i++) rkey[i] = lkey[i] = false;
}
void Update(float eTime)
{
	UpdateKeyState();
	nowScene->Update(eTime);
}
void Render()
{
	nowScene->Render();
}
void Destroy()
{
	delete nowScene;
	map<char*,LPDIRECT3DTEXTURE9>::iterator iter;
	for(iter = texMap.begin();iter != texMap.end();iter++)
		iter->second->Release();
}
float GetElapsedTime()
{
	QueryPerformanceCounter(&RInterval);
	__int64 Interval = (RInterval.QuadPart - LInterval.QuadPart);

	float eTime = (double)Interval/(double)Frequency.QuadPart;

	LInterval = RInterval;
	return eTime;
}
void UpdateKeyState()
{
	for(int i=0;i<256;i++)
	{
		lkey[i] = rkey[i];
		rkey[i] = GetKeyState(i) & 0x8000;
	}
}
int MyKeyState(int key)
{
	if(lkey[key]==true && rkey[key]==true) return 2;
	if(lkey[key]==false && rkey[key]==true) return 1;
	if(lkey[key]==true && rkey[key]==false) return -1;
	return 0;
}
D3DXVECTOR2 MyGetCursorPos()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd,&pt);//윈도우 화면을 좌표로삼음 윈도우 왼쪽위 0,0 ClientToScreen 모니터 왼쪽위 0,0
	D3DXVECTOR2 vector(float(pt.x),float(pt.y));
	return vector;
}
float GetDistanceSqaure(D3DXVECTOR2 v1,D3DXVECTOR2 v2)
{
	D3DXVECTOR2 d = v1-v2;
	return d.x*d.x + d.y*d.y;
}
void ChangeScene(IScene *p,bool nowSceneErase)
{
	if(nowSceneErase) delete nowScene;
	nowScene = p;
}
RECT Rect(float left,float top,float right,float bottom) {
	RECT rect;
	rect.top = top;
	rect.left = left;
	rect.bottom = bottom;
	rect.right = right;
	return rect;
}