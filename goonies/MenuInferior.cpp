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

MenuInferior::~MenuInferior() {
	if (spritePowerUps != NULL)
		delete spritePowerUps;
}

void MenuInferior::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritePowerUps = new Sprite[8];
	spritesheetPowerUps.loadFromFile("images/powerups.png", TEXTURE_PIXEL_FORMAT_RGBA);
	for (int i = 0; i < 8; ++i) {
		spritePowerUps[i] = *Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.0625, 0.5), &spritesheetPowerUps, &shaderProgram);
		spritePowerUps[i].setNumberAnimations(6);

		spritePowerUps[i].setAnimationSpeed(HYPER_SHOES, 8);
		spritePowerUps[i].addKeyframe(HYPER_SHOES, glm::vec2(0.25f, 0.5f));

		spritePowerUps[i].setAnimationSpeed(BLUE_RAINCOAT, 8);
		spritePowerUps[i].addKeyframe(BLUE_RAINCOAT, glm::vec2(0.f, 0.5f));

		spritePowerUps[i].setAnimationSpeed(GRAY_RAINCOAT, 8);
		spritePowerUps[i].addKeyframe(GRAY_RAINCOAT, glm::vec2(0.1875f, 0.5f));

		spritePowerUps[i].setAnimationSpeed(YELLOW_SPELLBOOK, 8);
		spritePowerUps[i].addKeyframe(YELLOW_SPELLBOOK, glm::vec2(0.5625f, 0.0f));

		spritePowerUps[i].setAnimationSpeed(BLUE_SPELLBOOK, 8);
		spritePowerUps[i].addKeyframe(BLUE_SPELLBOOK, glm::vec2(0.9375f, 0.0f));

		spritePowerUps[i].setAnimationSpeed(NONE, 8);
		spritePowerUps[i].addKeyframe(NONE, glm::vec2(0.9375f, 0.f));

		spritePowerUps[i].changeAnimation(NONE);
		spritePowerUps[i].setPosition(glm::vec2(float(tileMapPos.x + i * 32), float(tileMapPos.y)));
		spritePowerUps[i].setScale(glm::vec3(2.f, 2.f, 0.f));
	}
	tileMapDispl = tileMapPos;
}

void MenuInferior::update(int deltaTime)
{
	for (int i = 0; i < 8; ++i)
		spritePowerUps[i].update(deltaTime);
}

void MenuInferior::render()
{
	for (int i = 0; i < 8; ++i)
		spritePowerUps[i].render();
}

void MenuInferior::setPowerUp(int numPowerUp, bool active) {
	if (active)
		spritePowerUps[numPowerUp].changeAnimation(numPowerUp);
	else
		spritePowerUps[numPowerUp].changeAnimation(NONE);
}
