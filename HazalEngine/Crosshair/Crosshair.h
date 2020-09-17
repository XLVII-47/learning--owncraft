#pragma once

#include <glew.h> // holds all OpenGL type declarations
#include <glm.hpp>
#include "Shader.h"
#include <gtc/matrix_transform.hpp>
#include <string>
#include <vector>
#include <iostream>
#include "stb_image.h"
using namespace std;

class Crosshair {
public:
	Crosshair() {
		setup();
	}

	// render the mesh
	void Draw()
	{

		// draw mesh
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

private:
	// render data 
	unsigned int VAO, VerticesBuffer, TexBuffer, EBO, texID;

	// initializes all the buffer objects/arrays
	void setup()
	{
		float vertices[] = {
		 0.005f,  0.005f, 0.0f,  // top right
		 0.005f, -0.005f, 0.0f,  // bottom right
		-0.005f, -0.005f, 0.0f,  // bottom left
		-0.005f,  0.005f, 0.0f   // top left 
		};
		unsigned int indices[] = {  // note that we start from 0!
			0, 1, 3,   // first triangle
			1, 2, 3    // second triangle
		};
		// create buffers/arrays
		glGenVertexArrays(1, &VAO);



		glBindVertexArray(VAO);

		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glGenBuffers(1, &VerticesBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, VerticesBuffer);
		// A great thing about structs is that their memory layout is sequential for all its items.
		// The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
		// again translates to 3/2 floats which translates to a byte array.
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// set the vertex attribute pointers
		// vertex Positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);


		glBindVertexArray(0);


	}
};
