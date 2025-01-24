#pragma once
#include "fmod.hpp"

using namespace FMOD;

enum SOUND_ID {
	OPENING_BGM,
	MAIN_BGM,
	EMERGENCY_BGM,
	MOVE_BGM,
	SIREN_BGM,
	WHISTLE_BGM,
	COM_BGM,
	PICK_COIN_BGM,
	OPENDOOR_BGM,
	SOUND_END
};

class SoundMgr {
public:
	SoundMgr();
	~SoundMgr();

	bool NowPlaying[SOUND_END];

	void Update();
	void addSound(int num,char *path);
	void Play(int num);
	void Playis(int num);
	void Stop(int num);
	void SetVolume(int num,float fv);
};