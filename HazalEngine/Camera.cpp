#include "Camera.h"
#include <cmath>
#include <iostream>
#include <gtc/matrix_transform.hpp>
#include "Player.h"


Camera::Camera() noexcept
{

	up = glm::vec3(0.0f, 1.0f, 0.0f);
	yaw = -90.f;
	pitch = 0.0f;
	front = glm::vec3(0.0f, 0.0f, -1.0f);
	worldUp = up;
	
}



void Camera::update(float xoffset , float yoffset) noexcept
{
	position = player->position + glm::vec3(2,-1,2);
	yaw += xoffset;
	pitch += yoffset;
	if (pitch > 89.)pitch = 89.f;
	else if (pitch < -89.f)pitch = -89.f;
	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	this->front = glm::normalize(front);
	// also re-calculate the Right and Up vector
	right = glm::normalize(glm::cross(this->front, worldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	up = glm::normalize(glm::cross(right, this->front));
}

void Camera::hookPlayer(Player& player) noexcept
{
	this->player = &player;
	update();
}

const glm::mat4 Camera::getViewMatrix() noexcept
{
	return glm::lookAt(position, position + front, up);
}

const glm::mat4 Camera::getProjMatrix() noexcept
{
	return glm::perspective(glm::radians(90.f),
		(float)1200 / (float)600,
		0.1f,
		1000.0f);
}

const glm::vec3 Camera::getFront() noexcept
{
	return front;
}

const glm::vec3 Camera::getRight() noexcept{
	return right;
}