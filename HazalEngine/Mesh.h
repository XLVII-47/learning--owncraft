#pragma once
#ifndef MESH_H
#define MESH_H

#include <glew.h> // holds all OpenGL type declarations
#include <glm.hpp>
#include "Shader.h"
#include <gtc/matrix_transform.hpp>
#include <string>
#include <vector>
#include "stb_image.h"
using namespace std;

static unsigned int TextureFromFile(const char *path)
{
	string filename(path);

	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}


class Mesh {
public:

	glm::vec3 transform;

	// mesh Data
	vector<glm::vec3>       *vertices;
	vector<unsigned int> *indices;
	vector<glm::vec2>      *textures;
	unsigned int VAO;

	// constructor
	Mesh(vector<glm::vec3> &vertices, vector<unsigned int> &indices, vector<glm::vec2> &textures,glm::vec3 transform)
	{	
		glDeleteTextures(1, &texID);
		texID = TextureFromFile("./atlas.jpg");
		this->vertices = &vertices;
		this->indices = &indices;
		this->textures = &textures;
		this -> transform = transform;
		// now that we have all the required data, set the vertex buffers and its attribute pointers.
		setupMesh();
	}

	// render the mesh
	void Draw()
	{	

		// draw mesh
		glBindVertexArray(VAO);
		glBindTexture(GL_TEXTURE_2D, texID);
		glDrawElements(GL_TRIANGLES, indices->size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	void clear() {
		glDeleteBuffers(1, &VerticesBuffer);
		glDeleteBuffers(1, &TexBuffer);
		glDeleteBuffers(1, &EBO);
		glDeleteVertexArrays(1, &VAO);
		glDeleteTextures(1,&texID);
	}

private:
	// render data 
	unsigned int VerticesBuffer, TexBuffer ,EBO, texID;

	// initializes all the buffer objects/arrays
	void setupMesh()
	{
		// create buffers/arrays
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VerticesBuffer);
		glGenBuffers(1, &TexBuffer);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices->size() * sizeof(unsigned int), indices->data(), GL_STATIC_DRAW);

		// load data into VerticesBuffer
		glBindBuffer(GL_ARRAY_BUFFER, VerticesBuffer);
		// A great thing about structs is that their memory layout is sequential for all its items.
		// The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
		// again translates to 3/2 floats which translates to a byte array.
		glBufferData(GL_ARRAY_BUFFER, vertices->size() * sizeof(glm::vec3), vertices->data(), GL_STATIC_DRAW);

		// set the vertex attribute pointers
		// vertex Positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);

		glBindBuffer(GL_ARRAY_BUFFER, TexBuffer);
		// A great thing about structs is that their memory layout is sequential for all its items.
		// The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
		// again translates to 3/2 floats which translates to a byte array.
		glBufferData(GL_ARRAY_BUFFER, vertices->size() * sizeof(glm::vec2), textures->data(), GL_STATIC_DRAW);

		// set the vertex attribute pointers
		// vertex Positions
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

		glBindVertexArray(0);

		
	}
};
#endif