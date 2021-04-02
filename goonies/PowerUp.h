#ifndef _POWERUP_INCLUDE
#define _POWERUP_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


class PowerUp
{

public:
	~PowerUp();
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition( int numSprite);
	void setSpritePowerUp(int numPowerUp);

private:
	glm::ivec2 tileMapDispl;
	Texture spritesheetPowerUp;
	Sprite* spritePowerUp;
	TileMap* map;
	int powerUp, nextPos;

};
	#endif // _POWERup_INCLUDE

