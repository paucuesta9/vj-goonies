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
	time = -1;

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
	if (time != -1) {
		time += deltaTime;
		if (time > 5000) {
			time = 0;
			if (num < size) {
				sprite[num].changeAnimation(DIE);
				for (int i = num; i < size; ++i) sprite[i].update(deltaTime);
				if (num > size) {
					time = -1;
				}
				++num;
			}
			else if (num > 0) delete& sprite[num - 1];
		}
		else {
			for (int i = 0; i < size; ++i) sprite[i].update(deltaTime);
		}
	}
	else {
		for (int i = 0; i < num; ++i) {
			int Status = sprite[i].animation();
			if (Status == 0) sprite[i].changeAnimation(LIVE);
			if (i == size - 1 && Status != 3) {
				sprite[i].changeAnimation(WATER);
				time = 0;

			}
			sprite[i].update(deltaTime);
		}
		if (num < size) {
			initSprite(num);
			sprite[num].update(deltaTime);
			++num;
		}
		else if (num == size) num = 0;
	}
}

void Cascada::render()
{
	if (time == -1)	for (int i = 0; i < num; ++i) sprite[i].render();
	else if (num == 0) for (int i = 0; i < size; ++i) sprite[i].render();
	else for (int i = num - 1; i < size; ++i) sprite[i].render();
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
	return posCascada;
}

void Cascada::setStatus(int Status)
{
	sprite->changeAnimation(Status);
}

int Cascada::getStatus() {
	return sprite->animation();
}