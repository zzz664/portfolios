#include "WinFrame.h"
#include "Def.h"
#include "myFunction.h"

extern HINSTANCE g_Inst;

LPDIRECT3D9 g_pD3D = NULL; //그래픽디바이스의 정보 LP 포인터약자
LPDIRECT3DDEVICE9 g_pd3dDevice; //그래픽카드를 사용하기 위함
LPD3DXSPRITE g_pSprite;
D3DPRESENT_PARAMETERS d3dpp; //화면출력을 위한 세부정보를 담음

void InitD3D(HWND hWnd)
{
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	ZeroMemory(&d3dpp,sizeof(d3dpp)); //d3dpp를 초기화
	d3dpp.Windowed = true;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.BackBufferWidth = WIDTH;
	d3dpp.BackBufferHeight = HEIGHT;
	d3dpp.BackBufferCount = 1;
	/*
	d3dpp.Windowed = false;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferWidth = WIDTH;
	d3dpp.BackBufferHeight = HEIGHT;
	d3dpp.BackBufferCount = 1;
	d3dpp.FullScreen_RefreshRateInHz = 60;

	*/
	
	g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hWnd,
								D3DCREATE_SOFTWARE_VERTEXPROCESSING,
								&d3dpp,&g_pd3dDevice);
	D3DXCreateSprite(g_pd3dDevice,&g_pSprite);
	Init();
}

void InitWindow(HINSTANCE hInstance, int nCmdShow)
{
	WNDCLASS WndClass;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //뒷배경색
	WndClass.hCursor = LoadCursor(NULL,IDC_ARROW); //커서지정
	WndClass.hIcon = LoadIcon(NULL,IDI_APPLICATION); //윈도우 아이콘 지정
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = TEXT(NAME);
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW; //윈도우 스타일
	RegisterClass(&WndClass); //윈도우 등록
}
HWND FloatWindow(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	hWnd = CreateWindow(TEXT(NAME),TEXT(NAME),
		WS_SYSMENU|WS_MINIMIZEBOX|WS_MAXIMIZEBOX,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		WIDTH,
		HEIGHT,
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL);
	ShowWindow(hWnd,nCmdShow);
	return hWnd;

}
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,
						 WPARAM wParam,LPARAM lParam)
{
	switch(iMessage)
	{
	case WM_DESTROY:
		g_pd3dDevice->Release();
		g_pSprite->Release();
		g_pD3D->Release();
		Destroy();
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
int DoMainLoop()
{
	MSG Message = {0};
	while (Message.message != WM_QUIT)
	{
		if(PeekMessage(&Message,NULL,0,0,PM_REMOVE))
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
		else
		{
			if(FAILED(g_pd3dDevice->TestCooperativeLevel()))
				g_pd3dDevice->Reset(&d3dpp);
			g_pd3dDevice->Clear(0,NULL,D3DCLEAR_TARGET,
				D3DCOLOR_ARGB(255,0,0,0),1.0f,0);
			Update(GetElapsedTime());

			if(SUCCEEDED(g_pd3dDevice->BeginScene()))
			{
				Render();
				g_pd3dDevice->EndScene();
			}
			g_pd3dDevice->Present(NULL,NULL,NULL,NULL);
		}
	}
	return (int)Message.wParam;
}