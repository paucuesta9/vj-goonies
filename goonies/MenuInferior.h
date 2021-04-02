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

	void setPowerUp(int powerUp, bool active);

private:
	glm::ivec2 tileMapDispl;
	Texture spritesheetPowerUps;
	Sprite* spritePowerUps;
};


#endif // _MENU_INFERIOR_INCLUDE

