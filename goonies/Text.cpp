#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Object.h"
#include "Text.h"


enum Letters
{
	NUM_0, NUM_1, NUM_2, NUM_3, NUM_4, NUM_5, NUM_6, NUM_7, NUM_8, NUM_9, DASH, 
	A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
	QUESTION_MARK, EXCLAMATION_MARK, TYPE_POINT, SPACE
};

Text::~Text() {
	if (sprite != NULL)
		delete sprite;
}

void Text::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, int size, int color, string newText)
{
	posText = tileMapPos;
	sizeText = newText.size();
	shader = shaderProgram;
	sprite = new Sprite[sizeText];
	switch (color)
	{
	case 1:
		spritesheet.loadFromFile("images/tipografia_red.png", TEXTURE_PIXEL_FORMAT_RGBA);
		break;
	case 2:
		spritesheet.loadFromFile("images/tipografia_blue.png", TEXTURE_PIXEL_FORMAT_RGBA);
		break;
	case 3:
		spritesheet.loadFromFile("images/tipografia_green.png", TEXTURE_PIXEL_FORMAT_RGBA);
		break;
	default:
		spritesheet.loadFromFile("images/tipografia.png", TEXTURE_PIXEL_FORMAT_RGBA);
		break;
	}
	initSprites(size);
	setText(newText);
}

