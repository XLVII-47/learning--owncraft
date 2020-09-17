#pragma once
#include <vector>
#include "../Types/Block.h"

class DB_Blocks {
public:
	static std::vector<Block*> blockList;

	static void Start();

	static Block* getBlockByName(std::string name);
};