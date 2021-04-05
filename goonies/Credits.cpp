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
	printTexts();
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
}

void Credits::printTexts() {
	texts = new Text[11];
	
	texts[0].init(glm::vec2(float(272), float(100)), texProgram, 1, 0, "DEVELOPED BY");
	texts[1].init(glm::vec2(float(96), float(120)), texProgram, 2, 0, "JUDITH ALMONO AND PAU CUESTA");
	
	texts[2].init(glm::vec2(float(256), float(160)), texProgram, 1, 0, "MAPS DESIGNED BY");
	texts[3].init(glm::vec2(float(96), float(180)), texProgram, 2, 0, "JUDITH ALMONO AND PAU CUESTA");

	texts[4].init(glm::vec2(float(212), float(210)), texProgram, 1, 0, "CHARACTERS MODIFICATIONS BY");
	texts[5].init(glm::vec2(float(96), float(230)), texProgram, 2, 0, "JUDITH ALMONO AND PAU CUESTA");

	texts[6].init(glm::vec2(float(176), float(270)), texProgram, 1, 0, "ORIGINAL TILESHEET AND SPRITESHEETS FROM");
	texts[7].init(glm::vec2(float(152), float(290)), texProgram, 2, 0, "THE SPRITERS RESOURCE");

	texts[8].init(glm::vec2(float(288), float(330)), texProgram, 1, 0, "MUSIC BY");
	texts[9].init(glm::vec2(float(216), float(350)), texProgram, 2, 0, "WWW.VGMPF.COM");

	texts[10].init(glm::vec2(float(136), float(450)), texProgram, 2, 1, "PRESS ESC TO GO TO MENU");
}


void Credits::update(int deltaTime) {
	currentTime += deltaTime;
	background->update(deltaTime);
	for (int i = 0; i < 11; ++i)
		texts[i].update(deltaTime);
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
	for (int i = 0; i < 11; ++i)
		texts[i].render();
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