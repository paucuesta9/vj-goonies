#include "Audio.h"
#include <Windows.h>
#include <mmsystem.h>
#include <iostream>
#include <irrKlang.h>
#include <vector>
using namespace irrklang;



ISoundEngine* engineMusic;
ISoundEngine* engineEffects;
ISound* music;
ISound* effect;

Audio::Audio()
{
	init();
}


Audio::~Audio()
{
	music->drop();
	engineEffects->drop();
	engineMusic->drop();

}

void Audio::init() {
	engineMusic = createIrrKlangDevice();
	engineEffects = createIrrKlangDevice();
}

void Audio::playMusic(char* url)
{
	engineMusic->stopAllSounds();
	music = engineMusic->play2D(url, true, false, true);
	music->setVolume(0.1f);
}

void Audio::playIntro()
{
	engineMusic->stopAllSounds();
	music = engineMusic->play2D("sound/intro.mp3", false, false, true);
	music->setVolume(0.1f);
}

void Audio::playMenu()
{
	engineMusic->stopAllSounds();
	music = engineMusic->play2D("sound/menu.ogg", false, false, true);
	music->setVolume(0.1f);
}

void Audio::playLevel(int level) {
	engineMusic->stopAllSounds();
	switch (level)
	{
	case 1:
		music = engineMusic->play2D("sound/level1.ogg", true, false, true);
		break;
	case 2:
		music = engineMusic->play2D("sound/level2.ogg", true, false, true);
		break;
	case 3:
		music = engineMusic->play2D("sound/level3.ogg", true, false, true);
		break;
	case 4:
		music = engineMusic->play2D("sound/level4.ogg", true, false, true);
		break;
	case 5:
		music = engineMusic->play2D("sound/level5.ogg", true, false, true);
		break;
	default:
		break;
	}
	music->setVolume(0.1f);
}

void Audio::playWin() 
{
	engineMusic->stopAllSounds();
	music = engineMusic->play2D("sound/win.wav", false, false, true);
	music->setVolume(0.3f);
}

void Audio::playGameOver()
{
	engineMusic->stopAllSounds();
	music = engineMusic->play2D("sound/game_over.ogg", false, false, true);
	music->setVolume(0.3f);
}

void Audio::resumeMusic() {
	engineMusic->setAllSoundsPaused(false);
}


void Audio::pauseMusic() {
	engineMusic->setAllSoundsPaused();
}

void Audio::stopMusic() {
	engineMusic->stopAllSounds();
}

void Audio::hoverEffect() {
	effect = engineEffects->play2D("sound/hover.wav", false, false, true);
	effect->setVolume(0.5f);
}

void Audio::clickEffect() {
	effect = engineEffects->play2D("sound/click.wav", false, false, true);
	effect->setVolume(0.5f);
}

void Audio::stopEffect() {
	engineEffects->stopAllSounds();
}

void Audio::exitGameEffect() {
	effect = engineEffects->play2D("sound/bye.mp3", false, false, true);
	effect->setVolume(0.2f);
}

void Audio::jumpEffect() {
	effect = engineEffects->play2D("sound/salto.wav", false, false, true);
	effect->setVolume(0.2f);
}

void Audio::getKeyEffect() {
	effect = engineEffects->play2D("sound/key.wav", false, false, true);
	effect->setVolume(0.2f);
}

void Audio::killEffect() {
	effect = engineEffects->play2D("sound/kill.wav", false, false, true);
	effect->setVolume(0.2f);
}

void Audio::getBagEffect() {
	effect = engineEffects->play2D("sound/take_bag.wav", false, false, true);
	effect->setVolume(0.2f);
}

void Audio::openDoorEffect() {
	effect = engineEffects->play2D("sound/open_door.wav", false, false, true);
	effect->setVolume(0.2f);
}

void Audio::rescueFriedEffect() {
	effect = engineEffects->play2D("sound/rescue_friend.wav", false, false, true);
	effect->setVolume(0.2f);
}

void Audio::hitGotaEffect() {
	effect = engineEffects->play2D("sound/gota.wav", false, false, true);
	effect->setVolume(0.2f);
}

void Audio::hurtedEffect() {
	effect = engineEffects->play2D("sound/hurt.wav", false, false, true);
	effect->setVolume(0.2f);
}

void Audio::bornEnemiesEffect() {
	effect = engineEffects->play2D("sound/born_enemies.wav", false, false, true);
	effect->setVolume(0.2f);
}

void Audio::flotarEffect() {
	effect = engineEffects->play2D("sound/flotar.wav", false, false, true);
	effect->setVolume(0.2f);
}

void Audio::getPotionEffect() {
	effect = engineEffects->play2D("sound/potion.wav", false, false, true);
	effect->setVolume(0.2f);
}

void Audio::changeScreenEffect() {
	effect = engineEffects->play2D("sound/change_screen.wav", false, false, true);
	effect->setVolume(0.5f);
}

void Audio::waterHurtEffect() {
	effect = engineEffects->play2D("sound/water_hurt.wav", false, false, true);
	effect->setVolume(0.2f);
}