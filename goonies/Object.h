#ifndef _OBJECTS_INCLUDE
#define _OBJECTS_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


class Object
{

public:
	~Object();
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, glm::ivec2 pos, int type, int powerUp);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);
	glm::ivec2 getPosition();
	int getType();
	int getPowerUp();
	void setPicked();
	bool getPicked();

private:
	glm::ivec2 tileMapDispl, posObject;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
	int powerUp;
	bool picked;
};


#endif // _OBJECT_INCLUDE
