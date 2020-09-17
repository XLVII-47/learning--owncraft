#include "Chunk.h"
#include "World.h"
#include "Databases/DB_Blocks.h"


int Chunk::chunkSize = World::chunkSize;


void Chunk::End() {


	//std::cout << vertices.size() << std::endl;
	GenerateBlocksMap();
	GenerateChunk();
}

void Chunk::GenerateChunk() {
	
	ChunkMesh = new Mesh(vertices, indices, texturecoord,position);
}
/*
Chunk::Chunk(World *world,glm::vec3 position) {
	this->world = world;

	map = new int**[chunkSize];
	for (int i = 0; i < chunkSize; ++i) {
		map[i] = new int*[chunkSize];
		for (int j = 0; j < chunkSize; ++j)
			map[i][j] = new int[chunkSize];
	}

	this->position = position;

	GenerateVirtualMap();
};
*/
Chunk::Chunk(World *world, glm::vec3 position, const std::vector<int>& heightMap) {
	this->world = world;

	
	for (int i = 0; i < chunkSize; ++i) {
		map.push_back(std::vector<std::vector<Block>>());
		for (int j = 0; j < chunkSize; ++j) {
			map[i].push_back(std::vector<Block>());
		}
	}


	this->position = position;

	GenerateVirtualMap(heightMap);
};

Chunk::~Chunk() {
	
};



void Chunk::GenerateVirtualMap(const std::vector<int>& heightMap) {
	
	
		
		for (int x = 0; x < chunkSize; x++) {
			for (int z = 0; z < chunkSize; z++) {
				for (int y = 0; y < heightMap[x*chunkSize + z] ; y++) {

					if (y < heightMap[x*chunkSize + z] - 4) {
						map[x][z].push_back(*DB_Blocks::getBlockByName("Stone"));
					}
					else if (y == heightMap[x*chunkSize + z] - 1)
						map[x][z].push_back(*DB_Blocks::getBlockByName("Grass"));
					//printf("%d\n", map[x][y][z].multiTexture);
					else {
						map[x][z].push_back(*DB_Blocks::getBlockByName("Dirt"));
					}
				}
			}
		}
	/*
		for (int x = 0; x < chunkSize; x++) {
			for (int z = 0; z < chunkSize; z++) {
				for (int y = 0; y < map[x][z].size(); y++) {
					printf("%d-%d-%d %s\n" ,x,z,y,map[x][z][y].name);
				}
			}
		}

		*/
}

void Chunk::GenerateBlocksMap() {
	for (int x = 0; x < chunkSize; x++) {
		for (int z = 0; z < chunkSize; z++) {
			for (int y = 0; y < map[x][z].size(); y++) {
				if (map[x][z][y].name != "Air") {
					GenerateCube(glm::vec3(x, y, z) + position, &map[x][z][y]);
				}
			}
		}
	}

}

bool Chunk::BlockExistAtPos(glm::vec3 pos) {
	int x = (int)pos.x;
	int y = (int)pos.y;
	int z = (int)pos.z;

	x -= position.x;

	z -= position.z;
	
	if (y < 0) return false;
	if (x < 0 || x >= chunkSize ||
		z < 0 || z >= chunkSize
		)
	{

		Chunk* neighbour = world->getChunkAtPos(pos);

		if (neighbour != NULL) {
			//printf("%f %f %f\n", neighbour->position.x, neighbour->position.y, neighbour->position.z);
			return neighbour->BlockExistAtPos(pos);
		}
		else {
			return false;
		}

	}
	else if (y >= map[x][z].size()) {
		return false;
	}
	else if (map[x][z][y].isTransparent) {
		//puts(map[x][z][y].name.c_str());
		return false;
	}
	else
		return true;
}


Block* Chunk::getBlockExistAtPos(glm::vec3 pos) {
	int x = std::round(pos.x);
	int y = std::round(pos.y);
	int z = std::round(pos.z);

	x -= position.x;
	
	z -= position.z;
	
	if (y < 0) return nullptr;
	if (x < 0 || x >= chunkSize ||
		z < 0 || z >= chunkSize
		)
	{
		return nullptr;
	}
	else if (y >= map[x][z].size()) {
		return nullptr;
	}
	else if (map[x][z][y].isTransparent)
		return nullptr;

	else
		return &map[x][z][y];
}

void Chunk::MeshUpdate() {
	ChunkMesh->clear();
	vertices.clear();
	indices.clear();
	texturecoord.clear();
	delete this-> ChunkMesh;
	
}



