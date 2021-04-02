#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "MenuInferior.h"
#include "Game.h"


enum PowerUps
{
	HYPER_SHOES, BLUE_RAINCOAT, GRAY_RAINCOAT, YELLOW_SPELLBOOK, BLUE_SPELLBOOK, NONE
};

enum SavedFriends
{
	ROUND_UP, ROUND_DOWN, FRIEND_UP, FRIEND_DOWN, LINE, NONE_FRIENDS
};

MenuInferior::~MenuInferior() {
	if (spritePowerUps != NULL)
		delete spritePowerUps;
	if (spriteSavedFriends != NULL)
		delete spriteSavedFriends;
}

void MenuInferior::init()
{
	initShaders();
	friendsSaved = 0;
	activePowerUps = 0;
	spritePowerUps = new Sprite[8];
	spritesheetPowerUps.loadFromFile("images/powerups.png", TEXTURE_PIXEL_FORMAT_RGBA);
	for (int i = 0; i < 8; ++i) {
		spritePowerUps[i] = *Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.0625, 0.5), &spritesheetPowerUps, &texProgram);
		spritePowerUps[i].setNumberAnimations(6);

		spritePowerUps[i].setAnimationSpeed(HYPER_SHOES, 8);
		spritePowerUps[i].addKeyframe(HYPER_SHOES, glm::vec2(0.25f, 0.5f));

		spritePowerUps[i].setAnimationSpeed(BLUE_RAINCOAT, 8);
		spritePowerUps[i].addKeyframe(BLUE_RAINCOAT, glm::vec2(0.f, 0.5f));

		spritePowerUps[i].setAnimationSpeed(GRAY_RAINCOAT, 8);
		spritePowerUps[i].addKeyframe(GRAY_RAINCOAT, glm::vec2(0.125f, 0.5f));

		spritePowerUps[i].setAnimationSpeed(YELLOW_SPELLBOOK, 8);
		spritePowerUps[i].addKeyframe(YELLOW_SPELLBOOK, glm::vec2(0.5f, 0.0f));

		spritePowerUps[i].setAnimationSpeed(BLUE_SPELLBOOK, 8);
		spritePowerUps[i].addKeyframe(BLUE_SPELLBOOK, glm::vec2(0.875f, 0.0f));

		spritePowerUps[i].setAnimationSpeed(NONE, 8);
		spritePowerUps[i].addKeyframe(NONE, glm::vec2(0.9375f, 0.f));

		spritePowerUps[i].changeAnimation(NONE);
		spritePowerUps[i].setPosition(glm::vec2(float(60 + i * 32), float(70 + 20 * 16)));
		spritePowerUps[i].setScale(glm::vec3(2.f, 2.f, 0.f));
	}
	
	spriteSavedFriends = new Sprite[20];
	spriteSheetSavedFriends.loadFromFile("images/compis.png", TEXTURE_PIXEL_FORMAT_RGBA);
	for (int i = 0; i < 20; ++i) {
		spriteSavedFriends[i] = *Sprite::createSprite(glm::ivec2(8, 8), glm::vec2(0.25, 0.5), &spriteSheetSavedFriends, &texProgram);
		spriteSavedFriends[i].setNumberAnimations(6);

		spriteSavedFriends[i].setAnimationSpeed(ROUND_UP, 8);
		spriteSavedFriends[i].addKeyframe(ROUND_UP, glm::vec2(0.f, 0.f));

		spriteSavedFriends[i].setAnimationSpeed(ROUND_DOWN, 8);
		spriteSavedFriends[i].addKeyframe(ROUND_DOWN, glm::vec2(0.f, 0.5f));

		spriteSavedFriends[i].setAnimationSpeed(FRIEND_UP, 8);
		spriteSavedFriends[i].addKeyframe(FRIEND_UP, glm::vec2(0.5f, 0.f));

		spriteSavedFriends[i].setAnimationSpeed(FRIEND_DOWN, 8);
		spriteSavedFriends[i].addKeyframe(FRIEND_DOWN, glm::vec2(0.75f, 0.0f));

		spriteSavedFriends[i].setAnimationSpeed(LINE, 8);
		spriteSavedFriends[i].addKeyframe(LINE, glm::vec2(0.75f, 0.5f));

		spriteSavedFriends[i].setAnimationSpeed(NONE_FRIENDS, 8);
		spriteSavedFriends[i].addKeyframe(NONE, glm::vec2(0.5, 0.5f));

		if (i > 16)
			spriteSavedFriends[i].changeAnimation(ROUND_DOWN);
		else if (i > 11 && i < 16)
			spriteSavedFriends[i].changeAnimation(ROUND_UP);
		else if (i == 11)
			spriteSavedFriends[i].changeAnimation(LINE);
		else if (i == 10)
			spriteSavedFriends[i].changeAnimation(FRIEND_UP);
		else 
			spriteSavedFriends[i].changeAnimation(NONE_FRIENDS);
		if (i < 17)
			spriteSavedFriends[i].setPosition(glm::vec2(float(60 + 255 + i * 15), float(70 + 20 * 16)));
		else
			spriteSavedFriends[i].setPosition(glm::vec2(float(60 + 255 + 12 * 15 + (i - 17) * 15), float(70 + 20 * 16 + 20)));
		spriteSavedFriends[i].setScale(glm::vec3(2.f, 2.f, 0.f));
	}
}

void MenuInferior::update(int deltaTime)
{
	for (int i = 0; i < 8; ++i)
		spritePowerUps[i].update(deltaTime);
	for (int i = 0; i < 20; ++i)
		spriteSavedFriends[i].update(deltaTime);
}

void MenuInferior::render()
{
	for (int i = 0; i < 8; ++i)
		spritePowerUps[i].render();
	for (int i = 0; i < 20; ++i)
		spriteSavedFriends[i].render();
}

void MenuInferior::setPowerUp(int numPowerUp) {
	for (int i = activePowerUps; i >= 1; --i) {
		spritePowerUps[i].changeAnimation(spritePowerUps[i - 1].animation());
	}
	spritePowerUps[0].changeAnimation(numPowerUp);
	++activePowerUps;
}

void MenuInferior::savedNewFriend() {
	++friendsSaved;
	if (friendsSaved < 5)
		spriteSavedFriends[11 + friendsSaved].changeAnimation(FRIEND_UP);
	else spriteSavedFriends[12 + friendsSaved].changeAnimation(FRIEND_UP);
}


void MenuInferior::initShaders()
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



