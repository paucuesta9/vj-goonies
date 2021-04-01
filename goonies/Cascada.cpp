#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Cascada.h"
#include "Game.h"


enum CascadaAnims
{
	BORN, LIVE, DIE, WATER
};

Cascada::~Cascada() {
	if (sprite != NULL)
		delete sprite; 
}

void Cascada::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, glm::ivec2 pos, int sizeCascada)
{
	posCascada = pos;
	sprite = new Sprite[sizeCascada];
	size = sizeCascada;
	num = 1;
	spritesheet.loadFromFile("images/cascada.png", TEXTURE_PIXEL_FORMAT_RGBA);
	time = 0;
	Status = BORN;

	tileMapDispl = tileMapPos;	
	shader = shaderProgram;
	initSprite(0);
}

void Cascada::initSprite(int spriteNum) {
	sprite[spriteNum] = *Sprite::createSprite(glm::ivec2(24, 8), glm::vec2(0.5, 0.25), &spritesheet, &shader);
	sprite[spriteNum].setNumberAnimations(4);

	sprite[spriteNum].setAnimationSpeed(BORN, 8);
	sprite[spriteNum].addKeyframe(BORN, glm::vec2(0.f, 0.5f));
	sprite[spriteNum].addKeyframe(BORN, glm::vec2(0.5f, 0.5f));

	sprite[spriteNum].setAnimationSpeed(LIVE, 8);
	sprite[spriteNum].addKeyframe(LIVE, glm::vec2(0.f, 0.25f));
	sprite[spriteNum].addKeyframe(LIVE, glm::vec2(0.5f, 0.25f));

	sprite[spriteNum].setAnimationSpeed(DIE, 8);
	sprite[spriteNum].addKeyframe(DIE, glm::vec2(0.f, 0.f));
	sprite[spriteNum].addKeyframe(DIE, glm::vec2(0.5f, 0.f));

	sprite[spriteNum].setAnimationSpeed(WATER, 8);
	sprite[spriteNum].addKeyframe(WATER, glm::vec2(0.f, 0.75f));
	sprite[spriteNum].addKeyframe(WATER, glm::vec2(0.5f, 0.75f));

	sprite[spriteNum].changeAnimation(BORN);
	sprite[spriteNum].setScale(glm::vec3(2.f, 2.f, 0.f));
	sprite[spriteNum].setPosition(glm::vec2(float(tileMapDispl.x + posCascada.x), float(tileMapDispl.y + posCascada.y + spriteNum * 16)));
}

void Cascada::update(int deltaTime)
{
	time += deltaTime;
	if (Status == BORN) {
		for (int i = 0; i < num; ++i) {
			if (time > 50) {
				int state = sprite[i].animation();
				if (state == BORN) sprite[i].changeAnimation(LIVE);
				if (i == size - 1 && state != WATER) {
					sprite[i].changeAnimation(WATER);
					time = 0;
				}
			}
			sprite[i].update(deltaTime);
		}
		if (num < size && time > 50) {
			initSprite(num);
			sprite[num].update(deltaTime);
			++num;
			time = 0;
		}
		else if (num == size) {
			num = 0;
			Status = LIVE;
		}
	}
	else if (Status == LIVE) {
		for (int i = 0; i < size; ++i) sprite[i].update(deltaTime);
		if (time > 5000) {
			Status = DIE;
			time = 0;
		}
	}
	else if (Status == DIE) {
		if (num <= size && time > 50) {
			time = 0;
			if (num < size) sprite[num].changeAnimation(DIE);
			for (int i = num; i < size; ++i) sprite[i].update(deltaTime);
			++num;
		}
		else if (num > size) {
			Status = WATER;
		}
		//else if (num > 0) delete& sprite[num - 1];
	}
	else if (Status == WATER) {
		if (time > 5000) {
			time = 0;
			Status = BORN;
			num = 0;
		}
	}
}

void Cascada::render()
{
	if (Status == BORN) for (int i = 0; i < num; ++i) sprite[i].render();
	else if (Status == LIVE) for (int i = 0; i < size; ++i) sprite[i].render();
	else if (Status == DIE) {
		if (num > 0) for (int i = num - 1; i < size; ++i) sprite[i].render();
		else for (int i = 0; i < size; ++i) sprite[i].render();
	}
}

void Cascada::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Cascada::setPosition(const glm::vec2& pos)
{
	posCascada = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posCascada.x), float(tileMapDispl.y + posCascada.y)));
}

glm::ivec2 Cascada::getPosition() {
	if (Status == BORN || Status == LIVE) return posCascada;
	else if (Status == DIE) return glm::vec2(posCascada.x, posCascada.y + num * 16);
	else return glm::vec2(0, 0);
}

int Cascada::getStatus() {
	return Status;
}

int Cascada::getSize() {
	if (Status == BORN) return num;
	else if (Status == LIVE) return size;
	else if (Status == DIE) return size - num;
	else return 0;
}