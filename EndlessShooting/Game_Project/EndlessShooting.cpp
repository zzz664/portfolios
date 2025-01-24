#include "EndlessShooting.h"
#include "SoundEngine_Singleton.h"

EndlessShooting::EndlessShooting()
{
	SOUNDENGINE->createSound("BloodCage.mp3", "background", true);
	SOUNDENGINE->playSound("background");
	player = new Player(this);
	m = new Monster(player->GetPos());
}

EndlessShooting::~EndlessShooting()
{
	delete player;
	delete m;
}

void EndlessShooting::update()
{
	player->update(this->getTimeStep());
	m->update(this->getTimeStep());
}