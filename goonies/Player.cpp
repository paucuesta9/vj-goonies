#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4


enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, STAND_UP, MOVE_LEFT, MOVE_RIGHT, MOVE_UP_DOWN
};


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	bJumping = false;
	bLiana = false;
	bdoorCollision = false;
	animDoorNum = -1;
	spritesheet.loadFromFile("images/player.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.25, 0.25), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(6);
	
		sprite->setAnimationSpeed(STAND_LEFT, 8);
		sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.25f));
		
		sprite->setAnimationSpeed(MOVE_LEFT, 8);
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.25f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.25f, 0.25f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.5f, 0.25f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.75f, 0.25f));

		sprite->setAnimationSpeed(STAND_RIGHT, 8);
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.f, 0.f));
		
		sprite->setAnimationSpeed(MOVE_RIGHT, 8);
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0., 0.f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25, 0.f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.5, 0.f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.75, 0.f));

		sprite->setAnimationSpeed(STAND_UP, 8);
		sprite->addKeyframe(STAND_UP, glm::vec2(0.f, 0.5f));

		sprite->setAnimationSpeed(MOVE_UP_DOWN, 8);
		sprite->addKeyframe(MOVE_UP_DOWN, glm::vec2(0.f, 0.5f));
		sprite->addKeyframe(MOVE_UP_DOWN, glm::vec2(0.25f, 0.5f));
		
	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	
}

void Player::update(int deltaTime)
{
	sprite->update(deltaTime);
	if (animDoorNum != -1) {
		if (animDoorNum == 1) {
			posPlayer.y -= 2;
		}

		if (animDoorNum == 10) {
			posPlayer.y -= 2;
		}
			
		if (animDoorNum == 20) {
			sprite->changeAnimation(MOVE_RIGHT);
			posPlayer.x += 5;
		}

		if (animDoorNum == 30 || animDoorNum == 40 || animDoorNum == 50 || animDoorNum == 60) {
			posPlayer.x += 5;
		}
		
		if (animDoorNum == 70) {
			posPlayer.x += 5;
			bdoorCollision = true;
			animDoorNum = -2;
		}
		++animDoorNum;
	}
	else {
		if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
		{
			if (sprite->animation() != MOVE_LEFT && !map->collisionLiana(posPlayer, glm::ivec2(16, 20))) {
				sprite->changeAnimation(MOVE_LEFT);
				bLiana = false;
			}
			posPlayer.x -= 2;
			if (map->collisionMoveLeft(posPlayer, glm::ivec2(16, 16)))
			{
				posPlayer.x += 2;
				sprite->changeAnimation(STAND_LEFT);
			}
		}
		else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
		{
			if (sprite->animation() != MOVE_RIGHT && !map->collisionLiana(posPlayer, glm::ivec2(16, 20))) {
				sprite->changeAnimation(MOVE_RIGHT);
				bLiana = false;
			}
			posPlayer.x += 2;
			if (map->collisionMoveRight(posPlayer, glm::ivec2(16, 16)))
			{
				posPlayer.x -= 2;
				sprite->changeAnimation(STAND_RIGHT);
			}
		}
		else
		{
			if (sprite->animation() == MOVE_LEFT)
				sprite->changeAnimation(STAND_LEFT);
			else if (sprite->animation() == MOVE_RIGHT)
				sprite->changeAnimation(STAND_RIGHT);
			else if (sprite->animation() == STAND_UP && !bLiana)
				sprite->changeAnimation(STAND_LEFT);
		}

		if (bJumping)
		{
			jumpAngle += JUMP_ANGLE_STEP;
			if (jumpAngle == 180)
			{
				bJumping = false;
				posPlayer.y = startY;
			}
			else
			{
				posPlayer.y = int(startY - 48 * sin(3.14159f * jumpAngle / 180.f));
				if (jumpAngle > 90)
					bJumping = !map->collisionMoveDown(posPlayer, glm::ivec2(20, 20), &posPlayer.y);
				else bJumping = !map->collisionMoveUp(posPlayer, glm::ivec2(16, 16));
			}
		}
		else
		{
			posPlayer.y += FALL_STEP;
			if (Game::instance().getSpecialKey(GLUT_KEY_DOWN)) {
				if (map->collisionLiana(posPlayer, glm::ivec2(16, 20)) || map->collisionLiana(glm::ivec2(posPlayer.x, posPlayer.y + map->getTileSize()), glm::ivec2(16, 20))) {
					bLiana = true;
					posPlayer.y += FALL_STEP;
					posPlayer.x = (posPlayer.x / map->getTileSize()) * map->getTileSize() + 12;
					if (sprite->animation() != MOVE_UP_DOWN)
						sprite->changeAnimation(MOVE_UP_DOWN);
				}
			}
			else if (sprite->animation() == MOVE_UP_DOWN)
				sprite->changeAnimation(STAND_UP);
			if (map->collisionMoveDown(posPlayer, glm::ivec2(16, 20), &posPlayer.y))
			{
				if (Game::instance().getSpecialKey(GLUT_KEY_UP))
				{
					if (map->collisionSkullDoor(posPlayer, glm::ivec2(16, 20)) && !bdoorCollision) {
						animDoorNum = 1;
						int block = map->getBlockCode(posPlayer);
						if (block == 55) {
							posPlayer.x = (((posPlayer.x + 28)/ map->getTileSize())) * map->getTileSize() - 8;
						} else if (block == 56) posPlayer.x = ((posPlayer.x + 12) / map->getTileSize()) * map->getTileSize() - 8;
						else if (block == 57) posPlayer.x = (((posPlayer.x - 4)/ map->getTileSize())) * map->getTileSize() - 8;
					}
					else if (!map->collisionLiana(posPlayer, glm::ivec2(16, 20))) {
						if (!bLiana) {
							bJumping = true;
							jumpAngle = 0;
							startY = posPlayer.y;
							sprite->changeAnimation(STAND_LEFT);
						}
						bLiana = false;
					}
					else {
						bLiana = true;
						if (sprite->animation() != MOVE_UP_DOWN)
							sprite->changeAnimation(MOVE_UP_DOWN);
						bJumping = false;
						posPlayer.y -= FALL_STEP;
						posPlayer.x = (posPlayer.x / map->getTileSize()) * map->getTileSize() + 12;
					}
				}
				else if (sprite->animation() == MOVE_UP_DOWN)
					sprite->changeAnimation(STAND_UP);
			}
		}
	}
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Player::render()
{
	sprite->render();
}

void Player::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Player::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

glm::ivec2 Player::getPosition() {
	return posPlayer;
}

int Player::isOut() {
	if (posPlayer.x < 0) return 1;
	else if (posPlayer.x > 512 - map->getTileSize()) return 2;
	else if (posPlayer.y < 0) return 3;
	else if (posPlayer.y > 320 - map->getTileSize()) return 4;
}

int Player::getDoorCollision() {
	return bdoorCollision;
}

void Player::setDoorCollision(bool state) {
	bdoorCollision = state;
}



