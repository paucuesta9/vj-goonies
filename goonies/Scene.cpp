#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"


#define SCREEN_X 60 //Posicion del nivel respecto la pantalla X
#define SCREEN_Y 70 //Posicion del nivel respecto la pantalla Y

#define INIT_PLAYER_X_TILES 22 //Posici�n X inicial del jugador contando en TILES (cuadrados)
#define INIT_PLAYER_Y_TILES 4 //Posici�n Y inicial del jugador contando en TILES (cuadrados)


Scene::Scene()
{
	map = NULL;
	player = NULL;
	cabezaFlotante = NULL;
	esqueleto = NULL;
	cascada = NULL;
	aspersor = NULL;
	gota = NULL;
	skullDoor = NULL;
	greenDoor = NULL;
	startEndDoor = NULL;
	object = NULL;
	menuInferior = NULL;
	menuSuperior = NULL;
	friends = NULL;
}

Scene::~Scene()
{
}

void Scene::init()
{
	initShaders();
	menuInferior = new MenuInferior();
	menuInferior->init(glm::ivec2(SCREEN_X, SCREEN_Y + 20 * 16), texProgram);
	menuSuperior = new MenuSuperior();
	menuSuperior->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
}

void Scene::restart() {
	sceneNum = 1;
	screenNum = 1;
	numAsp = 0;
	numCasc = 0;
	numGotas = 0;
	numSkullDoors = 0;
	numGreenDoors = 0;
	numObjects = 0;
	numFriends = 0;
	numPowerUp = -1;
	sceneToChange = 0;
	for (int i = 0; i < 6; ++i) timeFriend[i] = -1;
	first = true;
	pressedN = false;
	releasedN = false;
	pressedG = false;
	releasedG = false;
	changingScene = false;
	win = false;
	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	menuInferior->restart();
	menuSuperior->restart();
	for (int i = 0; i < 5; ++i) special[i] = false;
	initObjects(texProgram);
	initFriends(texProgram);
	changeScreen(sceneNum, screenNum, glm::vec2(INIT_PLAYER_X_TILES * 16 + 8, INIT_PLAYER_Y_TILES * 16 + 4));
	startEndDoor = new StartEndDoor();
	startEndDoor->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(22 * map->getTileSize(), 3 * map->getTileSize()), 1);
	currentTime = 0.0f;
}

