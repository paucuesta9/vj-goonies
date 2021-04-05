#ifndef _INSTRUCTIONS_INCLUDE
#define _INSTRUCTIONS_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Text.h"

class Instructions
{

public:
	Instructions();
	~Instructions();

	void init();
	void update(int deltaTime);
	void render();

private:
	void initShaders();
	void printTexts();

private:
	ShaderProgram texProgram;
	glm::mat4 projection;
	float currentTime;
	Text* texts;
};


#endif // _CREDITS_INCLUDE
