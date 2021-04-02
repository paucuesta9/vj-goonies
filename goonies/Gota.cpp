#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Gota.h"
#include "Game.h"


enum GotaAnims
{
	BORN_1, BORN_2, FALL, HIT_OBJECT, HIT_FLOOR, NONE
};

Gota::~Gota() {
	if (sprite != NULL)
		delete sprite;
}

void Gota::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, glm::ivec2 pos)
{
	posGota = pos;
	initialPos = pos;
	sprite = new Sprite();
	spritesheet.loadFromFile("images/gotas.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(8, 8), glm::vec2(0.25, 0.5), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(6);

	sprite->setAnimationSpeed(BORN_1, 8);
	sprite->addKeyframe(BORN_1, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(BORN_2, 8);
	sprite->addKeyframe(BORN_2, glm::vec2(0.25f, 0.f));

	sprite->setAnimationSpeed(FALL, 8);
	sprite->addKeyframe(FALL, glm::vec2(0.5f, 0.f));

	sprite->setAnimationSpeed(HIT_OBJECT, 8);
	sprite->addKeyframe(HIT_OBJECT, glm::vec2(0.75f, 0.f));

	sprite->setAnimationSpeed(HIT_FLOOR, 8);
	sprite->addKeyframe(HIT_FLOOR, glm::vec2(0.f, 0.5f));

	sprite->setAnimationSpeed(NONE, 8);
	sprite->addKeyframe(NONE, glm::vec2(0.25f, 0.5f));

	sprite->changeAnimation(BORN_1);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posGota.x), float(tileMapDispl.y + posGota.y)));
	sprite->setScale(glm::vec3(2.f, 2.f, 0.f));
	animationTime = 0;
}

void Gota::update(int deltaTime)
{
	animationTime += deltaTime;
	if (sprite->animation() == BORN_1 || sprite->animation() == BORN_2) {
		if (animationTime > 150) {
			animationTime = 0;
			sprite->changeAnimation(sprite->animation() + 1);
		}
	}
	else if (sprite->animation() == FALL) {
		posGota.y += 4;
		if (map->collisionMoveDown(posGota, glm::vec2(8, 8), &posGota.y)) {
			posGota.y += 8;
			sprite->changeAnimation(HIT_FLOOR);
			animationTime = 0;
		}
	}
	else if (sprite->animation() == HIT_OBJECT) {
		if (animationTime > 150) {
			sprite->changeAnimation(NONE);
		}
	}
	else if (sprite->animation() == HIT_FLOOR) {
		if (animationTime > 150) {
			sprite->changeAnimation(NONE);
		}
	}
	else if (sprite->animation() == NONE) {
		int timeGota = (posGota.x / 16 - posGota.y / 16 + 40);
		if (timeGota < 40) timeGota += 40;
		if (animationTime > 85 * timeGota) {
			sprite->changeAnimation(BORN_1);
			posGota = initialPos;
			animationTime = 0;
		}
	}
	sprite->update(deltaTime);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posGota.x), float(tileMapDispl.y + posGota.y)));
}

void Gota::render()
{
	sprite->render();
}

void Gota::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Gota::setPosition(const glm::vec2& pos)
{
	posGota = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posGota.x), float(tileMapDispl.y + posGota.y)));
}

glm::ivec2 Gota::getPosition() {
	return posGota;
}

int Gota::getStatus() {
	return sprite->animation();
}

void Gota::hitObject() {
	sprite->changeAnimation(HIT_OBJECT);
	animationTime = 0;
}