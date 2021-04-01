#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "CabezaFlotante.h"
#include "Esqueleto.h"
#include "Cascada.h"
#include "Aspersor.h"


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	void init();
	void update(int deltaTime);
	void render();
	void changeScreen(int scene, int screen, glm::vec2 pos);

private:
	void initShaders();

private:
	TileMap *map;
	Player *player;
	CabezaFlotante *cabezaFlotante;
	Esqueleto *esqueleto;
	Cascada *cascada;
	Aspersor* aspersor;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	int sceneNum, screenNum, numAsp, numCasc;
};


#endif // _SCENE_INCLUDE

