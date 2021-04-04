#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Intro.h"
#include "Game.h"

enum AnimsProfessor {
	STAND_RIGHT, STAND_LEFT, PAUSED_RIGHT, PAUSED_LEFT, MOVE_RIGHT, MOVE_LEFT, GIVE_FIVE_RIGHT, GIVE_FIVE_LEFT, FALL
};

enum AnimsKid {
	STAND_FRONT, STAND_FRONT_ARMS, STAND_RIGHT_KID, MOVE_RIGHT_KID
};

enum AnimsMalo {
	STAND_RIGHT_MALO, STAND_LEFT_MALO, MOVE_RIGHT_MALO, MOVE_LEFT_MALO, FINGER_RIGHT, FINGER_LEFT, FALL_MALO
};

Intro::Intro()
{

}

Intro::~Intro()
{

}

void Intro::init() {
	initShaders();
	currentTime = 0.0f;
	finished = false;
	initSpriteBackground();
	initSpriteProfesor();
	initSpriteKids();
	initSpriteMalo();
	credits = new Text[3];
	credits[0].init(glm::vec2(float(48), float(250)), texProgram, 2, 0, "JUDITH ALMONO GOMEZ AND PAU CUESTA");
	credits[1].init(glm::vec2(float(168), float(280)), texProgram, 2, 0, "VIDEOJOCS - FIB UPC");
	credits[2].init(glm::vec2(float(224), float(310)), texProgram, 2, 0, "2021-2021 Q2");
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
}

