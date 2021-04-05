#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Instructions.h"
#include "Game.h"

Instructions::Instructions()
{

}

Instructions::~Instructions()
{

}

void Instructions::init() {
	initShaders();
	currentTime = 0.0f;
	initBackground();
	initSprites();
	printTexts();
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentScreen = 1;
}

void Instructions::printTexts() {
	texts = new Text[70];
	texts[0].init(glm::vec2(float(160), float(100)), texProgram, 4, 1, "OBJECTIVES");
	texts[1].init(glm::vec2(float(136), float(150)), texProgram, 2, 0, "RESCUE YOUR SIX FRIENDS");
	texts[2].init(glm::vec2(float(152), float(170)), texProgram, 2, 0, "EACH FRIEND IS BEHIND");
	texts[3].init(glm::vec2(float(208), float(190)), texProgram, 2, 0, "ONE GREEN DOOR");
	texts[4].init(glm::vec2(float(80), float(260)), texProgram, 2, 0, "WHICH CAN BE OPENED WITH A KEY");

	texts[5].init(glm::vec2(float(224), float(50)), texProgram, 4, 1, "PLAYER");
	texts[6].init(glm::vec2(float(176), float(100)), texProgram, 2, 0, "YOU HAVE A LIMITED");
	texts[7].init(glm::vec2(float(168), float(120)), texProgram, 2, 0, "LIFE AND EXPERIENCE");
	texts[8].init(glm::vec2(float(168), float(150)), texProgram, 2, 0, "TO MOVE RIGHT PRESS");
	texts[9].init(glm::vec2(float(168), float(170)), texProgram, 2, 0, "THE RIGHT ARROW KEY");
	texts[10].init(glm::vec2(float(176), float(220)), texProgram, 2, 0, "TO MOVE LEFT PRESS");
	texts[11].init(glm::vec2(float(176), float(240)), texProgram, 2, 0, "THE LEFT ARROW KEY");
	texts[12].init(glm::vec2(float(120), float(290)), texProgram, 2, 0, "TO JUMP OR CLIMBING PRESS");
	texts[13].init(glm::vec2(float(192), float(310)), texProgram, 2, 0, "THE UP ARROW KEY");
	texts[14].init(glm::vec2(float(184), float(360)), texProgram, 2, 0, "TO GET DOWN PRESS");
	texts[15].init(glm::vec2(float(176), float(380)), texProgram, 2, 0, "THE DOWN ARROW KEY");
	
	texts[16].init(glm::vec2(float(224), float(100)), texProgram, 4, 1, "PLAYER");
	texts[17].init(glm::vec2(float(80), float(150)), texProgram, 2, 0, "TO PROTECT YOU FROM BEING HURT");
	texts[18].init(glm::vec2(float(128), float(170)), texProgram, 2, 0, "PRESS THE DOWN ARROW KEY");
	texts[19].init(glm::vec2(float(64), float(230)), texProgram, 2, 0, "TO FLOAT UP WHEN FALLING PRESS B");
	texts[20].init(glm::vec2(float(112), float(290)), texProgram, 2, 0, "TO MOVE BETWEEN LIANAS USE");
	texts[21].init(glm::vec2(float(120), float(310)), texProgram, 2, 0, "LEFT AND RIGHT ARROW KEYS");
	
	texts[22].init(glm::vec2(float(208), float(100)), texProgram, 4, 1, "ENEMIES");
	texts[23].init(glm::vec2(float(88), float(150)), texProgram, 2, 0, "THERE ARE TWO KIND OF ENEMIES");
	texts[24].init(glm::vec2(float(88), float(170)), texProgram, 2, 0, "- SKULLS");
	texts[25].init(glm::vec2(float(88), float(190)), texProgram, 2, 0, "- SKELETONS WHICH THROW BONES");
	texts[26].init(glm::vec2(float(152), float(220)), texProgram, 2, 0, "TO KILL THEM YOU MUST");
	texts[27].init(glm::vec2(float(168), float(240)), texProgram, 2, 0, "PRESS THE SPACE BAR");

	texts[28].init(glm::vec2(float(176), float(100)), texProgram, 4, 1, "OBSTACLES");
	texts[29].init(glm::vec2(float(120), float(150)), texProgram, 2, 0, "THE ARE 3 KIND OF OBJECTS");
	texts[30].init(glm::vec2(float(88), float(170)), texProgram, 2, 0, "- WATER DROP");
	texts[31].init(glm::vec2(float(88), float(190)), texProgram, 2, 0, "- WATERFALLS");
	texts[32].init(glm::vec2(float(88), float(210)), texProgram, 2, 0, "- SPRINKLERS");
	texts[33].init(glm::vec2(float(160), float(240)), texProgram, 2, 0, "ALL OF THEM HURT YOU");

	texts[34].init(glm::vec2(float(208), float(100)), texProgram, 4, 1, "OBJECTS");
	texts[35].init(glm::vec2(float(120), float(150)), texProgram, 2, 0, "THE ARE 3 KIND OF OBJECTS");
	texts[36].init(glm::vec2(float(88), float(170)), texProgram, 2, 0, "- KEY TO OPEN THE GREEN DOORS");
	texts[37].init(glm::vec2(float(88), float(190)), texProgram, 2, 0, "- BAG TO EARN POWERUPS");
	texts[38].init(glm::vec2(float(120), float(210)), texProgram, 2, 0, "OR EXPERIENCE");
	texts[39].init(glm::vec2(float(88), float(230)), texProgram, 2, 0, "- POTIONS TO EARN POINTS");
	
	texts[40].init(glm::vec2(float(192), float(100)), texProgram, 4, 1, "POWERUPS");
	texts[41].init(glm::vec2(float(112), float(150)), texProgram, 2, 0, "THE ARE 5 KIND OF POWERUPS");
	texts[42].init(glm::vec2(float(208), float(180)), texProgram, 2, 0, "- HYPER SHOES.");
	texts[43].init(glm::vec2(float(192), float(200)), texProgram, 1, 0, "THE SPEED OF THE PLAYER IS INCREASED");
	texts[44].init(glm::vec2(float(192), float(220)), texProgram, 2, 0, "- GRAY RAINCOAT.");
	texts[45].init(glm::vec2(float(192), float(240)), texProgram, 1, 0, "IT PROTECTS YOU FROM WATER DROPS");
	texts[46].init(glm::vec2(float(192), float(260)), texProgram, 2, 0, "- BLUE RAINCOAT.");
	texts[47].init(glm::vec2(float(192), float(280)), texProgram, 1, 0, "IT PROTECTS YOU FROM WATERFALLS");
	texts[48].init(glm::vec2(float(168), float(300)), texProgram, 2, 0, "- YELLOW SPELLBOOK.");
	texts[49].init(glm::vec2(float(192), float(320)), texProgram, 1, 0, "IT PROTECTS YOU FROM SKELETONS");
	texts[50].init(glm::vec2(float(184), float(340)), texProgram, 2, 0, "- BLUE SPELLBOOK.");
	texts[51].init(glm::vec2(float(192), float(360)), texProgram, 1, 0, "IT PROTECTS YOU FROM SKULLS");
	
	texts[52].init(glm::vec2(float(224), float(100)), texProgram, 4, 1, "LEVELS");
	texts[53].init(glm::vec2(float(152), float(150)), texProgram, 2, 0, "THERE ARE FIVE LEVELS");
	texts[54].init(glm::vec2(float(128), float(180)), texProgram, 2, 0, "TO MOVE BETWEEN THEM YOU");
	texts[55].init(glm::vec2(float(112), float(200)), texProgram, 2, 0, "MUST CROSS THE SKULL DOORS");
	texts[56].init(glm::vec2(float(88), float(230)), texProgram, 2, 0, "TO DO THAT PRESS UP ARROW KEY");
	texts[57].init(glm::vec2(float(80), float(260)), texProgram, 2, 0, "WHEN BEING IN FRONT OF THE DOOR");
	
	texts[58].init(glm::vec2(float(128), float(50)), texProgram, 4, 1, "SPECIAL KEYS");
	texts[59].init(glm::vec2(float(280), float(100)), texProgram, 2, 0, "TO...");
	texts[59].init(glm::vec2(float(152), float(100)), texProgram, 2, 0, "CHANGE BETWEEN SCENES");
	texts[60].init(glm::vec2(float(192), float(120)), texProgram, 2, 0, "PRESS S AND THEN");
	texts[61].init(glm::vec2(float(104), float(140)), texProgram, 2, 0, "THE SCENE AND SCREEN NUMBER");
	texts[62].init(glm::vec2(float(120), float(180)), texProgram, 2, 0, "ACTIVATE GOD MODE PRESS G");
	texts[63].init(glm::vec2(float(160), float(200)), texProgram, 2, 0, "SAVE A FRIEND PESS N");
	texts[64].init(glm::vec2(float(96), float(240)), texProgram, 2, 0, "ACTIVATE HYPER SHOES PRESS 1");
	texts[65].init(glm::vec2(float(80), float(260)), texProgram, 2, 0, "ACTIVATE BLUE RAINCOAT PRESS 2");
	texts[66].init(glm::vec2(float(80), float(280)), texProgram, 2, 0, "ACTIVATE GRAY RAINCOAT PRESS 3");
	texts[67].init(glm::vec2(float(56), float(300)), texProgram, 2, 0, "ACTIVATE YELLOW SPELLBOOK PRESS 4");
	texts[68].init(glm::vec2(float(72), float(320)), texProgram, 2, 0, "ACTIVATE BLUE SPELLBOOK PRESS 5");

	texts[69].init(glm::vec2(float(136), float(450)), texProgram, 2, 1, "PRESS ESC TO GO TO MENU");
}

