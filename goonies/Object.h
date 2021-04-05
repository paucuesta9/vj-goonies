#ifndef _OBJECTS_INCLUDE
#define _OBJECTS_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


class Object
{

public:
	~Object();
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, glm::ivec2 pos, int sceneNum, int screenNum, int type, int powerUp);
	void update(int deltaTime);
	void render(int sceneNum, int screenNum);

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);
	glm::ivec2 getPosition();
	int getType();
	int getPowerUp();
	void setPicked();
	bool getPicked();
	glm::vec2 getLevel();
	bool isActive();
	bool getAgotado();

private:
	glm::ivec2 tileMapDispl, posObject;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
	int powerUp;
	bool picked, agotado;
	int scene, screen, time;
};


#endif // _OBJECT_INCLUDE
