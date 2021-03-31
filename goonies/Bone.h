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
	void die();
	int getStatus();

private:
	glm::ivec2 tileMapDispl, posBone;
	Texture spritesheetMove, spritesheetBornDie;
	Sprite* sprite, *spriteMove, *spriteBornDie;
	TileMap* map;
	int direction, Status, animationTime;
	bool isActive;
};


#endif // _BONE_INCLUDE