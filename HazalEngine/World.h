#pragma once
#include <unordered_map>
#include <glm.hpp>
#include <gtx/hash.hpp>
#include "Chunk.h"
class World {
public:
	static int worldSize;
	static int chunkSize;
	
	std::unordered_map<glm::vec3, Chunk*> chunkList;
	
	World();

	void createChunk(glm::vec3 pos, const std::vector<int>& heightMap);
	void GenerateColumn(int x, int z);
	Chunk* getChunkAtPos(glm::vec3 position);
	std::vector<int> createChunkHeightMap(glm::vec2 position);

	Block getBlock(glm::vec3 pos);
	bool chunkUpdate(glm::vec3 pos);

	void start();
	void end();
};