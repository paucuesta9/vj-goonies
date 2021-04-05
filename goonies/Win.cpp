#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Win.h"
#include "Game.h"

Win::Win()
{

}

Win::~Win()
{

}

void Win::init() {
	initShaders();
	currentTime = 0.0f;
	printWinText();
	printTextsActions();
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
}

void Win::printWinText() {
	textWin = new Text();
	textWin->init(glm::vec2(float(192), float(200)), texProgram, 4, 3, "YOU WIN!");
}

void Win::printTextsActions() {
	textGoMenu = new Text();
	textGoMenu->init(glm::vec2(float(136), float(300)), texProgram, 2, 0, "PRESS ESC TO GO TO MENU");
}


void Win::update(int deltaTime) {
	currentTime += deltaTime;

	textWin->update(deltaTime);
	textGoMenu->update(deltaTime);
}

void Win::render() {
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	textWin->render();
	textGoMenu->render();
}

void Win::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if (!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}

