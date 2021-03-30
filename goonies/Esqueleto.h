#ifndef _ESQUELETO_INCLUDE
#define _ESQUELETO_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "Bone.h"


class Esqueleto
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);
	void startAnimationAndThrowBone(int from);
	void throwBone();
	glm::ivec2 getPosition();
	int isOut();

private: 
	glm::ivec2 tileMapDispl, posEsqueleto;
	int jumpAngle, startY, timeAnimation;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
	Bone* bone;
	ShaderProgram& shader;
};


#endif // _ESQUELETO_INCLUDE