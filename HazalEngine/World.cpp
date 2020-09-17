#include "World.h"
#include "gtc/noise.hpp"
#include "Noise.h"
#include "Databases/DB_Blocks.h"
int World::worldSize = 20;
int World::chunkSize = 16;

void World::createChunk(glm::vec3 pos, const std::vector<int>& heightMap) {
	Chunk * newChunk = new Chunk(this,pos,heightMap);
	//printf("%f %f %f\n", pos.x, pos.y, pos.z);
	chunkList.insert({ pos,newChunk });
}

World::World() {
	start();
	end();
}

Chunk*  World::getChunkAtPos(glm::vec3 position) {

	float x = position.x;
	float z = position.z;

	x /= chunkSize;
	z /= chunkSize;
	
	x = floorf(x);
	z = floorf(z);

	x *= chunkSize;
	z *= chunkSize;

	auto itr = chunkList.find(glm::vec3(x,0,z));

	if (itr == chunkList.end())
		return NULL;
	else {
		//printf("%f %f %f\n", itr->second->position.x, itr->second->position.y, itr->second->position.z);
		return itr->second;
	}
}

void World::start() {
	for (int z = 0; z < worldSize*chunkSize; z+= chunkSize) {
		for (int x = 0; x < worldSize*chunkSize; x+= chunkSize) {
			GenerateColumn(x, z);
		}
	}
}

void World::end() {
	for (auto itr = chunkList.begin(); itr != chunkList.end(); ++itr) {
		itr->second->End();
	}
}

void World::GenerateColumn(int x, int z) {
	
	std::vector<int> heightMap = createChunkHeightMap(glm::vec2(x, z));
	
	createChunk(glm::vec3(x, 0, z), heightMap);

}

std::vector<int> World::createChunkHeightMap(glm::vec2 position) {
	//std::cout << position.x << " "<< position.y<<std::endl;

	std::vector<int> heightMap(chunkSize*chunkSize);

	for (int x = 0; x < chunkSize; x++) {
		for (int z = 0; z < chunkSize; z++) {
			
			int voxelx = x + position.x;
			int voxelz = z + position.y;//position.z
			//std::cout << voxelx << "==" << voxelz << std::endl;
			float value = glm::perlin(glm::vec2(voxelx / 64., voxelz / 64.));

			value = (value + 1.0) / 2.0;
			value *= Noise::Lerp(0.0,70.0,value);
			heightMap[x*chunkSize + z] = (int)value;

		}
	}
	
	return heightMap;
}

bool World::chunkUpdate(glm::vec3 pos) {
	Chunk * chunk = getChunkAtPos(pos);
	
	if (chunk != nullptr) {
		
		Block * blk = chunk->getBlockExistAtPos(pos);
		
		if (blk != nullptr) {
			
			chunk->MeshUpdate();
			*blk = *DB_Blocks::getBlockByName("Air");
			chunk->End();
			
			return true;
		}
	}
	return false;
}

Block World::getBlock(glm::vec3 pos) {
	Chunk * chunk = getChunkAtPos(pos);

	if (chunk != nullptr) {

		Block * blk = chunk->getBlockExistAtPos(pos);

		if (blk != nullptr) {

			return *blk;
		}
	}
	return *DB_Blocks::getBlockByName("Air");;
}