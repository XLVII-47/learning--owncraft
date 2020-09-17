#pragma once
#include "glm.hpp"

class Player;

class Camera
{
public:
	Camera() noexcept;


	void update(float xoffset=0.0f, float yoffset=0.0f)  noexcept;
	void hookPlayer( Player& player)  noexcept ;


	const glm::mat4 getViewMatrix() noexcept;
	const glm::mat4 getProjMatrix() noexcept;
	const glm::vec3 getFront() noexcept;
	const glm::vec3 getRight() noexcept;
private:
	

	Player* player;
	
	glm::vec3 position;

	float yaw;
	float pitch;


	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;
};