bool Scene::isGameOver() {
	return player->getLife() <= 0;
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	player->update(deltaTime);
	glm::vec2 pos = player->getPosition();
	if (Game::instance().getKey(110)) pressedN = true;
	else if (pressedN) releasedN = true;

	if (Game::instance().getKey(103)) pressedG = true;
	else if (pressedG) releasedG = true;

	if (Game::instance().getKey(115)) pressedS = true;
	else if (pressedS) releasedS = true;

	if (Game::instance().getKey(49)) pressed1 = true;
	else if (pressed1) released1 = true;

	if (Game::instance().getKey(50)) pressed2 = true;
	else if (pressed2) released2 = true;

	if (Game::instance().getKey(51)) pressed3 = true;
	else if (pressed3) released3 = true;

	if (Game::instance().getKey(52)) pressed4 = true;
	else if (pressed4) released4 = true;

	if (Game::instance().getKey(53)) pressed5 = true;
	else if (pressed5) released5 = true;

	if (releasedN) {
		pressedN = releasedN = false;
		if (numFriends < 6) {
			++numFriends;
			menuInferior->savedNewFriend();
			if (startEndDoor != NULL && sceneNum == 5 && screenNum == 3 && numFriends == 6) startEndDoor->open();
		}
	}

	if (releasedG) {
		pressedG = releasedG = false;
		player->swapGodMode();
	}

	if (released1) {
		pressed1 = released1 = false;
		if (releasedS) {
			pressedS = releasedS = false;
			sceneToChange = 1;
		}
		else if (sceneToChange != 0) {
			int tileSize = map->getTileSize();
			if (sceneToChange == 1) changeScreen(sceneToChange, 1, glm::vec2(22 * tileSize, 4 * tileSize));
			else if (sceneToChange == 2) changeScreen(sceneToChange, 1, glm::vec2(5 * tileSize, 3 * tileSize));
			else if (sceneToChange == 3) changeScreen(sceneToChange, 1, glm::vec2(14 * tileSize, 16 * tileSize));
			else if (sceneToChange == 4) changeScreen(sceneToChange, 1, glm::vec2(4 * tileSize, 13 * tileSize));
			else if (sceneToChange == 5) changeScreen(sceneToChange, 1, glm::vec2(3 * tileSize, 3 * tileSize));
			sceneToChange = 0;
		}
		else if (sceneToChange == 0) {
			if (!player->hasPowerUp(0)) {
				player->setPowerUp(0, true);
				menuInferior->setPowerUp(0);
				menuInferior->update(deltaTime);
				special[0] = true;
			}
			else {
				player->setPowerUp(0, false);
				menuInferior->deletePowerUp(0);
				menuInferior->update(deltaTime);
				special[0] = false;
			}
		}
	}

	if (released2) {
		pressed2 = released2 = false;
		if (releasedS) {
			pressedS = releasedS = false;
			sceneToChange = 2;
		}
		else if (sceneToChange != 0) {
			int tileSize = map->getTileSize();
			if (sceneToChange == 1) changeScreen(sceneToChange, 2, glm::vec2(5 * tileSize, 6 * tileSize));
			else if (sceneToChange == 2) changeScreen(sceneToChange, 2, glm::vec2(1 * tileSize, 3 * tileSize));
			else if (sceneToChange == 3) changeScreen(sceneToChange, 2, glm::vec2(1 * tileSize, 7 * tileSize));
			else if (sceneToChange == 4) changeScreen(sceneToChange, 2, glm::vec2(28 * tileSize, 16 * tileSize));
			else if (sceneToChange == 5) changeScreen(sceneToChange, 2, glm::vec2(1 * tileSize, 1 * tileSize));
			sceneToChange = 0;
		}
		else if (sceneToChange == 0) {
			if (!player->hasPowerUp(1)) {
				player->setPowerUp(1, true);
				menuInferior->setPowerUp(1);
				menuInferior->update(deltaTime);
				special[1] = true;
			}
			else {
				player->setPowerUp(1, false);
				menuInferior->deletePowerUp(1);
				menuInferior->update(deltaTime);
				special[1] = false;
			}
		}
	}

	if (released3) {
		pressed3 = released3 = false;
		if (releasedS) {
			pressedS = releasedS = false;
			sceneToChange = 3;
		}
		else if (sceneToChange != 0) {
			int tileSize = map->getTileSize();
			if (sceneToChange == 1) changeScreen(sceneToChange, 3, glm::vec2(1 * tileSize, 3 * tileSize));
			else if (sceneToChange == 2) changeScreen(sceneToChange, 3, glm::vec2(4 * tileSize, 3 * tileSize));
			else if (sceneToChange == 3) changeScreen(sceneToChange, 3, glm::vec2(30 * tileSize, 11 * tileSize));
			else if (sceneToChange == 4) changeScreen(sceneToChange, 3, glm::vec2(6 * tileSize, 15 * tileSize));
			else if (sceneToChange == 5) changeScreen(sceneToChange, 3, glm::vec2(22 * tileSize, 3 * tileSize));
			sceneToChange = 0;
		}
		else if (sceneToChange == 0) {
			if (!player->hasPowerUp(2)) {
				player->setPowerUp(2, true);
				menuInferior->setPowerUp(2);
				menuInferior->update(deltaTime);
				special[2] = true;
			}
			else {
				player->setPowerUp(2, false);
				menuInferior->deletePowerUp(2);
				menuInferior->update(deltaTime);
				special[2] = false;
			}
		}
	}

	if (released4) {
		pressed4 = released4 = false;
		if (releasedS) {
			pressedS = releasedS = false;
			sceneToChange = 4;
		}
		else if (sceneToChange == 0) {
			if (!player->hasPowerUp(3)) {
				player->setPowerUp(3, true);
				menuInferior->setPowerUp(3);
				menuInferior->update(deltaTime);
				special[3] = true;
			}
			else {
				player->setPowerUp(3, false);
				menuInferior->deletePowerUp(3);
				menuInferior->update(deltaTime);
				special[3] = false;
			}
		}
	}

	if (released5) {
		pressed5 = released5 = false;
		if (releasedS) {
			pressedS = releasedS = false;
			sceneToChange = 5;
		}
		else if (sceneToChange == 0) {
			if (!player->hasPowerUp(4)) {
				player->setPowerUp(4, true);
				menuInferior->setPowerUp(4);
				menuInferior->update(deltaTime);
				special[4] = true;
			}
			else {
				player->setPowerUp(4, false);
				menuInferior->deletePowerUp(4);
				menuInferior->update(deltaTime);
				special[4] = true;
			}
		}
	}

	if (cabezaFlotante != NULL) {
		glm::vec2 posCabezaFlotante = cabezaFlotante->getPosition();
		cabezaFlotante->update(deltaTime);
		if (player->isPunching() == 1 && pos.x + 8 > posCabezaFlotante.x && pos.x - 24 < posCabezaFlotante.x &&
			pos.y < posCabezaFlotante.y + 8 && posCabezaFlotante.y < pos.y + 32 && cabezaFlotante->getStatus() == 1) {
				cabezaFlotante->die(glm::vec2(pos.x - 20, pos.y - 8));
				player->setPoints(50);
				menuSuperior->setPoints(player->getPoints());
				player->ganeExp(50);
				menuSuperior->calculateVitExp(player->getExp(), 1);
				Audio::instance().killEffect();
		}
		else if (player->isPunching() == 2 && pos.x + 8 < posCabezaFlotante.x + 8 && pos.x + 40 > posCabezaFlotante.x + 8 &&
			pos.y < posCabezaFlotante.y + 8 && posCabezaFlotante.y < pos.y + 32 && cabezaFlotante->getStatus() == 1) {
				cabezaFlotante->die(glm::vec2(pos.x + 20, pos.y - 8));
				player->setPoints(50);
				menuSuperior->setPoints(player->getPoints());
				player->ganeExp(50);
				menuSuperior->calculateVitExp(player->getExp(), 1);
				Audio::instance().killEffect();
		}
		if (cabezaFlotante->getStatus() == 3) {
			cabezaFlotante = NULL;
			delete cabezaFlotante;
		}
		else if (pos.x < posCabezaFlotante.x + 8 && posCabezaFlotante.x < pos.x + 32 &&
			pos.y < posCabezaFlotante.y + 8 && posCabezaFlotante.y < pos.y + 32 && cabezaFlotante->getStatus()==1 && !player->isHurted() && !player->isBall()) {
			if (!player->getBlueSpellbook()) {
				Audio::instance().hurtedEffect();
				player->hurted(200);
				menuSuperior->calculateVitExp(player->getLife(), 0);
			}
		}	
	}
	if (esqueleto != NULL) {
		esqueleto->update(deltaTime);
		glm::vec2 posEsqueleto = esqueleto->getPosition();
		if (player->isPunching() == 1 && pos.x + 8 > posEsqueleto.x && pos.x - 32 < posEsqueleto.x &&
			pos.y < posEsqueleto.y + 8 && posEsqueleto.y < pos.y + 32 && esqueleto->getStatus() == 1) {
				esqueleto->die(glm::vec2 (pos.x - 20, pos.y- 8));
				player->setPoints(50);
				menuSuperior->setPoints(player->getPoints());
				player->ganeExp(50);
				menuSuperior->calculateVitExp(player->getExp(), 1);
				Audio::instance().killEffect();
		}
			
		else if (player->isPunching() == 2 && pos.x + 8 < posEsqueleto.x + 16 && pos.x + 48 > posEsqueleto.x + 8 &&
			pos.y < posEsqueleto.y + 8 && posEsqueleto.y < pos.y + 32 && esqueleto->getStatus() == 1) {
				esqueleto->die(glm::vec2(pos.x + 20, pos.y - 8));
				player->setPoints(50);
				menuSuperior->setPoints(player->getPoints());
				player->ganeExp(50);
				menuSuperior->calculateVitExp(player->getExp(), 1);
				Audio::instance().killEffect();
		}
		if (esqueleto->getStatus() == 3) {
			esqueleto = NULL;
			delete esqueleto;
		}
		else {
			if (esqueleto->isThereBone()) {
				glm::vec2 posBone = esqueleto->getBonePosition();
				if (player->isPunching() == 1 && pos.x + 8 > posBone.x && pos.x - 22 < posBone.x &&
					pos.y < posBone.y + 8 && posBone.y < pos.y + 32) {
					esqueleto->dieBone();
					if (esqueleto->getBoneStatus() == 2) {
						player->setPoints(25);
						menuSuperior->setPoints(player->getPoints());
						player->ganeExp(25);
						menuSuperior->calculateVitExp(player->getExp(), 1);
						Audio::instance().killEffect();
					}
				}
				else if (player->isPunching() == 2 && pos.x + 8 < posBone.x + 6 && pos.x + 38 > posBone.x + 6 &&
					pos.y < posBone.y + 8 && posBone.y < pos.y + 32) {
					esqueleto->dieBone();
					if (esqueleto->getBoneStatus() == 2) {
						player->setPoints(25);
						menuSuperior->setPoints(player->getPoints());
						player->ganeExp(25);
						menuSuperior->calculateVitExp(player->getExp(), 1);
						Audio::instance().killEffect();
					}
				}
				if (esqueleto->getBoneStatus() == 3) {
					esqueleto->deleteBone();
				}
				else if (pos.x < posBone.x + 6 && posBone.x < pos.x + 32 &&
					pos.y < posBone.y + 8 && posBone.y < pos.y + 32 && esqueleto->getBoneStatus() == 1 && !player->isBall()) {
					Audio::instance().hurtedEffect();
					player->hurted(150);
					esqueleto->deleteBone();
					menuSuperior->calculateVitExp(player->getLife(), 0);
				}
			}

			if (pos.x < posEsqueleto.x + 8 && posEsqueleto.x < pos.x + 32 &&
				pos.y < posEsqueleto.y + 8 && posEsqueleto.y < pos.y + 32 && esqueleto->getStatus() == 1 && !player->isHurted() && !player->isBall()) {
				if (!player->getYellowSpellbook()) {
					Audio::instance().hurtedEffect();
					player->hurted(200);
					menuSuperior->calculateVitExp(player->getLife(), 0);
				}
			}
		}
	}
	if (cascada != NULL) {
		for (int i = 0; i < numCasc; ++i) {
			cascada[i].update(deltaTime);
			int size = cascada[i].getSize();
			if (size != 0) {
				glm::vec2 positionCascada = cascada[i].getPosition();
				if (pos.x < positionCascada.x + 40 && positionCascada.x < pos.x + 24 &&
					pos.y < positionCascada.y + size * 16 && positionCascada.y < pos.y + 32 && !player->isBall()) {
					if (!player->getBlueRaincoat()) {
						if (!player->isHurted()) Audio::instance().waterHurtEffect();
						player->hurted(5);
						menuSuperior->calculateVitExp(player->getLife(), 0);
					}
				}
			}
		}	
	}
	if (aspersor != NULL) {
		for (int i = 0; i < numAsp; ++i) {
			aspersor[i].update(deltaTime);
			int sizeLeft = aspersor[i].getSize(true);
			if (sizeLeft != 0) {
				glm::vec2 position = aspersor[i].getPosition(true);
				if (pos.x < position.x + sizeLeft && position.x < pos.x + 24 &&
					pos.y < position.y + 32 && position.y < pos.y + 32 && !player->isBall()) {
					if (!player->isHurted()) Audio::instance().waterHurtEffect();
					player->hurted(5);
					menuSuperior->calculateVitExp(player->getLife(), 0);
				}
			}
			int sizeRight = aspersor[i].getSize(false);
			if (sizeRight != 0) {
				glm::vec2 position = aspersor[i].getPosition(false);
				if (pos.x < position.x + sizeRight && position.x < pos.x + 24 &&
					pos.y < position.y + 32 && position.y < pos.y + 32 && !player->isBall()) {
					if (!player->isHurted()) Audio::instance().waterHurtEffect();
					player->hurted(5);
					menuSuperior->calculateVitExp(player->getLife(), 0);
				}
			}
		}
	}
	if (gota != NULL) {
		for (int i = 0; i < numGotas; ++i) {
			glm::vec2 position = gota[i].getPosition();
			if (pos.x < position.x + 16 && position.x < pos.x + 24 &&
				pos.y < position.y + 16 && position.y < pos.y + 32 && gota[i].getStatus() != 5 
				&& gota[i].getStatus() != 4 && gota[i].getStatus() != 3 && !player->isHurted() && !player->isBall()) {
				if (!player->getGrayRaincoat()) {
					Audio::instance().hitGotaEffect();
					player->hurted(100);
					menuSuperior->calculateVitExp(player->getLife(), 0);
				}
				gota[i].hitObject();
			}
			gota[i].update(deltaTime);
		}
	}
	if (skullDoor != NULL) {
		for (int i = 0; i < numSkullDoors; ++i) {
			skullDoor[i].update(deltaTime);
			glm::vec2 position = skullDoor[i].getPosition();
			if (pos.x < position.x + 36 && position.x < pos.x + 16 &&
				pos.y < position.y + 16 && position.y < pos.y + 32 && !changingScene && Game::instance().getSpecialKey(0x0065)) {
				changingScene = true;
				player->setPosition(glm::vec2(position.x + 10, position.y + 28));
				player->setDoorCollision(true);
			}
		}
	}
	if (greenDoor != NULL) {
		for (int i = 0; i < numGreenDoors; ++i) {
			greenDoor[i].update(deltaTime);
		}
	}
	if (startEndDoor != NULL) {
		if (sceneNum == 1) {
			if (first) {
				player->animateChange();
			}
			startEndDoor->update(deltaTime);
			if (player->getAnimDoorNum() == -1) {
				delete startEndDoor;
				startEndDoor = NULL;
			}
		} 
		else if (sceneNum == 5) {
			glm::vec2 position = startEndDoor->getPosition();
			if (pos.x < position.x + 40 && position.x < pos.x + 24 &&
				pos.y < position.y + 32 && position.y < pos.y + 32 && !changingScene && Game::instance().getSpecialKey(0x0065)) {
				changingScene = true;
				player->setPosition(glm::vec2(position.x + 10, position.y + 28));
				player->setDoorCollision(true);
			}
			startEndDoor->update(deltaTime);
		}
		
	}
	menuInferior->update(deltaTime);
	int out = player->isOut();
	switch (out) {
		case 1: //Left
			pos = glm::vec2(512 - map->getTileSize() * 2, player->getPosition().y);
			if (sceneNum == 1 && screenNum == 3) {
				changeScreen(1, 2, pos);
			} else if (sceneNum == 2 && screenNum == 2) {
				changeScreen(2, 1, pos);
			} else if (sceneNum == 3 && screenNum == 1) {
				changeScreen(3, 3, pos);
			} else if (sceneNum == 3 && screenNum == 2) {
				changeScreen(3, 1, pos);
			} else if (sceneNum == 5 && screenNum == 2) {
				changeScreen(5, 1, pos);
			}
			break;
		case 2: //Right
			pos = glm::vec2(0, player->getPosition().y);
			if (sceneNum == 1 && screenNum == 2) {
				changeScreen(1, 3, pos);
			}
			else if (sceneNum == 2 && screenNum == 1) {
				changeScreen(2, 2, pos);
			}
			else if (sceneNum == 3 && screenNum == 3) {
				changeScreen(3, 1, pos);
			}
			else if (sceneNum == 3 && screenNum == 1) {
				changeScreen(3, 2, pos);
			}
			else if (sceneNum == 5 && screenNum == 1) {
				changeScreen(5, 2, pos);
			}
			break;
		case 3: //Top
			pos = glm::vec2(player->getPosition().x, 320 - map->getTileSize() * 2);
			if (sceneNum == 1 && screenNum == 2) {
				changeScreen(1, 1, pos);
			}
			else if (sceneNum == 2 && screenNum == 3) {
				changeScreen(2, 2, pos);
			}
			else if (sceneNum == 5 && screenNum == 3) {
				changeScreen(5, 1, pos);
			}
			break;
		case 4: //Bottom
			pos = glm::vec2(player->getPosition().x, 0);
			if (sceneNum == 1 && screenNum == 1) {
				changeScreen(1, 2, pos);
			}
			else if (sceneNum == 2 && screenNum == 2) {
				changeScreen(2, 3, pos);
			}
			else if (sceneNum == 5 && screenNum == 1) {
				changeScreen(5, 3, pos);
			}
			break;
	}
	if (object != NULL) {
		for (int i = 0; i < numObjects; ++i) {
			glm::vec2 level = object[i].getLevel();
			if (level.x == sceneNum && level.y == screenNum) {
				glm::vec2 position = object[i].getPosition();
				if (pos.x < position.x + 16 && position.x < pos.x + 24 &&
					pos.y < position.y + 16 && position.y < pos.y + 32 && !object[i].getPicked()) {
					if (object[i].getType() == 1) {
						Audio::instance().getBagEffect();
						numPowerUp = object[i].getPowerUp();
						player->setPowerUp(numPowerUp, true);
						object[i].setPicked();
						if (numPowerUp != 5 && !special[numPowerUp]) menuInferior->setPowerUp(numPowerUp);
						else {
							player->setPoints(100);
							menuSuperior->setPoints(player->getPoints());
							player->ganeExp(100);
							menuSuperior->calculateVitExp(player->getExp(), 1);
						}
						menuSuperior->update(deltaTime);
						menuInferior->update(deltaTime);
					}
					else if (object[i].getType() == 3) {
						Audio::instance().getPotionEffect();
						object[i].setPicked();
						player->setPoints(50);
						menuSuperior->setPoints(player->getPoints());
						menuSuperior->update(deltaTime);
					}
					else if (object[i].getType() == 0) {
						object[i].setPicked();
						player->setKey(true);
						menuInferior->setKey(true);
						player->setPoints(10);
						menuSuperior->setPoints(player->getPoints());
						Audio::instance().getKeyEffect();
					}
					else if (object[i].getType() == 2) {
						if (player->haveKey()) {
							object[i].setPicked();
							menuInferior->setKey(false);
							if (sceneNum == 1 && screenNum == 2) {
								Audio::instance().openDoorEffect();
								greenDoor[0].open();
								friends[0].setPosition(glm::vec2(3 * map->getTileSize(), 15 * map->getTileSize()));
							}
							else if (sceneNum == 2 && screenNum == 3) {
								Audio::instance().openDoorEffect();
								greenDoor[0].open();
								friends[1].setPosition(glm::vec2(21 * map->getTileSize(), 6 * map->getTileSize()));
							}
							else if (sceneNum == 3 && screenNum == 3) {
								Audio::instance().openDoorEffect();
								greenDoor[0].open();
								friends[2].setPosition(glm::vec2(18 * map->getTileSize(), 4 * map->getTileSize()));
							}
							else if (sceneNum == 4 && screenNum == 2) {
								Audio::instance().openDoorEffect();
								greenDoor[0].open();
								friends[3].setPosition(glm::vec2(6 * map->getTileSize(), 5 * map->getTileSize()));
							}
							else if (sceneNum == 4 && screenNum == 3) {
								Audio::instance().openDoorEffect();
								greenDoor[0].open();
								friends[4].setPosition(glm::vec2(16 * map->getTileSize(), 4 * map->getTileSize()));
							}
							else if (sceneNum == 5 && screenNum == 1) {
								Audio::instance().openDoorEffect();
								greenDoor[0].open();
								friends[5].setPosition(glm::vec2(3 * map->getTileSize(), 17 * map->getTileSize()));
							}
							player->setKey(false);
						}
					}
				}
			}
			if (object[i].getType() == 1 && object[i].getPowerUp() != 5 && object[i].getPicked() && !object[i].getAgotado() && !object[i].isActive() && !special[numPowerUp]) {
				menuInferior->deletePowerUp(object[i].getPowerUp());
				player->setPowerUp(object[i].getPowerUp(), false);
			}
			object[i].update(deltaTime);
		}
	}
	if (friends != NULL) {
		for (int i = 0; i < 6; ++i) {
			glm::vec2 position = friends[i].getPosition();
			if (pos.x < position.x + 16 && position.x < pos.x + 24 &&
				pos.y < position.y + 16 && position.y < pos.y + 32 && !friends[i].isPicked()) {
				timeFriend[i] = 0;
			}
			if (timeFriend[i] > 350) {
				Audio::instance().rescueFriedEffect();
				friends[i].setPicked();
				menuInferior->savedNewFriend();
				++numFriends;
				player->setPoints(100);
				menuSuperior->setPoints(player->getPoints());
				timeFriend[i] = -1;
			}
			if (timeFriend[i] >= 0) timeFriend[i] += deltaTime;
		}
		
	}

	int tileSize = map->getTileSize();
	if (map->getBlockCode(pos) == 117 || map->getBlockCode(pos) == 118 && !player->isHurted()) {
		player->hurted(500);
		menuSuperior->calculateVitExp(player->getLife(), 0);
	}
	if (player->getAnimDoorNum() == -2) {
		glm::ivec2 position = player->getPosition();
		Audio::instance().changeScreenEffect();
		if (sceneNum == 1 && screenNum == 3) {
			changeScreen(2, 1, glm::ivec2(5 * tileSize, 4 * tileSize - 8));
			Audio::instance().playLevel(2);
		}
		else if (sceneNum == 2 && screenNum == 1) {
			changeScreen(1, 3, glm::ivec2(28 * tileSize, 7 * tileSize - 8));
			Audio::instance().playLevel(1);
		}
		else if (sceneNum == 2 && screenNum == 3) {
			changeScreen(3, 1, glm::ivec2(14 * tileSize, 17 * tileSize - 8));
			Audio::instance().playLevel(3);
		}
		else if (sceneNum == 3 && screenNum == 1) {
			changeScreen(2, 3, glm::ivec2(10 * tileSize, 10 * tileSize - 8));
			Audio::instance().playLevel(2);
		}
		else if (sceneNum == 3 && screenNum == 3) {
			changeScreen(4, 1, glm::ivec2(4 * tileSize, 14 * tileSize - 8));
			Audio::instance().playLevel(4);
		}
		else if (sceneNum == 4 && screenNum == 1) {
			if (position.x == 4*tileSize + 24 && position.y == 5*tileSize - 8)
				changeScreen(4, 2, glm::ivec2(28 * tileSize, 17 * tileSize - 8));
			else if (position.x == 4 * tileSize + 24 && position.y == 14 * tileSize - 8) {
				changeScreen(3, 3, glm::ivec2(2 * tileSize, 13 * tileSize - 8));
				Audio::instance().playLevel(3);
			}
			else if (position.x == 27*tileSize + 24 && position.y == 5*tileSize - 8)
				changeScreen(4, 3, glm::ivec2(6 * tileSize, 16 * tileSize - 8));
		}
		else if (sceneNum == 4 && screenNum == 2) {
			changeScreen(4, 1, glm::ivec2(4 * tileSize, 5 * tileSize - 8));
		}
		else if (sceneNum == 4 && screenNum == 3) {
			if (position.x == 14 * tileSize + 24 && position.y == 15 * tileSize - 8) {
				changeScreen(5, 1, glm::ivec2(3 * tileSize, 4 * tileSize - 8));
				Audio::instance().playLevel(5);
			}
			else if (position.x == 6*tileSize + 24 && position.y == 16*tileSize - 8)
				changeScreen(4, 1, glm::ivec2(26 * tileSize, 5 * tileSize - 8));
		}
		else if (sceneNum == 5 && screenNum == 1) {
			changeScreen(4, 3, glm::ivec2(14 * tileSize, 15 * tileSize - 8));
			Audio::instance().playLevel(4);
		}
		else if (sceneNum == 5 && screenNum == 3) {
			win = true;
		}
		player->setDoorCollision(false);
	}
	if (player->getExp() >= 1000) {
		player->setPoints(200);
		menuSuperior->setPoints(player->getPoints());
		menuSuperior->update(deltaTime);
	}
	first = false;
}

