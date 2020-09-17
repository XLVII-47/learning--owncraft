#pragma once
#include "glm.hpp"
#ifndef BLOCK_CUBE_H
#define BLOCK_CUBE_H
#include "Types/Block.h"


class Chunk;


class Blockcube
{
public:
	enum FaceType
	{
		TOP, BOTTOM, LEFT, RIGHT, FRONT, BACK
	};

	Chunk* owner;
	glm::vec3 position;
	Block *block;

	Blockcube(Chunk* own, glm::vec3 pos, Block* block);

	void GenerateCube();

	void GenerateCubeSide(FaceType face);

	glm::vec2 getTexture(FaceType face);
private:

};


#endif // !BLOCK_CUBE_H

