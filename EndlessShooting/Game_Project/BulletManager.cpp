#include "BulletManager.h"

BulletManager::BulletManager()
{

}

BulletManager::~BulletManager()
{
	for (std::list<Bullet*>::iterator it = bullet_list.begin(); it != bullet_list.end(); ++it)
	{
		if ((*it)->IsErase())
		{
			delete (*it);
			it = bullet_list.erase(it);
		}
	}

	bullet_list.clear();
}

void BulletManager::update(float dt)
{
	for (std::list<Bullet*>::iterator it = bullet_list.begin(); it != bullet_list.end(); ++it)
	{
		(*it)->update(dt);

		if ((*it)->IsErase())
		{
			delete (*it);
			it = bullet_list.erase(it);
			if (it == bullet_list.end())
			{
				break;
			}
		}
	}
}

void BulletManager::push(Bullet* bullet)
{
	bullet_list.push_back(bullet);
}