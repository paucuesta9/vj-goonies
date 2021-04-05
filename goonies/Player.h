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
	int getAnimDoorNum();
	void setDoorCollision(bool state);
	void hurted(int damage);
	int isOut();
	void setSprite(int numSprite);
	int isPunching();
	void animateChange();
	void setPowerUp(int powerUp, bool active);
	void ganeExp(int quantity);
	bool getBlueRaincoat();
	bool getGrayRaincoat();
	bool getYellowSpellbook();
	bool getBlueSpellbook();
	int getLife();
	bool isHurted();
	bool isBall();
	void setPoints(int points);
	int getPoints();
	int getExp();
	void die();
	void setKey(bool state);
	bool haveKey();
	void swapGodMode();
	bool hasPowerUp(int powerUp);
	
private:
	bool bJumping, bLiana, bdoorCollision, key;
	glm::ivec2 tileMapDispl, posPlayer;
	int jumpAngle, startY, animDoorNum, animationTime, punchTime;
	Texture spritesheetNormal, spritesheetHurt;
	Sprite *sprite, *spriteNormal, *spriteHurt;
	TileMap *map;
	int life, exp, Status, speed, points;
	bool blueRaincoat, grayRaincoat, yellowSpellbook, blueSpellbook, godMode, pressedB;
};


#endif // _PLAYER_INCLUDE