void Scene::render()
{
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	map->render();
	if (cascada != NULL) for (int i = 0; i < numCasc; ++i) cascada[i].render();
	if (aspersor != NULL) {
		for (int i = 0; i < numAsp; ++i) aspersor[i].render();
	}
	if (gota != NULL) {
		for (int i = 0; i < numGotas; ++i) {
			if (gota[i].getStatus() != 5)
				gota[i].render();
		}
	}
	if (greenDoor != NULL) {
		for (int i = 0; i < numGreenDoors; ++i) {
			if (friends != NULL && greenDoor[i].isOpen()) {
				if (sceneNum == 1 && screenNum == 2) {
					if (!friends[0].isPicked()) friends[0].render();
				}
				else if (sceneNum == 2 && screenNum == 3) {
					if (!friends[1].isPicked()) friends[1].render();
				}
				else if (sceneNum == 3 && screenNum == 3) {
					if (!friends[2].isPicked()) friends[2].render();
				}
				else if (sceneNum == 4 && screenNum == 2) {
					if (!friends[3].isPicked()) friends[3].render();
				}
				else if (sceneNum == 4 && screenNum == 3) {
					if (!friends[4].isPicked()) friends[4].render();
				}
				else if (sceneNum == 5 && screenNum == 1) {
					if (!friends[5].isPicked()) friends[5].render();
				}
			}
			greenDoor[i].render();
		}
	}
	if (object != NULL) {
		for (int i = 0; i < numObjects; ++i) {
			if (!object[i].getPicked()) object[i].render(sceneNum, screenNum);
		}
	}
	menuInferior->render();
	menuSuperior->render();
	if (!changingScene && startEndDoor != NULL) startEndDoor->render();
	if (!changingScene && skullDoor != NULL) for (int i = 0; i < numSkullDoors; ++i) skullDoor[i].render();
	player->render();
	if (changingScene && skullDoor != NULL) for (int i = 0; i < numSkullDoors; ++i) skullDoor[i].render();
	if (changingScene && startEndDoor != NULL) startEndDoor->render();
	if (cabezaFlotante != NULL) cabezaFlotante->render();
	if (esqueleto != NULL) esqueleto->render();
}

