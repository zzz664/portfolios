#include "WinFrame.h"
HINSTANCE g_Inst;
HWND g_hWnd;

int APIENTRY WinMain(HINSTANCE hInstance,
					 HINSTANCE hPrevInstance,
					 LPSTR lpszCmdParam,
					 int nCmdShow)
{
	g_Inst = hInstance;
	InitWindow(hInstance,nCmdShow);
	InitD3D(g_hWnd = FloatWindow(hInstance,nCmdShow));
	return DoMainLoop();
}