void Chunk::GenerateCube(glm::vec3 position,Block * block) {
	if (BlockExistAtPos(glm::vec3(position.x, position.y, position.z + 1)) == false)
		GenerateCubeSide(FRONT, position, block);
	if (BlockExistAtPos(glm::vec3(position.x, position.y, position.z - 1)) == false)
		GenerateCubeSide(BACK, position, block);
	if (BlockExistAtPos(glm::vec3(position.x, position.y + 1, position.z)) == false)
		GenerateCubeSide(TOP, position, block);
	if (BlockExistAtPos(glm::vec3(position.x, position.y - 1, position.z)) == false && position.y - 1 >= 0)
		GenerateCubeSide(BOTTOM, position, block);
	if (BlockExistAtPos(glm::vec3(position.x - 1, position.y, position.z)) == false)
		GenerateCubeSide(RIGHT, position, block);
	if (BlockExistAtPos(glm::vec3(position.x + 1, position.y, position.z)) == false)
		GenerateCubeSide(LEFT, position, block);
}




void Chunk::GenerateCubeSide(FaceType face, glm::vec3 position, Block * block) {
	indices.push_back(0 + vertices.size());
	indices.push_back(1 + vertices.size());
	indices.push_back(2 + vertices.size());


	indices.push_back(0 + vertices.size());
	indices.push_back(2 + vertices.size());
	indices.push_back(3 + vertices.size());

	float textureOffset = 1.f / 4.f;
	//printf("%d %d\n", block.texture.x, block.texture.y);

	glm::vec2 texturePos(2, 0);

	//printf("%d\n", block->multiTexture);
	if (block->multiTexture) {
		if (face == TOP) {
			texturePos = block->textureUp;
		}
		else if (face == BOTTOM) {
			texturePos = block->textureBot;
		}
		else
			texturePos = block->textureSide;
	}
	else
		texturePos = block->texture;

	texturecoord.push_back(glm::vec2((textureOffset * texturePos.x) + textureOffset, textureOffset*texturePos.y));
	texturecoord.push_back(glm::vec2((textureOffset * texturePos.x) + textureOffset, (textureOffset*texturePos.y) + textureOffset));
	texturecoord.push_back(glm::vec2((textureOffset * texturePos.x), (textureOffset*texturePos.y) + textureOffset));
	texturecoord.push_back(glm::vec2((textureOffset * texturePos.x), textureOffset*texturePos.y));

	/*
		owner->texturecoord.push_back(glm::vec2(1.0, 1.0));
		owner->texturecoord.push_back(glm::vec2(0.0, 1.0));
		owner->texturecoord.push_back(glm::vec2(0.0, 0.0));
		owner->texturecoord.push_back(glm::vec2(1.0, 0.0));

		*/


	glm::vec3 V0 = glm::vec3(0.5f, -0.5f, 0.5f);
	glm::vec3 V1 = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::vec3 V2 = glm::vec3(-0.5f, 0.5f, 0.5f);
	glm::vec3 V3 = glm::vec3(-0.5f, -0.5f, 0.5f);

	glm::vec3 V4 = glm::vec3(-0.5f, -0.5f, -0.5f);
	glm::vec3 V5 = glm::vec3(-0.5f, 0.5f, -0.5f);
	glm::vec3 V6 = glm::vec3(0.5f, 0.5f, -0.5f);
	glm::vec3 V7 = glm::vec3(0.5f, -0.5f, -0.5f);

	switch (face)
	{
	case FRONT:
		vertices.push_back(V0 + position);
		vertices.push_back(V1 + position);
		vertices.push_back(V2 + position);
		vertices.push_back(V3 + position);
		break;
	case BACK:
		vertices.push_back(V4 + position);
		vertices.push_back(V5 + position);
		vertices.push_back(V6 + position);
		vertices.push_back(V7 + position);
		break;
	case TOP:
		vertices.push_back(V1 + position);
		vertices.push_back(V6 + position);
		vertices.push_back(V5 + position);
		vertices.push_back(V2 + position);
		break;
	case BOTTOM:
		vertices.push_back(V7 + position);
		vertices.push_back(V0 + position);
		vertices.push_back(V3 + position);
		vertices.push_back(V4 + position);
		break;
	case RIGHT:
		vertices.push_back(V3 + position);
		vertices.push_back(V2 + position);
		vertices.push_back(V5 + position);
		vertices.push_back(V4 + position);
		break;
	case LEFT:
		vertices.push_back(V7 + position);
		vertices.push_back(V6 + position);
		vertices.push_back(V1 + position);
		vertices.push_back(V0 + position);
		break;
	default:
		break;
	}
}