void Scene::changeScreen(int scene, int screen, glm::vec2 pos)
{
	sceneNum = scene;
	screenNum = screen;
	menuSuperior->setScreen(scene, screen);
	map = TileMap::createTileMap("levels/level" + to_string(scene) + "_" + to_string(screen) + ".txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(pos);
	player->setTileMap(map);
	if (changingScene) {
		player->animateChange();
	}
	changingScene = false;
	esqueleto = NULL;
	cabezaFlotante = NULL;
	cascada = NULL;
	aspersor = NULL;
	gota = NULL;
	skullDoor = NULL;
	greenDoor = NULL;
	startEndDoor = NULL;
	numAsp = 0;
	numCasc = 0;
	numGotas = 0;
	numSkullDoors = 0;
	numGreenDoors = 0;
	if (scene == 1 && screen == 1) {
		cabezaFlotante = new CabezaFlotante();
		cabezaFlotante->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		cabezaFlotante->setPosition(glm::vec2(22 * map->getTileSize(), 10 * map->getTileSize()));
		cabezaFlotante->setTileMap(map);
		numGotas = 3;
		gota = new Gota[3];
		gota[0].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(6 * map->getTileSize(), 2 * map->getTileSize()));
		gota[0].setTileMap(map);
		gota[1].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(3 * map->getTileSize(), 14 * map->getTileSize()));
		gota[1].setTileMap(map);
		gota[2].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(21 * map->getTileSize(), 14 * map->getTileSize()));
		gota[2].setTileMap(map);
		object[0].setTileMap(map);
		Audio::instance().bornEnemiesEffect();
	}
	else if (scene == 1 && screen == 2) {
		esqueleto = new Esqueleto();
		esqueleto->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		esqueleto->setPosition(glm::vec2(10 * map->getTileSize(), 15 * map->getTileSize() - 4));
		esqueleto->setTileMap(map);
		cabezaFlotante = new CabezaFlotante();
		cabezaFlotante->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		cabezaFlotante->setPosition(glm::vec2(26 * map->getTileSize(), 4 * map->getTileSize()));
		cabezaFlotante->setTileMap(map);
		numCasc = 1;
		cascada = new Cascada[1];
		cascada[0].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(10 * map->getTileSize(), 4 * map->getTileSize()), 14);
		cascada[0].setTileMap(map);
		numGreenDoors = 1;
		greenDoor = new GreenDoor[1];
		greenDoor[0].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(2 * map->getTileSize(), 13 * map->getTileSize()));
		greenDoor[0].setTileMap(map);
		if (friends[0].isPicked()) greenDoor[0].open();
		numGotas = 1;
		gota = new Gota[1];
		gota[0].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(17 * map->getTileSize(), 7 * map->getTileSize()));
		gota[0].setTileMap(map);
		object[1].setTileMap(map);
		Audio::instance().bornEnemiesEffect();
	} 
	else if (scene == 1 and screen == 3) {
		numAsp = 1;
		aspersor = new Aspersor[1];
		aspersor[0].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(8 * map->getTileSize(), 14 * map->getTileSize()));
		aspersor[0].setTileMap(map);
		numSkullDoors = 1;
		skullDoor = new SkullDoor[1];
		skullDoor[0].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(27 * map->getTileSize(), 5 * map->getTileSize()));
		skullDoor[0].setTileMap(map);
		numGotas = 1;
		gota = new Gota[1];
		gota[0].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(4 * map->getTileSize(), 1 * map->getTileSize()));
		gota[0].setTileMap(map);
		object[2].setTileMap(map);
	}
	else if (scene == 2 && screen == 1) {
		esqueleto = new Esqueleto();
		esqueleto->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		esqueleto->setPosition(glm::vec2(24 * map->getTileSize(), 4 * map->getTileSize() - 4));
		esqueleto->setTileMap(map);
		cabezaFlotante = new CabezaFlotante();
		cabezaFlotante->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		cabezaFlotante->setPosition(glm::vec2(7 * map->getTileSize(), 14 * map->getTileSize()));
		cabezaFlotante->setTileMap(map);
		numSkullDoors = 1;
		skullDoor = new SkullDoor[1];
		skullDoor[0].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(4 * map->getTileSize(), 2 * map->getTileSize()));
		skullDoor[0].setTileMap(map);
		numGotas = 8;
		gota = new Gota[8];
		gota[0].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(9 * map->getTileSize(), 1 * map->getTileSize()));
		gota[0].setTileMap(map);
		gota[1].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(21 * map->getTileSize(), 1 * map->getTileSize()));
		gota[1].setTileMap(map);
		gota[2].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(23 * map->getTileSize(), 7 * map->getTileSize()));
		gota[2].setTileMap(map);
		gota[3].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(10 * map->getTileSize(), 7 * map->getTileSize()));
		gota[3].setTileMap(map);
		gota[4].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(6 * map->getTileSize(), 11 * map->getTileSize()));
		gota[4].setTileMap(map);
		gota[5].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(12 * map->getTileSize(), 17 * map->getTileSize()));
		gota[5].setTileMap(map);
		gota[6].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(25 * map->getTileSize(), 13 * map->getTileSize()));
		gota[6].setTileMap(map);
		gota[7].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(29 * map->getTileSize(), 13 * map->getTileSize()));
		gota[7].setTileMap(map);
		object[3].setTileMap(map);
		object[4].setTileMap(map);
		Audio::instance().bornEnemiesEffect();
	}
	else if (scene == 2 && screen == 2) {
		esqueleto = new Esqueleto();
		esqueleto->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		esqueleto->setPosition(glm::vec2(24 * map->getTileSize(), 8 * map->getTileSize()- 4));
		esqueleto->setTileMap(map);
		cabezaFlotante = new CabezaFlotante();
		cabezaFlotante->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		cabezaFlotante->setPosition(glm::vec2(23 * map->getTileSize(), 14 * map->getTileSize()));
		cabezaFlotante->setTileMap(map);
		numGotas = 5;
		gota = new Gota[5];
		gota[0].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(5 * map->getTileSize(), 1 * map->getTileSize()));
		gota[0].setTileMap(map);
		gota[1].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(15 * map->getTileSize(), 1 * map->getTileSize()));
		gota[1].setTileMap(map);
		gota[2].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(29 * map->getTileSize(), 1 * map->getTileSize()));
		gota[2].setTileMap(map);
		gota[3].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(25 * map->getTileSize(), 11 * map->getTileSize()));
		gota[3].setTileMap(map);
		gota[4].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(9 * map->getTileSize(), 13 * map->getTileSize()));
		gota[4].setTileMap(map);
		object[5].setTileMap(map);
		Audio::instance().bornEnemiesEffect();
	}
	else if (scene == 2 && screen == 3) {
		esqueleto = new Esqueleto();
		esqueleto->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		esqueleto->setPosition(glm::vec2(23 * map->getTileSize(), 18 * map->getTileSize() - 4));
		esqueleto->setTileMap(map);
		cabezaFlotante = new CabezaFlotante();
		cabezaFlotante->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		cabezaFlotante->setPosition(glm::vec2(7 * map->getTileSize(), 4 * map->getTileSize()));
		cabezaFlotante->setTileMap(map);
		numSkullDoors = 1;
		skullDoor = new SkullDoor[1];
		skullDoor[0].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(9 * map->getTileSize(), 8 * map->getTileSize()));
		skullDoor[0].setTileMap(map);
		numGreenDoors = 1;
		greenDoor = new GreenDoor[1];
		greenDoor[0].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(20 * map->getTileSize(), 4 * map->getTileSize()));
		greenDoor[0].setTileMap(map);
		if (friends[1].isPicked()) greenDoor[0].open();
		numGotas = 2;
		gota = new Gota[2];
		gota[0].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(7 * map->getTileSize(), 7 * map->getTileSize()));
		gota[0].setTileMap(map);
		gota[1].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(15 * map->getTileSize(), 13 * map->getTileSize()));
		gota[1].setTileMap(map);
		object[6].setTileMap(map);
		object[7].setTileMap(map);
		Audio::instance().bornEnemiesEffect();
	}
	else if (scene == 3 && screen == 1) {
		cabezaFlotante = new CabezaFlotante();
		cabezaFlotante->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		cabezaFlotante->setPosition(glm::vec2(12 * map->getTileSize(), 10 * map->getTileSize()));
		cabezaFlotante->setTileMap(map);
		numAsp = 4;
		aspersor = new Aspersor[4];
		aspersor[0].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(7 * map->getTileSize(), 16 * map->getTileSize()));
		aspersor[0].setTileMap(map);
		aspersor[1].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(21 * map->getTileSize(), 16 * map->getTileSize()));
		aspersor[1].setTileMap(map);
		aspersor[2].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(21 * map->getTileSize(), 9 * map->getTileSize()));
		aspersor[2].setTileMap(map);
		aspersor[3].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(29 * map->getTileSize(), 7 * map->getTileSize()));
		aspersor[3].setTileMap(map);
		numSkullDoors = 1;
		skullDoor = new SkullDoor[1];
		skullDoor[0].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(13 * map->getTileSize(), 15 * map->getTileSize()));
		skullDoor[0].setTileMap(map);
		numGotas = 4;
		gota = new Gota[4];
		gota[0].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(5 * map->getTileSize(), 3 * map->getTileSize()));
		gota[0].setTileMap(map);
		gota[1].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(15 * map->getTileSize(), 7 * map->getTileSize()));
		gota[1].setTileMap(map);
		gota[2].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(18 * map->getTileSize(), 2 * map->getTileSize()));
		gota[2].setTileMap(map);
		gota[3].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(28 * map->getTileSize(), 2 * map->getTileSize()));
		gota[3].setTileMap(map);
		object[8].setTileMap(map);
		Audio::instance().bornEnemiesEffect();
	}
	else if (scene == 3 && screen == 2) {
		esqueleto = new Esqueleto();
		esqueleto->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		esqueleto->setPosition(glm::vec2(12 * map->getTileSize(), 3 * map->getTileSize() - 4));
		esqueleto->setTileMap(map);
		cabezaFlotante = new CabezaFlotante();
		cabezaFlotante->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		cabezaFlotante->setPosition(glm::vec2(11 * map->getTileSize(), 16 * map->getTileSize()));
		cabezaFlotante->setTileMap(map);
		numAsp = 2;
		aspersor = new Aspersor[4];
		aspersor[0].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(6 * map->getTileSize(), 7 * map->getTileSize()));
		aspersor[0].setTileMap(map);
		aspersor[1].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(14 * map->getTileSize(), 7 * map->getTileSize()));
		aspersor[1].setTileMap(map);
		numGotas = 3;
		gota = new Gota[3];
		gota[0].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(16 * map->getTileSize(), 2 * map->getTileSize()));
		gota[0].setTileMap(map);
		gota[1].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(4 * map->getTileSize(), 2 * map->getTileSize()));
		gota[1].setTileMap(map);
		gota[2].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(15 * map->getTileSize(), 15 * map->getTileSize()));
		gota[2].setTileMap(map);
		object[9].setTileMap(map);
		object[10].setTileMap(map);
		Audio::instance().bornEnemiesEffect();
	}
	else if (scene == 3 && screen == 3) {
		numSkullDoors = 1;
		skullDoor = new SkullDoor[1];
		skullDoor[0].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(1 * map->getTileSize(), 11 * map->getTileSize()));
		skullDoor[0].setTileMap(map);
		numGreenDoors = 1;
		greenDoor = new GreenDoor[1];
		greenDoor[0].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(17 * map->getTileSize(), 2 * map->getTileSize()));
		greenDoor[0].setTileMap(map);
		if (friends[2].isPicked()) greenDoor[0].open();
		numGotas = 3;
		gota = new Gota[3];
		gota[0].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(23 * map->getTileSize(), 3 * map->getTileSize()));
		gota[0].setTileMap(map);
		gota[1].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(24 * map->getTileSize(), 7 * map->getTileSize()));
		gota[1].setTileMap(map);
		gota[2].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(6 * map->getTileSize(), 7 * map->getTileSize()));
		gota[2].setTileMap(map);
		object[11].setTileMap(map);
	}
	else if (scene == 4 && screen == 1) {
		numCasc = 2;
		cascada = new Cascada[2];
		cascada[0].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(9 * map->getTileSize(), 2 * map->getTileSize()), 15);
		cascada[0].setTileMap(map);
		cascada[1].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(16 * map->getTileSize(), 5 * map->getTileSize()), 12);
		cascada[1].setTileMap(map);
		numSkullDoors = 3;
		skullDoor = new SkullDoor[3];
		skullDoor[0].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(3 * map->getTileSize(), 12 * map->getTileSize()));
		skullDoor[0].setTileMap(map);
		skullDoor[1].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(3 * map->getTileSize(), 3 * map->getTileSize()));
		skullDoor[1].setTileMap(map);
		skullDoor[2].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(26 * map->getTileSize(), 3 * map->getTileSize()));
		skullDoor[2].setTileMap(map);
		object[12].setTileMap(map);
	}
	else if (scene == 4 && screen == 2) {
		cabezaFlotante = new CabezaFlotante();
		cabezaFlotante->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		cabezaFlotante->setPosition(glm::vec2(26 * map->getTileSize(), 7 * map->getTileSize()));
		cabezaFlotante->setTileMap(map);
		esqueleto = new Esqueleto();
		esqueleto->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		esqueleto->setPosition(glm::vec2(6 * map->getTileSize(), 16 * map->getTileSize() - 4));
		esqueleto->setTileMap(map);
		numSkullDoors = 1;
		skullDoor = new SkullDoor[1];
		skullDoor[0].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(27 * map->getTileSize(), 15 * map->getTileSize()));
		skullDoor[0].setTileMap(map);
		numGreenDoors = 1;
		greenDoor = new GreenDoor[1];
		greenDoor[0].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(5 * map->getTileSize(), 3 * map->getTileSize()));
		greenDoor[0].setTileMap(map);
		if (friends[3].isPicked()) greenDoor[0].open();
		numGotas = 5;
		gota = new Gota[5];
		gota[0].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(23 * map->getTileSize(), 10 * map->getTileSize()));
		gota[0].setTileMap(map);
		gota[1].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(25 * map->getTileSize(), 14 * map->getTileSize()));
		gota[1].setTileMap(map);
		gota[2].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(19 * map->getTileSize(), 2 * map->getTileSize()));
		gota[2].setTileMap(map);
		gota[3].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(26 * map->getTileSize(), 4 * map->getTileSize()));
		gota[3].setTileMap(map);
		gota[4].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(9 * map->getTileSize(), 8 * map->getTileSize()));
		gota[4].setTileMap(map);
		object[13].setTileMap(map);
		object[14].setTileMap(map);
		Audio::instance().bornEnemiesEffect();
	}
	else if (scene == 4 && screen == 3) {
		esqueleto = new Esqueleto();
		esqueleto->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		esqueleto->setPosition(glm::vec2(7 * map->getTileSize(), 4 * map->getTileSize() - 4));
		esqueleto->setTileMap(map);
		numCasc = 1;
		cascada = new Cascada[1];
		cascada[0].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(18 * map->getTileSize(), 9 * map->getTileSize()), 9);
		cascada[0].setTileMap(map);
		numSkullDoors = 2;
		skullDoor = new SkullDoor[2];
		skullDoor[0].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(5 * map->getTileSize(), 14 * map->getTileSize()));
		skullDoor[0].setTileMap(map);
		skullDoor[1].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(13 * map->getTileSize(), 13 * map->getTileSize()));
		skullDoor[1].setTileMap(map);
		numGreenDoors = 1;
		greenDoor = new GreenDoor[1];
		greenDoor[0].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(15 * map->getTileSize(), 2 * map->getTileSize()));
		greenDoor[0].setTileMap(map);
		if (friends[4].isPicked()) greenDoor[0].open();
		numGotas = 5;
		gota = new Gota[5];
		gota[0].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(4 * map->getTileSize(), 2 * map->getTileSize()));
		gota[0].setTileMap(map);
		gota[1].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(6 * map->getTileSize(), 7 * map->getTileSize()));
		gota[1].setTileMap(map);
		gota[2].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(12 * map->getTileSize(), 2 * map->getTileSize()));
		gota[2].setTileMap(map);
		gota[3].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(25 * map->getTileSize(), 2 * map->getTileSize()));
		gota[3].setTileMap(map);
		gota[4].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(22 * map->getTileSize(), 8 * map->getTileSize()));
		gota[4].setTileMap(map);
		object[15].setTileMap(map);
		object[16].setTileMap(map);
		Audio::instance().bornEnemiesEffect();
	}
	else if (scene == 5 && screen == 1) {
		cabezaFlotante = new CabezaFlotante();
		cabezaFlotante->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		cabezaFlotante->setPosition(glm::vec2(27 * map->getTileSize(), 2 * map->getTileSize()));
		cabezaFlotante->setTileMap(map);
		numAsp = 2;
		aspersor = new Aspersor[2];
		aspersor[0].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(7 * map->getTileSize(), 16 * map->getTileSize()));
		aspersor[0].setTileMap(map);
		aspersor[1].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(15 * map->getTileSize(), 16 * map->getTileSize()));
		aspersor[1].setTileMap(map);
		numSkullDoors = 1;
		skullDoor = new SkullDoor[1];
		skullDoor[0].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(2 * map->getTileSize(), 2 * map->getTileSize()));
		skullDoor[0].setTileMap(map);
		numGreenDoors = 1;
		greenDoor = new GreenDoor[1];
		greenDoor[0].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(2 * map->getTileSize(), 15 * map->getTileSize()));
		greenDoor[0].setTileMap(map);
		if (friends[5].isPicked()) greenDoor[0].open();
		numGotas = 2;
		gota = new Gota[2];
		gota[0].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(10 * map->getTileSize(), 1 * map->getTileSize()));
		gota[0].setTileMap(map);
		gota[1].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(23 * map->getTileSize(), 1 * map->getTileSize()));
		gota[1].setTileMap(map);
		object[17].setTileMap(map);
		object[18].setTileMap(map);
		Audio::instance().bornEnemiesEffect();
	}
	else if (scene == 5 && screen == 2) {
		cabezaFlotante = new CabezaFlotante();
		cabezaFlotante->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		cabezaFlotante->setPosition(glm::vec2(25 * map->getTileSize(), 6 * map->getTileSize()));
		cabezaFlotante->setTileMap(map);
		numAsp = 1;
		aspersor = new Aspersor[1];
		aspersor[0].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(4 * map->getTileSize(), 15 * map->getTileSize()));
		aspersor[0].setTileMap(map);
		numGotas = 4;
		gota = new Gota[4];
		gota[0].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(26 * map->getTileSize(), 9 * map->getTileSize()));
		gota[0].setTileMap(map);
		gota[1].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(7 * map->getTileSize(), 1 * map->getTileSize()));
		gota[1].setTileMap(map);
		gota[2].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(15 * map->getTileSize(), 1 * map->getTileSize()));
		gota[2].setTileMap(map);
		gota[3].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(13 * map->getTileSize(), 14 * map->getTileSize()));
		gota[3].setTileMap(map);
		object[19].setTileMap(map);
		object[20].setTileMap(map);
		Audio::instance().bornEnemiesEffect();
	}
	else if (scene = 5 && screen == 3) {
		numCasc = 1;
		cascada = new Cascada[1];
		cascada[0].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(7 * map->getTileSize(), 2 * map->getTileSize()), 14);
		cascada[0].setTileMap(map);
		numAsp = 2;
		aspersor = new Aspersor[2];
		aspersor[0].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(15 * map->getTileSize(), 3 * map->getTileSize()));
		aspersor[0].setTileMap(map);
		aspersor[1].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(15 * map->getTileSize(), 8 * map->getTileSize()));
		aspersor[1].setTileMap(map);
		startEndDoor = new StartEndDoor();
		if (numFriends == 6) startEndDoor->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(21 * map->getTileSize(), 11 * map->getTileSize()), 1);
		else startEndDoor->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(21 * map->getTileSize(), 11 * map->getTileSize()), 0);
		object[21].setTileMap(map);
	}
}

