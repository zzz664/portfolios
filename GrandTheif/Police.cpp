#include "Police.h"
#include "CCTV.h"
#include "Player.h"
#include "Safe.h"
#include "CAnimation.h"
#include "myFunction.h"
#include <time.h>

Police::Police(Player *player,Safe *safe,CCTV *cctv,int Stage_arr[][100],int x,int y) {
	this->player = player;
	this->cctv = cctv;

		this->safe = safe;

	center = new CSprite("image/Police/pw1.png");
	walk = new CAnimation(2,7.0f);
	uAni = new CAnimation(2,7.0f);
	dAni = new CAnimation(2,7.0f);

	walk->PushFrame("image/Police/pw1.png",0);
	walk->PushFrame("image/Police/pw2.png",1);
	uAni->PushFrame("image/Police/up1.png",0);
	uAni->PushFrame("image/Police/up2.png",1);
	dAni->PushFrame("image/Police/down1.png",0);
	dAni->PushFrame("image/Police/down2.png",1);

	walk->scalingCenter = center->GetCenter();

	left_y_c1 = left_y_c2 = left_y_c3 = left_y_c4
		= right_y_c1 = right_y_c2 = right_y_c3 = right_y_c4
		= top_x_c1 = top_x_c2 = top_x_c3 = top_x_c4
		= bottom_x_c1 = bottom_x_c2 = bottom_x_c3 = bottom_x_c4 = 0;

	left_u = left_d = right_u = right_d
		= top_r = top_l = bottom_r = bottom_l = 0;

	left_c = right_c = top_c = bottom_c = 0;

	check_u = check_d = check_l = check_r = 0;

	chase = save = stock = FALSE;

	go_x = go_y = FALSE;

	Uw = Dw = 0;

	delay = clock();

	pos.x = x;
	pos.y = y;

	this->x = 0;
	this->y = 120;

	for(int i = 0;i < 76;i++) {
		for(int j = 0;j < 100;j++) {
			this->Stage_arr[i][j] = Stage_arr[i][j];
		}
	}
}
Police::~Police() {
	delete center;
	delete walk;
	delete uAni;
	delete dAni;
}
void Police::Update(float eTime) {
	uAni->Update(eTime);
	dAni->Update(eTime);
	walk->Update(eTime);

	RECT tempRect;

	rect = Rect(pos.x,pos.y,pos.x+center->width,pos.y+center->height);
	ex_mid = rect.left+center->width/2, ey_mid = rect.top+center->height/2;

	if(IntersectRect(&tempRect,&player->rect,&rect))
		player->die = 1;

	if(chase == FALSE)
		AI();
	if (x != 0) {
		if (x > 0 && ey_mid - 45 < player->py_mid && ey_mid + 45 > player->py_mid &&
			ex_mid - 45 < player->px_mid && ex_mid + 105 > player->px_mid)
			stock = true;
		if (x < 0 && ey_mid - 45 < player->py_mid && ey_mid + 45 > player->py_mid &&
			ex_mid + 45 > player->px_mid && ex_mid - 105 < player->px_mid)
			stock = true;
	}
	if (y != 0) {
		if (y > 0 && ey_mid - 45 < player->py_mid && ey_mid + 105 > player->py_mid &&
			ex_mid - 45 < player->px_mid && ex_mid + 45 > player->px_mid)
			stock = true;
		if (y < 0 && ey_mid + 45 > player->py_mid && ey_mid - 105 < player->py_mid &&
			ex_mid - 45 < player->px_mid && ex_mid + 45 > player->px_mid)
			stock = true;
	}
		if(MyKeyState('E') > 0 && IntersectRect(&tempRect,&safe->sRect,&player->rect)) {
			stock = FALSE;
			cctv->police_ch == FALSE;
			player->box = 1;
			player->sf = 1;
		} else {
			player->box = 0;
			player->sf = 0;
		}
	if ((stock == true || cctv->police_ch))
	{
		cctv->ch = 1;
		save_ch = 0;
		Collision();
		if(player->sf == 1)
			Return(eTime);

		if (left == true) {
			Left();
		} else if (right == true) {
			Right();
		} else if (top == true) {
			Up();
		} else if (bottom == true)  {
			Down();
		}
		else {
			if (save == FALSE) {
				save_x = pos.x;
				save_y = pos.y;
				save_gx = x;
				save_gy = y;
				save = TRUE;
				chase = TRUE;
			}

			if (rect.left > player->rect.left && left_c == false) {
				x = -140;
			} else if (rect.left < player->rect.left && right_c == false) {
				x = 140;
			}
			if (abs(player->rect.left - rect.left) < 2)
				x = 0;

			if (rect.top > player->rect.top && top_c == false) {
				y = -140;
			} else if (rect.top < player->rect.top && bottom_c == false) {
				y = 140;
			}
			if (abs(player->rect.top - rect.top) < 2)
				y = 0;
			savex = x, savey = y;

			save_pos.left = pos.x + (x * eTime);
			save_pos.right = save_pos.left + center->width;
			save_pos.top = pos.y + (y * eTime);
			save_pos.bottom = save_pos.top + center->height;

			if ((Stage_arr[(save_pos.top-3) / 10][(save_pos.left-3) / 10] >= 5 && Stage_arr[(save_pos.bottom +3)/ 10][(save_pos.left-3) / 10] >= 5))
				left_c = false;
			if (Stage_arr[(save_pos.top-3) / 10][(save_pos.right+3) / 10] >= 5 && Stage_arr[(save_pos.bottom+3) / 10][(save_pos.right+3) / 10] >= 5)
				right_c = false;
			if (Stage_arr[(save_pos.top-3) / 10][(save_pos.left-3) / 10] >= 5 && Stage_arr[(save_pos.top-3) / 10][(save_pos.right+3) / 10] >= 5)
				top_c = false;
			if (Stage_arr[(save_pos.bottom+3) / 10][(save_pos.left-3) / 10] >= 5 && Stage_arr[(save_pos.bottom+3) / 10][(save_pos.right+3) / 10] >= 5)
				bottom_c = false;

			if ((Stage_arr[save_pos.top / 10][(save_pos.left) / 10] < 5 || Stage_arr[save_pos.bottom / 10][(save_pos.left) / 10] < 5) && x < 0) {
				if (Stage_arr[save_pos.top / 10][(save_pos.right) / 10] >= 5 && 
					Stage_arr[save_pos.bottom / 10][(save_pos.right) / 10] >= 5) 
					x = 0;
				left_c = true;
			} if (Stage_arr[save_pos.top / 10][(save_pos.right) / 10] < 5 || Stage_arr[save_pos.bottom / 10][(save_pos.right) / 10] < 5 && x > 0) {
				if (Stage_arr[save_pos.top / 10][(save_pos.left) / 10] >= 5 && 
					Stage_arr[save_pos.bottom / 10][(save_pos.left) / 10] >= 5)
					x = 0;
				right_c = true;
			} if ((Stage_arr[(save_pos.top) / 10][(save_pos.left) / 10] < 5 || Stage_arr[(save_pos.top) / 10][(save_pos.right) / 10] < 5) && y < 0) {
				if (Stage_arr[(save_pos.bottom) / 10][(save_pos.left) / 10] >= 5 &&
					Stage_arr[(save_pos.bottom) / 10][(save_pos.right)] >= 5) 
					y = 0;
				top_c = true;

			} if ((Stage_arr[(save_pos.bottom) / 10][(save_pos.left) / 10] < 5 || Stage_arr[(save_pos.bottom) / 10][(save_pos.right) / 10] < 5) && y > 0) {
				if (Stage_arr[(save_pos.top) / 10][(save_pos.left) / 10] >= 5 && 
					Stage_arr[(save_pos.top) / 10][(save_pos.right) / 10] >= 5) 
					y = 0;
				bottom_c = true;
			}
			Collision();

			if ((bottom_c == true && right_c == true && ey_mid < player->py_mid && ex_mid < player->px_mid && 
				(bottom_x_c3 > rect.left && bottom_x_c4 < rect.left) || (bottom_x_c3 > rect.right && bottom_x_c4 < rect.right)) ||
				(bottom_c == true && left_c == true && ey_mid < player->py_mid && ex_mid > player->px_mid &&  
				(bottom_x_c3 > rect.left && bottom_x_c4 < rect.left) || (bottom_x_c3 > rect.right && bottom_x_c4 < rect.right)) ||
				(top_c == true && right_c == true && ey_mid > player->py_mid && ex_mid < player->px_mid &&   
				(top_x_c3 > rect.left && top_x_c4 < rect.left) || (top_x_c3 > rect.right && top_x_c4 < rect.right)) ||
				(top_c == true && left_c == true && ey_mid > player->py_mid && ex_mid > player->px_mid &&    
				(top_x_c3 > rect.left && top_x_c4 < rect.left) || (top_x_c3 > rect.right && top_x_c4 < rect.right))) 
				x = savex, y = 0;

			else if ((bottom_c == true && right_c == true && ey_mid < player->py_mid && ex_mid < player->px_mid) ||
				(bottom_c == true && left_c == true && ey_mid < player->py_mid && ex_mid > player->px_mid) ||
				(top_c == true && right_c == true && ey_mid > player->py_mid && ex_mid < player->px_mid) ||
				(top_c == true && left_c == true && ey_mid > player->py_mid && ex_mid > player->px_mid)) 
				y = savey, x = 0;

			if (check_r == true && right_c == false)
				x = 150, y = 0, check_r = false;
			if (check_l == true && left_c == false)
				x = -150, y = 0, check_l = false;
			if (check_u == true && top_c == false)
				x = 0, y = -150, check_u = false;
			if (check_d == true && bottom_c == false)
				x = 0, y = 150, check_d = false;
		}

	} else {
		chase = false;
		stock = false;
		cctv->police_ch = 0;
		cctv->ch = 0;
		Return(eTime);
	} if (abs(player->px_mid - ex_mid) > 200 || abs(player->py_mid - ey_mid) > 200) {
		chase = false;
		stock = false;
		cctv->police_ch = 0;
		cctv->ch = 0;
		Return(eTime);
	}

	if (y == 0) go_y = false;
	if (x == 0) go_y = true;

	if (go_y == false)
	{
		pos.x += x * eTime;
		go_x = true;
		if(x < 0) {
			Uw = Dw = 0;
			walk->scale = D3DXVECTOR2(1,1);
		} else if(x > 0) {
			Uw = Dw = 0;
			walk->scale = D3DXVECTOR2(-1,1);
		}
	}

	if (x == 0) go_x = false;
	if (y == 0) go_x = true;

	if (go_x == false)
	{
		pos.y += y * eTime;
		go_y = true;
		if(y < 0) {
			Uw = 1;
			Dw = 0;
		} else if(y > 0) {
			Uw = 0;
			Dw = 1;
		}
	}
}
void Police::Render(D3DXMATRIX *pmat) {
	IObject::Render(pmat);
	if(Uw) uAni->Render(&this->mat);
	else if(Dw) dAni->Render(&this->mat);
	else walk->Render(&this->mat);
}
void Police::Collision() {
	if (right_c == true || right == true) {
		if (right_y_c3 == 0 && right_y_c4 == 0) {
			while (Stage_arr[(ey_mid + right_y_c3 ) / 10][(ex_mid + 18) / 10] < 5)
				right_y_c3 += 10;
			while (Stage_arr[(ey_mid - right_y_c4 ) / 10][(ex_mid + 18) / 10] < 5)
				right_y_c4 += 10;
			if (right_y_c3 == 0 && right_y_c4 == 0) {
				while (Stage_arr[(rect.top + right_y_c3) / 10][(ex_mid + 18) / 10] < 5)
					right_y_c3 += 10;
				while (Stage_arr[(rect.top - right_y_c4) / 10][(ex_mid + 18) / 10] < 5)
					right_y_c4 += 10;
			}
			if (right_y_c3 == 0 && right_y_c4 == 0) {
				while (Stage_arr[(rect.bottom + right_y_c3) / 10][(ex_mid + 18) / 10] < 5)
					right_y_c3 += 10;
				while (Stage_arr[(rect.bottom - right_y_c4) / 10][(ex_mid + 18) / 10] < 5)
					right_y_c4 += 10;
			}
			if (right_y_c3 != 0 && right_y_c4 != 0) {
				right_y_c3 = ey_mid / 10 * 10 + right_y_c3;
				right_y_c4 = ey_mid / 10 * 10 - right_y_c4;
			}
		}
		if (player->rect.top < right_y_c3 && player->rect.bottom > right_y_c4) 
			right = true;
	}

	if (left_c == true || left == true) {
		if (left_y_c3 == 0 && left_y_c4 == 0) {
			while (Stage_arr[(ey_mid + left_y_c3) / 10][(ex_mid - 18) / 10] < 5)
				left_y_c3 += 10;
			while (Stage_arr[(ey_mid - left_y_c4) / 10][(ex_mid - 18) / 10] < 5)
				left_y_c4 += 10;
			if (left_y_c3 == 0 && left_y_c4 == 0) {
				while (Stage_arr[(rect.top + left_y_c3) / 10][(ex_mid - 18) / 10] < 5)
					left_y_c3 += 10;
				while (Stage_arr[(rect.top - left_y_c4) / 10][(ex_mid - 18) / 10] < 5)
					left_y_c4 += 10;
			}
			if (left_y_c3 == 0 && left_y_c4 == 0) {
				while (Stage_arr[(rect.bottom + left_y_c3) / 10][(ex_mid - 18) / 10] < 5)
					left_y_c3 += 10;
				while (Stage_arr[(rect.bottom - left_y_c4) / 10][(ex_mid - 18) / 10] < 5)
					left_y_c4 += 10;
			}
			if (left_y_c3 != 0 && left_y_c4 != 0) {
				left_y_c3 = ey_mid / 10 * 10 + left_y_c3;
				left_y_c4 = ey_mid / 10 * 10 - left_y_c4;
			}
		}
		if (player->rect.top < left_y_c3 && player->rect.bottom > left_y_c4) 
			left = true;
	}

	if (top_c == true || top == true) {
		if (top_x_c3 == 0 && top_x_c4 == 0) {
			while (Stage_arr[(ey_mid - 18) / 10][(ex_mid + top_x_c3) / 10] < 5)
				top_x_c3 += 10;
			while (Stage_arr[(ey_mid - 18) / 10][(ex_mid - top_x_c4) / 10] < 5)
				top_x_c4 += 10;
			if (top_x_c3 == 0 && top_x_c4 == 0) {
				while (Stage_arr[(ey_mid - 18) / 10][(rect.left + top_x_c3) / 10] < 5)
					top_x_c3 += 10;
				while (Stage_arr[(ey_mid - 18) / 10][(rect.left - top_x_c4) / 10] < 5)
					top_x_c4 += 10;
			}
			if (top_x_c3 == 0 && top_x_c4 == 0) {
				while (Stage_arr[(ey_mid - 18) / 10][(rect.right + top_x_c3) / 10] < 5)
					top_x_c3 += 10;
				while (Stage_arr[(ey_mid - 18) / 10][(rect.right - top_x_c4) / 10] < 5)
					top_x_c4 += 10;
			}
			if (top_x_c3 != 0 && top_x_c4 != 0) {
				top_x_c3 = ex_mid / 10 * 10 + top_x_c3;
				top_x_c4 = ex_mid / 10 * 10 - top_x_c4;
			}
		}
		if (player->rect.left < top_x_c3 && player->rect.right > top_x_c4) 
			top = true;
	}

	if (bottom_c == true || bottom == true) {
		if (bottom_x_c3 == 0 && bottom_x_c4 == 0) {
			while (Stage_arr[(ey_mid + 18) / 10][(ex_mid + bottom_x_c3) / 10] < 5)
				bottom_x_c3 += 10;
			while (Stage_arr[(ey_mid + 18) / 10][(ex_mid - bottom_x_c4) / 10] < 5)
				bottom_x_c4 += 10;
			if (bottom_x_c3 == 0 && bottom_x_c4 == 0) {
				while (Stage_arr[(ey_mid + 18) / 10][(rect.left + bottom_x_c3) / 10] < 5)
					bottom_x_c3 += 10;
				while (Stage_arr[(ey_mid + 18) / 10][(rect.left - bottom_x_c4) / 10] < 5)
					bottom_x_c4 += 10;
			}
			if (bottom_x_c3 == 0 && bottom_x_c4 == 0) {
				while (Stage_arr[(ey_mid + 18) / 10][(rect.right + bottom_x_c3) / 10] < 5)
					bottom_x_c3 += 10;
				while (Stage_arr[(ey_mid + 18) / 10][(rect.right - bottom_x_c4) / 10] < 5)
					bottom_x_c4 += 10;
			}
			if (bottom_x_c3 != 0 && bottom_x_c4 != 0) {
				bottom_x_c3 = ex_mid / 10 * 10 + bottom_x_c3;
				bottom_x_c4 = ex_mid / 10 * 10 - bottom_x_c4;
			}
		}
		if (player->rect.left < bottom_x_c3 && player->rect.right > bottom_x_c4) 
			bottom = true;
	}
}
void Police::AI() {
	if (Stage_arr[(rect.bottom - 3) / 10][(rect.left + 3) / 10] == 50 && Stage_arr[(rect.top + 3) / 10][(rect.right - 3) / 10] == 50 &&
		Stage_arr[(rect.bottom - 3) / 10][(rect.left + 3) / 10] == 50 && Stage_arr[(rect.top + 3) / 10][(rect.right - 3) / 10] == 50 && clock() > delay + 50) {
			x = 0;
			y = -120;
			Dw = 0;
			Uw = 1;
			delay = clock();
	} if (Stage_arr[(rect.top + 3) / 10][(rect.left + 3) / 10] == 51 && Stage_arr[(rect.bottom - 3) / 10][(rect.right - 3) / 10] == 51 && 
		Stage_arr[(rect.top + 3) / 10][(rect.left + 3) / 10] == 51 && Stage_arr[(rect.bottom - 3) / 10][(rect.right - 3) / 10] == 51 && clock() > delay + 50) {
			x = 0;
			y = 120;
			Dw = 1;
			Uw = 0;
			delay = clock();
	} if (Stage_arr[(rect.bottom - 3) / 10][(rect.right - 3) / 10] == 52 && Stage_arr[(rect.top + 3) / 10][(rect.left + 3) / 10] == 52 &&
		Stage_arr[(rect.bottom - 3) / 10][(rect.right - 3) / 10] == 52 && Stage_arr[(rect.top + 3) / 10][(rect.left + 3) / 10] == 52 && clock() > delay + 50) {
			x = -120;
			y = 0;
			Dw = 0;
			Uw = 0;
			walk->scale = D3DXVECTOR2(1,1);
			delay = clock();
	} if (Stage_arr[(rect.top + 3) / 10][(rect.right - 3) / 10] == 53 && Stage_arr[(rect.top + 3) / 10][(rect.left + 3) / 10] == 53 && 
		Stage_arr[(rect.bottom - 3) / 10][(rect.right - 3) / 10] == 53 && Stage_arr[(rect.bottom - 3) / 10][(rect.left + 3) / 10] == 53 && clock() > delay + 50) {
			x = 120;
			y = 0;
			Dw = 0;
			Uw = 0;
			walk->scale = D3DXVECTOR2(-1,1);
			delay = clock();
	}
}
void Police::Return(float eTime) {
	if (save == TRUE) {
		if (save_ch == FALSE) {
			save_tel = clock();
			save_ch++;
		}
		Collision();

		if (left == true || right == true || top == true || bottom == true) {
			if (left == TRUE) 
				Left();
			else if (right == TRUE) 
				Right();
			else if (top == TRUE) 
				Up();
			else if (bottom == TRUE) 
				Down();
		} else {
			if (rect.left > save_x && left_c == FALSE) 
				x = -140;
			else if (rect.left < save_x && right_c == FALSE) 
				x = 140;
			if (abs(save_x - rect.left) < 2) 
				x = 0;

			if (rect.top > save_y && top_c == FALSE) 
				y = -140;
			else if (rect.top < save_y && bottom_c == FALSE) 
				y = 140;

			if (abs(save_y - rect.top) < 2) 
				y = 0;

			save_pos.left = pos.x + (x * eTime);
			save_pos.right = save_pos.left + 30;
			save_pos.top = pos.y + (y * eTime);
			save_pos.bottom = save_pos.top + 30;

			if ((Stage_arr[(save_pos.top - 3) / 10][(save_pos.left - 3) / 10] >= 5 && 
				Stage_arr[(save_pos.bottom + 3) / 10][(save_pos.left - 3) / 10] >= 5))
				left_c = FALSE;
			if (Stage_arr[(save_pos.top - 3) / 10][(save_pos.right + 3) / 10] >= 5 && 
				Stage_arr[(save_pos.bottom + 3) / 10][(save_pos.right + 3) / 10] >= 5)
				right_c = FALSE;
			if (Stage_arr[(save_pos.top - 3) / 10][(save_pos.left - 3) / 10] >= 5 && 
				Stage_arr[(save_pos.top - 3) / 10][(save_pos.right + 3) / 10] >= 5)
				top_c = FALSE;
			if (Stage_arr[(save_pos.bottom + 3) / 10][(save_pos.left - 3) / 10] >= 5 && 
				Stage_arr[(save_pos.bottom + 3) / 10][(save_pos.right + 3) / 10] >= 5)
				bottom_c = FALSE;

			if ((Stage_arr[save_pos.top / 10][(save_pos.left) / 10] < 5 || 
				Stage_arr[save_pos.bottom / 10][(save_pos.left) / 10] < 5) && x < 0) {
					if (Stage_arr[save_pos.top / 10][(save_pos.right) / 10] >= 5 && 
						Stage_arr[save_pos.bottom / 10][(save_pos.right) / 10] >= 5)
						x = 0;
					left_c = TRUE;
			} if (Stage_arr[save_pos.top / 10][(save_pos.right) / 10] < 5 || 
				Stage_arr[save_pos.bottom / 10][(save_pos.right) / 10] < 5 && x > 0) {
					if (Stage_arr[save_pos.top / 10][(save_pos.left) / 10] >= 5 && 
						Stage_arr[save_pos.bottom / 10][(save_pos.left) / 10] >= 5)
						x = 0;
					right_c = TRUE;
			} if ((Stage_arr[(save_pos.top) / 10][(save_pos.left) / 10] < 5 || 
				Stage_arr[(save_pos.top) / 10][(save_pos.right) / 10] < 5) && y < 0) {
					if (Stage_arr[(save_pos.bottom) / 10][(save_pos.left) / 10] >= 5 && 
						Stage_arr[(save_pos.bottom) / 10][(save_pos.right)] >= 5)
						y = 0;
					top_c = TRUE;
			} if ((Stage_arr[(save_pos.bottom) / 10][(save_pos.left) / 10] < 5 || 
				Stage_arr[(save_pos.bottom) / 10][(save_pos.right) / 10] < 5) && y > 0) {
					if (Stage_arr[(save_pos.top) / 10][(save_pos.left) / 10] >= 5 && 
						Stage_arr[(save_pos.top) / 10][(save_pos.right) / 10] >= 5)
						y = 0;
					bottom_c = TRUE;
			}

			Collision();

			if ((bottom_c == true && right_c == true && ey_mid < save_y && ex_mid < save_x && 
				(bottom_x_c3 > rect.left && bottom_x_c4 < rect.left) || (bottom_x_c3 > rect.right && bottom_x_c4 < rect.right)) ||
				(bottom_c == true && left_c == true && ey_mid < save_y && ex_mid > save_x && 
				(bottom_x_c3 > rect.left && bottom_x_c4 < rect.left) || (bottom_x_c3 > rect.right && bottom_x_c4 < rect.right)) ||
				(top_c == true && right_c == true && ey_mid > save_y && ex_mid < save_x && 
				(top_x_c3 > rect.left && top_x_c4 < rect.left) || (top_x_c3 > rect.right && top_x_c4 < rect.right)) ||
				(top_c == true && left_c == true && ey_mid > save_y && ex_mid > save_x && 
				(top_x_c3 > rect.left && top_x_c4 < rect.left) || (top_x_c3 > rect.right && top_x_c4 < rect.right))) 
				x = savex, y = 0;

			else if ((bottom_c == true && right_c == true && ey_mid < save_y && ex_mid < save_x) ||
				(bottom_c == true && left_c == true && ey_mid < save_y && ex_mid > save_x) ||
				(top_c == true && right_c == true && ey_mid > save_y && ex_mid < save_x) ||
				(top_c == true && left_c == true && ey_mid > save_y && ex_mid > save_x)) 
				y = savey, x = 0;

			if (check_r == true && right_c == false)
				x = 150, y = 0, check_r = false;
			if (check_l == true && left_c == false)
				x = -150, y = 0, check_l = false;
			if (check_u == true && top_c == false)
				x = 0, y = -150, check_u = false;
			if (check_d == true && bottom_c == false)
				x = 0, y = 150, check_d = false;

			if (abs(save_x - pos.x) < 2&& abs(save_y - pos.y) < 2) {
				chase = FALSE;
				x = save_gx;
				y = save_gy;
				save = FALSE;
				save_ch = FALSE;
				right_c = left_c = top_c = bottom_c = 0;
			} if (save_tel + 2000 < clock()) {
				chase = FALSE;
				x = save_gx, y = save_gy;
				save = FALSE;
				pos.x = save_x, pos.y = save_y;
				save_ch = FALSE;
			}
		}
	}
}
void Police::Up() {
	y = 0;
	top_x_c3 = top_x_c4 = 0;
	if (top_x_c1 == 0 && top_x_c2 == 0)
	{
		while (Stage_arr[(ey_mid - 18) / 10][(ex_mid + top_x_c1) / 10] < 5) {
			top_x_c1 += 10;
			if (Stage_arr[(ey_mid) / 10][(ex_mid + top_x_c1) / 10] >= 5)
				top_r = false;
			else 
				top_r = true;
		}
		while (Stage_arr[(ey_mid - 18) / 10][(ex_mid - top_x_c2) / 10] < 5) {
			top_x_c2 += 10;
			if (Stage_arr[(ey_mid) / 10][(ex_mid -  top_x_c2) / 10] >= 5)
				top_l = false;
			else 
				top_l = true;
		}
	}
	if (top_x_c1 > top_x_c2) x = -140;
	else x = 140;

	if(top_r == TRUE)
		x = -140;
	if(top_l == TRUE)
		x = 140;

	if ((Stage_arr[(ey_mid - 18) / 10][(ex_mid - 18) / 10] >= 5 && 
		Stage_arr[(ey_mid - 18) / 10][(ex_mid + 18) / 10] >= 5) ||
		(Stage_arr[(ey_mid - 18) / 10][(ex_mid - 18) / 10] < 5 &&  
		Stage_arr[(ey_mid - 18) / 10][(ex_mid + 18) / 10] < 5)) {
			check_u = true;
			top = FALSE;
			if (top_x_c1 > top_x_c2) 
				x = -150;
			else 
				x = 150;
			if (top_x_c1 == 0) 
				x = 150;
			else if (top_x_c2 == 0)  
				x = -150;
			top_x_c1 = top_x_c2 = top_x_c3 = top_x_c4 = 0;
			top_r = top_l = 0;
	}
}
void Police::Down() {
	y = 0;
	bottom_x_c3 = bottom_x_c4 = 0;
	if (bottom_x_c1 == 0 && bottom_x_c2 == 0) {
		while (Stage_arr[(ey_mid + 18) / 10][(ex_mid + bottom_x_c1) / 10] < 5) {
			bottom_x_c1 += 10;
			if (Stage_arr[(ey_mid) / 10][(ex_mid + bottom_x_c1) / 10] >= 5)
				bottom_r = false;
			else 
				bottom_r = true;
		}
		while (Stage_arr[(ey_mid + 18) / 10][(ex_mid - bottom_x_c2) / 10] < 5) {
			bottom_x_c2 += 10;
			if (Stage_arr[(ey_mid) / 10][(ex_mid - bottom_x_c2) / 10] >= 5)
				bottom_l = false;
			else 
				bottom_l = true;
		}
	}
	if (bottom_x_c1 > bottom_x_c2) x = -140;
	else x = 140;

	if(bottom_r == TRUE)
		x = -140;
	if(bottom_l == TRUE)
		x = 140;

	if ((Stage_arr[(ey_mid + 18) / 10][(ex_mid - 18) / 10] >= 5 && 
		Stage_arr[(ey_mid + 18) / 10][(ex_mid + 18) / 10] >= 5) ||
		(Stage_arr[(ey_mid) / 10][(ex_mid - 18) / 10] < 5 || 
		Stage_arr[(ey_mid) / 10][(ex_mid + 18) / 10] < 5)) {
			check_d = true;
			bottom = FALSE;
			if (bottom_x_c1 > bottom_x_c2) 
				x = -150;
			else 
				x = 150;
			if (bottom_x_c1 == 0) 
				x = 150;
			else if (bottom_x_c2 == 0)  
				x = -150;
			bottom_x_c1 = bottom_x_c2 = bottom_x_c3 = bottom_x_c4 = 0;
			bottom_r = bottom_l = 0;
	}
}
void Police::Left() {
	x = 0;
	left_y_c3 = left_y_c4 = 0;
	if (left_y_c1 == 0 && left_y_c2== 0) {
		while (Stage_arr[(ey_mid + left_y_c1) / 10][(ex_mid - 18) / 10] < 5) {
			left_y_c1 += 10;
			if (Stage_arr[(ey_mid + left_y_c1) / 10][(ex_mid) / 10] >= 5)
				left_d = false;
			else 
				left_d = true;
		}
		while (Stage_arr[(ey_mid - left_y_c2) / 10][(ex_mid - 18) / 10] < 5) {
			left_y_c2 += 10;
			if (Stage_arr[(ey_mid - left_y_c2) / 10][(ex_mid) / 10] >= 5)
				left_u = false;
			else 
				left_u = true;
		}
	}
	if (left_y_c1 > left_y_c2) y = -140;
	else y = 140;

	if(left_d == TRUE)
		y = -140;
	if(left_u == TRUE)
		y = 140;

	if ((Stage_arr[(ey_mid - 18) / 10][(ex_mid - 18) / 10] >= 5 && 
		Stage_arr[(ey_mid + 18) / 10][(ex_mid - 18) / 10] >= 5) ||
		(Stage_arr[(ey_mid - 18) / 10][(ex_mid) / 10] < 5 || 
		Stage_arr[(ey_mid + 18) / 10][(ex_mid) / 10] < 5)) {
			check_l = true;
			left = FALSE;
			if (left_y_c1 > left_y_c2) 
				x = -150;
			else 
				x = 150;
			if (left_y_c1 == 0) 
				x = 150;
			else if (left_y_c2 == 0)  
				x = -150;
			left_y_c1 = left_y_c2 = left_y_c3 = left_y_c4 = 0;
			left_d = left_u = 0;
	}
}
void Police::Right() {
	x = 0;
	right_y_c3 = right_y_c4 = 0;
	if (right_y_c1 == 0 && right_y_c2 == 0) {
		while (Stage_arr[(ey_mid + right_y_c1) / 10][(ex_mid + 18) / 10] < 5) {
			right_y_c1 += 10;
			if (Stage_arr[(ey_mid + right_y_c1) / 10][(ex_mid) / 10] >= 5)
				right_d = FALSE;
			else 
				right_d = TRUE;
		}
		while (Stage_arr[(ey_mid - right_y_c2) / 10][(ex_mid + 18) / 10] < 5) {
			right_y_c2 += 10;
			if (Stage_arr[(ey_mid - right_y_c2) / 10][(ex_mid) / 10] >= 5)
				right_u = FALSE;
			else 
				right_u = TRUE;
		}
	}
	if (right_y_c1 > right_y_c2) y = -140;
	else y = 140;

	if(right_d == TRUE)
		y = -150;
	if(right_u == TRUE)
		y = 150;

	if ((Stage_arr[(ey_mid - 18) / 10][(ex_mid + 18) / 10] >= 5 &&
		Stage_arr[(ey_mid + 18) / 10][(ex_mid + 18) / 10] >= 5) ||
		(Stage_arr[(ey_mid - 18) / 10][(ex_mid) / 10] < 5 ||
		Stage_arr[(ey_mid + 18) / 10][(ex_mid) / 10] < 5)) {
			check_r = true;
			right = FALSE;
			if (right_y_c1 > right_y_c2) 
				y= -150;
			else 
				y = 150;
			if (right_y_c1 == 0) 
				y = 150;
			else if (right_y_c2 == 0)  
				y = -150;
			right_y_c1 = right_y_c2 = right_y_c3 = right_y_c4 = 0;
			right_d = right_u = FALSE;
	}
}