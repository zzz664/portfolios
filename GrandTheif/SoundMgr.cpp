#include "SoundMgr.h"

System *g_pSystem;
Sound *g_pSound[SOUND_END];
Channel *g_pChannel[SOUND_END];

SoundMgr::SoundMgr() {
	System_Create(&g_pSystem);
	g_pSystem->init(20,FMOD_INIT_NORMAL,0);
}
SoundMgr::~SoundMgr() {
	for(int i = 0;i < SOUND_END;i++) {
		g_pSound[i]->release();
	}
	g_pSystem->close();
	g_pSystem->release();
}
void SoundMgr::Update() {
	g_pSystem->update();
}
void SoundMgr::addSound(int num,char *path) {
	g_pSystem->createSound(path,FMOD_HARDWARE,0,&g_pSound[num]);
	SetVolume(num,1.0f);
}
void SoundMgr::Play(int num) {
	g_pSystem->playSound(FMOD_CHANNEL_FREE,g_pSound[num],0,&g_pChannel[num]);
}
void SoundMgr::Playis(int num) {
	g_pChannel[num]->isPlaying(&NowPlaying[num]);
	if(!NowPlaying[num])
		g_pSystem->playSound(FMOD_CHANNEL_FREE,g_pSound[num],0,&g_pChannel[num]);
}
void SoundMgr::Stop(int num) {
	g_pChannel[num]->stop();
}
void SoundMgr::SetVolume(int num,float fv){
	g_pChannel[num]->setVolume(fv);
}