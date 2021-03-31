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

void Cascada::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/cascada.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(24, 8), glm::vec2(0.5, 0.25), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(4);

	sprite->setAnimationSpeed(BORN, 8);
	sprite->addKeyframe(BORN, glm::vec2(0.f, 0.5f));
	sprite->addKeyframe(BORN, glm::vec2(0.5f, 0.5f));

	sprite->setAnimationSpeed(LIVE, 8);
	sprite->addKeyframe(LIVE, glm::vec2(0.f, 0.25f));
	sprite->addKeyframe(LIVE, glm::vec2(0.5f, 0.25f));

	sprite->setAnimationSpeed(DIE, 8);
	sprite->addKeyframe(DIE, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(DIE, glm::vec2(0.5f, 0.f));

	sprite->setAnimationSpeed(WATER, 8);
	sprite->addKeyframe(WATER, glm::vec2(0.f, 0.75f));
	sprite->addKeyframe(WATER, glm::vec2(0.5f, 0.75f));

	tileMapDispl = tileMapPos;
	sprite->changeAnimation(BORN);
	sprite->setScale(glm::vec3(2.f, 2.f, 0.f));
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posCascada.x), float(tileMapDispl.y + posCascada.y)));
}

void Cascada::update(int deltaTime)
{
	sprite->update(deltaTime);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posCascada.x), float(tileMapDispl.y + posCascada.y)));
}

void Cascada::render()
{
	sprite->render();
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