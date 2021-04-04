#ifndef _INTRO_INCLUDE
#define _INTRO_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Text.h"
#include "Sprite.h"

class Intro
{

public:
	Intro();
	~Intro();

	void init();
	void update(int deltaTime);
	void render();

	bool isFinished();

private:
	void initShaders();
	void initSpriteBackground();
	void initSpriteProfesor();
	void initSpriteKids();
	void initSpriteMalo();

private:
	ShaderProgram texProgram;
	Texture spritesheetBackground, spritesheetProfessor, spritesheetKids, spritesheetMalo;
	glm::mat4 projection;
	float currentTime;
	bool finished;
	Sprite* background, *profesor, *kids, *malo;
	Text* credits;
	int animTime;
	glm::vec2 posProfesor, posMalo;
	glm::vec2 posKid[7];
};


#endif // _PAUSE_INCLUDE

