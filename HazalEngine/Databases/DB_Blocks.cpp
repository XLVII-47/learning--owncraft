#include "DB_Blocks.h"


std::vector<Block*>  DB_Blocks::blockList;

void DB_Blocks::Start() {
	blockList.emplace_back(new Block());

	blockList.emplace_back(new Block("Dirt",true,false,glm::vec2(0,0)));

	blockList.emplace_back(new Block("Grass", true, false, glm::vec2(1, 0),glm::vec2(2,0),glm::vec2(0,0)));

	blockList.emplace_back(new Block("Stone", true, false, glm::vec2(0, 2)));

	blockList.emplace_back(new Block("Bedrock", true, false, glm::vec2(0, 1)));

}


Block* DB_Blocks::getBlockByName(std::string name) {
	for (int i = 0; i < blockList.size(); i++) {
		if (blockList[i]->name == name) {
			return blockList[i];
		}
	}
}