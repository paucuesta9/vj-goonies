#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "CabezaFlotante.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4

enum AnimsM
{
	MOVE_LEFT, MOVE_RIGHT
};

enum AnimsB
{
	BORN, DIE
};


void CabezaFlotante::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	animationTime = 0;
	Status = 0;
	spritesheetMovement.loadFromFile("images/cabeza_volante.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spriteMovement = Sprite::createSprite(glm::ivec2(16, 20), glm::vec2(0.5, 0.5), &spritesheetMovement, &shaderProgram);
	spriteMovement->setNumberAnimations(2);

	spriteMovement->setAnimationSpeed(MOVE_LEFT, 8);
	spriteMovement->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.f));
	spriteMovement->addKeyframe(MOVE_LEFT, glm::vec2(0.5f, 0.f));

	spriteMovement->setAnimationSpeed(MOVE_RIGHT, 8);
	spriteMovement->addKeyframe(MOVE_RIGHT, glm::vec2(0., 0.5f));
	spriteMovement->addKeyframe(MOVE_RIGHT, glm::vec2(0.5, 0.5f));

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
	spriteBornDie->setPosition(glm::vec2(float(tileMapDispl.x + posCabeza.x), float(tileMapDispl.y + posCabeza.y)));
	spriteMovement->setPosition(glm::vec2(float(tileMapDispl.x + posCabeza.x), float(tileMapDispl.y + posCabeza.y)));
	spriteBornDie->setScale(glm::vec3(2.f, 2.f, 0.f));
	sprite = spriteBornDie;
}

void CabezaFlotante::update(int deltaTime)
{
	sprite->update(deltaTime);
	if (animationTime != -1) {
		animationTime += deltaTime;
		if (Status == 0) {
			if (animationTime > 1000) {
				sprite = spriteMovement;
				sprite->changeAnimation(MOVE_LEFT);
				Status = 1;
				animationTime = -1;
			}
		}
		else if (Status == 2) {
			if (animationTime > 500) {
				Status = 3;
				animationTime = -1;
			}
		}
	}
	if (Status == 1) {
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
		else if (sprite->animation() == MOVE_RIGHT) {
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

void CabezaFlotante::die()
{
	spriteBornDie->setPosition(glm::vec2(float(tileMapDispl.x + posCabeza.x), float(tileMapDispl.y + posCabeza.y)));
	sprite = spriteBornDie;
	Status = 2;
	animationTime = 0;
}

glm::ivec2 CabezaFlotante::getPosition() {
	return posCabeza;
}

int CabezaFlotante::getStatus() {
	return Status;
}