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
	timeAnimation = -1;
	animationPhase = -1;
	spritesheet.loadFromFile("images/esqueleto.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.5, 0.5), &spritesheet, &shaderProgram);
	shader = shaderProgram;
	sprite->setNumberAnimations(4);

	sprite->setAnimationSpeed(STAND_RIGHT, 8);
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.5f, 0.f));

	sprite->setAnimationSpeed(MOVE_RIGHT, 8);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.5f, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(STAND_LEFT, 8);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.5f, 0.5f));

	sprite->setAnimationSpeed(MOVE_LEFT, 8);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.5f, 0.5f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.5f));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setScale(glm::vec3(2.f, 2.f, 0.f));
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEsqueleto.x), float(tileMapDispl.y + posEsqueleto.y)));
}

void Esqueleto::update(int deltaTime)
{
	sprite->update(deltaTime); 
	if (bone != NULL) bone->update(deltaTime);
	if (timeAnimation != -1) {
		timeAnimation += deltaTime;
		if (timeAnimation > 2000 && animationPhase == 3) {
			if (sprite->animation() == STAND_RIGHT) {
				posEsqueleto.x += 2;
				sprite->changeAnimation(MOVE_RIGHT);
			}
			else {
				posEsqueleto.x -= 2;
				sprite->changeAnimation(MOVE_LEFT);
			}
			timeAnimation = -1;
			animationPhase = -1;
		}
		else if (timeAnimation > 900 && animationPhase == 2) {
			if (sprite->animation() == STAND_RIGHT) sprite->changeAnimation(STAND_LEFT);
			else sprite->changeAnimation(STAND_RIGHT);
			throwBone();
			++animationPhase;
		}
		else if (timeAnimation > 600 && animationPhase == 1) {
			if (sprite->animation() == STAND_RIGHT) sprite->changeAnimation(STAND_LEFT);
			else sprite->changeAnimation(STAND_RIGHT);
			++animationPhase;
		}
		else if (timeAnimation > 300 && animationPhase == 0) {
			if (sprite->animation() == MOVE_RIGHT) sprite->changeAnimation(STAND_LEFT);
			else sprite->changeAnimation(STAND_RIGHT);
			++animationPhase;
		}
	}
	else if (sprite->animation() == MOVE_LEFT) {
		posEsqueleto.y += 4;
		if (map->collisionMoveDown(glm::vec2(posEsqueleto.x, posEsqueleto.y), glm::ivec2(16, 20), &posEsqueleto.y)) {
			if (map->collisionMoveLeft(posEsqueleto, glm::ivec2(16, 16))) {
				startAnimationAndThrowBone();
			}
			else {
				posEsqueleto.x -= 2;
			}
		}
		else {
			sprite->changeAnimation(MOVE_RIGHT);
			posEsqueleto.x += 2;
		}
	}
	else {
		posEsqueleto.y += 4;
		if (map->collisionMoveDown(glm::vec2(posEsqueleto.x, posEsqueleto.y), glm::ivec2(16, 20), &posEsqueleto.y)) {
			if (map->collisionMoveRight(posEsqueleto, glm::ivec2(16, 16))) {
				startAnimationAndThrowBone();
			}
			else {
				posEsqueleto.x += 2;
			}
		}
		else {
			sprite->changeAnimation(MOVE_LEFT);
			posEsqueleto.x -= 2;
		}
	}
	if (bone != NULL) {
		if (!bone->getState()) {
			deleteBone();
		}

	}
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEsqueleto.x), float(tileMapDispl.y + posEsqueleto.y)));
}

void Esqueleto::render()
{
	sprite->render();
	if (bone != NULL) bone->render();
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

void Esqueleto::startAnimationAndThrowBone() {
	timeAnimation = 0;
	animationPhase = 0;
}

void Esqueleto::throwBone() {
	if (bone == NULL) {
		if (sprite->animation() == STAND_LEFT) {
			bone = new Bone();
			bone->init(glm::vec2(60, 70), shader, 1);
			bone->setPosition(glm::vec2(posEsqueleto.x - 6, posEsqueleto.y + 8));
			bone->setTileMap(map);
		}
		else {
			bone = new Bone();
			bone->init(glm::vec2(60, 70), shader, 2);
			bone->setPosition(glm::vec2(posEsqueleto.x + 16, posEsqueleto.y + 8));
			bone->setTileMap(map);
		}
	}
}

bool Esqueleto::isThereBone() {
	return bone != NULL;
}

glm::ivec2 Esqueleto::getBonePosition() {
	return bone->getPosition();
}

void Esqueleto::deleteBone() {
	delete bone;
	bone = NULL;
}