#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Esqueleto.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4

enum EsqueletoAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT
};


void Esqueleto::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/esqueleto.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.25, 0.25), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(8);

	sprite->setAnimationSpeed(STAND_LEFT, 8);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.5f, 0.f));

	sprite->setAnimationSpeed(MOVE_LEFT, 8);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.5f, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(STAND_RIGHT, 8);
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.5f, 0.5f));

	sprite->setAnimationSpeed(MOVE_RIGHT, 8);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.5f, 0.5f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.5f));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEsqueleto.x), float(tileMapDispl.y + posEsqueleto.y)));

}

void Esqueleto::update(int deltaTime)
{
	sprite->update(deltaTime);
	posEsqueleto.y += FALL_STEP;

	if (map->collisionMoveDown(posEsqueleto, glm::ivec2(16, 20), &posEsqueleto.y))
	{
		

	}
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEsqueleto.x), float(tileMapDispl.y + posEsqueleto.y)));
}

void Esqueleto::render()
{
	sprite->render();
}

void Esqueleto::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Esqueleto::setPosition(const glm::vec2& pos)
{
	posEsqueleto = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEsqueleto.x), float(tileMapDispl.y + posEsqueleto.y)));
}

glm::ivec2 Esqueleto::getPosition() {
	return posEsqueleto;
}

int Esqueleto::isOut() {
	if (posEsqueleto.x < 0) return 1;
	else if (posEsqueleto.x > 512 - map->getTileSize()) return 2;
	else if (posEsqueleto.y < 0) return 3;
	else if (posEsqueleto.y > 320 - map->getTileSize()) return 4;
}



