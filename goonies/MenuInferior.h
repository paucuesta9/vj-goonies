#ifndef _MENU_INFERIOR_INCLUDE
#define _MENU_INFERIOR_INCLUDE


#include "Sprite.h"
#include "Text.h"


class MenuInferior
{

public:
	~MenuInferior();
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);

	void update(int deltaTime);
	void render();

	void setPowerUp(int powerUp);
	void deletePowerUp();
	void savedNewFriend();
	void setKey(bool haveKey);
	void setInit();

private:
	glm::ivec2 tileMapDispl;
	Texture spritesheetPowerUps, spriteSheetSavedFriends, spritesheetKey;
	Sprite* spritePowerUps, *spriteSavedFriends, *spriteKey;
	Text* text;
	int friendsSaved, activePowerUps;
};


#endif // _MENU_INFERIOR_INCLUDE

