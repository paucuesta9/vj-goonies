#ifndef _FRIEND_INCLUDE
#define _FRIEND_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


class Friend
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);
	glm::ivec2 getPosition();
	bool isPicked();
	void setPicked();

private:
	glm::ivec2 tileMapDispl;
	glm::ivec2 position;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
	bool picked;

};


#endif // _FRIEND_INCLUDE
