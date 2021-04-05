#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "MainMenu.h"
#include "Game.h"

MainMenu::MainMenu()
{

}

MainMenu::~MainMenu()
{

}

void MainMenu::init() {
	initShaders();
	currentTime = 0.0f;
	initSpriteBackground();
	initSpriteLogo();
	printTextsActions();
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
}

void MainMenu::printTextsActions() {
	textPlay = new Text();
	textPlay->init(glm::vec2(float(288), float(160)), texProgram, 2, 0, "PLAY");
	textInstructions = new Text();
	textInstructions->init(glm::vec2(float(224), float(224)), texProgram, 2, 0, "INSTRUCTIONS");
	textCredits = new Text();
	textCredits->init(glm::vec2(float(264), float(288)), texProgram, 2, 0, "CREDITS");
	textExit = new Text();
	textExit->init(glm::vec2(float(288), float(352)), texProgram, 2, 0, "EXIT");
}


void MainMenu::update(int deltaTime) {
	currentTime += deltaTime;

	background->update(deltaTime);
	logo->update(deltaTime);
	textPlay->update(deltaTime);
	textInstructions->update(deltaTime);
	textCredits->update(deltaTime);
	textExit->update(deltaTime);
}

void MainMenu::render() {
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	background->render();
	logo->render();
	textPlay->render();
	textInstructions->render();
	textCredits->render();
	textExit->render();
}

void MainMenu::initSpriteBackground() {
	spritesheetBackground.loadFromFile("images/menu.png", TEXTURE_PIXEL_FORMAT_RGBA);
	background = new Sprite();
	background = Sprite::createSprite(glm::ivec2(640, 480), glm::vec2(1.0, 1.0), &spritesheetBackground, &texProgram);
	background->setNumberAnimations(1);

	background->setAnimationSpeed(0, 8);
	background->addKeyframe(0, glm::vec2(0.f, 0.f));
	
	background->changeAnimation(0);
	background->setPosition(glm::vec2(0, 0));
}

void MainMenu::initSpriteLogo() {
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

void MainMenu::hover(int textIndex, int isHover) {
	switch (textIndex)
	{
	case 0:
		textPlay->init(glm::vec2(float(288), float(160)), texProgram, 2, isHover, "PLAY");
		break;
	case 1:
		textInstructions->init(glm::vec2(float(224), float(224)), texProgram, 2, isHover, "INSTRUCTIONS");
		break;
	case 2:
		textCredits->init(glm::vec2(float(264), float(288)), texProgram, 2, isHover, "CREDITS");
		break;
	case 3:
		textExit->init(glm::vec2(float(288), float(352)), texProgram, 2, isHover, "EXIT");
		break;
	default:
		break;
	}
}

void MainMenu::initShaders()
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