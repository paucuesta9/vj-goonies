#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Object.h"
#include "Game.h"


enum Objects
{
	KEY, POWERUP, LOCK, POTION
};

Object::~Object() {
	if (sprite != NULL)
		delete sprite;
}

void Object::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, glm::ivec2 pos, int sceneNum, int screenNum, int type, int power)
{
	time = 0;
	agotado = false;
	powerUp = power;
	picked = false;
	posObject = pos;
	scene = sceneNum;
	screen = screenNum;
	sprite = new Sprite();
	spritesheet.loadFromFile("images/objects.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(8, 8), glm::vec2(0.25, 0.5), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(4);

	sprite->setAnimationSpeed(KEY, 8);
	sprite->addKeyframe(KEY, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(KEY, glm::vec2(0.75f, 0.0f));

	sprite->setAnimationSpeed(POWERUP, 8);
	sprite->addKeyframe(POWERUP, glm::vec2(0.25f, 0.f));
	sprite->addKeyframe(POWERUP, glm::vec2(0.75f, 0.0f));

	sprite->setAnimationSpeed(LOCK, 8);
	sprite->addKeyframe(LOCK, glm::vec2(0.f, 0.5f));

	sprite->setAnimationSpeed(POTION, 8);
	sprite->addKeyframe(POTION, glm::vec2(0.25f, 0.5f));

	sprite->changeAnimation(type);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posObject.x), float(tileMapDispl.y + posObject.y)));
	sprite->setScale(glm::vec3(2.f, 2.f, 0.f));
}

void Object::update(int deltaTime)
{
	sprite->update(deltaTime);
	time += deltaTime;
}

void Object::render(int sceneNum, int screenNum)
{
	if (sceneNum == scene && screenNum == screen)
		sprite->render();
}

void Object::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Object::setPosition(const glm::vec2& pos)
{
	posObject = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posObject.x), float(tileMapDispl.y + posObject.y)));
}

glm::ivec2 Object::getPosition() {
	return posObject;
}

int Object::getType() {
	return sprite->animation();
}

int Object::getPowerUp() {
	return powerUp;
}

void Object::setPicked() {
	picked = true;
	time = 0;
}

bool Object::getPicked() {
	return picked;
}

bool Object::getAgotado() {
	return agotado;
}

glm::vec2 Object::getLevel() {
	return glm::vec2(scene, screen);
}

bool Object::isActive() {
	if (time < 20000) return true;
	else {
		agotado = true;
		return false;
	}
}