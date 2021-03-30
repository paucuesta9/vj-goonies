#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"


#define SCREEN_X 60 //Posicion del nivel respecto la pantalla X
#define SCREEN_Y 70 //Posicion del nivel respecto la pantalla Y

#define INIT_PLAYER_X_TILES 5 //Posición X inicial del jugador contando en TILES (cuadrados)
#define INIT_PLAYER_Y_TILES 10 //Posición Y inicial del jugador contando en TILES (cuadrados)


Scene::Scene()
{
	map = NULL;
	player = NULL;
}

Scene::~Scene()
{
	if(map != NULL)
		delete map;
	if(player != NULL)
		delete player;
}


void Scene::init()
{
	initShaders();
	sceneNum = 1;
	screenNum = 1;
	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	changeScreen(sceneNum, screenNum, glm::vec2(INIT_PLAYER_X_TILES * 16, INIT_PLAYER_Y_TILES * 16));
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	player->update(deltaTime);
	cabezaFlotante->update(deltaTime);
	esqueleto->update(deltaTime);
	glm::vec2 pos = player->getPosition();
	glm::vec2 posCabezaFlotante = cabezaFlotante->getPosition();
	if (pos.x < posCabezaFlotante.x + 8 && posCabezaFlotante.x < pos.x + 32 &&
		pos.y < posCabezaFlotante.y + 8 && posCabezaFlotante.y < pos.y + 32) {
		player->hurted();
	}
	if (esqueleto->isThereBone()) {
		glm::vec2 bonePos = esqueleto->getBonePosition();
		if (pos.x < bonePos.x + 6 && bonePos.x < pos.x + 32 &&
			pos.y < bonePos.y + 8 && bonePos.y < pos.y + 32) {
			player->hurted();
			esqueleto->deleteBone();
		}
	}
	glm::vec2 posEsqueleto = esqueleto->getPosition();
	if (pos.x < posEsqueleto.x + 8 && posEsqueleto.x < pos.x + 32 &&
		pos.y < posEsqueleto.y + 8 && posEsqueleto.y < pos.y + 32) {
		player->hurted();
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
	int tileSize = map->getTileSize();
	if (player->getDoorCollision()) {
		glm::ivec2 position = player->getPosition();
		if (sceneNum == 1 && screenNum == 3) {
			changeScreen(2, 1, glm::ivec2(5 * tileSize - 8, 4 * tileSize - 4));
		}
		else if (sceneNum == 2 && screenNum == 1) {
			changeScreen(1, 3, glm::ivec2(28 * tileSize - 8, 7 * tileSize - 4));
		}
		else if (sceneNum == 2 && screenNum == 3) {
			changeScreen(3, 1, glm::ivec2(14 * tileSize - 8, 17 * tileSize - 4));
		}
		else if (sceneNum == 3 && screenNum == 1) {
			changeScreen(2, 3, glm::ivec2(10 * tileSize - 8, 10 * tileSize - 4));
		}
		else if (sceneNum == 3 && screenNum == 3) {
			changeScreen(4, 1, glm::ivec2(4 * tileSize - 8, 14 * tileSize - 4));
		}
		else if (sceneNum == 4 && screenNum == 1) {
			if (position.x == 4*tileSize + 22 && position.y == 5*tileSize - 8)
				changeScreen(4, 2, glm::ivec2(28 * tileSize - 8, 17 * tileSize - 4));
			else if (position.x == 4*tileSize + 22 && position.y == 14*tileSize - 8)
				changeScreen(3, 3, glm::ivec2(2 * tileSize - 8, 13 * tileSize - 4));
			else if (position.x == 27*tileSize + 22 && position.y == 5*tileSize - 8)
				changeScreen(4, 3, glm::ivec2(6 * tileSize - 8, 16 * tileSize - 4));
		}
		else if (sceneNum == 4 && screenNum == 2) {
			changeScreen(4, 1, glm::ivec2(4 * tileSize - 8, 5 * tileSize - 4));
		}
		else if (sceneNum == 4 && screenNum == 3) {
			if (position.x == 14 * tileSize + 22 && position.y == 15*tileSize - 8)
				changeScreen(5, 1, glm::ivec2(3 * tileSize - 8, 4 * tileSize - 4));
			else if (position.x == 6*tileSize + 22 && position.y == 16*tileSize - 8)
				changeScreen(4, 1, glm::ivec2(26 * tileSize - 8, 5 * tileSize - 4));
		}
		else if (sceneNum == 5 && screenNum == 1) {
			changeScreen(4, 3, glm::ivec2(14 * tileSize - 8, 15 * tileSize - 4));
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
	player->render();
	cabezaFlotante->render();
	esqueleto->render();
}

void Scene::changeScreen(int scene, int screen, glm::vec2 pos)
{
	sceneNum = scene;
	screenNum = screen;
	map = TileMap::createTileMap("levels/level" + to_string(scene) + "_" + to_string(screen) + ".txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(pos);
	player->setTileMap(map);
	if (scene == 1 && screen == 1) {
		cabezaFlotante = new CabezaFlotante();
		cabezaFlotante->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		cabezaFlotante->setPosition(glm::vec2(22 * map->getTileSize(), 10 * map->getTileSize()));
		cabezaFlotante->setTileMap(map);
		//QUITAR
		esqueleto = new Esqueleto();
		esqueleto->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		esqueleto->setPosition(glm::vec2(10 * map->getTileSize(), 13 * map->getTileSize()));
		esqueleto->setTileMap(map);
	}
	else if (scene == 1 && screen == 2) {
		esqueleto = new Esqueleto();
		esqueleto->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		esqueleto->setPosition(glm::vec2(10 * map->getTileSize(), 13 * map->getTileSize()));
		esqueleto->setTileMap(map);
		cabezaFlotante = new CabezaFlotante();
		cabezaFlotante->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		cabezaFlotante->setPosition(glm::vec2(26 * map->getTileSize(), 4 * map->getTileSize()));
		cabezaFlotante->setTileMap(map);

	} else if (scene == 2 && screen == 1) {
		esqueleto = new Esqueleto();
		esqueleto->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		esqueleto->setPosition(glm::vec2(24 * map->getTileSize(), 3 * map->getTileSize()));
		esqueleto->setTileMap(map);
		cabezaFlotante = new CabezaFlotante();
		cabezaFlotante->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		cabezaFlotante->setPosition(glm::vec2(7 * map->getTileSize(), 14 * map->getTileSize()));
		cabezaFlotante->setTileMap(map);
	}
	else if (scene == 2 && screen == 2) {
		esqueleto = new Esqueleto();
		esqueleto->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		esqueleto->setPosition(glm::vec2(27 * map->getTileSize(), 6 * map->getTileSize()));
		esqueleto->setTileMap(map);
		cabezaFlotante = new CabezaFlotante();
		cabezaFlotante->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		cabezaFlotante->setPosition(glm::vec2(23 * map->getTileSize(), 14 * map->getTileSize()));
		cabezaFlotante->setTileMap(map);
	}
	else if (scene == 2 && screen == 3) {
		esqueleto = new Esqueleto();
		esqueleto->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		esqueleto->setPosition(glm::vec2(23 * map->getTileSize(), 16 * map->getTileSize()));
		esqueleto->setTileMap(map);
		cabezaFlotante = new CabezaFlotante();
		cabezaFlotante->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		cabezaFlotante->setPosition(glm::vec2(7 * map->getTileSize(), 4 * map->getTileSize()));
		cabezaFlotante->setTileMap(map);
	}
	else if (scene == 3 && screen == 1) {
		cabezaFlotante = new CabezaFlotante();
		cabezaFlotante->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		cabezaFlotante->setPosition(glm::vec2(12 * map->getTileSize(), 10 * map->getTileSize()));
		cabezaFlotante->setTileMap(map);
	}
	else if (scene == 3 && screen == 2) {
		esqueleto = new Esqueleto();
		esqueleto->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		esqueleto->setPosition(glm::vec2(12 * map->getTileSize(), 2 * map->getTileSize()));
		esqueleto->setTileMap(map);
		cabezaFlotante = new CabezaFlotante();
		cabezaFlotante->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		cabezaFlotante->setPosition(glm::vec2(11 * map->getTileSize(), 17 * map->getTileSize()));
		cabezaFlotante->setTileMap(map);
	}
	else if (scene == 4 && screen == 2) {
		cabezaFlotante = new CabezaFlotante();
		cabezaFlotante->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		cabezaFlotante->setPosition(glm::vec2(26 * map->getTileSize(), 7 * map->getTileSize()));
		cabezaFlotante->setTileMap(map);
		esqueleto = new Esqueleto();
		esqueleto->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		esqueleto->setPosition(glm::vec2(6 * map->getTileSize(), 14 * map->getTileSize()));
		esqueleto->setTileMap(map);
	}
	else if (scene == 4 && screen == 3) {
		esqueleto = new Esqueleto();
		esqueleto->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		esqueleto->setPosition(glm::vec2(7 * map->getTileSize(), 2 * map->getTileSize()));
		esqueleto->setTileMap(map);
	}
	else if (scene == 5 && screen == 1) {
		cabezaFlotante = new CabezaFlotante();
		cabezaFlotante->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		cabezaFlotante->setPosition(glm::vec2(27 * map->getTileSize(), 2 * map->getTileSize()));
		cabezaFlotante->setTileMap(map);
	}
	else if (scene == 5 && screen == 2) {
		cabezaFlotante = new CabezaFlotante();
		cabezaFlotante->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		cabezaFlotante->setPosition(glm::vec2(25 * map->getTileSize(), 6 * map->getTileSize()));
		cabezaFlotante->setTileMap(map);
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



