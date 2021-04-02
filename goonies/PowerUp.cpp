#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "PowerUp.h"
#include "Game.h"

enum PowerUps
{
	HYPER_SHOES, BLUE_RAINCOAT, GRAY_RAINCOAT, YELLOW_SPELLBOOK, BLUE_SPELLBOOK, NONE
};

PowerUp::~PowerUp() {
	if (spritePowerUp != NULL)
		delete spritePowerUp;
}

void PowerUp::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritePowerUp = new Sprite();
	spritesheetPowerUp.loadFromFile("images/powerups.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritePowerUp = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.0625, 0.5), &spritesheetPowerUp, &shaderProgram);
	spritePowerUp->setNumberAnimations(6);

	spritePowerUp->setAnimationSpeed(HYPER_SHOES, 8);
	spritePowerUp->addKeyframe(HYPER_SHOES, glm::vec2(0.25f, 0.5f));

	spritePowerUp->setAnimationSpeed(BLUE_RAINCOAT, 8);
	spritePowerUp->addKeyframe(BLUE_RAINCOAT, glm::vec2(0.f, 0.5f));

	spritePowerUp->setAnimationSpeed(GRAY_RAINCOAT, 8);
	spritePowerUp->addKeyframe(GRAY_RAINCOAT, glm::vec2(0.1875f, 0.5f));

	spritePowerUp->setAnimationSpeed(YELLOW_SPELLBOOK, 8);
	spritePowerUp->addKeyframe(YELLOW_SPELLBOOK, glm::vec2(0.5625f, 0.0f));

	spritePowerUp->setAnimationSpeed(BLUE_SPELLBOOK, 8);
	spritePowerUp->addKeyframe(BLUE_SPELLBOOK, glm::vec2(0.9375f, 0.0f));

	spritePowerUp->setAnimationSpeed(NONE, 8);
	spritePowerUp->addKeyframe(NONE, glm::vec2(0.5625f, 0.5f));

	spritePowerUp->changeAnimation(NONE);
	tileMapDispl = tileMapPos;
	spritePowerUp->setPosition(glm::vec2(float(tileMapDispl.x), float(tileMapDispl.y)));
	spritePowerUp->setScale(glm::vec3(2.0, 2.0, 0.0));

}

void PowerUp::update(int deltaTime, int nextPos)
{
	spritePowerUp->update(deltaTime);
	spritePowerUp->setPosition(glm::vec2(float(tileMapDispl.x + nextPos), float(tileMapDispl.y)));
}

void PowerUp::render()
{
	spritePowerUp->render();
}

void PowerUp::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void PowerUp::setSpritePowerUp(int numPowerUp) {
	switch (numPowerUp) {
	case 0:
		spritePowerUp->changeAnimation(HYPER_SHOES);
		break;
	case 1:
		spritePowerUp->changeAnimation(BLUE_RAINCOAT);
		break;
	case 2:
		spritePowerUp->changeAnimation(GRAY_RAINCOAT);
		break;
	case 3:
		spritePowerUp->changeAnimation(YELLOW_SPELLBOOK);
		break;
	case 4:
		spritePowerUp->changeAnimation(BLUE_SPELLBOOK);
		break;
	default:
		break;
	}
	

}


