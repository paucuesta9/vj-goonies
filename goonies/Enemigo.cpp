#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Enemigo.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4

enum EnemigoAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, MOVE_UP_DOWN, FALL, SHOOT_RIGHT, SHOOT_LEFT
};


void Enemigo::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	bJumping = false;
	bLiana = false;
	bdoorCollision = false;
	animDoorNum = -1;
	spritesheet.loadFromFile("images/ia_red.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.25, 0.25), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(8);

	sprite->setAnimationSpeed(STAND_LEFT, 8);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.25f));

	sprite->setAnimationSpeed(MOVE_LEFT, 8);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.25f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.25f, 0.25f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.5f, 0.25f));

	sprite->setAnimationSpeed(STAND_RIGHT, 8);
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(MOVE_RIGHT, 8);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0., 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.5, 0.f));

	sprite->setAnimationSpeed(MOVE_UP_DOWN, 8);
	sprite->addKeyframe(MOVE_UP_DOWN, glm::vec2(0.f, 0.5f));
	sprite->addKeyframe(MOVE_UP_DOWN, glm::vec2(0.25f, 0.5f));

	sprite->setAnimationSpeed(FALL, 8);
	sprite->addKeyframe(FALL, glm::vec2(0.5f, 0.5f));
	sprite->addKeyframe(FALL, glm::vec2(0.75f, 0.5f));

	sprite->setAnimationSpeed(SHOOT_RIGHT, 8);
	sprite->addKeyframe(SHOOT_RIGHT, glm::vec2(0.75f, 0.f));

	sprite->setAnimationSpeed(SHOOT_LEFT, 8);
	sprite->addKeyframe(SHOOT_LEFT, glm::vec2(0.75f, 0.25f));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemigo.x), float(tileMapDispl.y + posEnemigo.y)));

}

void Enemigo::update(int deltaTime)
{
	sprite->update(deltaTime);
	if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		if (sprite->animation() != MOVE_LEFT && !map->collisionLiana(posEnemigo, glm::ivec2(16, 20))) {
			sprite->changeAnimation(MOVE_LEFT);
			bLiana = false;
		}
		posEnemigo.x -= 2;
		if (map->collisionMoveLeft(posEnemigo, glm::ivec2(16, 16)))
		{
			posEnemigo.x += 2;
			sprite->changeAnimation(STAND_LEFT);
		}
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
		if (sprite->animation() != MOVE_RIGHT && !map->collisionLiana(posEnemigo, glm::ivec2(16, 20))) {
			sprite->changeAnimation(MOVE_RIGHT);
			bLiana = false;
		}
		posEnemigo.x += 2;
		if (map->collisionMoveRight(posEnemigo, glm::ivec2(16, 16)))
		{
			posEnemigo.x -= 2;
			sprite->changeAnimation(STAND_RIGHT);
		}
	}
	else
	{
		if (sprite->animation() == MOVE_LEFT)
			sprite->changeAnimation(STAND_LEFT);
		else if (sprite->animation() == MOVE_RIGHT)
			sprite->changeAnimation(STAND_RIGHT);
	}

	posEnemigo.y += FALL_STEP;
	if (Game::instance().getSpecialKey(GLUT_KEY_DOWN)) {
		if (map->collisionLiana(posEnemigo, glm::ivec2(16, 20)) || map->collisionLiana(glm::ivec2(posEnemigo.x, posEnemigo.y + map->getTileSize()), glm::ivec2(16, 20))) {
			bLiana = true;
			posEnemigo.y += FALL_STEP;
			posEnemigo.x = (posEnemigo.x / map->getTileSize()) * map->getTileSize() + 8;
			if (sprite->animation() != MOVE_UP_DOWN)
				sprite->changeAnimation(MOVE_UP_DOWN);
		}
	}

	if (map->collisionMoveDown(posEnemigo, glm::ivec2(16, 20), &posEnemigo.y))
	{
		if (Game::instance().getSpecialKey(GLUT_KEY_UP))
		{
			if (map->collisionSkullDoor(posEnemigo, glm::ivec2(16, 20)) && !bdoorCollision) {
				animDoorNum = 1;
				int block = map->getBlockCode(posEnemigo);
				if (block == 55) {
					posEnemigo.x = (((posEnemigo.x + 28) / map->getTileSize())) * map->getTileSize() - 8;
				}
				else if (block == 56) posEnemigo.x = ((posEnemigo.x + 12) / map->getTileSize()) * map->getTileSize() - 8;
				else if (block == 57) posEnemigo.x = (((posEnemigo.x - 4) / map->getTileSize())) * map->getTileSize() - 8;
			}
			else if (!map->collisionLiana(posEnemigo, glm::ivec2(16, 20))) {
				if (!bLiana) {
					bJumping = true;
					jumpAngle = 0;
					startY = posEnemigo.y;
					sprite->changeAnimation(STAND_LEFT);
				}
				bLiana = false;
			}
			else {
				bLiana = true;
				if (sprite->animation() != MOVE_UP_DOWN)
					sprite->changeAnimation(MOVE_UP_DOWN);
				bJumping = false;
				posEnemigo.y -= FALL_STEP;
				posEnemigo.x = (posEnemigo.x / map->getTileSize()) * map->getTileSize() + 8;
			}
		}
		else if (map->collisionLiana(posEnemigo, glm::ivec2(16, 20))) {
			if (sprite->animation() != MOVE_RIGHT && sprite->animation() != MOVE_LEFT && sprite->animation() != STAND_LEFT)
				sprite->changeAnimation(STAND_RIGHT);
		}

	}
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemigo.x), float(tileMapDispl.y + posEnemigo.y)));
}

void Enemigo::render()
{
	sprite->render();
}

void Enemigo::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Enemigo::setPosition(const glm::vec2& pos)
{
	posEnemigo = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemigo.x), float(tileMapDispl.y + posEnemigo.y)));
}

glm::ivec2 Enemigo::getPosition() {
	return posEnemigo;
}

int Enemigo::isOut() {
	if (posEnemigo.x < 0) return 1;
	else if (posEnemigo.x > 512 - map->getTileSize()) return 2;
	else if (posEnemigo.y < 0) return 3;
	else if (posEnemigo.y > 320 - map->getTileSize()) return 4;
	return 0;
}



