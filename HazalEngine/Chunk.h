#pragma once
#include "glm.hpp"
#include <vector>
#include "Mesh.h"

#include "Types/Block.h"

class World;


class Chunk
{
public:
	enum FaceType
	{
		TOP, BOTTOM, LEFT, RIGHT, FRONT, BACK
	};


	std::vector< std::vector<std::vector<Block> > > map;


	World *world;
	static int chunkSize;

	glm::vec3 position;

	std::vector<glm::vec3> vertices;
	std::vector<unsigned int> indices;
	std::vector<glm::vec2> texturecoord;

	Mesh * ChunkMesh;

	
	void End();

	void GenerateChunk();
	void GenerateVirtualMap(const std::vector<int>& heightMap);
	void GenerateBlocksMap();
	bool BlockExistAtPos(glm::vec3 pos);
	Block* getBlockExistAtPos(glm::vec3 pos);
	void MeshUpdate();
	
	void GenerateCube(glm::vec3 position, Block * block);
	void GenerateCubeSide(FaceType face, glm::vec3 position,Block * block);
	//void createSmoothTerrain(const std::vector<int>& heightMap);

	Chunk(World* owner, glm::vec3 position, const std::vector<int>& heightMap);
	//Chunk(World* owner, glm::vec3 position);
	~Chunk();

private:

};
