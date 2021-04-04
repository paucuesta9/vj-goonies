#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"
#include <Windows.h>
#pragma comment(lib, "winmm.lib")

enum CurrentScreen {
	INTRO, MAIN_MENU, GAME, GAME_OVER, CREDITS, INSTRUCTIONS, PAUSE
};

void Game::init()
{
	bPlay = true;
	glClearColor(0.f, 0.f, 0.f, 1.0f);
	currentScreen = GAME;
	//PlaySound("", NULL, SND_FILENAME);

	intro.init();
	scene.init();
	gameOver.init();
	pause.init();
}

bool Game::update(int deltaTime)
{
	switch (currentScreen)
	{
	case 0:
		intro.update(deltaTime);
		if (intro.isFinished()) currentScreen = GAME;
		break;
	case 1:
		break;
	case 2:
		scene.update(deltaTime);
		if (scene.isGameOver())
			currentScreen = 3;
		break;
	case 3:
		gameOver.update(deltaTime);
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		pause.update(deltaTime);
	}
	
	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	switch (currentScreen)
	{
	case 0:
		intro.render();
		break;
	case 1:
		break;
	case 2:
		scene.render();
		break;
	case 3:
		gameOver.render();
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		pause.render();
	}
}

void Game::keyPressed(int key)
 {
	if (key == 27) {// Escape code
		switch (currentScreen)
		{
		case MAIN_MENU:
			bPlay = false;
			break;
		case GAME:
			currentScreen = PAUSE;
			break;
		case GAME_OVER:
			currentScreen = MAIN_MENU;
			break;
		case CREDITS:
			currentScreen = MAIN_MENU;
			break;
		case INSTRUCTIONS:
			currentScreen = MAIN_MENU;
			break;
		case PAUSE:
			currentScreen = GAME;
			break;
		}
	}
	else if (key == 114) { // R code
		if (currentScreen == GAME_OVER) {
			currentScreen = GAME;
			scene.restart();
		}
	}
	keys[key] = true;
}

void Game::keyReleased(int key)
{
	keys[key] = false;
}

void Game::specialKeyPressed(int key)
{
	specialKeys[key] = true;
}

void Game::specialKeyReleased(int key)
{
	specialKeys[key] = false;
}

void Game::mouseMove(int x, int y)
{
}

void Game::mousePress(int button)
{
}

void Game::mouseRelease(int button)
{
}

bool Game::getKey(int key) const
{
	return keys[key];
}

bool Game::getSpecialKey(int key) const
{
	return specialKeys[key];
}






