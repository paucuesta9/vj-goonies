#ifndef _ENEMIGO_INCLUDE
#define _ENEMIGO_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Enemigo
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);
	glm::ivec2 getPosition();
	int isOut();

private:
	bool bJumping, bLiana, bdoorCollision;
	glm::ivec2 tileMapDispl, posEnemigo;
	int jumpAngle, startY, animDoorNum;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;

};


#endif // _ENEMIGO_INCLUDE


