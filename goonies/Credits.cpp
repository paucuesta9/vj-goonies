#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Credits.h"
#include "Game.h"

Credits::Credits()
{

}

Credits::~Credits()
{

}

void Credits::init() {
	initShaders();
	currentTime = 0.0f;
	initSpriteBackground();
	initSpriteLogo();
	printTexts();
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
}

void Credits::printTexts() {
	
}


void Credits::update(int deltaTime) {
	currentTime += deltaTime;
	background->update(deltaTime);
	logo->update(deltaTime);
	texts->update(deltaTime);
}

void Credits::render() {
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	background->render();
	logo->render();
	texts->render();
}

void Credits::initSpriteBackground() {
	spritesheetBackground.loadFromFile("images/creditos.png", TEXTURE_PIXEL_FORMAT_RGBA);
	background = new Sprite();
	background = Sprite::createSprite(glm::ivec2(640, 480), glm::vec2(1.0, 1.0), &spritesheetBackground, &texProgram);
	background->setNumberAnimations(1);

	background->setAnimationSpeed(0, 8);
	background->addKeyframe(0, glm::vec2(0.f, 0.f));

	background->changeAnimation(0);
	background->setPosition(glm::vec2(0, 0));
}

void Credits::initSpriteLogo() {
	spritesheetLogo.loadFromFile("images/logo_goonies.png", TEXTURE_PIXEL_FORMAT_RGBA);
	logo = new Sprite();
	logo = Sprite::createSprite(glm::ivec2(140, 40), glm::vec2(1.0, 1.0), &spritesheetLogo, &texProgram);
	logo->setNumberAnimations(1);

	logo->setAnimationSpeed(0, 8);
	logo->addKeyframe(0, glm::vec2(0.f, 0.f));

	logo->changeAnimation(0);
	logo->setPosition(glm::vec2(180, 64));
	logo->setScale(glm::vec3(2.0f, 2.0f, 0.f));
}

void Credits::initShaders()
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