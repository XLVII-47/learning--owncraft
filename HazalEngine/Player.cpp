#pragma once
#include "Player.h"
#include "Camera.h"
#include "gtc/noise.hpp"
#include "Noise.h"
#include "World.h"
#include "SDL.h"


Player::Player(Camera& camera) noexcept
	: box({ 0.5, 1.5, 0.5 })
	, mcamera(&camera)
{
	position = glm::vec3(10.0, 50.0, 10.0);
	camera.hookPlayer(*this);
	
}

const glm::vec3 Player::front() {
	return mcamera->getFront();
}

const glm::vec3 Player::right() {
	return mcamera->getRight();
}

void Player::addForce(const glm::vec3& force) noexcept
{
	m_velocity += force;
}

void Player::update(float dt)
{
	position    += m_velocity * dt;
	box.update(position);
	
	m_velocity.x *= 0.95;
	m_velocity.z *= 0.95; ///@TODO Dampen the velocity using dt

	if (m_isFlying)
	{
		m_velocity.y *= 0.95;
	}
	
	if (position.y < -20.f) position = glm::vec3(50, 100, 50);
}

void Player::doCollisionTest(World& world, float dt)
{
	float gravity = 50.0f;

	if (!m_isFlying)
	{
		if (!m_isOnGround && !m_isInLiquid)
		{	
			m_velocity.y -= gravity * dt;
		}
		else if (m_isInLiquid)
		{
			m_velocity.y -= (gravity / 10) * dt;
		}
		m_isOnGround = false;
	}

	position.x += m_velocity.x * dt;
	collisionTest(world, {m_velocity.x, 0, 0}, dt);

	position.y += m_velocity.y * dt;
	collisionTest(world, {0, m_velocity.y, 0}, dt);

	position.z += m_velocity.z * dt;
	collisionTest(world, {0, 0, m_velocity.z}, dt);


}

void Player::collisionTest(World& world,
	const glm::vec3& velocity,
	float dt)
{
	
	const auto& dim = box.getDimensions();

	///@TODO Allow player
	///to enter 2 height hole
	for (int64_t x = position.x - dim.x ; x < position.x + dim.x    ; x++)
	for (int64_t y = position.y - dim.y ; y < position.y + 0.7      ; y++)
	for (int64_t z = position.z - dim.z ; z < position.z + dim.z    ; z++)
	{
		auto block = world.getBlock({x, y, z});

		

		if (block.isSolid)
		{
			if (velocity.x > 0)
			{
				position.x = x - dim.x;
			}
			if (velocity.x < 0)
			{
				position.x = x + dim.x + 1;
			}
			if (velocity.y > 0)
			{
				position.y = y - dim.y;
				m_velocity.y = 0;
			}
			if (velocity.y < 0)
			{
				position.y = y + dim.y + 1;
				m_isOnGround = true;
				m_velocity.y = 0;
			}
			if (velocity.z > 0)
			{
				position.z = z - dim.z;
			}
			if (velocity.z < 0)
			{
				position.z = z + dim.z + 1;
			}
		}
	}
	
}

void Player::keyBoardInput(const uint8_t* keyState)
{	
	glm::vec3 position{};
	if (keyState[SDL_SCANCODE_W]) {
		position.x += front().x;
		position.z += front().z;
	}
		
	if (keyState[SDL_SCANCODE_S]) {
		position.x -= front().x;
		position.z -= front().z;
	}
		
	if (keyState[SDL_SCANCODE_A]) {
		position.x -= right().x;
		position.z -= right().z;
	}
		
	if (keyState[SDL_SCANCODE_D]){
		position.x += right().x;
		position.z += right().z;
	}
	addForce(position);
}


void Player::mouseInput(int xoff, int yoff)
{
	mcamera->update(xoff, yoff);
}

void Player::input(const uint8_t* keyState, int xoff, int yoff)
{
	keyBoardInput(keyState);
	mouseInput(xoff,yoff);

}