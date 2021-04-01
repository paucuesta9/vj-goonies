#ifndef _GOTA_INCLUDE
#define _GOTA_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


class Gota
{

public:
	~Gota();
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, glm::ivec2 pos);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);
	glm::ivec2 getPosition();
	int getStatus();
	void hitObject();

private:
	glm::ivec2 tileMapDispl, posGota, initialPos;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
	int animationTime;
};


#endif // _GOTA_INCLUDE
