#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Bone.h"
#include "Game.h"


enum BoneAnims
{
	MOVING_LEFT, MOVING_RIGHT
};

enum AnimsB
{
	BORN, DIE
};

void Bone::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, int dir)
{
	isActive = true;
	direction = dir;
	Status = 1;
	animationTime = -1;
	spritesheetMove.loadFromFile("images/huesos.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spriteMove = Sprite::createSprite(glm::ivec2(6, 6), glm::vec2(0.25, 1.0), &spritesheetMove, &shaderProgram);
	spriteMove->setNumberAnimations(2);

	spriteMove->setAnimationSpeed(MOVING_LEFT, 8);
	spriteMove->addKeyframe(MOVING_LEFT, glm::vec2(0.f, 0.f));
	spriteMove->addKeyframe(MOVING_LEFT, glm::vec2(0.25f, 0.f));
	spriteMove->addKeyframe(MOVING_LEFT, glm::vec2(0.5f, 0.f));

	spriteMove->setAnimationSpeed(MOVING_RIGHT, 8);
	spriteMove->addKeyframe(MOVING_RIGHT, glm::vec2(0.5f, 0.f));
	spriteMove->addKeyframe(MOVING_RIGHT, glm::vec2(0.25f, 0.f));
	spriteMove->addKeyframe(MOVING_RIGHT, glm::vec2(0.f, 0.f));

	spritesheetBornDie.loadFromFile("images/animaciones_cabeza_flotante.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spriteBornDie = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.5, 0.5), &spritesheetBornDie, &shaderProgram);
	spriteBornDie->setNumberAnimations(2);

	spriteBornDie->setAnimationSpeed(BORN, 8);
	spriteBornDie->addKeyframe(BORN, glm::vec2(0.f, 0.f));
	spriteBornDie->addKeyframe(BORN, glm::vec2(0.5f, 0.f));

	spriteBornDie->setAnimationSpeed(DIE, 8);
	spriteBornDie->addKeyframe(DIE, glm::vec2(0., 0.5f));
	
	tileMapDispl = tileMapPos;
	spriteMove->setScale(glm::vec3(2.f, 2.f, 0.f));
	spriteMove->setPosition(glm::vec2(float(tileMapDispl.x + posBone.x), float(tileMapDispl.y + posBone.y)));
	spriteBornDie->setScale(glm::vec3(2.f, 2.f, 0.f));
	sprite = spriteMove;
	if (direction == 1)
		sprite->changeAnimation(0);
	else sprite->changeAnimation(1);
}

void Bone::update(int deltaTime)
{
	sprite->update(deltaTime);
	if (Status == 1) {
		if (direction == 1) {
			if (map->collisionSimpleMoveLeft(posBone, glm::ivec2(6, 6))) {
				isActive = false;
			}
			else posBone.x -= 4;
		}
		else {
			if (map->collisionSimpleMoveRight(posBone, glm::ivec2(6, 6))) {
				isActive = false;
			}
			else posBone.x += 4;
		}
		if (isOut() != 0) {
			isActive = false;
		}
	}
	else if (Status == 2) {
		animationTime += deltaTime;
		if (animationTime > 500) {
			Status = 3;
			animationTime = -1;
		}
	}
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBone.x), float(tileMapDispl.y + posBone.y)));
}

void Bone::render()
{
	sprite->render();
}

void Bone::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Bone::setPosition(const glm::vec2& pos)
{
	posBone = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBone.x), float(tileMapDispl.y + posBone.y)));
}

glm::ivec2 Bone::getPosition() {
	return posBone;
}

int Bone::isOut() {
	if (posBone.x < 0) return 1;
	else if (posBone.x > 512 - 6) return 2;
	else if (posBone.y < 0) return 3;
	else if (posBone.y > 320 - 6) return 4;
	return 0;
}

void Bone::die()
{
	posBone.y -= 8;
	spriteBornDie->setPosition(glm::vec2(float(tileMapDispl.x + posBone.x), float(tileMapDispl.y + posBone.y)));
	sprite = spriteBornDie;
	spriteBornDie->changeAnimation(DIE);
	Status = 2;
	animationTime = 0;
}

int Bone::getStatus() {
	return Status;
}

int Bone::getState() {
	return isActive;
}