void Intro::update(int deltaTime) {
	currentTime += deltaTime;
	background->update(deltaTime);
	if (animTime < 100) {
		for (int i = 0; i < 3; ++i) credits[i].update(deltaTime);
		++animTime;
	}
	else if (animTime > 200 && animTime < 300) {
		++animTime;
	}
	else if (animTime == 300) {
		++animTime;
		malo->changeAnimation(MOVE_LEFT_MALO);
	}
	else if (animTime == 301) {
		if (posMalo.x > posKid[6].x - 1) {
			posMalo.x -= 4;
			malo->setPosition(posMalo);
		}
		else {
			malo->changeAnimation(FINGER_RIGHT);
			animTime = 401;
		}
	}
	else if (animTime > 400 && animTime < 500) {
		++animTime;
	}
	else if (animTime == 500) {
		malo->changeAnimation(MOVE_LEFT_MALO);
		profesor->changeAnimation(MOVE_LEFT);
		++animTime;
	}
	else if (animTime == 501) {
		posMalo.x -= 4;
		malo->setPosition(posMalo);
		posProfesor.x -= 4;
		profesor->setPosition(posProfesor);
		if (posProfesor.x < -128) finished = true;
	}
	else {
		if (posProfesor.x < 500) {
			posProfesor.x += 4;
			profesor->setPosition(posProfesor);
		}
		else {
			profesor->changeAnimation(PAUSED_LEFT);
			if (posKid[0].x < 450) {
				posKid[0].x += 4;
				kids[0].setPosition(posKid[0]);
			}
			else {
				kids[0].changeAnimation(STAND_FRONT);
				if (posKid[1].x < 400) {
					posKid[1].x += 4;
					kids[1].setPosition(posKid[1]);
				}
				else {
					kids[1].changeAnimation(STAND_FRONT);
					if (posKid[2].x < 350) {
						posKid[2].x += 4;
						kids[2].setPosition(posKid[2]);
					}
					else {
						kids[2].changeAnimation(STAND_FRONT);
						if (posKid[3].x < 300) {
							posKid[3].x += 4;
							kids[3].setPosition(posKid[3]);
						}
						else {
							kids[3].changeAnimation(STAND_FRONT);
							if (posKid[4].x < 250) {
								posKid[4].x += 4;
								kids[4].setPosition(posKid[4]);
							}
							else {
								kids[4].changeAnimation(STAND_FRONT);
								if (posKid[5].x < 200) {
									posKid[5].x += 4;
									kids[5].setPosition(posKid[5]);
								}
								else {
									kids[5].changeAnimation(STAND_FRONT);
									if (posKid[6].x < 150) {
										posKid[6].x += 4;
										kids[6].setPosition(posKid[6]);
									}
									else {
										kids[6].changeAnimation(STAND_FRONT);
										posMalo.x -= 4;
										malo->setPosition(posMalo);
										if (posProfesor.x + 32 == posMalo.x) {
											animTime = 201;
											malo->changeAnimation(STAND_LEFT_MALO);
											profesor->changeAnimation(FALL);
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	profesor->update(deltaTime);
	for (int i = 0; i < 7; ++i) if (posMalo.x > posKid[i].x) kids[i].update(deltaTime);
	malo->update(deltaTime);
}

void Intro::render() {
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	background->render();
	if (animTime < 100)
		for (int i = 0; i < 3; ++i) credits[i].render();
	else {
		if (posProfesor.x > -32) profesor->render();
		for (int i = 0; i < 7; ++i) if (posKid[i].x > -32 && posMalo.x > posKid[i].x) kids[i].render();
		if (posMalo.x < 640) malo->render();
	}
}

void Intro::initSpriteBackground() {
	spritesheetBackground.loadFromFile("images/pantalla_inicial.png", TEXTURE_PIXEL_FORMAT_RGBA);
	background = new Sprite();
	background = Sprite::createSprite(glm::ivec2(256, 191), glm::vec2(1.0, 1.0), &spritesheetBackground, &texProgram);
	background->setNumberAnimations(1);

	background->setAnimationSpeed(0, 8);
	background->addKeyframe(0, glm::vec2(0.f, 0.f));

	background->changeAnimation(0);
	background->setPosition(glm::vec2(float(64), float(50)));
	background->setScale(glm::vec3(2.0f, 2.0f, 0.f));
}

void Intro::initSpriteProfesor() {
	spritesheetProfessor.loadFromFile("images/profesor.png", TEXTURE_PIXEL_FORMAT_RGBA);
	profesor = new Sprite();
	profesor = Sprite::createSprite(glm::ivec2(16, 28), glm::vec2(0.25, 0.25), &spritesheetProfessor, &texProgram);
	profesor->setNumberAnimations(9);

	profesor->setAnimationSpeed(STAND_RIGHT, 8);
	profesor->addKeyframe(STAND_RIGHT, glm::vec2(0.f, 0.f));

	profesor->setAnimationSpeed(STAND_LEFT, 8);
	profesor->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.25f));

	profesor->setAnimationSpeed(PAUSED_RIGHT, 8);
	profesor->addKeyframe(PAUSED_RIGHT, glm::vec2(0.25f, 0.f));

	profesor->setAnimationSpeed(PAUSED_LEFT, 8);
	profesor->addKeyframe(PAUSED_LEFT, glm::vec2(0.25f, 0.25f));

	profesor->setAnimationSpeed(MOVE_RIGHT, 8);
	profesor->addKeyframe(MOVE_RIGHT, glm::vec2(0.5f, 0.f));
	profesor->addKeyframe(MOVE_RIGHT, glm::vec2(0.755f, 0.f));
	profesor->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.f));

	profesor->setAnimationSpeed(MOVE_LEFT, 8);
	profesor->addKeyframe(MOVE_LEFT, glm::vec2(0.5f, 0.25f));
	profesor->addKeyframe(MOVE_LEFT, glm::vec2(0.755f, 0.25f));
	profesor->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.25f));

	profesor->setAnimationSpeed(GIVE_FIVE_RIGHT, 8);
	profesor->addKeyframe(GIVE_FIVE_RIGHT, glm::vec2(0.0f, 0.5f));

	profesor->setAnimationSpeed(GIVE_FIVE_LEFT, 8);
	profesor->addKeyframe(GIVE_FIVE_LEFT, glm::vec2(0.25f, 0.5f));

	profesor->setAnimationSpeed(FALL, 8);
	profesor->addKeyframe(FALL, glm::vec2(0.5f, 0.5f));
	profesor->addKeyframe(FALL, glm::vec2(0.75f, 0.5f));

	profesor->changeAnimation(MOVE_RIGHT);
	posProfesor = glm::vec2(-32.f, 250.f);
	profesor->setPosition(posProfesor);
	profesor->setScale(glm::vec3(2.0f, 2.0f, 0.f));
}

void Intro::initSpriteKids() {
	spritesheetKids.loadFromFile("images/ninos.png", TEXTURE_PIXEL_FORMAT_RGBA);
	kids = new Sprite[7];
	for (int i = 0; i < 7; ++i) {
		kids[i] = *Sprite::createSprite(glm::ivec2(16, 22), glm::vec2(0.5, 0.5), &spritesheetKids, &texProgram);
		kids[i].setNumberAnimations(4);

		kids[i].setAnimationSpeed(STAND_FRONT, 8);
		kids[i].addKeyframe(STAND_FRONT, glm::vec2(0.f, 0.f));

		kids[i].setAnimationSpeed(STAND_FRONT_ARMS, 8);
		kids[i].addKeyframe(STAND_FRONT_ARMS, glm::vec2(0.5f, 0.f));

		kids[i].setAnimationSpeed(STAND_RIGHT_KID, 8);
		kids[i].addKeyframe(STAND_RIGHT_KID, glm::vec2(0.f, 0.5f));

		kids[i].setAnimationSpeed(MOVE_RIGHT_KID, 8);
		kids[i].addKeyframe(MOVE_RIGHT_KID, glm::vec2(0.5f, 0.5f));
		kids[i].addKeyframe(MOVE_RIGHT_KID, glm::vec2(0.f, 0.5f));

		kids[i].changeAnimation(MOVE_RIGHT_KID);
		posKid[i] = glm::vec2(-32.f, 262.f);
		kids[i].setPosition(posKid[i]);
		kids[i].setScale(glm::vec3(2.0f, 2.0f, 0.f));
	}
}

void Intro::initSpriteMalo() {
	spritesheetMalo.loadFromFile("images/malo.png", TEXTURE_PIXEL_FORMAT_RGBA);
	malo = new Sprite();
	malo = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.5, 0.25), &spritesheetMalo, &texProgram);
	malo->setNumberAnimations(7);

	malo->setAnimationSpeed(STAND_RIGHT_MALO, 8);
	malo->addKeyframe(STAND_RIGHT_MALO, glm::vec2(0.f, 0.f));

	malo->setAnimationSpeed(STAND_LEFT_MALO, 8);
	malo->addKeyframe(STAND_LEFT_MALO, glm::vec2(0.f, 0.25f));

	malo->setAnimationSpeed(MOVE_RIGHT_MALO, 8);
	malo->addKeyframe(MOVE_RIGHT_MALO, glm::vec2(0.5f, 0.f));
	malo->addKeyframe(MOVE_RIGHT_MALO, glm::vec2(0.f, 0.f));

	malo->setAnimationSpeed(MOVE_LEFT_MALO, 8);
	malo->addKeyframe(MOVE_LEFT_MALO, glm::vec2(0.5f, 0.25f));
	malo->addKeyframe(MOVE_LEFT_MALO, glm::vec2(0.f, 0.25f));

	malo->setAnimationSpeed(FINGER_RIGHT, 8);
	malo->addKeyframe(FINGER_RIGHT, glm::vec2(0.5f, 0.f));

	malo->setAnimationSpeed(FINGER_LEFT, 8);
	malo->addKeyframe(FINGER_LEFT, glm::vec2(0.5f, 0.25f));

	malo->setAnimationSpeed(FALL_MALO, 8);
	malo->addKeyframe(FALL_MALO, glm::vec2(0.0f, 0.5f));
	malo->addKeyframe(FALL_MALO, glm::vec2(0.5f, 0.5f));

	malo->changeAnimation(MOVE_LEFT_MALO);
	posMalo = glm::vec2(640.f, 242.f);
	malo->setPosition(posMalo);
	malo->setScale(glm::vec3(2.0f, 2.0f, 0.f));
}

bool Intro::isFinished() {
	return finished;
}

void Intro::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if (!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}

