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
	STAND_LEFT, STAND_RIGHT, STAND_UP, MOVE_LEFT, MOVE_RIGHT, MOVE_UP_DOWN, PUNCH_LEFT, PUNCH_RIGHT, BALL, WATER, NONE
};


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	bJumping = false;
	bLiana = false;
	bdoorCollision = false;

	animDoorNum = -1;
	animationTime = -1;
	punchTime = -1;

	life = 1000;
	exp = 0;
	points = 0;

	Status = -1;
	speed = 2;

	blueRaincoat = false;
	grayRaincoat = false;
	yellowSpellbook = false;
	blueSpellbook = false;
	spritesheetNormal.loadFromFile("images/player.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spriteNormal = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.25, 0.25), &spritesheetNormal, &shaderProgram);
	spriteNormal->setNumberAnimations(11);
	
	spriteNormal->setAnimationSpeed(STAND_LEFT, 8);
	spriteNormal->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.25f));
		
	spriteNormal->setAnimationSpeed(MOVE_LEFT, 8);
	spriteNormal->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.25f));
	spriteNormal->addKeyframe(MOVE_LEFT, glm::vec2(0.25f, 0.25f));
	spriteNormal->addKeyframe(MOVE_LEFT, glm::vec2(0.5f, 0.25f));
	spriteNormal->addKeyframe(MOVE_LEFT, glm::vec2(0.75f, 0.25f));

	spriteNormal->setAnimationSpeed(STAND_RIGHT, 8);
	spriteNormal->addKeyframe(STAND_RIGHT, glm::vec2(0.f, 0.f));
		
	spriteNormal->setAnimationSpeed(MOVE_RIGHT, 8);
	spriteNormal->addKeyframe(MOVE_RIGHT, glm::vec2(0., 0.f));
	spriteNormal->addKeyframe(MOVE_RIGHT, glm::vec2(0.25, 0.f));
	spriteNormal->addKeyframe(MOVE_RIGHT, glm::vec2(0.5, 0.f));
	spriteNormal->addKeyframe(MOVE_RIGHT, glm::vec2(0.75, 0.f));

	spriteNormal->setAnimationSpeed(STAND_UP, 8);
	spriteNormal->addKeyframe(STAND_UP, glm::vec2(0.f, 0.5f));

	spriteNormal->setAnimationSpeed(MOVE_UP_DOWN, 8);
	spriteNormal->addKeyframe(MOVE_UP_DOWN, glm::vec2(0.f, 0.5f));
	spriteNormal->addKeyframe(MOVE_UP_DOWN, glm::vec2(0.25f, 0.5f));

	spriteNormal->setAnimationSpeed(PUNCH_LEFT, 8);
	spriteNormal->addKeyframe(PUNCH_LEFT, glm::vec2(0.75f, 0.5f));

	spriteNormal->setAnimationSpeed(PUNCH_RIGHT, 8);
	spriteNormal->addKeyframe(PUNCH_RIGHT, glm::vec2(0.5f, 0.5f));

	spriteNormal->setAnimationSpeed(BALL, 8);
	spriteNormal->addKeyframe(BALL, glm::vec2(0.25f, 0.75f));

	spriteNormal->setAnimationSpeed(WATER, 8);
	spriteNormal->addKeyframe(WATER, glm::vec2(0.0f, 0.75f));

	spriteNormal->setAnimationSpeed(NONE, 8);
	spriteNormal->addKeyframe(NONE, glm::vec2(0.75f, 0.75f));
	
	spritesheetHurt.loadFromFile("images/player_hurt.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spriteHurt = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.25, 0.25), &spritesheetHurt, &shaderProgram);
	spriteHurt->setNumberAnimations(11);

	spriteHurt->setAnimationSpeed(STAND_LEFT, 8);
	spriteHurt->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.25f));
	spriteHurt->addKeyframe(STAND_LEFT, glm::vec2(0.75f, 0.75f));

	spriteHurt->setAnimationSpeed(MOVE_LEFT, 8);
	spriteHurt->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.25f));
	spriteHurt->addKeyframe(MOVE_LEFT, glm::vec2(0.75f, 0.75f));
	spriteHurt->addKeyframe(MOVE_LEFT, glm::vec2(0.25f, 0.25f));
	spriteHurt->addKeyframe(MOVE_LEFT, glm::vec2(0.75f, 0.75f));
	spriteHurt->addKeyframe(MOVE_LEFT, glm::vec2(0.5f, 0.25f));
	spriteHurt->addKeyframe(MOVE_LEFT, glm::vec2(0.75f, 0.75f));
	spriteHurt->addKeyframe(MOVE_LEFT, glm::vec2(0.75f, 0.25f));
	spriteHurt->addKeyframe(MOVE_LEFT, glm::vec2(0.75f, 0.75f));

	spriteHurt->setAnimationSpeed(STAND_RIGHT, 8);
	spriteHurt->addKeyframe(STAND_RIGHT, glm::vec2(0.f, 0.f));
	spriteHurt->addKeyframe(STAND_RIGHT, glm::vec2(0.75f, 0.75f));

	spriteHurt->setAnimationSpeed(MOVE_RIGHT, 8);
	spriteHurt->addKeyframe(MOVE_RIGHT, glm::vec2(0., 0.f));
	spriteHurt->addKeyframe(MOVE_RIGHT, glm::vec2(0.75f, 0.75f));
	spriteHurt->addKeyframe(MOVE_RIGHT, glm::vec2(0.25, 0.f));
	spriteHurt->addKeyframe(MOVE_RIGHT, glm::vec2(0.75f, 0.75f));
	spriteHurt->addKeyframe(MOVE_RIGHT, glm::vec2(0.5, 0.f));
	spriteHurt->addKeyframe(MOVE_RIGHT, glm::vec2(0.75f, 0.75f));
	spriteHurt->addKeyframe(MOVE_RIGHT, glm::vec2(0.75, 0.f));
	spriteHurt->addKeyframe(MOVE_RIGHT, glm::vec2(0.75f, 0.75f));

	spriteHurt->setAnimationSpeed(STAND_UP, 8);
	spriteHurt->addKeyframe(STAND_UP, glm::vec2(0.f, 0.5f));
	spriteHurt->addKeyframe(STAND_UP, glm::vec2(0.75f, 0.75f));

	spriteHurt->setAnimationSpeed(MOVE_UP_DOWN, 8);
	spriteHurt->addKeyframe(MOVE_UP_DOWN, glm::vec2(0.f, 0.5f));
	spriteHurt->addKeyframe(MOVE_UP_DOWN, glm::vec2(0.75f, 0.75f));
	spriteHurt->addKeyframe(MOVE_UP_DOWN, glm::vec2(0.25f, 0.5f));
	spriteHurt->addKeyframe(MOVE_UP_DOWN, glm::vec2(0.75f, 0.75f));

	spriteHurt->setAnimationSpeed(PUNCH_LEFT, 8);
	spriteHurt->addKeyframe(PUNCH_LEFT, glm::vec2(0.75f, 0.5f));

	spriteHurt->setAnimationSpeed(PUNCH_RIGHT, 8);
	spriteHurt->addKeyframe(PUNCH_RIGHT, glm::vec2(0.5f, 0.5f));

	spriteHurt->setAnimationSpeed(BALL, 8);
	spriteHurt->addKeyframe(BALL, glm::vec2(0.025f, 0.75f));

	spriteHurt->setAnimationSpeed(WATER, 8);
	spriteHurt->addKeyframe(WATER, glm::vec2(0.0f, 0.75f));

	spriteHurt->setAnimationSpeed(NONE, 8);
	spriteHurt->addKeyframe(NONE, glm::vec2(0.75f, 0.75f));

	spriteNormal->changeAnimation(0);
	spriteHurt->changeAnimation(NONE);
	tileMapDispl = tileMapPos;
	spriteNormal->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	spriteNormal->setScale(glm::vec3(2.f, 2.f, 0.f));
	spriteHurt->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	spriteHurt->setScale(glm::vec3(2.f, 2.f, 0.f));
	sprite = spriteNormal;
}

