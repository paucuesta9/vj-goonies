#ifndef _CASCADA_INCLUDE
#define _CASCADA_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


class Cascada
{

public:
	~Cascada();
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, glm::ivec2 pos, int size);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);
	glm::ivec2 getPosition();
	int getStatus();
	int getSize();
	void initSprite(int spriteNum);

private:
	glm::ivec2 tileMapDispl, posCascada;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
	ShaderProgram shader;
	int num, size, time, Status;
};


#endif // _CASCADA_INCLUDE
