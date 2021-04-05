#ifndef _WIN_INCLUDE
#define _WIN_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Text.h"

class Win
{

public:
	Win();
	~Win();

	void init();
	void update(int deltaTime);
	void render();

private:
	void initShaders();
	void printWinText();
	void printTextsActions();

private:
	ShaderProgram texProgram;
	glm::mat4 projection;
	float currentTime;
	Text* textWin, * textGoMenu;
};


#endif // _WIN_INCLUDE

