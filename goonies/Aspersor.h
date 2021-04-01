#ifndef _ASPERSOR_INCLUDE
#define _ASPERSOR_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


class Aspersor
{

public:
	~Aspersor();
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, glm::ivec2 pos);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);
	glm::ivec2 getPosition(bool left);
	int getStatus(bool left);
	int getSize(bool left);
	void initSprite(int spriteNum);

private:
	glm::ivec2 tileMapDispl, posAspersor;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
	ShaderProgram shader;
	int num, size, timeAnimLeft, timeAnimRight, StatusLeft, StatusRight;
};


#endif // _ASPERSOR_INCLUDE

