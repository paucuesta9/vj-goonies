#ifndef _MENU_INFERIOR_INCLUDE
#define _MENU_INFERIOR_INCLUDE


#include "Sprite.h"


class MenuInferior
{

public:
	~MenuInferior();
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);

	void update(int deltaTime);
	void render();

	void setPowerUp(int powerUp);
	void savedNewFriend();

private:
	glm::ivec2 tileMapDispl;
	Texture spritesheetPowerUps, spriteSheetSavedFriends;
	Sprite* spritePowerUps, *spriteSavedFriends;
	int friendsSaved, activePowerUps;
};


#endif // _MENU_INFERIOR_INCLUDE