void Scene::initFriends(ShaderProgram& texProgram) {
	friends = new Friend[6];
	for (int i = 0; i < 6; ++i) friends[i].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
}

void Scene::initObjects(ShaderProgram& texProgram) {
	numObjects = 23;
	object = new Object[numObjects];
	object[0].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(3 * 16, 5 * 16), 1, 1, 0, 0);
	object[1].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(1 * 16, 14 * 16), 1, 2, 2, 0);
	object[2].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(5 * 16, 15 * 16), 1, 3, 1, 3);
	object[3].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(26 * 16, 10 * 16), 2, 1, 1, 0);
	object[4].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(28 * 16, 18 * 16), 2, 1, 3, 0);
	object[5].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(8 * 16, 10 * 16), 2, 2, 0, 0);
	object[6].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(18 * 16, 18 * 16), 2, 3, 1, 5);
	object[7].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(19 * 16, 5 * 16), 2, 3, 2, 0);
	object[8].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(4 * 16, 17 * 16), 3, 1, 3, 0);
	object[9].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(19 * 16, 3 * 16), 3, 2, 1, 1);
	object[10].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(21 * 16, 16 * 16), 3, 2, 0, 0);
	object[11].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(16 * 16, 3 * 16), 3, 3, 2, 0);
	object[12].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(27 * 16, 14 * 16), 4, 1, 0, 0);
	object[13].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(13 * 16, 16 * 16), 4, 2, 1, 4);
	object[14].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(8 * 16, 4 * 16), 4, 2, 2, 0);
	object[15].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(7 * 16, 10 * 16), 4, 3, 0, 0);
	object[16].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(18 * 16, 3 * 16), 4, 3, 2, 0);
	object[17].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(16 * 16, 4 * 16), 5, 1, 3, 0);
	object[18].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(1 * 16, 16 * 16), 5, 1, 2, 0);
	object[19].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(27 * 16, 6 * 16), 5, 2, 1, 2);
	object[20].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(3 * 16, 6 * 16), 5, 2, 1, 5);
	object[21].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(28 * 16, 6 * 16), 5, 3, 0, 0);
	object[22].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(28 * 16, 8 * 16), 3, 2, 1, 5);
}

void Scene::renderFriends() {
	if (sceneNum == 1 && screenNum == 2 && !friends[0].isPicked()) {
		friends[0].render();
	}
	else if (sceneNum == 2 && screenNum == 3 && !friends[1].isPicked()) {
		friends[1].render();
	}
	else if (sceneNum == 3 && screenNum == 3 && !friends[2].isPicked()) {
		friends[2].render();
	}
	else if (sceneNum == 4 && screenNum == 2 && !friends[3].isPicked()) {
		friends[3].render();
	}
	else if (sceneNum == 4 && screenNum == 3 && !friends[4].isPicked()) {
		friends[4].render();
	}
	else if (sceneNum == 5 && screenNum == 1 && !friends[5].isPicked()) {
		friends[5].render();
	}
}

bool Scene::hasWon() {
	return win;
}

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if(!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}



