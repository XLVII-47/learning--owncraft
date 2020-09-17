#pragma once
#include <glew.h> // holds all OpenGL type declarations
#include <glm.hpp>
#include "Shader.h"
#include <gtc/matrix_transform.hpp>
#include <string>
#include <vector>
#include <iostream>
class DrawLine {
public:
	glm::vec3 pos1, pos2;
	DrawLine(glm::vec3 pos1,glm::vec3 pos2) {
		this->pos1 = pos1;
		this->pos2 = pos2;

		setup();
	}

	// render the mesh
	void Draw()
	{
		
		// draw mesh
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
	}
private:
	// render data 
	unsigned int VAO, VerticesBuffer, TexBuffer, EBO, texID;

	// initializes all the buffer objects/arrays
	void setup()
	{
		float vertices[] = {
		 pos1.x,  pos1.y, pos1.z,  // top right
		 pos1.x, pos1.y-0.05f, pos1.z,  // bottom right
		pos2.x, pos2.y, pos2.z // bottom left
		};
	
		glGenVertexArrays(1, &VAO);



		glBindVertexArray(VAO);

	
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