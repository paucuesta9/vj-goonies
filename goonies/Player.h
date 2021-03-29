#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Player
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();
	
	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	glm::ivec2 getPosition();
	int getDoorCollision();
	void setDoorCollision(bool state);
	void setAnimation(int animation);
	int isOut();
	void setSprite(int numSprite);
	
private:
	bool bJumping, bLiana, bdoorCollision;
	glm::ivec2 tileMapDispl, posPlayer;
	int jumpAngle, startY, animDoorNum, animationTime;
	Texture spritesheetNormal, spritesheetHurt;
	Sprite *sprite, *spriteNormal, *spriteHurt;
	TileMap *map;

};


#endif // _PLAYER_INCLUDE


