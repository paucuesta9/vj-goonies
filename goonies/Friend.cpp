#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Friend.h"
#include "Game.h"

enum AnimsB
{
	FRIEND
};

void Friend::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	picked = false;
	sprite = new Sprite();
	spritesheet.loadFromFile("images/amigos.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(8, 16), glm::vec2(0.5, 1.0), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(FRIEND, 8);
	sprite->addKeyframe(FRIEND, glm::vec2(0.0f, 0.0f));
	sprite->addKeyframe(FRIEND, glm::vec2(0.5f, 0.0f));

	tileMapDispl = tileMapPos;
	sprite->setPosition(tileMapDispl);
	sprite->setScale(glm::vec3(2.0, 2.0, 0.0));
}

void Friend::update(int deltaTime)
{
	sprite->update(deltaTime);
}

void Friend::render()
{
	sprite->render();
}

void Friend::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

glm::ivec2 Friend::getPosition() {
	return position;
}

void Friend::setPosition(const glm::vec2& pos)
{
	position = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));
}

void Friend::setPicked() {
	picked = true;
}

bool Friend::isPicked() {
	return picked;
}
