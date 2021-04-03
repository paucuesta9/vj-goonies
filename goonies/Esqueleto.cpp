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
	STAND_RIGHT, MOVE_RIGHT, STAND_LEFT, MOVE_LEFT
};

enum AnimsB
{
	BORN, DIE
};

void Esqueleto::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	timeAnimation = 0;
	animationPhase = -1;
	Status = 0;
	spritesheetMovement.loadFromFile("images/esqueleto.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spriteMove = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.5, 0.5), &spritesheetMovement, &shaderProgram);
	shader = shaderProgram;
	spriteMove->setNumberAnimations(4);

	spriteMove->setAnimationSpeed(STAND_RIGHT, 8);
	spriteMove->addKeyframe(STAND_RIGHT, glm::vec2(0.5f, 0.f));

	spriteMove->setAnimationSpeed(MOVE_RIGHT, 8);
	spriteMove->addKeyframe(MOVE_RIGHT, glm::vec2(0.5f, 0.f));
	spriteMove->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.f));

	spriteMove->setAnimationSpeed(STAND_LEFT, 8);
	spriteMove->addKeyframe(STAND_LEFT, glm::vec2(0.5f, 0.5f));

	spriteMove->setAnimationSpeed(MOVE_LEFT, 8);
	spriteMove->addKeyframe(MOVE_LEFT, glm::vec2(0.5f, 0.5f));
	spriteMove->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.5f));

	spritesheetBornDie.loadFromFile("images/animaciones_cabeza_flotante.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spriteBornDie = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.5, 0.5), &spritesheetBornDie, &shaderProgram);
	spriteBornDie->setNumberAnimations(2);

	spriteBornDie->setAnimationSpeed(BORN, 8);
	spriteBornDie->addKeyframe(BORN, glm::vec2(0.f, 0.f));
	spriteBornDie->addKeyframe(BORN, glm::vec2(0.5f, 0.f));

	spriteBornDie->setAnimationSpeed(DIE, 8);
	spriteBornDie->addKeyframe(DIE, glm::vec2(0., 0.5f));

	spriteBornDie->changeAnimation(BORN);
	tileMapDispl = tileMapPos;
	posEsqueleto.y -= 8;
	spriteMove->setPosition(glm::vec2(float(tileMapDispl.x + posEsqueleto.x), float(tileMapDispl.y + posEsqueleto.y)));
	spriteMove->setScale(glm::vec3(2.f, 2.f, 0.f));
	spriteBornDie->setPosition(glm::vec2(float(tileMapDispl.x + posEsqueleto.x), float(tileMapDispl.y + posEsqueleto.y)));
	spriteBornDie->setScale(glm::vec3(2.f, 2.f, 0.f));
	sprite = spriteBornDie;
	
}

void Esqueleto::update(int deltaTime)
{
	sprite->update(deltaTime); 
	if (Status == 1) {
		if (bone != NULL) bone->update(deltaTime);
		/*srand(time(NULL));
		if (deltaTime * rand() % 500 < 20) {
			if (sprite->animation() == MOVE_RIGHT)
				sprite->changeAnimation(STAND_RIGHT);
			else if (sprite->animation() == MOVE_LEFT)
				sprite->changeAnimation(STAND_LEFT);
			throwBone();
			timeAnimation = 900;
			animationPhase = 3;
		}*/
	} 
	if (timeAnimation != -1) {
		timeAnimation += deltaTime;
		if (Status == 0) {
			if (timeAnimation > 1000) {
				sprite = spriteMove;
				sprite->changeAnimation(MOVE_LEFT);
				Status = 1;
				timeAnimation = -1;
			}
		}
		if (Status == 1) {
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
		else if (Status == 2) {
			if (timeAnimation > 500) {
				Status = 3;
				timeAnimation = -1;
			}
		}
	}
	else if (isOut() != 0) startAnimationAndThrowBone();
	else if (sprite->animation() == MOVE_LEFT) {
		posEsqueleto.y += 4;
		if (map->collisionMoveDown(glm::vec2(posEsqueleto.x - 8, posEsqueleto.y), glm::ivec2(16, 20), &posEsqueleto.y)) {
			if (map->collisionSimpleMoveLeft(posEsqueleto, glm::ivec2(16, 16))) {
				startAnimationAndThrowBone();
			}
			else {
				posEsqueleto.x -= 2;
			}
		}
		else {
			startAnimationAndThrowBone();
			posEsqueleto.y -= 4;
		}
	}
	else if (sprite->animation() == MOVE_RIGHT) {
		posEsqueleto.y += 4;
		if (map->collisionMoveDown(glm::vec2(posEsqueleto.x + 24, posEsqueleto.y), glm::ivec2(16, 20), &posEsqueleto.y)) {
			if (map->collisionSimpleMoveRight(posEsqueleto, glm::ivec2(16, 16))) {
				startAnimationAndThrowBone();
			}
			else {
				posEsqueleto.x += 2;
			}
		}
		else {
			startAnimationAndThrowBone();
			posEsqueleto.y -= 4;
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
	return 0;
}

void Esqueleto::die(const glm::vec2& pos)
{
	posEsqueleto = pos;
	spriteBornDie->setPosition(glm::vec2(float(tileMapDispl.x + posEsqueleto.x), float(tileMapDispl.y + posEsqueleto.y)));
	sprite = spriteBornDie;
	spriteBornDie->changeAnimation(DIE);
	Status = 2;
	timeAnimation = 0;
}

int Esqueleto::getStatus() {
	return Status;
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

int Esqueleto::getBoneStatus() {
	return bone->getStatus();
}

void Esqueleto::dieBone() {
	bone->die();
}

void Esqueleto::deleteBone() {
	delete bone;
	bone = NULL;
}