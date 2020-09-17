#include "Blockcube.h"
#include "Chunk.h"
/*
Blockcube::Blockcube(Chunk* own, glm::vec3 pos, Block* block) {
	owner = own;
	position = pos;
	this->block = block;

	GenerateCube();
}

inline void Blockcube::GenerateCube() {
	if(owner->BlockExistAtPos(glm::vec3(position.x,position.y,position.z+1))==false)
		GenerateCubeSide(FRONT);
	if (owner->BlockExistAtPos(glm::vec3(position.x, position.y, position.z-1)) == false)
		GenerateCubeSide(BACK);
	if (owner->BlockExistAtPos(glm::vec3(position.x, position.y+1, position.z)) == false)
		GenerateCubeSide(TOP);
	if (owner->BlockExistAtPos(glm::vec3(position.x, position.y - 1, position.z)) == false && position.y - 1 >= 0)
		GenerateCubeSide(BOTTOM);
	if (owner->BlockExistAtPos(glm::vec3(position.x-1, position.y, position.z)) == false)
		GenerateCubeSide(RIGHT);
	if (owner->BlockExistAtPos(glm::vec3(position.x+1, position.y, position.z)) == false)
		GenerateCubeSide(LEFT);
}




inline void Blockcube::GenerateCubeSide(FaceType face) {
	owner->indices.push_back(0 + owner->vertices.size());
	owner->indices.push_back(1 + owner->vertices.size());
	owner->indices.push_back(2 + owner->vertices.size());


	owner->indices.push_back(0 + owner->vertices.size());
	owner->indices.push_back(2 + owner->vertices.size());
	owner->indices.push_back(3 + owner->vertices.size());
	
	float textureOffset = 1.f / 4.f;
	//printf("%d %d\n", block.texture.x, block.texture.y);

	glm::vec2 texturePos(2,0);
	
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
	
		owner->texturecoord.push_back(glm::vec2((textureOffset * texturePos.x)+textureOffset,textureOffset*texturePos.y));
		owner->texturecoord.push_back(glm::vec2((textureOffset * texturePos.x) + textureOffset, (textureOffset*texturePos.y)+textureOffset));
		owner->texturecoord.push_back(glm::vec2((textureOffset * texturePos.x) , (textureOffset*texturePos.y) + textureOffset));
		owner->texturecoord.push_back(glm::vec2((textureOffset * texturePos.x), textureOffset*texturePos.y));
		

		owner->texturecoord.push_back(glm::vec2(1.0, 1.0));
		owner->texturecoord.push_back(glm::vec2(0.0, 1.0));
		owner->texturecoord.push_back(glm::vec2(0.0, 0.0));
		owner->texturecoord.push_back(glm::vec2(1.0, 0.0));
		

		
	
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
		owner->vertices.push_back(V0 + position);
		owner->vertices.push_back(V1 + position);
		owner->vertices.push_back(V2 + position);
		owner->vertices.push_back(V3 + position);
		break;
	case BACK:
		owner->vertices.push_back(V4 + position);
		owner->vertices.push_back(V5 + position);
		owner->vertices.push_back(V6 + position);
		owner->vertices.push_back(V7 + position);
		break;
	case TOP:
		owner->vertices.push_back(V1 + position);
		owner->vertices.push_back(V6 + position);
		owner->vertices.push_back(V5 + position);
		owner->vertices.push_back(V2 + position);
		break;
	case BOTTOM:
		owner->vertices.push_back(V7 + position);
		owner->vertices.push_back(V0 + position);
		owner->vertices.push_back(V3 + position);
		owner->vertices.push_back(V4 + position);
		break;
	case RIGHT:
		owner->vertices.push_back(V3 + position);
		owner->vertices.push_back(V2 + position);
		owner->vertices.push_back(V5 + position);
		owner->vertices.push_back(V4 + position);
		break;
	case LEFT:
		owner->vertices.push_back(V7 + position);
		owner->vertices.push_back(V6 + position);
		owner->vertices.push_back(V1 + position);
		owner->vertices.push_back(V0 + position);
		break;
	default:
		break;
	}
}

*/