void Instructions::initBackground() {
	spritesheetBackground.loadFromFile("images/creditos.png", TEXTURE_PIXEL_FORMAT_RGBA);
	background = new Sprite();
	background = Sprite::createSprite(glm::ivec2(640, 480), glm::vec2(1.0, 1.0), &spritesheetBackground, &texProgram);
	background->setNumberAnimations(1);

	background->setAnimationSpeed(0, 8);
	background->addKeyframe(0, glm::vec2(0.f, 0.f));

	background->changeAnimation(0);
	background->setPosition(glm::vec2(0, 0));
}

void Instructions::initSprites() {
	// OBJECTS
	object = new Object[3];
	object[0].init(glm::vec2(0, 0), texProgram, glm::vec2(312, 280), 0, 0, 0, 0);
	object[1].init(glm::vec2(0, 0), texProgram, glm::vec2(312, 280), 0, 0, 1, 1);
	object[2].init(glm::vec2(0, 0), texProgram, glm::vec2(312, 280), 0, 0, 3, 0);

	//GREEN DOOR WITH FRIEND
	spritesheetFriend.loadFromFile("images/green_door_instructions.png", TEXTURE_PIXEL_FORMAT_RGBA);
	friends = new Sprite();
	friends = Sprite::createSprite(glm::ivec2(24, 32), glm::vec2(0.5, 1.0), &spritesheetFriend, &texProgram);
	friends->setNumberAnimations(1);

	friends->setAnimationSpeed(0, 2);
	friends->addKeyframe(0, glm::vec2(0.f, 0.f));
	friends->addKeyframe(0, glm::vec2(0.5f, 0.f));

	friends->changeAnimation(0);
	friends->setPosition(glm::vec2(308, 210));

	// ANIMATION LIANA
	spritesheetAnimationLiana.loadFromFile("images/animation_lianas_instructions.png", TEXTURE_PIXEL_FORMAT_RGBA);
	animationLiana = new Sprite();
	animationLiana = Sprite::createSprite(glm::ivec2(64, 48), glm::vec2(0.5, 0.5), &spritesheetAnimationLiana, &texProgram);
	animationLiana->setNumberAnimations(1);

	animationLiana->setAnimationSpeed(0, 4);
	animationLiana->addKeyframe(0, glm::vec2(0.f, 0.f));
	animationLiana->addKeyframe(0, glm::vec2(0.5f, 0.f));
	animationLiana->addKeyframe(0, glm::vec2(0.f, 0.5f));
	animationLiana->addKeyframe(0, glm::vec2(0.5f, 0.5f));

	animationLiana->changeAnimation(0);
	animationLiana->setPosition(glm::vec2(288, 360));

	// MOVE KEYS
	spritesheetMoveKeys.loadFromFile("images/Keys/Move-Key.png", TEXTURE_PIXEL_FORMAT_RGBA);
	moveKeys = new Sprite[4];
	for (int i = 0; i < 4; ++i) {
		moveKeys[i] = *Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.25, 0.5), &spritesheetMoveKeys, &texProgram);
		moveKeys[i].setNumberAnimations(4);

		moveKeys[i].setAnimationSpeed(0, 2);
		moveKeys[i].addKeyframe(0, glm::vec2(0.f, 0.f));

		moveKeys[i].setAnimationSpeed(1, 2);
		moveKeys[i].addKeyframe(1, glm::vec2(0.5f, 0.f));

		moveKeys[i].setAnimationSpeed(2, 2);
		moveKeys[i].addKeyframe(2, glm::vec2(0.f, 0.5f));

		moveKeys[i].setAnimationSpeed(3, 2);
		moveKeys[i].addKeyframe(3, glm::vec2(0.5f, 0.5f));
	}
	moveKeys[0].changeAnimation(0); //RIGHT
	moveKeys[1].changeAnimation(1); //LEFT
	moveKeys[2].changeAnimation(2); //UP
	moveKeys[3].changeAnimation(3); //DOWN

	// OTHER KEYS
	spritesheetKeys.loadFromFile("images/Keys/Keys.png", TEXTURE_PIXEL_FORMAT_RGBA);
	keys = new Sprite[4];
	for (int i = 0; i < 4; ++i) {
		keys[i] = *Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.25, 0.5), &spritesheetKeys, &texProgram);
		keys[i].setNumberAnimations(1);

		keys[i].setAnimationSpeed(0, 2);
		keys[i].addKeyframe(0, glm::vec2(0.f, 0.f));
	}
	moveKeys[0].changeAnimation(0); //B

	// BIG KEYS
	bigKeys = new Sprite[4];
	for (int i = 0; i < 4; ++i) {
		bigKeys[i] = *Sprite::createSprite(glm::ivec2(64 , 32), glm::vec2(0.5, 0.5), &spritesheetKeys, &texProgram);
		bigKeys[i].setNumberAnimations(1);

		bigKeys[i].setAnimationSpeed(0, 2);
		bigKeys[i].addKeyframe(0, glm::vec2(0.f, 0.5f));
	}
	bigKeys[0].changeAnimation(0); //SPACE

	// CABEZA FLOTANTE
	spritesheetCabezaFlotante.loadFromFile("images/cabeza_volante.png", TEXTURE_PIXEL_FORMAT_RGBA);
	cabezaFlotante = new Sprite();
	cabezaFlotante = Sprite::createSprite(glm::ivec2(8, 10), glm::vec2(0.5, 0.5), &spritesheetCabezaFlotante, &texProgram);
	cabezaFlotante->setNumberAnimations(1);

	cabezaFlotante->setAnimationSpeed(0, 8);
	cabezaFlotante->addKeyframe(0, glm::vec2(0.f, 0.5f));
	cabezaFlotante->addKeyframe(0, glm::vec2(0.5f, 0.5f));

	cabezaFlotante->changeAnimation(0);
	cabezaFlotante->setPosition(glm::vec2(260, 310));
	cabezaFlotante->setScale(glm::vec3(2.0f, 2.f, 0.f));

	// ESQUELETO
	spritesheetEsqueleto.loadFromFile("images/esqueleto.png", TEXTURE_PIXEL_FORMAT_RGBA);
	esqueleto = new Sprite();
	esqueleto = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.5, 0.5), &spritesheetEsqueleto, &texProgram);
	esqueleto->setNumberAnimations(1);

	esqueleto->setAnimationSpeed(0, 8);
	esqueleto->addKeyframe(0, glm::vec2(0.f, 0.0f));
	esqueleto->addKeyframe(0, glm::vec2(0.5f, 0.0f));
	esqueleto->changeAnimation(0);
	esqueleto->setPosition(glm::vec2(340, 300));
	esqueleto->setScale(glm::vec3(2.0f, 2.f, 0.f));

	// MOVE SCREEN
	spritesheetMoveScreen.loadFromFile("images/instructions_change.png", TEXTURE_PIXEL_FORMAT_RGBA);
	moveScreen = new Sprite[2];
	for (int i = 0; i < 2; ++i) {
		moveScreen[i] = *Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.5, 0.5), &spritesheetMoveScreen, &texProgram);
		moveScreen[i].setNumberAnimations(4);

		moveScreen[i].setAnimationSpeed(0, 8);
		moveScreen[i].addKeyframe(0, glm::vec2(0.f, 0.f));

		moveScreen[i].setAnimationSpeed(1, 8);
		moveScreen[i].addKeyframe(1, glm::vec2(0.5f, 0.f));

		moveScreen[i].setAnimationSpeed(2, 8);
		moveScreen[i].addKeyframe(2, glm::vec2(0.f, 0.5f));

		moveScreen[i].setAnimationSpeed(3, 8);
		moveScreen[i].addKeyframe(3, glm::vec2(0.5f, 0.5f));
	}
	moveScreen[0].changeAnimation(0);
	moveScreen[0].setPosition(glm::vec2(10, 224));

	moveScreen[1].changeAnimation(2);
	moveScreen[1].setPosition(glm::vec2(598, 224));
}

