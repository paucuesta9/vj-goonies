#ifndef _MENU_SUPERIOR_INCLUDE
#define _MENU_SUPERIOR_INCLUDE

#include "Sprite.h"


class MenuSuperior
{

public:
	~MenuSuperior();
	void init(glm::ivec2 pos, ShaderProgram& shaderProgram);

	void update(int deltaTime);
	void render();
	void calculateVitExp(int vit, int exp);

private:
	glm::ivec2 tileMapDispl;
	Texture spritesheetVitExp;
	Sprite* spriteVitExp;
};


#endif // _MENU_SUPERIOR_INCLUDE

