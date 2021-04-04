#ifndef _PAUSE_INCLUDE
#define _PAUSE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Text.h"

class Pause
{

public:
	Pause();
	~Pause();

	void init();
	void update(int deltaTime);
	void render();

private:
	void initShaders();
	void printPauseText();
	void printTextsActions();

private:
	ShaderProgram texProgram;
	glm::mat4 projection;
	float currentTime;
	Text* textPaused, *textReturnToGame;
};


#endif // _PAUSE_INCLUDE

