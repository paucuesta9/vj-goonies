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
#include "Gota.h"
#include "SkullDoor.h"
#include "GreenDoor.h"
#include "StartEndDoor.h"
#include "Object.h"
#include "MenuInferior.h"


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
	Aspersor *aspersor;
	Gota* gota;
	SkullDoor* skullDoor;
	GreenDoor* greenDoor;
	StartEndDoor* startEndDoor;
	Object* object;
	MenuInferior* menuInferior;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	int sceneNum, screenNum, numAsp, numCasc, numGotas, numSkullDoors, numGreenDoors, numObjects, numPowerUp;
	bool changingScene;
	int numFriends, nextPos;
	bool first, pressedN;
};


#endif // _SCENE_INCLUDE

