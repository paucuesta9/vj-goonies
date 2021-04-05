#ifndef _CREDITS_INCLUDE
#define _CREDITS_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Text.h"

class Credits
{

public:
	Credits();
	~Credits();

	void init();
	void update(int deltaTime);
	void render();

private:
	void initShaders();
	void printTexts();
	void initSpriteBackground();
	void initSpriteLogo();

private:
	ShaderProgram texProgram;
	glm::mat4 projection;
	Texture spritesheetBackground, spritesheetLogo;
	Sprite* background;
	float currentTime;
	Text* texts;
};


#endif // _CREDITS_INCLUDE
