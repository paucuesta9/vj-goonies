#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "GreenDoor.h"
#include "Game.h"


enum DoorAnims
{
	CLOSED, OPENED
};

GreenDoor::~GreenDoor() {
	if (sprite != NULL)
		delete sprite;
}

void GreenDoor::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, glm::ivec2 pos)
{
	posDoor = pos;
	sprite = new Sprite();
	spritesheet.loadFromFile("images/puerta_verde.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(24, 32), glm::vec2(0.5, 1.0), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(CLOSED, 8);
	sprite->addKeyframe(CLOSED, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(OPENED, 8);
	sprite->addKeyframe(OPENED, glm::vec2(0.5f, 0.f));

	sprite->changeAnimation(OPENED);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posDoor.x), float(tileMapDispl.y + posDoor.y)));
	sprite->setScale(glm::vec3(2.f, 2.f, 0.f));
}

void GreenDoor::update(int deltaTime)
{
	sprite->update(deltaTime);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posDoor.x), float(tileMapDispl.y + posDoor.y)));
}

void GreenDoor::render()
{
	sprite->render();
}

void GreenDoor::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void GreenDoor::setPosition(const glm::vec2& pos)
{
	posDoor = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posDoor.x), float(tileMapDispl.y + posDoor.y)));
}

glm::ivec2 GreenDoor::getPosition() {
	return posDoor;
}

void GreenDoor::open() {
	sprite->changeAnimation(OPENED);
}