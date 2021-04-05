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
	shader = shaderProgram;
	int high = 0;
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
		else if (i < 12) spriteVitExp[i].changeAnimation(VIT8);
		else spriteVitExp[i].changeAnimation(VACIO);
		if (i < 12) spriteVitExp[i].setPosition(glm::vec2(float(pos.x + i*16 + 220), float(pos.y - 36)));
		else spriteVitExp[i].setPosition(glm::vec2(float(pos.x + (i%12)*16 + 220), float(pos.y - 20)));
		spriteVitExp[i].setScale(glm::vec3(2.f, 2.f, 0.f));

		text = new Text[8];
		text[0].init(glm::vec2(float(pos.x + 176), float(pos.y - 36)), shaderProgram, 2, 0, "VIT");
		text[1].init(glm::vec2(float(pos.x + 176), float(pos.y - 20)), shaderProgram, 2, 0, "EXP");
		text[2].init(glm::vec2(float(pos.x + 420), float(pos.y - 36)), shaderProgram, 2, 0, "SCENE");
		text[3].init(glm::vec2(float(pos.x + 420), float(pos.y - 20)), shaderProgram, 2, 0, "01-01");
		text[4].init(glm::vec2(float(pos.x), float(pos.y - 36)), shaderProgram, 2, 0, "HI-");
		text[5].init(glm::vec2(float(pos.x + 50), float(pos.y - 36)), shaderProgram, 2, 0, "000000");
		text[6].init(glm::vec2(float(pos.x), float(pos.y - 20)), shaderProgram, 2, 0, "1P-");
		text[7].init(glm::vec2(float(pos.x + 50), float(pos.y - 20)), shaderProgram, 2, 0, "000000");

	}
}

void MenuSuperior::restart() {
	text[0].init(glm::vec2(float(60 + 176), float(70 - 36)), shader, 2, 0, "VIT");
	text[1].init(glm::vec2(float(60 + 176), float(70 - 20)), shader, 2, 0, "EXP");
	text[2].init(glm::vec2(float(60 + 420), float(70 - 36)), shader, 2, 0, "SCENE");
	text[3].init(glm::vec2(float(60 + 420), float(70 - 20)), shader, 2, 0, "01-01");
	text[6].init(glm::vec2(float(60), float(70 - 20)), shader, 2, 0, "1P-");
	text[7].init(glm::vec2(float(60 + 50), float(70 - 20)), shader, 2, 0, "000000");
	calculateVitExp(1000, 0);
	calculateVitExp(0, 1);
}

void MenuSuperior::update(int deltaTime)
{
	for (int i = 0; i < 24; ++i) spriteVitExp[i].update(deltaTime);
	for (int i = 0; i < 8; ++i) text[i].update(deltaTime);
}

void MenuSuperior::render()
{
	for (int i = 0; i < 24; ++i) spriteVitExp[i].render();
	for (int i = 0; i < 8; ++i) text[i].render();
}

void MenuSuperior::calculateVitExp(int vitExp, int option) {
	int VitExp8 = vitExp / 100 + 1;
	if (VitExp8 < 0) VitExp8 = 0;
	int aux = vitExp % 100;
	if (option == 0) {
		for (int i = 1; i < VitExp8; ++i) spriteVitExp[i].changeAnimation(VIT8);
		for (int i = VitExp8 + 1; i < 11; ++i) spriteVitExp[i].changeAnimation(VACIO);
		if (aux > 0) {
		if (aux < 3) spriteVitExp[VitExp8].changeAnimation(VIT1);
		else if (aux < 7) spriteVitExp[VitExp8].changeAnimation(VIT2);
		else if (aux < 15) spriteVitExp[VitExp8].changeAnimation(VIT3);
		else if (aux < 30) spriteVitExp[VitExp8].changeAnimation(VIT4);
		else if (aux < 60) spriteVitExp[VitExp8].changeAnimation(VIT5);
		else if (aux < 85) spriteVitExp[VitExp8].changeAnimation(VIT6);
		else if (aux < 95) spriteVitExp[VitExp8].changeAnimation(VIT7);
		}
	}
	else {
		VitExp8 += 12;
		if (vitExp >= 1000) {
			aux = 100;
			VitExp8 = 23;
		}
		for (int i = 13; i < VitExp8; ++i) spriteVitExp[i].changeAnimation(EXP8);
		for (int i = VitExp8 + 1; i < 23; ++i) spriteVitExp[i].changeAnimation(VACIO);
		if (aux < 3) spriteVitExp[VitExp8].changeAnimation(EXP1);
		else if (aux < 7) spriteVitExp[VitExp8].changeAnimation(EXP2);
		else if (aux < 15) spriteVitExp[VitExp8].changeAnimation(EXP3);
		else if (aux < 30) spriteVitExp[VitExp8].changeAnimation(EXP4);
		else if (aux < 60) spriteVitExp[VitExp8].changeAnimation(EXP5);
		else if (aux < 85) spriteVitExp[VitExp8].changeAnimation(EXP6);
		else if (aux < 95) spriteVitExp[VitExp8].changeAnimation(EXP7);
	}
}

void MenuSuperior::setScreen(int scene, int screen) {
	string num = "0" + to_string(scene) + "-0"+ to_string(screen);
	text[3].setText(num);
}

void MenuSuperior::setPoints(int points) {
	string num = to_string(points);
	while (num.size() != 6) num = "0" + num;
	text[7].setText(num);
	if (points > high) {
		text[5].setText(num);
		high = points;
	}
}



