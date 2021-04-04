#ifndef _GAME_OVER_INCLUDE
#define _GAME_OVER_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Text.h"

class GameOver
{

public:
	GameOver();
	~GameOver();

	void init();
	void update(int deltaTime);
	void render();

private:
	void initShaders();
	void printGameOverText();
	void printTextsActions();

private:
	ShaderProgram texProgram;
	glm::mat4 projection;
	float currentTime;
	Text* textGameOver, *textRestart, *textOr, *textGoMenu;
	bool rPressed, rReleased;
};


#endif // _GAME_OVER_INCLUDE

