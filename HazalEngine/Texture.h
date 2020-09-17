#pragma once
#include <unordered_map>


class Texture {
public:
	std::unordered_map<std::string, unsigned int> textures;

	void addTexture(const char* path, std::string name);

	void bindTexture(std::string);
	void unbindTexture();

private:
	unsigned int loadFromFile(const char * path);


};