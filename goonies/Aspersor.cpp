#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Aspersor.h"
#include "Game.h"


enum AspersorAnims
{
	BORN_LEFT, BORN_RIGHT, LIVE_LEFT, LIVE_RIGHT, NONE
};

Aspersor::~Aspersor() {
	if (sprite != NULL)
		delete sprite;
}

void Aspersor::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, glm::ivec2 pos)
{
	posAspersor = pos;
	sprite = new Sprite[4];
	num = 1;
	spritesheet.loadFromFile("images/chorro_agua.png", TEXTURE_PIXEL_FORMAT_RGBA);
	timeAnimLeft = 0;
	timeAnimRight = 0;
	StatusLeft = NONE;
	StatusRight = NONE;
	tileMapDispl = tileMapPos;
	shader = shaderProgram;
}

void Aspersor::initSprite(int spriteNum) {
	sprite[spriteNum] = *Sprite::createSprite(glm::ivec2(8, 16), glm::vec2(0.125, 1.0), &spritesheet, &shader);
	sprite[spriteNum].setNumberAnimations(4);

	sprite[spriteNum].setAnimationSpeed(BORN_LEFT, 8);
	sprite[spriteNum].addKeyframe(BORN_LEFT, glm::vec2(0.25f, 0.f));

	sprite[spriteNum].setAnimationSpeed(BORN_RIGHT, 8);
	sprite[spriteNum].addKeyframe(BORN_RIGHT, glm::vec2(0.5f, 0.f));

	sprite[spriteNum].setAnimationSpeed(LIVE_LEFT, 8);
	sprite[spriteNum].addKeyframe(LIVE_LEFT, glm::vec2(0.125f, 0.f));
	sprite[spriteNum].addKeyframe(LIVE_LEFT, glm::vec2(0.f, 0.f));

	sprite[spriteNum].setAnimationSpeed(LIVE_RIGHT, 8);
	sprite[spriteNum].addKeyframe(LIVE_RIGHT, glm::vec2(0.625f, 0.f));
	sprite[spriteNum].addKeyframe(LIVE_RIGHT, glm::vec2(0.75f, 0.f));

	if (spriteNum == 0 || spriteNum == 1) {
		sprite[spriteNum].changeAnimation(LIVE_LEFT);
		sprite[spriteNum].setPosition(glm::vec2(float(tileMapDispl.x + posAspersor.x - (spriteNum + 1) * 16), float(tileMapDispl.y + posAspersor.y)));
	}
	else {
		sprite[spriteNum].changeAnimation(LIVE_RIGHT);
		sprite[spriteNum].setPosition(glm::vec2(float(tileMapDispl.x + posAspersor.x + (spriteNum - 1) * 16), float(tileMapDispl.y + posAspersor.y)));
	}
	sprite[spriteNum].setScale(glm::vec3(2.f, 2.f, 0.f));
}

void Aspersor::update(int deltaTime)
{
	timeAnimLeft += deltaTime;
	timeAnimRight += deltaTime;
	if (StatusLeft == NONE) {
		srand(time(NULL) * (posAspersor.x - 32 - posAspersor.y + 20));
		if (deltaTime * rand() % 500 < 20) {
			StatusLeft = BORN_LEFT;
			timeAnimLeft = 0;
			initSprite(0);
		}
	}
	else if (StatusLeft == BORN_LEFT) {
		sprite[0].update(deltaTime);
		if (timeAnimLeft > 2500) {
			timeAnimLeft = 0;
			StatusLeft = LIVE_LEFT;
			initSprite(1);
			sprite[0].changeAnimation(BORN_LEFT);
		}
	}
	else if (StatusLeft == LIVE_LEFT) {
		sprite[0].update(deltaTime);
		sprite[1].update(deltaTime);
		if (timeAnimLeft > 4500) {
			StatusLeft = NONE;
		}
	}
	if (StatusRight == NONE) {
		srand(time(NULL) * (posAspersor.x + 16 - posAspersor.y + 20));
		if ((deltaTime * rand()) % 1000 < 20) {
			StatusRight = BORN_RIGHT;
			timeAnimRight = 0;
			initSprite(2);
		}
	}
	else if (StatusRight == BORN_RIGHT) {
		sprite[2].update(deltaTime);
		if (timeAnimRight > 2500) {
			timeAnimRight = 0;
			StatusRight = LIVE_RIGHT;
			initSprite(3);
			sprite[2].changeAnimation(BORN_RIGHT);
		}
	}
	else if (StatusRight == LIVE_RIGHT) {
		sprite[2].update(deltaTime);
		sprite[3].update(deltaTime);
		if (timeAnimRight > 4500) {
			StatusRight = NONE;
		}
	}
}

void Aspersor::render()
{
	if (StatusLeft == BORN_LEFT) sprite[0].render();
	else if (StatusLeft == LIVE_LEFT) {
		sprite[0].render();
		sprite[1].render();
	}
	if (StatusRight == BORN_RIGHT) sprite[2].render();
	else if (StatusRight == LIVE_RIGHT) {
		sprite[2].render();
		sprite[3].render();
	}
}

void Aspersor::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Aspersor::setPosition(const glm::vec2& pos)
{
	posAspersor = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posAspersor.x), float(tileMapDispl.y + posAspersor.y)));
}

glm::ivec2 Aspersor::getPosition(bool left) {
	if (left) {
		if (StatusLeft == BORN_LEFT) return glm::vec2(posAspersor.x - 16, posAspersor.y);
		else if (StatusLeft == LIVE_LEFT) return glm::vec2(posAspersor.x - 32, posAspersor.y);
		else return glm::vec2(0, 0);
	}
	else {
		if (StatusRight == BORN_RIGHT) return glm::vec2(posAspersor.x + 16, posAspersor.y);
		else if (StatusRight == LIVE_RIGHT) return glm::vec2(posAspersor.x + 32, posAspersor.y);
		else return glm::vec2(0, 0);
	}
}

int Aspersor::getStatus(bool left) {
	if (left) {
		return StatusLeft;
	}
	else {
		return StatusRight;
	}
}

int Aspersor::getSize(bool left) {
	if (left) {
		if (StatusLeft == BORN_LEFT) return 16;
		else if (StatusLeft == LIVE_LEFT) return 32;
		else return 0;
	}
	else {
		if (StatusRight == BORN_RIGHT) return 16;
		else if (StatusRight == LIVE_RIGHT) return 32;
		else return 0;
	}
}