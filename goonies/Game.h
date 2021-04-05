#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE

#include "Intro.h"
#include "MainMenu.h"
#include "Scene.h"
#include "GameOver.h"
#include "Pause.h"
#include "Credits.h"
#include "Instructions.h"
#include "Win.h"
#include "Audio.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480


// Game is a singleton (a class with a single instance) that represents our whole application


class Game
{

public:
	Game() {}
	
	
	static Game &instance()
	{
		static Game G;
	
		return G;
	}
	
	void init();
	bool update(int deltaTime);
	void render();
	
	// Input callback methods
	void keyPressed(int key);
	void keyReleased(int key);
	void specialKeyPressed(int key);
	void normalKey(int key);
	void specialKeyReleased(int key);
	void mouseMove(int x, int y);
	void moveMouse(int x, int y);
	void mousePress(int button, int x, int y);
	void mouseRelease(int button, int x, int y);
	
	bool getKey(int key) const;
	bool getSpecialKey(int key) const;

private:
	bool bPlay;                       // Continue to play game?
	Intro intro;
	MainMenu mainMenu;
	Scene scene;                      // Scene to render
	GameOver gameOver;
	Pause pause;
	Instructions instructions;
	Credits credits;
	Win win;
	bool keys[256], specialKeys[256]; // Store key states so that 
	                                  // we can have access at any time
	int currentScreen;

};


#endif // _GAME_INCLUDE