void Player::update(int deltaTime)
{
	sprite->update(deltaTime);
	if (animationTime != -1) {
		animationTime += deltaTime;
		if (animationTime > 2500) {
			animationTime = -1;
			setSprite(1);
		}
	}
	if (punchTime != -1) {
		punchTime += deltaTime;
		if (punchTime > 100) {
			if (sprite->animation() == PUNCH_LEFT)
				sprite->changeAnimation(STAND_LEFT);
			else if (sprite->animation() == PUNCH_RIGHT)
				sprite->changeAnimation(STAND_RIGHT);
			punchTime = -1;
		}
	}
	if (animDoorNum != -1 && animDoorNum != -2) {
		if (Status == 0) {
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
				animDoorNum = -3;
				Status = -1;
			}
		}
		else if (Status == 1) {
			sprite->changeAnimation(STAND_RIGHT);
			if (animDoorNum == 50) {
				posPlayer.y += 2;
			}

			if (animDoorNum == 70) {
				posPlayer.y += 2;
				animDoorNum = -2;
				Status = -1;
			}
		}
		++animDoorNum;
	}
	else {
		if (Game::instance().getKey(32) && sprite->animation() != BALL) {
			punchTime = 0;
			if (sprite->animation() == STAND_LEFT || sprite->animation() == MOVE_LEFT)
				sprite->changeAnimation(PUNCH_LEFT);
			else if (sprite->animation() == STAND_RIGHT || sprite->animation() == MOVE_RIGHT)
				sprite->changeAnimation(PUNCH_RIGHT);
			Game::instance().keyReleased(32);
		}
		else if (Game::instance().getSpecialKey(GLUT_KEY_LEFT) && sprite->animation() != BALL && sprite->animation() != WATER)
		{
			if (sprite->animation() != MOVE_LEFT && !map->collisionLiana(posPlayer, glm::ivec2(16, 20))) {
				sprite->changeAnimation(MOVE_LEFT);
				bLiana = false;
			}
			posPlayer.x -= speed;
			if (map->collisionMoveLeft(posPlayer, glm::ivec2(16, 16)))
			{
				posPlayer.x += speed;
				sprite->changeAnimation(STAND_LEFT);
			}
		}
		else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT) && sprite->animation() != BALL && sprite->animation() != WATER)
		{
			if (sprite->animation() != MOVE_RIGHT && !map->collisionLiana(posPlayer, glm::ivec2(16, 20))) {
				sprite->changeAnimation(MOVE_RIGHT);
				bLiana = false;
			}
			posPlayer.x += speed;
			if (map->collisionMoveRight(posPlayer, glm::ivec2(16, 16)))
			{
				posPlayer.x -= speed;
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
			else if (sprite->animation() == BALL || sprite->animation() == WATER)
				sprite->changeAnimation(STAND_RIGHT);
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
				if (jumpAngle > 90) {
					bJumping = !map->collisionMoveDown(posPlayer, glm::ivec2(20, 20), &posPlayer.y);
				}
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
					posPlayer.x = (posPlayer.x / map->getTileSize()) * map->getTileSize() + 8;
					if (sprite->animation() != MOVE_UP_DOWN)
						sprite->changeAnimation(MOVE_UP_DOWN);
				}
			}
			else if (sprite->animation() == MOVE_UP_DOWN && !Game::instance().getSpecialKey(GLUT_KEY_UP))
				sprite->changeAnimation(STAND_UP);

			if (map->collisionMoveDown(posPlayer, glm::ivec2(16, 20), &posPlayer.y))
			{
				if (Game::instance().getSpecialKey(GLUT_KEY_UP) && sprite->animation() != BALL)
				{
					if (!map->collisionLiana(posPlayer, glm::ivec2(16, 20))) {
						if (!bLiana) {
							bJumping = true;
							jumpAngle = 0;
							startY = posPlayer.y;
							if (sprite->animation() == STAND_LEFT)
								sprite->changeAnimation(STAND_LEFT);
							else if (sprite->animation() == STAND_RIGHT)
								sprite->changeAnimation(STAND_RIGHT);

						}
						bLiana = false;
						if (sprite->animation() == MOVE_UP_DOWN) sprite->changeAnimation(STAND_LEFT);

						

					}
					else {
						bLiana = true;
						if (sprite->animation() != MOVE_UP_DOWN)
							sprite->changeAnimation(MOVE_UP_DOWN);
						bJumping = false;
						posPlayer.y -= FALL_STEP;
						posPlayer.x = (posPlayer.x / map->getTileSize()) * map->getTileSize() + 8;
					}
				}
				else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN) && !bLiana) {
					if (sprite->animation() != BALL) sprite->changeAnimation(BALL);
				}
				else if (map->collisionLiana(posPlayer, glm::ivec2(16, 20))) {
					if (map->getBlockCode(posPlayer) != 127 && map->getBlockCode(posPlayer) != 128 && sprite->animation() != STAND_UP && sprite->animation() != MOVE_UP_DOWN)
						sprite->changeAnimation(STAND_UP);
					else if (sprite->animation() != MOVE_RIGHT && sprite->animation() != MOVE_LEFT && sprite->animation() != STAND_LEFT && sprite->animation() != STAND_UP && sprite->animation() != MOVE_UP_DOWN)
						sprite->changeAnimation(STAND_RIGHT);
				}
				else if (sprite->animation() == MOVE_UP_DOWN && sprite->animation() != STAND_UP && !Game::instance().getSpecialKey(GLUT_KEY_DOWN))
					sprite->changeAnimation(STAND_UP);

			}
			else if (Game::instance().getKey(66) || Game::instance().getKey(98) && !map->collisionMoveUp(posPlayer, glm::ivec2(16, 16))) {
				posPlayer.y -= 5;
				if (sprite->animation() != WATER) sprite->changeAnimation(WATER);
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

int Player::getAnimDoorNum() {
	return animDoorNum;
}

void Player::setDoorCollision(bool state) {
	if (state) {
		animDoorNum = 0;
		bJumping = false;
		Status = 0;
	}
	else if (Status == 1) {
		animDoorNum = 0;
	}
	else animDoorNum = -1;
}

void Player::hurted(int damage) {
	if (sprite != spriteHurt) {
		setSprite(2);
		animationTime = 0;
	}
	life -= damage;
	
}
void Player::setSprite(int numSprite) {
	if (numSprite == 1) {
		spriteNormal->changeAnimation(sprite->animation());
		spriteHurt->changeAnimation(NONE);
		spriteNormal->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
		sprite = spriteNormal;
	}
	else {
		spriteHurt->changeAnimation(sprite->animation());
		spriteNormal->changeAnimation(NONE);
		spriteHurt->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
		sprite = spriteHurt;
	}
}

int Player::isPunching() {
	if (sprite->animation() == PUNCH_LEFT) return 1;
	else if (sprite->animation() == PUNCH_RIGHT) return 2;
	else return 0;
}

void Player::animateChange() {
	animDoorNum = 0;
	Status = 1;
}

void Player::ganeExp(int quantity) {
	exp += quantity;
}

void Player::pickPowerUp(int powerUp) {
	switch (powerUp)
	{
	case 0:
		speed *= 2;
		break;
	case 1:
		blueRaincoat = true;
		break;
	case 2:
		grayRaincoat = true;
		break;
	case 3:
		yellowSpellbook = true;
		break;
	case 4:
		blueSpellbook = true;
		break;
	default:
		break;
	}
}

bool Player::getBlueRaincoat() {
	return blueRaincoat;
}

bool Player::getGrayRaincoat() {
	return grayRaincoat;
}

bool Player::getYellowSpellbook() {
	return yellowSpellbook;
}

bool Player::getBlueSpellbook() {
	return blueSpellbook;
}

int Player::getLife() {
	return life;
}

bool Player::isHurted() {
	return sprite == spriteHurt;
}

bool Player::isBall() {
	return sprite->animation() == BALL;
}

void Player::setPoints(int points) {
	this->points += points;
}

int Player::getPoints() {
	return points;
}