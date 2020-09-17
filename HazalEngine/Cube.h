#pragma once
#include "glew.h"
#include "glm.hpp"
#include <vector>
#include "Mesh.h"
#include "Player.h"



class Cube
{
public:
	enum FaceType
	{
		TOP, BOTTOM, LEFT, RIGHT, FRONT, BACK
	};

	std::vector<glm::vec3> vertices;
	std::vector<unsigned int> indices;
	
	
	Cube(){
		Start();
	};
	~Cube() {};
	void Start() {
		GenerateCube();
		setupMesh();
	}
	void Draw()
	{
		// draw mesh
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
	void GenerateCube() {
		//CubeMesh = new Mesh();
		GenerateCubeSide(FRONT);
		GenerateCubeSide(BACK);
		GenerateCubeSide(TOP);
		GenerateCubeSide(BOTTOM);
		GenerateCubeSide(RIGHT);
		GenerateCubeSide(LEFT);	
	}

	void GenerateCubeSide(FaceType side) {

		indices.push_back(0 + vertices.size() );
		indices.push_back(1 + vertices.size() );
		indices.push_back(2 + vertices.size() );

		 
		indices.push_back(0 + vertices.size() );
		indices.push_back(2 + vertices.size() );
		indices.push_back(3 + vertices.size() );

		glm::vec3 V0 = glm::vec3(0.5f, -0.5f, 0.5f);
		glm::vec3 V1 = glm::vec3(0.5f, 1.5f, 0.5f);
		glm::vec3 V2 = glm::vec3(-0.5f, 1.5f, 0.5f);
		glm::vec3 V3 = glm::vec3(-0.5f, -0.5f, 0.5f);

		glm::vec3 V4 = glm::vec3(-0.5f, -0.5f, -0.5f);
		glm::vec3 V5 = glm::vec3(-0.5f, 1.5f, -0.5f);
		glm::vec3 V6 = glm::vec3(0.5f, 1.5f, -0.5f);
		glm::vec3 V7 = glm::vec3(0.5f, -0.5f, -0.5f);


		switch (side)
		{
		case FRONT:
			vertices.push_back(V0);
			vertices.push_back(V1);
			vertices.push_back(V2);
			vertices.push_back(V3);
			break;
		case BACK:
			vertices.push_back(V4);
			vertices.push_back(V5);
			vertices.push_back(V6);
			vertices.push_back(V7);
			break;
		case TOP:
			vertices.push_back(V1);
			vertices.push_back(V6);
			vertices.push_back(V5);
			vertices.push_back(V2);
			break;
		case BOTTOM:
			vertices.push_back(V7);
			vertices.push_back(V0);
			vertices.push_back(V3);
			vertices.push_back(V4);
			break;
		case RIGHT:
			vertices.push_back(V3);
			vertices.push_back(V2);
			vertices.push_back(V5);
			vertices.push_back(V4);
			break;
		case LEFT:
			vertices.push_back(V7);
			vertices.push_back(V6);
			vertices.push_back(V1);
			vertices.push_back(V0);
			break;
		default:
			break;
		}
	}
private:
	unsigned int VAO,VerticesBuffer, EBO;

	// initializes all the buffer objects/arrays
	void setupMesh()
	{
		// create buffers/arrays
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VerticesBuffer);
		
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

		// load data into VerticesBuffer
		glBindBuffer(GL_ARRAY_BUFFER, VerticesBuffer);
		// A great thing about structs is that their memory layout is sequential for all its items.
		// The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
		// again translates to 3/2 floats which translates to a byte array.
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

		// set the vertex attribute pointers
		// vertex Positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

		glBindVertexArray(0);


	}
};
