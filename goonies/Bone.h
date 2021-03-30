#ifndef _BONE_INCLUDE
#define _BONE_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


class Bone
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, int dir);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);
	glm::ivec2 getPosition();
	int getState();
	int isOut();

private:
	glm::ivec2 tileMapDispl, posBone;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
	int direction;
	bool isActive;
};


#endif // _BONE_INCLUDE