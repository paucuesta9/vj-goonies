#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"


#define SCREEN_X 60 //Posicion del nivel respecto la pantalla X
#define SCREEN_Y 70 //Posicion del nivel respecto la pantalla Y

#define INIT_PLAYER_X_TILES 22 //Posición X inicial del jugador contando en TILES (cuadrados)
#define INIT_PLAYER_Y_TILES 4 //Posición Y inicial del jugador contando en TILES (cuadrados)


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
}

Scene::~Scene()
{
	if(map != NULL)
		delete map;
	if(player != NULL)
		delete player;
	if (cabezaFlotante != NULL)
		delete cabezaFlotante;
	if (esqueleto != NULL)
		delete esqueleto;
	if (cascada != NULL)
		delete cascada;
	if (aspersor != NULL)
		delete aspersor;
	if (gota != NULL)
		delete gota;
	if (skullDoor != NULL)
		delete skullDoor;
	if (greenDoor != NULL)
		delete greenDoor;
	if (startEndDoor != NULL)
		delete startEndDoor;
	if (object != NULL)
		delete object;
}


void Scene::init()
{
	initShaders();
	sceneNum = 2;
	screenNum = 1;
	numAsp = 0;
	numCasc = 0;
	numGotas = 0;
	numSkullDoors = 0;
	numGreenDoors = 0;
	numObjects = 0;
	numFriends = 0;
	first = true;
	changingScene = false;
	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	changeScreen(sceneNum, screenNum, glm::vec2(INIT_PLAYER_X_TILES * 16 + 8, INIT_PLAYER_Y_TILES * 16 + 4));
	startEndDoor = new StartEndDoor();
	startEndDoor->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(22 * map->getTileSize(), 3 * map->getTileSize()), 1);
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	player->update(deltaTime);
	glm::vec2 pos = player->getPosition();
	if (cabezaFlotante != NULL) {
		glm::vec2 posCabezaFlotante = cabezaFlotante->getPosition();
		cabezaFlotante->update(deltaTime);
		if (player->isPunching() == 1 && pos.x - 16 < posCabezaFlotante.x + 8 && pos.x - 16 > posCabezaFlotante.x + 4 && 
			pos.y < posCabezaFlotante.y + 8 && posCabezaFlotante.y < pos.y + 32)
			cabezaFlotante->die();
		else if (player->isPunching() == 2 && pos.x + 36 > posCabezaFlotante.x && pos.x + 32 < posCabezaFlotante.x && 
			pos.y < posCabezaFlotante.y + 8 && posCabezaFlotante.y < pos.y + 32) cabezaFlotante->die();
		if (cabezaFlotante->getStatus() == 3) {
			cabezaFlotante = NULL;
			delete cabezaFlotante;
		}
		else if (pos.x < posCabezaFlotante.x + 8 && posCabezaFlotante.x < pos.x + 32 &&
			pos.y < posCabezaFlotante.y + 8 && posCabezaFlotante.y < pos.y + 32 && cabezaFlotante->getStatus()==1) {
			player->hurted(5);
		}	
	}
	if (esqueleto != NULL) {
		esqueleto->update(deltaTime);
		glm::vec2 posEsqueleto = esqueleto->getPosition();
		if (player->isPunching() == 1 && pos.x - 16 < posEsqueleto.x + 8 && pos.x - 16 > posEsqueleto.x + 4 &&
			pos.y < posEsqueleto.y + 8 && posEsqueleto.y < pos.y + 32)
			esqueleto->die();
		else if (player->isPunching() == 2 && pos.x + 36 > posEsqueleto.x && pos.x + 32 < posEsqueleto.x &&
			pos.y < posEsqueleto.y + 8 && posEsqueleto.y < pos.y + 32) esqueleto->die();
		if (esqueleto->getStatus() == 3) {
			esqueleto = NULL;
			delete esqueleto;
		}
		else {
			if (esqueleto->isThereBone()) {
				glm::vec2 posBone = esqueleto->getBonePosition();
				if (player->isPunching() == 1 && pos.x > posBone.x + 6  && pos.x  < posBone.x + 24 &&
					pos.y < posBone.y + 8 && posBone.y < pos.y + 32)
					esqueleto->dieBone();
				else if (player->isPunching() == 2 && pos.x + 38 > posBone.x && pos.x + 32 < posBone.x &&
					pos.y < posBone.y + 8 && posBone.y < pos.y + 32) esqueleto->dieBone();
				if (esqueleto->getBoneStatus() == 3) {
					esqueleto->deleteBone();
				}
				else if (pos.x < posBone.x + 6 && posBone.x < pos.x + 32 &&
					pos.y < posBone.y + 8 && posBone.y < pos.y + 32 && esqueleto->getBoneStatus() == 1) {
					player->hurted(10);
					esqueleto->deleteBone();
				}
			}

			if (pos.x < posEsqueleto.x + 8 && posEsqueleto.x < pos.x + 32 &&
				pos.y < posEsqueleto.y + 8 && posEsqueleto.y < pos.y + 32 && esqueleto->getStatus() == 1) {
				player->hurted(5);
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
					pos.y < positionCascada.y + size * 16 && positionCascada.y < pos.y + 32) {
					player->hurted(1);
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
					pos.y < position.y + 32 && position.y < pos.y + 32) {
					player->hurted(1);
				}
			}
			int sizeRight = aspersor[i].getSize(false);
			if (sizeRight != 0) {
				glm::vec2 position = aspersor[i].getPosition(false);
				if (pos.x < position.x + sizeRight && position.x < pos.x + 24 &&
					pos.y < position.y + 32 && position.y < pos.y + 32) {
					player->hurted(1);
				}
			}
		}
	}
	if (gota != NULL) {
		for (int i = 0; i < numGotas; ++i) {
			glm::vec2 position = gota[i].getPosition();
			if (pos.x < position.x + 16 && position.x < pos.x + 24 &&
				pos.y < position.y + 16 && position.y < pos.y + 32 && gota[i].getStatus() != 5) {
				player->hurted(1);
				gota[i].hitObject();
			}
			gota[i].update(deltaTime);
		}
	}
	if (skullDoor != NULL) {
		for (int i = 0; i < numSkullDoors; ++i) {
			skullDoor[i].update(deltaTime);
			glm::vec2 position = skullDoor[i].getPosition();
			if (pos.x < position.x + 40 && position.x < pos.x + 24 &&
				pos.y < position.y + 32 && position.y < pos.y + 32 && !changingScene && Game::instance().getSpecialKey(0x0065)) {
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
				first = false;
			}
			startEndDoor->update(deltaTime);
			if (player->getAnimDoorNum() == -1) {
				delete startEndDoor;
				startEndDoor = NULL;
			}
		} else startEndDoor->update(deltaTime);
	}
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
			glm::vec2 position = object[i].getPosition();
			if (pos.x < position.x + 16 && position.x < pos.x + 24 &&
				pos.y < position.y + 16 && position.y < pos.y + 32 && !object[i].getPicked()) {
				if (object[i].getType() == 1) {
					player->pickPowerUp(object[i].getPowerUp());
					object[i].setPicked();
					object[i].update(deltaTime);
				}
			}
		}
	}
	int tileSize = map->getTileSize();
	if (player->getAnimDoorNum() == -2) {
		glm::ivec2 position = player->getPosition();
		if (sceneNum == 1 && screenNum == 3) {
			changeScreen(2, 1, glm::ivec2(5 * tileSize, 4 * tileSize - 8));
		}
		else if (sceneNum == 2 && screenNum == 1) {
			changeScreen(1, 3, glm::ivec2(28 * tileSize, 7 * tileSize - 8));
		}
		else if (sceneNum == 2 && screenNum == 3) {
			changeScreen(3, 1, glm::ivec2(14 * tileSize, 17 * tileSize - 8));
		}
		else if (sceneNum == 3 && screenNum == 1) {
			changeScreen(2, 3, glm::ivec2(10 * tileSize, 10 * tileSize - 8));
		}
		else if (sceneNum == 3 && screenNum == 3) {
			changeScreen(4, 1, glm::ivec2(4 * tileSize, 14 * tileSize - 8));
		}
		else if (sceneNum == 4 && screenNum == 1) {
			if (position.x == 4*tileSize + 24 && position.y == 5*tileSize - 8)
				changeScreen(4, 2, glm::ivec2(28 * tileSize, 17 * tileSize - 8));
			else if (position.x == 4*tileSize + 24 && position.y == 14*tileSize - 8)
				changeScreen(3, 3, glm::ivec2(2 * tileSize, 13 * tileSize - 8));
			else if (position.x == 27*tileSize + 24 && position.y == 5*tileSize - 8)
				changeScreen(4, 3, glm::ivec2(6 * tileSize, 16 * tileSize - 8));
		}
		else if (sceneNum == 4 && screenNum == 2) {
			changeScreen(4, 1, glm::ivec2(4 * tileSize, 5 * tileSize - 8));
		}
		else if (sceneNum == 4 && screenNum == 3) {
			if (position.x == 14 * tileSize + 24 && position.y == 15*tileSize - 8)
				changeScreen(5, 1, glm::ivec2(3 * tileSize, 4 * tileSize - 8));
			else if (position.x == 6*tileSize + 24 && position.y == 16*tileSize - 8)
				changeScreen(4, 1, glm::ivec2(26 * tileSize, 5 * tileSize - 8));
		}
		else if (sceneNum == 5 && screenNum == 1) {
			changeScreen(4, 3, glm::ivec2(14 * tileSize, 15 * tileSize - 8));
		}
		player->setDoorCollision(false);
	}
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
	if (greenDoor != NULL) for (int i = 0; i < numGreenDoors; ++i) greenDoor[i].render();
	if (startEndDoor != NULL) startEndDoor->render();
	if (object != NULL) {
		for (int i = 0; i < numObjects; ++i) {
			if (!object[i].getPicked()) object[i].render();
		}
	}
	if (!changingScene && skullDoor != NULL) for (int i = 0; i < numSkullDoors; ++i) skullDoor[i].render();
	player->render();
	if (changingScene && skullDoor != NULL) for (int i = 0; i < numSkullDoors; ++i) skullDoor[i].render();
	if (cabezaFlotante != NULL) cabezaFlotante->render();
	if (esqueleto != NULL) esqueleto->render();
}

void Scene::changeScreen(int scene, int screen, glm::vec2 pos)
{
	sceneNum = scene;
	screenNum = screen;
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
		numGotas = 1;
		gota = new Gota[1];
		gota[0].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(5 * map->getTileSize(), 2 * map->getTileSize()));
		gota[0].setTileMap(map);
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
		numObjects = 1;
		object = new Object[1];
		object[0].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(26 * map->getTileSize(), 10 * map->getTileSize()), 1, 1);
		object[0].setTileMap(map);
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
	}
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



