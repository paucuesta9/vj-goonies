#ifndef _MENU_SUPERIOR_INCLUDE
#define _MENU_SUPERIOR_INCLUDE

#include "Sprite.h"
#include "Text.h"


class MenuSuperior
{

public:
	~MenuSuperior();
	void init(glm::ivec2 pos, ShaderProgram& shaderProgram);
	void restart();

	void update(int deltaTime);
	void render();
	void calculateVitExp(int vitExp, int option);
	void setScreen(int scene, int screen);
	void setPoints(int points);

private:
	glm::ivec2 tileMapDispl;
	ShaderProgram shader;
	Texture spritesheetVitExp;
	Sprite* spriteVitExp;
	Text* text;
	int high;
};


#endif // _MENU_SUPERIOR_INCLUDE

