#ifndef _AUDIO_INCLUDE
#define _AUDIO_INCLUDE

#include <string>

class Audio
{
public:
	static Audio &instance()
	{
		static Audio A;

		return A;
	}
	Audio();
	~Audio();
	void playMusic(char* url);
	void playIntro();
	void playMenu();
	void playLevel(int level);
	void playWin();
	void playGameOver();

	void resumeMusic();
	void pauseMusic();
	void stopMusic();

	void exitGameEffect();
	void hoverEffect();
	void clickEffect();
	void stopEffect();
	void jumpEffect();
	void getKeyEffect();
	void killEffect();
	void getBagEffect();
	void openDoorEffect();
	void rescueFriedEffect();
	void hitGotaEffect();
	void hurtedEffect();
	void bornEnemiesEffect();
	void flotarEffect();
	void getPotionEffect();
	void changeScreenEffect();
	void waterHurtEffect();

private:
	void init();
};

#endif // _AUDIO_INCLUDE