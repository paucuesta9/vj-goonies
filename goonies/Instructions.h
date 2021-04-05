#ifndef _INSTRUCTIONS_INCLUDE
#define _INSTRUCTIONS_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Text.h"
#include "Object.h"

class Instructions
{

public:
	Instructions();
	~Instructions();

	void init();
	void update(int deltaTime);
	void render();

	void hover(int which, bool isHover);
	void clicked(int which);

private:
	void initShaders();
	void initBackground();
	void initSprites();
	void printTexts();

private:
	ShaderProgram texProgram;
	glm::mat4 projection;
	float currentTime;
	Texture spritesheetBackground, spritesheetFriend, spritesheetMoveKeys, spritesheetKeys, spritesheetAnimationLiana, spritesheetCabezaFlotante, spritesheetEsqueleto, spritesheetMoveScreen;
	Sprite* friends, *background, *moveKeys, *keys, *animationLiana, *bigKeys, *cabezaFlotante, *esqueleto, *moveScreen;
	Object* object;
	Text* texts;
	int currentScreen;
	bool pressedLeft, pressedRight, releasedLeft, releasedRight;
};


#endif // _CREDITS_INCLUDE
