#ifndef _MENU_SUPERIOR_INCLUDE
#define _MENU_SUPERIOR_INCLUDE

#include "Sprite.h"
#include "Text.h"


class MenuSuperior
{

public:
	~MenuSuperior();
	void init(glm::ivec2 pos, ShaderProgram& shaderProgram);

	void update(int deltaTime);
	void render();
	void calculateVitExp(int vit, int exp);
	void setScreen(int scene, int screen);
	void setPoints(int points);

private:
	glm::ivec2 tileMapDispl;
	Texture spritesheetVitExp;
	Sprite* spriteVitExp;
	Text* text;
	int high;
};


#endif // _MENU_SUPERIOR_INCLUDE