void Text::initSprites(int size) {
	for (int i = 0; i < sizeText; ++i) {
		sprite[i] = *Sprite::createSprite(glm::ivec2(8, 8), glm::vec2(0.03125, 0.5), &spritesheet, &shader);
		sprite[i].setNumberAnimations(41);

		/* NUMEROS */
		sprite[i].setAnimationSpeed(NUM_0, 8);
		sprite[i].addKeyframe(NUM_0, glm::vec2(0.5f, 0.f));

		sprite[i].setAnimationSpeed(NUM_1, 8);
		sprite[i].addKeyframe(NUM_1, glm::vec2(0.53125f, 0.f));

		sprite[i].setAnimationSpeed(NUM_2, 8);
		sprite[i].addKeyframe(NUM_2, glm::vec2(0.5625f, 0.f));

		sprite[i].setAnimationSpeed(NUM_3, 8);
		sprite[i].addKeyframe(NUM_3, glm::vec2(0.59375f, 0.f));

		sprite[i].setAnimationSpeed(NUM_4, 8);
		sprite[i].addKeyframe(NUM_4, glm::vec2(0.625f, 0.f));

		sprite[i].setAnimationSpeed(NUM_5, 8);
		sprite[i].addKeyframe(NUM_5, glm::vec2(0.65625f, 0.f));

		sprite[i].setAnimationSpeed(NUM_6, 8);
		sprite[i].addKeyframe(NUM_6, glm::vec2(0.6875f, 0.f));

		sprite[i].setAnimationSpeed(NUM_7, 8);
		sprite[i].addKeyframe(NUM_7, glm::vec2(0.71875f, 0.f));

		sprite[i].setAnimationSpeed(NUM_8, 8);
		sprite[i].addKeyframe(NUM_8, glm::vec2(0.75f, 0.f));

		sprite[i].setAnimationSpeed(NUM_9, 8);
		sprite[i].addKeyframe(NUM_9, glm::vec2(0.78125f, 0.f));

		/* LETTERS AND SYMBOLS */
		sprite[i].setAnimationSpeed(DASH, 8);
		sprite[i].addKeyframe(DASH, glm::vec2(0.f, 0.5f));

		sprite[i].setAnimationSpeed(A, 8);
		sprite[i].addKeyframe(A, glm::vec2(0.03125f, 0.5f));

		sprite[i].setAnimationSpeed(B, 8);
		sprite[i].addKeyframe(B, glm::vec2(0.03125f * 2, 0.5f));

		sprite[i].setAnimationSpeed(C, 8);
		sprite[i].addKeyframe(C, glm::vec2(0.03125f * 3, 0.5f));

		sprite[i].setAnimationSpeed(D, 8);
		sprite[i].addKeyframe(D, glm::vec2(0.03125f * 4, 0.5f));

		sprite[i].setAnimationSpeed(E, 8);
		sprite[i].addKeyframe(E, glm::vec2(0.03125f * 5, 0.5f));

		sprite[i].setAnimationSpeed(F, 8);
		sprite[i].addKeyframe(F, glm::vec2(0.03125f * 6, 0.5f));

		sprite[i].setAnimationSpeed(G, 8);
		sprite[i].addKeyframe(G, glm::vec2(0.03125f * 7, 0.5f));

		sprite[i].setAnimationSpeed(H, 8);
		sprite[i].addKeyframe(H, glm::vec2(0.03125f * 8, 0.5f));

		sprite[i].setAnimationSpeed(I, 8);
		sprite[i].addKeyframe(I, glm::vec2(0.03125f * 9, 0.5f));

		sprite[i].setAnimationSpeed(J, 8);
		sprite[i].addKeyframe(J, glm::vec2(0.03125f * 10, 0.5f));

		sprite[i].setAnimationSpeed(K, 8);
		sprite[i].addKeyframe(K, glm::vec2(0.03125f * 11, 0.5f));

		sprite[i].setAnimationSpeed(L, 8);
		sprite[i].addKeyframe(L, glm::vec2(0.03125f * 12, 0.5f));

		sprite[i].setAnimationSpeed(M, 8);
		sprite[i].addKeyframe(M, glm::vec2(0.03125f * 13, 0.5f));

		sprite[i].setAnimationSpeed(N, 8);
		sprite[i].addKeyframe(N, glm::vec2(0.03125f * 14, 0.5f));

		sprite[i].setAnimationSpeed(O, 8);
		sprite[i].addKeyframe(O, glm::vec2(0.03125f * 15, 0.5f));

		sprite[i].setAnimationSpeed(P, 8);
		sprite[i].addKeyframe(P, glm::vec2(0.03125f * 16, 0.5f));

		sprite[i].setAnimationSpeed(Q, 8);
		sprite[i].addKeyframe(Q, glm::vec2(0.03125f * 17, 0.5f));

		sprite[i].setAnimationSpeed(R, 8);
		sprite[i].addKeyframe(R, glm::vec2(0.03125f * 18, 0.5f));

		sprite[i].setAnimationSpeed(S, 8);
		sprite[i].addKeyframe(S, glm::vec2(0.03125f * 19, 0.5f));

		sprite[i].setAnimationSpeed(T, 8);
		sprite[i].addKeyframe(T, glm::vec2(0.03125f * 20, 0.5f));

		sprite[i].setAnimationSpeed(U, 8);
		sprite[i].addKeyframe(U, glm::vec2(0.03125f * 21, 0.5f));

		sprite[i].setAnimationSpeed(V, 8);
		sprite[i].addKeyframe(V, glm::vec2(0.03125f * 22, 0.5f));

		sprite[i].setAnimationSpeed(W, 8);
		sprite[i].addKeyframe(W, glm::vec2(0.03125f * 23, 0.5f));

		sprite[i].setAnimationSpeed(X, 8);
		sprite[i].addKeyframe(X, glm::vec2(0.03125f * 24, 0.5f));

		sprite[i].setAnimationSpeed(Y, 8);
		sprite[i].addKeyframe(Y, glm::vec2(0.03125f * 25, 0.5f));

		sprite[i].setAnimationSpeed(Z, 8);
		sprite[i].addKeyframe(Z, glm::vec2(0.03125f * 26, 0.5f));

		sprite[i].setAnimationSpeed(QUESTION_MARK, 8);
		sprite[i].addKeyframe(QUESTION_MARK, glm::vec2(0.03125f * 27, 0.5f));

		sprite[i].setAnimationSpeed(EXCLAMATION_MARK, 8);
		sprite[i].addKeyframe(EXCLAMATION_MARK, glm::vec2(0.03125f * 28, 0.5f));

		sprite[i].setAnimationSpeed(TYPE_POINT, 8);
		sprite[i].addKeyframe(TYPE_POINT, glm::vec2(0.03125f * 29, 0.5f));

		sprite[i].setAnimationSpeed(SPACE, 8);
		sprite[i].addKeyframe(SPACE, glm::vec2(0.03125f * 30, 0.5f));

		sprite[i].changeAnimation(SPACE);
		sprite[i].setPosition(glm::vec2(float(posText.x + 8 * size * i), float(posText.y)));
		sprite[i].setScale(glm::vec3(size, size, 0.f));
	}
}

void Text::update(int deltaTime)
{
	for (int i = 0; i < sizeText; ++i)
		sprite[i].update(deltaTime);
}

void Text::render()
{
	for (int i = 0; i < sizeText; ++i)
		sprite[i].render();
}

void Text::setText(string newText) {
	for (int i = 0; i < newText.size(); ++i) {
		int character = (int)newText.at(i);
		if (character == 33) sprite[i].changeAnimation(EXCLAMATION_MARK);
		else if (character == 63) sprite[i].changeAnimation(QUESTION_MARK);
		else if (character == 45) sprite[i].changeAnimation(DASH);
		else if (character == 46) sprite[i].changeAnimation(TYPE_POINT);
		else if (character >= 48 && character <=57) sprite[i].changeAnimation(character - 48);
		else if (character >= 64 && character <= 90) sprite[i].changeAnimation(character - 54);
		else sprite[i].changeAnimation(SPACE);
	}
}