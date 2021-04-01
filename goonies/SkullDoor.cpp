#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "SkullDoor.h"
#include "Game.h"


enum DoorAnims
{
	SKULL_DOOR
};

SkullDoor::~SkullDoor() {
	if (sprite != NULL)
		delete sprite;
}

void SkullDoor::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, glm::ivec2 pos)
{
	posDoor = pos;
	sprite = new Sprite();
	spritesheet.loadFromFile("images/puerta_skull.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(24, 32), glm::vec2(1.0, 1.0), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(SKULL_DOOR, 8);
	sprite->addKeyframe(SKULL_DOOR, glm::vec2(0.f, 0.f));

	sprite->changeAnimation(SKULL_DOOR);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posDoor.x), float(tileMapDispl.y + posDoor.y)));
	sprite->setScale(glm::vec3(2.f, 2.f, 0.f));
}

void SkullDoor::update(int deltaTime)
{
	sprite->update(deltaTime);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posDoor.x), float(tileMapDispl.y + posDoor.y)));
}

void SkullDoor::render()
{
	sprite->render();
}

void SkullDoor::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void SkullDoor::setPosition(const glm::vec2& pos)
{
	posDoor = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posDoor.x), float(tileMapDispl.y + posDoor.y)));
}

glm::ivec2 SkullDoor::getPosition() {
	return posDoor;
}