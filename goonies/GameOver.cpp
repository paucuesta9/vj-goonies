#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "GameOver.h"
#include "Game.h"

GameOver::GameOver()
{

}

GameOver::~GameOver()
{

}

void GameOver::init() {
	initShaders();
	currentTime = 0.0f;
	rPressed = false;
	rReleased = false;
	printGameOverText();
	printTextsActions();
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
}

void GameOver::printGameOverText() {
	textGameOver = new Text();
	textGameOver->init(glm::vec2(float(160), float(200)), texProgram, 4, 1, "GAME OVER!");
}

void GameOver::printTextsActions() {
	textRestart = new Text();
	textRestart->init(glm::vec2(float(136), float(300)), texProgram, 2, 0, "PRESS R TO RESTART GAME");
	textOr = new Text();
	textOr->init(glm::vec2(float(312), float(330)), texProgram, 1, 0, "OR");
	textGoMenu = new Text();
	textGoMenu->init(glm::vec2(float(136), float(350)), texProgram, 2, 0, "PRESS ESC TO GO TO MENU");
}


void GameOver::update(int deltaTime) {
	currentTime += deltaTime;

	textGameOver->update(deltaTime);
	textRestart->update(deltaTime);
	textOr->update(deltaTime);
	textGoMenu->update(deltaTime);
}

void GameOver::render() {
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	textGameOver->render();
	textRestart->render();
	textOr->render();
	textGoMenu->render();
}

void GameOver::initShaders()
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

