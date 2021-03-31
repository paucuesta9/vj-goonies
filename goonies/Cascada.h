#ifndef _CASCADA_INCLUDE
#define _CASCADA_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


class Cascada
{

public:
	~Cascada();
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);
	glm::ivec2 getPosition();
	int getStatus();
	void setStatus(int Status);

private:
	glm::ivec2 tileMapDispl, posCascada;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
};


#endif // _CASCADA_INCLUDE
