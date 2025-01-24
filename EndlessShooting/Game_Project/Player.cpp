#include "Player.h"

Player::Player(Game2D* game)
{
	this->game = game;

	bullet_manager = new BulletManager();

	dot_datas = new DotDatas();
	dot_image = new DotSystem(dot_datas->player_dots, 2.0f);

	pos = { 0.f, 0.f };
	degree = 0.f;
	vel = 0.f;
	acc = 175.f;

	is_move = false;

	col_rad = dot_image->getDotSize() * (dot_image->getDotImageWidth() / 2.f) * 0.5f;

	shoot_delay = 0.3f;
}

Player::~Player()
{
	delete dot_datas;
	delete dot_image;
	delete bullet_manager;
}

void Player::update(float dt)
{

	atan_dx = (-(game->w / 2) + game->getCursorPos(false).x) - (pos.x + dot_image->getCenter().x);
	atan_dy = ((game->h / 2) - game->getCursorPos(false).y) - (pos.y + dot_image->getCenter().y);

	degree = 180.f * atan2(atan_dy, atan_dx) / 3.141592f - 90.f;

	distance = sqrt((atan_dx * atan_dx) + (atan_dy * atan_dy));

	if (distance <= 120.f)
	{
		is_move = false;
	}
	
	else
	{
		is_move = true;
	}


	if (is_move)
	{
		if (vel <= 350.f)
		{
			vel += acc * dt;
		}
	}

	else
	{
		if (vel > 0.f)
		{
			vel -= acc * 4.f * dt;
		}
		else if (vel <= 0.f)
		{
			vel = 0.f;
		}
	}

	if (shoot_delay < 0.09f)
	{
		shoot_delay += dt;
	}

	if ((shoot_delay >= 0.09f) && game->isKeyReleased(GLFW_KEY_SPACE))
	{
		bullet = new Bullet();
		bullet->SetPos(pos.x, pos.y);
		bullet->SetDeg(degree);
		bullet->SetCenter(dot_image->getCenter().x, dot_image->getCenter().y);
		bullet_manager->push(bullet);

		bullet = new Bullet();
		bullet->SetPos(pos.x - 8 * sin(3.141592f * (degree + 90) / 180.f), pos.y + 8 * cos(3.141592f * (degree + 90) / 180.f));
		bullet->SetDeg(degree);
		bullet->SetCenter(dot_image->getCenter().x, dot_image->getCenter().y);
		bullet_manager->push(bullet);
		
		bullet = new Bullet();
		bullet->SetPos(pos.x + 8 * sin(3.141592f * (degree + 90) / 180.f), pos.y - 8 * cos(3.141592f * (degree + 90) / 180.f));
		bullet->SetDeg(degree);
		bullet->SetCenter(dot_image->getCenter().x, dot_image->getCenter().y);
		bullet_manager->push(bullet);

		shoot_delay = 0.f;
	}


	pos.x += vel * dt * cos(atan2(atan_dy, atan_dx));
	pos.y += vel * dt * sin(atan2(atan_dy, atan_dx));

	//beginTransformation();
	//{
	//	translate(pos.x + dot_image->getCenter().x, pos.y + dot_image->getCenter().y);
	//	drawWiredCircle(Colors::green, col_rad);
	//}
	//endTransformation();
		
	bullet_manager->update(dt);

	beginTransformation();
	{
		translate(pos);
		translate(dot_image->getCenter());
		rotate(degree);
		translate(-dot_image->getCenter());
		dot_image->render();
	}
	endTransformation();

	
}
