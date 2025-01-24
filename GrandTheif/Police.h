#pragma once
#include "IObject.h"

class Player;
class CCTV;
class Safe;
class CAnimation;
class CSprite;

class Police : public IObject {
public:
	Police(Player *player,Safe *safe,CCTV *cctv,int Stage_arr[][100],int x,int y);
	~Police();

	Player *player;
	CSprite *center;
	CAnimation *uAni;
	CAnimation *dAni;
	CAnimation *walk;
	Safe *safe;
	CCTV *cctv;

	RECT save_pos;

	double delay;

	int Stage_arr[76][100];

	int left, left_c,
		right, right_c,
		top, top_c,
		bottom, bottom_c;

	int left_y_c1, left_y_c2, left_y_c3, left_y_c4,
		right_y_c1, right_y_c2, right_y_c3, right_y_c4,
		top_x_c1, top_x_c2, top_x_c3, top_x_c4,
		bottom_x_c1, bottom_x_c2, bottom_x_c3, bottom_x_c4;

	int right_d,right_u,
		left_d,left_u,
		top_r,top_l,
		bottom_r,bottom_l;
	
	int x, y,
		go_x, go_y,
		ex_mid, ey_mid,
		chase, stock;

	int save_x, save_y, save, 
		save_gx, save_gy, save_tel, save_ch;
	int savex,savey;

	int check_u, check_d, check_l, check_r;

	int Uw,Dw;

	void Up();
	void Down();
	void Left();
	void Right();

	void Collision();
	void AI();
	void Return(float eTime);
	void Update(float eTime);
	void Render(D3DXMATRIX *pmat);
};