#ifndef _SKULL_DOOR_INCLUDE
#define _SKULL_DOOR_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


class SkullDoor
{

public:
	~SkullDoor();
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, glm::ivec2 pos);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);
	glm::ivec2 getPosition();

private:
	glm::ivec2 tileMapDispl, posDoor;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
};


#endif // _SKULL_DOOR_INCLUDE
