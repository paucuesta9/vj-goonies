#ifndef _MENU_INFERIOR_INCLUDE
#define _MENU_INFERIOR_INCLUDE

#include <glm/glm.hpp>
#include "Sprite.h"
#include "ShaderProgram.h"


class MenuInferior
{

public:
	~MenuInferior();

	void init();
	void update(int deltaTime);
	void render();
	void initShaders();

	void setPowerUp(int powerUp);
	void savedNewFriend();

private:
	ShaderProgram texProgram;
	Texture spritesheetPowerUps, spriteSheetSavedFriends;
	Sprite* spritePowerUps, *spriteSavedFriends;
	int friendsSaved, activePowerUps;
};


#endif // _MENU_INFERIOR_INCLUDE

