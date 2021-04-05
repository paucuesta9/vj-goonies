#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
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
	printTexts();
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
}

void Instructions::printTexts() {
	texts = new Text[52];
	texts[0].init(glm::vec2(float(160), float(100)), texProgram, 4, 0, "OBJECTIVES");
	texts[1].init(glm::vec2(float(272), float(100)), texProgram, 2, 0, "RESCUE YOUR SIX FRIENDS");
	texts[2].init(glm::vec2(float(272), float(100)), texProgram, 2, 0, "EACH FRIEND IS BEHIND ONE GREEN DOOR");
	texts[3].init(glm::vec2(float(272), float(100)), texProgram, 2, 0, "WHICH CAN BE OPENED WITH A KEY");

	texts[4].init(glm::vec2(float(272), float(100)), texProgram, 4, 0, "PLAYER");
	texts[5].init(glm::vec2(float(272), float(100)), texProgram, 2, 0, "YOU HAVE A LIMITED LIFE AND EXPERIENCE");
	texts[6].init(glm::vec2(float(272), float(100)), texProgram, 2, 0, "TO MOVE RIGHT PRESS THE RIGHT ARROW KEY");
	texts[7].init(glm::vec2(float(272), float(100)), texProgram, 2, 0, "TO MOVE LEFT PRESS THE LEFT ARROW KEY");
	texts[8].init(glm::vec2(float(272), float(100)), texProgram, 2, 0, "TO JUMP OR CLIMBING PRESS THE UP ARROW KEY");
	texts[9].init(glm::vec2(float(272), float(100)), texProgram, 2, 0, "TO GET DOWN PRESS THE DOWN ARROW KEY");

	texts[10].init(glm::vec2(float(272), float(100)), texProgram, 4, 0, "PLAYER");
	texts[11].init(glm::vec2(float(272), float(100)), texProgram, 2, 0, "TO PROTECT YOU FROM BEING HURT PRESS THE DOWN ARROY KEY");
	texts[12].init(glm::vec2(float(272), float(100)), texProgram, 2, 0, "TO FLOAT UP WHEN FALLING PRESS B");
	texts[13].init(glm::vec2(float(272), float(100)), texProgram, 2, 0, "TO MOVE BETWEEN LIANAS USE LEFT AND RIGHT ARROW KEYS");

	texts[14].init(glm::vec2(float(272), float(100)), texProgram, 4, 0, "ENEMIES");
	texts[15].init(glm::vec2(float(272), float(100)), texProgram, 2, 0, "THERE ARE TWO KIND OF ENEMIES");
	texts[16].init(glm::vec2(float(272), float(100)), texProgram, 2, 0, "- SKULLS");
	texts[17].init(glm::vec2(float(272), float(100)), texProgram, 2, 0, "- SKELETONS WHICH THROW BONES");
	texts[18].init(glm::vec2(float(272), float(100)), texProgram, 2, 0, "TO KILL THEM YOU MUST PRESS THE SPACE BAR");

	texts[19].init(glm::vec2(float(272), float(100)), texProgram, 4, 0, "OBSTACLES");
	texts[20].init(glm::vec2(float(272), float(100)), texProgram, 2, 0, "THE ARE 3 DIFFERENT KIND OF OBJECTS");
	texts[21].init(glm::vec2(float(272), float(100)), texProgram, 2, 0, "- WATER DROP");
	texts[22].init(glm::vec2(float(272), float(100)), texProgram, 2, 0, "- WATERFALLS");
	texts[23].init(glm::vec2(float(272), float(100)), texProgram, 2, 0, "- SPRINKLERS");
	texts[24].init(glm::vec2(float(272), float(100)), texProgram, 2, 0, "ALL OF THEM HURT YOU");

	texts[25].init(glm::vec2(float(272), float(100)), texProgram, 4, 0, "OBJECTS");
	texts[26].init(glm::vec2(float(272), float(100)), texProgram, 2, 0, "THE ARE 3 DIFFERENT KIND OF OBJECTS");
	texts[27].init(glm::vec2(float(272), float(100)), texProgram, 2, 0, "- KEY TO OPEN THE GREEN DOORS");
	texts[28].init(glm::vec2(float(272), float(100)), texProgram, 2, 0, "- BAG WHICH CAN HAVE POWERUPS OR EXPERIENCE");
	texts[29].init(glm::vec2(float(272), float(100)), texProgram, 2, 0, "- POTIONS TO EARN POINTS");

	texts[30].init(glm::vec2(float(272), float(100)), texProgram, 4, 0, "POWERUPS");
	texts[31].init(glm::vec2(float(272), float(100)), texProgram, 2, 0, "THE ARE 5 DIFFERENT KIND OF POWERUPS");
	texts[32].init(glm::vec2(float(272), float(100)), texProgram, 2, 0, "- HYPER SHOES. THE SPEED OF THE PLEAYER IS INCREASED");
	texts[33].init(glm::vec2(float(272), float(100)), texProgram, 2, 0, "- GRAY RAINCOAT. IT PROTECTS YOU FROM WATER DROPS");
	texts[34].init(glm::vec2(float(272), float(100)), texProgram, 2, 0, "- BLUE RAINCOAT. IT PROTECTS YOU FROM WATERFALLS");
	texts[35].init(glm::vec2(float(272), float(100)), texProgram, 2, 0, "- YELLOW SPELLBOOK. IT PROTECTS YOU FROM SKELETONS");
	texts[36].init(glm::vec2(float(272), float(100)), texProgram, 2, 0, "- BLUE SPELLBOOK. IT PROTECTS YOU FROM SKULLS");

	texts[37].init(glm::vec2(float(272), float(100)), texProgram, 4, 0, "LEVELS");
	texts[38].init(glm::vec2(float(272), float(100)), texProgram, 2, 0, "THERE ARE FIVE LEVELS");
	texts[39].init(glm::vec2(float(272), float(100)), texProgram, 2, 0, "TO MOVE BETWEEN THEM YOU MUST CROSS THE SKULL DOORS");
	texts[40].init(glm::vec2(float(272), float(100)), texProgram, 2, 0, "TO DO THAT PRESS UP ARROW KEY WHEN BEING IN FRONT OF THE DOOR");
	
	texts[41].init(glm::vec2(float(272), float(100)), texProgram, 4, 0, "SPECIAL KEYS");
	texts[42].init(glm::vec2(float(272), float(100)), texProgram, 2, 0, "TO CHANGE BETWEEN SCENES PRESS S AND THEN");
	texts[43].init(glm::vec2(float(272), float(100)), texProgram, 2, 0, "THE NUMBER OF THE SCENE AND SCREEN");
	texts[44].init(glm::vec2(float(272), float(100)), texProgram, 2, 0, "TO ACTIVATE GOD MODE PRESS G");
	texts[45].init(glm::vec2(float(272), float(100)), texProgram, 2, 0, "TO SAVE A FRIEND PESS N");
	texts[46].init(glm::vec2(float(272), float(100)), texProgram, 2, 0, "TO ACTIVATE HYPER SHOES PRESS 1");
	texts[47].init(glm::vec2(float(272), float(100)), texProgram, 2, 0, "TO ACTIVATE BLUE RAINCOA PRESS 2");
	texts[48].init(glm::vec2(float(272), float(100)), texProgram, 2, 0, "TO ACTIVATE GRAY RAINCOAT PRESS 3");
	texts[49].init(glm::vec2(float(272), float(100)), texProgram, 2, 0, "TO ACTIVATE YELLOW SPELLBOOK PRESS 4");
	texts[50].init(glm::vec2(float(272), float(100)), texProgram, 2, 0, "TO ACTIVATE BLUE SPELLBOOK PRESS 5");
	texts[51].init(glm::vec2(float(272), float(100)), texProgram, 2, 0, "TO ACTIVATE BLUE SPELLBOOK PRESS 5");
}


void Instructions::update(int deltaTime) {
	currentTime += deltaTime;

	texts->update(deltaTime);
}

void Instructions::render() {
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	texts->render();
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