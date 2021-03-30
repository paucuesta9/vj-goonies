#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Bone.h"
#include "Game.h"


enum BoneAnims
{
	MOVING_LEFT, MOVING_RIGHT
};

void Bone::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, int dir)
{
	isActive = true;
	direction = dir;
	spritesheet.loadFromFile("images/huesos.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(6, 6), glm::vec2(0.25, 1.0), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);

	sprite->setAnimationSpeed(MOVING_LEFT, 8);
	sprite->addKeyframe(MOVING_LEFT, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(MOVING_LEFT, glm::vec2(0.25f, 0.f));
	sprite->addKeyframe(MOVING_LEFT, glm::vec2(0.5f, 0.f));

	sprite->setAnimationSpeed(MOVING_RIGHT, 8);
	sprite->addKeyframe(MOVING_RIGHT, glm::vec2(0.5f, 0.f));
	sprite->addKeyframe(MOVING_RIGHT, glm::vec2(0.25f, 0.f));
	sprite->addKeyframe(MOVING_RIGHT, glm::vec2(0.f, 0.f));
	
	if (direction == 1)
		sprite->changeAnimation(0);
	else sprite->changeAnimation(1);
	tileMapDispl = tileMapPos;
	sprite->setScale(glm::vec3(2.f, 2.f, 0.f));
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBone.x), float(tileMapDispl.y + posBone.y)));
}

void Bone::update(int deltaTime)
{
	sprite->update(deltaTime);
	if (direction == 1) {
		if (map->collisionSimpleMoveLeft(posBone, glm::ivec2(6, 6))) {
			isActive = false;
		} else posBone.x -= 4;
	}
	else {
		if (map->collisionSimpleMoveRight(posBone, glm::ivec2(6, 6))) {
			isActive = false;
		}
		else posBone.x += 4;
	}
	if (isOut() != 0) {
		isActive = false;
	}
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBone.x), float(tileMapDispl.y + posBone.y)));
}

void Bone::render()
{
	sprite->render();
}

void Bone::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Bone::setPosition(const glm::vec2& pos)
{
	posBone = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBone.x), float(tileMapDispl.y + posBone.y)));
}

glm::ivec2 Bone::getPosition() {
	return posBone;
}

int Bone::isOut() {
	if (posBone.x < 0) return 1;
	else if (posBone.x > 512 - 6) return 2;
	else if (posBone.y < 0) return 3;
	else if (posBone.y > 320 - 6) return 4;
	return 0;
}

int Bone::getState() {
	return isActive;
}