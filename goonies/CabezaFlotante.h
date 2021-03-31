#ifndef _CABEZA_FLOTANTE_INCLUDE
#define _CABEZA_FLOTANTE_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


class CabezaFlotante
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);
	void die();
	glm::ivec2 getPosition();
	int getStatus();

private:
	glm::ivec2 tileMapDispl, posCabeza;
	int animationTime, Status;
	Texture spritesheetMovement, spritesheetBornDie;
	Sprite* spriteMovement, *spriteBornDie, *sprite;
	TileMap* map;

};


#endif // _ENEMIGO_INCLUDE

