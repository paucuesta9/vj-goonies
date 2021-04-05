#ifndef _MAIN_MENU_INCLUDE
#define _MAIN_MENU_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Text.h"
#include "Sprite.h"

class MainMenu
{

public:
	MainMenu();
	~MainMenu();

	void init();
	void update(int deltaTime);
	void render();
	void hover(int textIndex, int isHover);

private:
	void initShaders();
	void initSpriteBackground();
	void initSpriteLogo();
	void printTextsActions();

private:
	ShaderProgram texProgram;
	Texture spritesheetBackground, spritesheetLogo;
	Sprite *background, *logo;
	glm::mat4 projection;
	float currentTime;
	Text* textPlay, * textInstructions, * textCredits, * textExit;
};


#endif // _MAIN_MENU_INCLUDE
