#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "CabezaFlotante.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4

enum Anims
{
	MOVE_LEFT, MOVE_RIGHT, BORN, DIE
};


void CabezaFlotante::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	bJumping = false;
	bLiana = false;
	bdoorCollision = false;
	animDoorNum = -1;
	spritesheet.loadFromFile("images/cabeza_volante.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(16, 20), glm::vec2(0.5, 0.5), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(4);

	sprite->setAnimationSpeed(MOVE_LEFT, 8);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.5f, 0.f));

	sprite->setAnimationSpeed(MOVE_RIGHT, 8);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0., 0.5f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.5, 0.5f));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posCabeza.x), float(tileMapDispl.y + posCabeza.y)));
}

void CabezaFlotante::update(int deltaTime)
{
	sprite->update(deltaTime);
	if (sprite->animation() == MOVE_LEFT) {
		posCabeza.y += 4;
		if (map->collisionMoveDown(glm::vec2(posCabeza.x - 8, posCabeza.y), glm::ivec2(8, 14), &posCabeza.y)) {
			if (map->collisionMoveLeft(posCabeza, glm::ivec2(8, 10))) {
				sprite->changeAnimation(MOVE_RIGHT);
				posCabeza.x += 2;
			}
			else {
				posCabeza.x -= 2;
			}
		}
		else {
			sprite->changeAnimation(MOVE_RIGHT);
			posCabeza.x += 2;
			posCabeza.y -= 4;
		}
	}
	else {
		posCabeza.y += 4;
		if (map->collisionMoveDown(glm::vec2(posCabeza.x + 8, posCabeza.y), glm::ivec2(8, 14), &posCabeza.y)) {
			if (map->collisionMoveRight(posCabeza, glm::ivec2(8, 10))) {
				sprite->changeAnimation(MOVE_LEFT);
				posCabeza.x -= 2;
			}
			else {
				posCabeza.x += 2;
			}
		}
		else {
			sprite->changeAnimation(MOVE_LEFT);
			posCabeza.x -= 2;
			posCabeza.y -= 4;
		}
	}
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posCabeza.x), float(tileMapDispl.y + posCabeza.y)));
}

void CabezaFlotante::render()
{
	sprite->render();
}

void CabezaFlotante::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void CabezaFlotante::setPosition(const glm::vec2& pos)
{
	posCabeza = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posCabeza.x), float(tileMapDispl.y + posCabeza.y)));
}