#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "MenuSuperior.h"
#include "Game.h"


enum Vitalidad_Experiencia
{
	VIT1, VIT2, VIT3, VIT4, VIT5, VIT6, VIT7,VIT8, EXP1, EXP2, EXP3, EXP4, EXP5, EXP6, EXP7, EXP8, INICIO, FIN, VACIO
};


MenuSuperior::~MenuSuperior() {
	if (spriteVitExp != NULL)
		delete spriteVitExp;
}

void MenuSuperior::init(glm::ivec2 pos, ShaderProgram& shaderProgram)
{
	spriteVitExp = new Sprite[24];
	spritesheetVitExp.loadFromFile("images/vida_experiencia.png", TEXTURE_PIXEL_FORMAT_RGBA);
	for (int i = 0; i < 24; ++i) {
		spriteVitExp[i] = *Sprite::createSprite(glm::ivec2(8, 8), glm::vec2(0.125, 0.25), &spritesheetVitExp, &shaderProgram);
		spriteVitExp[i].setNumberAnimations(19);

		spriteVitExp[i].setAnimationSpeed(VIT1, 8);
		spriteVitExp[i].addKeyframe(VIT1, glm::vec2(0.0f, 0.0f));

		spriteVitExp[i].setAnimationSpeed(VIT2, 8);
		spriteVitExp[i].addKeyframe(VIT2, glm::vec2(0.125f, 0.0f));

		spriteVitExp[i].setAnimationSpeed(VIT3, 8);
		spriteVitExp[i].addKeyframe(VIT3, glm::vec2(0.25f, 0.0f));

		spriteVitExp[i].setAnimationSpeed(VIT4, 8);
		spriteVitExp[i].addKeyframe(VIT4, glm::vec2(0.375f, 0.0f));

		spriteVitExp[i].setAnimationSpeed(VIT5, 8);
		spriteVitExp[i].addKeyframe(VIT5, glm::vec2(0.5f, 0.0f));

		spriteVitExp[i].setAnimationSpeed(VIT6, 8);
		spriteVitExp[i].addKeyframe(VIT6, glm::vec2(0.625f, 0.0f));

		spriteVitExp[i].setAnimationSpeed(VIT7, 8);
		spriteVitExp[i].addKeyframe(VIT7, glm::vec2(0.75f, 0.0f));

		spriteVitExp[i].setAnimationSpeed(VIT8, 8);
		spriteVitExp[i].addKeyframe(VIT8, glm::vec2(0.875f, 0.0f));

		spriteVitExp[i].setAnimationSpeed(EXP1, 8);
		spriteVitExp[i].addKeyframe(EXP1, glm::vec2(0.0f, 0.25f));

		spriteVitExp[i].setAnimationSpeed(EXP2, 8);
		spriteVitExp[i].addKeyframe(EXP2, glm::vec2(0.125f, 0.25f));

		spriteVitExp[i].setAnimationSpeed(EXP3, 8);
		spriteVitExp[i].addKeyframe(EXP3, glm::vec2(0.25f, 0.25f));

		spriteVitExp[i].setAnimationSpeed(EXP4, 8);
		spriteVitExp[i].addKeyframe(EXP4, glm::vec2(0.375f, 0.25f));

		spriteVitExp[i].setAnimationSpeed(EXP5, 8);
		spriteVitExp[i].addKeyframe(EXP5, glm::vec2(0.5f, 0.25f));

		spriteVitExp[i].setAnimationSpeed(EXP6, 8);
		spriteVitExp[i].addKeyframe(EXP6, glm::vec2(0.625f, 0.25f));

		spriteVitExp[i].setAnimationSpeed(EXP7, 8);
		spriteVitExp[i].addKeyframe(EXP7, glm::vec2(0.75f, 0.25f));

		spriteVitExp[i].setAnimationSpeed(EXP8, 8);
		spriteVitExp[i].addKeyframe(EXP8, glm::vec2(0.875f, 0.25f));

		spriteVitExp[i].setAnimationSpeed(INICIO, 8);
		spriteVitExp[i].addKeyframe(INICIO, glm::vec2(0.0f, 0.5f));

		spriteVitExp[i].setAnimationSpeed(FIN, 8);
		spriteVitExp[i].addKeyframe(FIN, glm::vec2(0.125f, 0.5f));

		spriteVitExp[i].setAnimationSpeed(VACIO, 8);
		spriteVitExp[i].addKeyframe(VACIO, glm::vec2(0.25f, 0.5f));

		if (i == 0 || i == 12) spriteVitExp[i].changeAnimation(INICIO);
		else if (i == 23 || i == 11) spriteVitExp[i].changeAnimation(FIN);
		else spriteVitExp[i].changeAnimation(VACIO);
		if (i < 12) spriteVitExp[i].setPosition(glm::vec2(float(pos.x + i*16 + 200), float(pos.y - 36)));
		else spriteVitExp[i].setPosition(glm::vec2(float(pos.x + (i%12)*16 + 200), float(pos.y - 20)));
		spriteVitExp[i].setScale(glm::vec3(2.f, 2.f, 0.f));
	}
}

void MenuSuperior::update(int deltaTime)
{
	for (int i = 0; i < 24; ++i)
		spriteVitExp[i].update(deltaTime);
}

void MenuSuperior::render()
{
	for (int i = 0; i < 24; ++i)
		spriteVitExp[i].render();
}

void MenuSuperior::calculateVitExp(int vit, int exp) {
	int Vit8 = vit / 100 + 1;
	int aux = vit % 100;
	for (int i = 1; i < Vit8; ++i) spriteVitExp[i].changeAnimation(VIT8);
	for (int i = Vit8+1; i < 11; ++i) spriteVitExp[i].changeAnimation(VACIO);
	if (aux < 3) spriteVitExp[Vit8].changeAnimation(VIT1);
	else if (aux < 7) spriteVitExp[Vit8].changeAnimation(VIT2);
	else if (aux < 15) spriteVitExp[Vit8].changeAnimation(VIT3);
	else if (aux < 30) spriteVitExp[Vit8].changeAnimation(VIT4);
	else if (aux < 60) spriteVitExp[Vit8].changeAnimation(VIT5);
	else if (aux < 85) spriteVitExp[Vit8].changeAnimation(VIT6);
	else if (aux < 95) spriteVitExp[Vit8].changeAnimation(VIT7);
}



