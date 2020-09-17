#pragma once
#include <string>
#include "glm.hpp"

class Block {
public:
	std::string name;

	bool isSolid;
	bool isTransparent;

	//Fullblock
	glm::vec2 texture;

	//GrassType
	glm::vec2 textureUp;
	glm::vec2 textureSide;
	glm::vec2 textureBot;

	bool multiTexture;

	Block(std::string _name, bool _solid, bool _transparent, glm::vec2 _texture);

	Block(std::string _name, bool _solid, bool _transparent, glm::vec2 _textureUp, glm::vec2 _textureSide,glm::vec2 _textureBot);
	
	Block();

	//Block(const Block& obj);
};