void Instructions::hover(int which, bool isHover) {
	switch (which)
	{
	case 0:
		if (isHover) moveScreen[0].changeAnimation(2);
		else moveScreen[0].changeAnimation(0);
		break;
	case 1:
		if (isHover) moveScreen[1].changeAnimation(3);
		else moveScreen[1].changeAnimation(1);
		break;
	default:
		break;
	}
}

void Instructions::clicked(int which) {
	switch (which)
	{
	case 0:
		if (currentScreen != 1)
			--currentScreen;
		break;
	case 1:
		if (currentScreen != 9)
			++currentScreen;
		break;
	default:
		break;
	}
}

void Instructions::update(int deltaTime) {
	currentTime += deltaTime;
	if (Game::instance().getSpecialKey(GLUT_KEY_LEFT)) pressedLeft = true;
	else if (pressedLeft) releasedLeft = true;

	if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) pressedRight = true;
	else if (pressedRight) releasedRight = true;

	if (releasedLeft) {
		pressedLeft = releasedLeft = false;
		if (currentScreen > 1) --currentScreen;
	}

	if (releasedRight) {
		pressedRight = releasedRight = false;
		if (currentScreen < 9) ++currentScreen;
	}

	texts[69].update(deltaTime);

	moveScreen[0].update(deltaTime);
	moveScreen[1].update(deltaTime);

	switch (currentScreen)
	{
	case 1:
		object[0].setPosition(glm::vec2(312, 280));
		object[0].update(deltaTime);
		friends->update(deltaTime);
		for (int i = 0; i < 5; ++i) texts[i].update(deltaTime);
		break;
	case 2:
		for (int i = 5; i < 16; ++i) texts[i].update(deltaTime);
		moveKeys[0].setPosition(glm::vec2(304, 185));
		moveKeys[1].setPosition(glm::vec2(304, 255));
		moveKeys[2].setPosition(glm::vec2(304, 325));
		moveKeys[3].setPosition(glm::vec2(304, 395));
		for (int i = 0; i < 4; ++i) moveKeys[i].update(deltaTime);
		break;
	case 3:
		for (int i = 16; i < 22; ++i) texts[i].update(deltaTime);
		moveKeys[3].setPosition(glm::vec2(304, 185));
		moveKeys[1].setPosition(glm::vec2(288, 325));
		moveKeys[0].setPosition(glm::vec2(320, 325));
		for (int i = 0; i < 4; ++i) moveKeys[i].update(deltaTime);
		keys[0].setPosition(glm::vec2(304, 245));
		for (int i = 0; i < 4; ++i) keys[i].update(deltaTime);
		animationLiana->update(deltaTime);
		break;
	case 4:
		for (int i = 22; i < 28; ++i) texts[i].update(deltaTime);
		bigKeys[0].setPosition(glm::vec2(288, 260));
		bigKeys[0].update(deltaTime);
		cabezaFlotante->update(deltaTime);
		esqueleto->update(deltaTime);
		break;
	case 5:
		for (int i = 28; i < 34; ++i) texts[i].update(deltaTime);
		break;
	case 6:
		for (int i = 34; i < 40; ++i) texts[i].update(deltaTime);
		object[0].setPosition(glm::vec2(248, 280));
		object[0].update(deltaTime);
		object[1].setPosition(glm::vec2(312, 280));
		object[1].update(deltaTime);
		object[2].setPosition(glm::vec2(376, 280));
		object[2].update(deltaTime);
		break;
	case 7:
		for (int i = 40; i < 52; ++i) texts[i].update(deltaTime);
		break;
	case 8:
		for (int i = 52; i < 58; ++i) texts[i].update(deltaTime);
		moveKeys[2].setPosition(glm::vec2(304, 275));
		moveKeys[2].update(deltaTime);
		break;
	case 9:
		for (int i = 58; i < 69; ++i) texts[i].update(deltaTime);
		break;
	default:
		break;
	}
	background->update(deltaTime);
}

