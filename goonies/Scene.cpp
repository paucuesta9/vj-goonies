#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"


#define SCREEN_X 60 //Posicion del nivel respecto la pantalla X
#define SCREEN_Y 70 //Posicion del nivel respecto la pantalla Y

#define INIT_PLAYER_X_TILES 23 //Posición X inicial del jugador contando en TILES (cuadrados)
#define INIT_PLAYER_Y_TILES 7 //Posición Y inicial del jugador contando en TILES (cuadrados)


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
	sceneNum = 4;
	screenNum = 2;
	map = TileMap::createTileMap("levels/level4_2.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(map);
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	player->update(deltaTime);
	int out = player->isOut();
	glm::vec2 pos;
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
}

void Scene::changeScreen(int scene, int screen, glm::vec2 pos)
{
	sceneNum = scene;
	screenNum = screen;
	map = TileMap::createTileMap("levels/level" + to_string(scene) + "_" + to_string(screen) + ".txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(pos);
	player->setTileMap(map);
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



