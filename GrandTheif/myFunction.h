#pragma once
#include <windows.h>
#include <d3dx9.h>
#include "IScene.h"

void Init();
void Update(float eTime); //Elapsed Time
void Render();
void Destroy();
float GetElapsedTime();
LPDIRECT3DTEXTURE9 LoadTexture(char *path);

void UpdateKeyState();
int MyKeyState(int key);
float GetDistanceSqaure(D3DXVECTOR2 v1,D3DXVECTOR2 v2);
D3DXVECTOR2 MyGetCursorPos();

void ChangeScene(IScene *p,bool nowSceneErase = true);
RECT Rect(float left,float top,float right,float bottom);