void Instructions::render() {
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	background->render();
	if (currentScreen != 1) moveScreen[0].render();
	if (currentScreen != 9) moveScreen[1].render();
	switch (currentScreen)
	{
	case 1:
		for (int i = 0; i < 5; ++i) texts[i].render();
		object[0].render(0, 0);
		friends->render();
		break;
	case 2:
		for (int i = 5; i < 16; ++i) texts[i].render();
		for (int i = 0; i < 4; ++i) moveKeys[i].render();
		break;
	case 3:
		for (int i = 16; i < 22; ++i) texts[i].render();
		animationLiana->render();
		moveKeys[3].render();
		moveKeys[1].render();
		moveKeys[0].render();
		keys[0].render();
		break;
	case 4:
		for (int i = 22; i < 28; ++i) texts[i].render();
		bigKeys[0].render();
		cabezaFlotante->render();
		esqueleto->render();
		break;
	case 5:
		for (int i = 28; i < 34; ++i) texts[i].render();
		break;
	case 6:
		for (int i = 34; i < 40; ++i) texts[i].render();
		object[0].render(0, 0);
		object[1].render(0, 0);
		object[2].render(0, 0);
		break;
	case 7:
		for (int i = 40; i < 52; ++i) texts[i].render();
		break;
	case 8:
		for (int i = 52; i < 58; ++i) texts[i].render();
		moveKeys[2].render();
		break;
	case 9:
		for (int i = 58; i < 69; ++i) texts[i].render();
		break;
	default:
		break;
	}
	texts[69].render();
}

void Instructions::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if (!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}