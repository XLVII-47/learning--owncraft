#include "Block.h"

Block::Block(std::string _name, bool _solid, bool _transparent, glm::vec2 _texture) {
	name = _name;
	isSolid = _solid;
	isTransparent = _transparent;
	texture = _texture;

	multiTexture = false;
}

Block::Block(std::string _name, bool _solid, bool _transparent, glm::vec2 _textureUp, glm::vec2 _textureSide, glm::vec2 _textureBot) {
	name = _name;
	isSolid = _solid;
	isTransparent = _transparent;
	textureUp = _textureUp;
	textureSide = _textureSide;
	textureBot = _textureBot;

	multiTexture = true;
}

Block::Block() {
	name = "Air";
	isSolid = false;
	isTransparent = true;
}
/*
Block::Block(const Block& obj) {
	this->isSolid = obj.isSolid;
	this->isTransparent = obj.isTransparent;
	this->multiTexture = obj.multiTexture;
	this->name = obj.name;
	this->texture = obj.texture;
	this->textureBot = obj.textureBot;
	this->textureSide = obj.textureSide;
	this->textureUp = obj.textureUp;
}
*/