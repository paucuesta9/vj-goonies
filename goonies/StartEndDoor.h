#ifndef _START_END_DOOR_INCLUDE
#define _START_END_DOOR_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


class StartEndDoor
{

public:
	~StartEndDoor();
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, glm::ivec2 pos);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);
	void open();
	void close();
	glm::ivec2 getPosition();

private:
	glm::ivec2 tileMapDispl, posDoor;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
};


#endif // _START_END_DOOR_INCLUDE

