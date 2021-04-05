#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"
#include <Windows.h>
#pragma comment(lib, "winmm.lib")

enum CurrentScreen {
	INTRO, MAIN_MENU, GAME, GAME_OVER, CREDITS, INSTRUCTIONS, PAUSE, WIN
};

void Game::init()
{
	bPlay = true;
	glClearColor(0.f, 0.f, 0.f, 1.0f);
	currentScreen = MAIN_MENU;
	//PlaySound("", NULL, SND_FILENAME);

	intro.init();
	mainMenu.init();
	scene.init();
	gameOver.init();
	credits.init();
	instructions.init();
	pause.init();
	win.init();
}

bool Game::update(int deltaTime)
{
	switch (currentScreen)
	{
	case INTRO:
		intro.update(deltaTime);
		if (intro.isFinished()) currentScreen = MAIN_MENU;
		break;
	case MAIN_MENU:
		mainMenu.update(deltaTime);
		break;
	case GAME:
		scene.update(deltaTime);
		if (scene.isGameOver())
			currentScreen = GAME_OVER;
		if (scene.hasWon())
			currentScreen = WIN;
		break;
	case GAME_OVER:
		gameOver.update(deltaTime);
		break;
	case CREDITS:
		credits.update(deltaTime);
		break;
	case INSTRUCTIONS:
		instructions.update(deltaTime);
		break;
	case PAUSE:
		pause.update(deltaTime);
		break;
	case WIN:
		win.update(deltaTime);
		break;
	}
	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	switch (currentScreen)
	{
	case INTRO:
		intro.render();
		break;
	case MAIN_MENU:
		mainMenu.render();
		break;
	case GAME:
		scene.render();
		break;
	case GAME_OVER:
		gameOver.render();
		break;
	case CREDITS:
		credits.render();
		break;
	case INSTRUCTIONS:
		instructions.render();
		break;
	case PAUSE:
		pause.render();
		break;
	case WIN:
		win.render();
		break;
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
		case WIN:
			currentScreen = MAIN_MENU;
			break;
		}
	}
	else if (key == 114) { // R code
		if (currentScreen == GAME_OVER) {
			currentScreen = GAME;
			scene.restart();
		}
	}
	else if (key == 109) {
		if (currentScreen == PAUSE) {
			currentScreen = MAIN_MENU;
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

void Game::moveMouse(int x, int y)
{
	if (currentScreen == MAIN_MENU) {
		if (x >= 288 && x < 352 && y >= 160 && y < 176) mainMenu.hover(0, 1);
		else mainMenu.hover(0, 0);
		if (x >= 224 && x < 416 && y >= 224 && y < 240) mainMenu.hover(1, 1);
		else mainMenu.hover(1, 0);
		if (x >= 264 && x < 376 && y >= 288 && y < 304) mainMenu.hover(2, 1);
		else mainMenu.hover(2, 0);
		if (x >= 288 && x < 352 && y >= 352 && y < 368) mainMenu.hover(3, 1);
		else mainMenu.hover(3, 0);
	}
	else if (currentScreen == INSTRUCTIONS) {
		if (x >= 10 && x < 42 && y >= 224 && y < 256) instructions.hover(0, true);
		else instructions.hover(0, false);

		if (x >= 598 && x < 630 && y >= 224 && y < 256) instructions.hover(1, true);
		else instructions.hover(1, false);
	}
}

void Game::mousePress(int button, int x, int y)
{

}

void Game::mouseRelease(int button, int x, int y)
{
	if (currentScreen == MAIN_MENU) {
		if (x >= 288 && x < 352 && y >= 160 && y < 176) {
			currentScreen = GAME;
			scene.restart();
		}
		if (x >= 224 && x < 416 && y >= 224 && y < 240) currentScreen = INSTRUCTIONS;
		if (x >= 264 && x < 376 && y >= 288 && y < 304) currentScreen = CREDITS;
		if (x >= 288 && x < 352 && y >= 352 && y < 368) bPlay = false;
	}
	else if (currentScreen == INSTRUCTIONS) {
		if (x >= 10 && x < 42 && y >= 224 && y < 256) instructions.clicked(0);
		if (x >= 598 && x < 630 && y >= 224 && y < 256) instructions.clicked(1);
	}
}

bool Game::getKey(int key) const
{
	return keys[key];
}

bool Game::getSpecialKey(int key) const
{
	return specialKeys[key];
}






