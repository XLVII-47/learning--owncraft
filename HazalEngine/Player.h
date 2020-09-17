#pragma once
#include "Physics/AABB.h"


class World;
class Camera;

class Player
{
public:
	Player(Camera& camera) noexcept;

	void input(const uint8_t* keyState, int xoff, int yoff);
	void update(float dt);

	void addForce(const glm::vec3& force) noexcept;

	void doCollisionTest(World& world, float dt);

	const glm::vec3 front();
	const glm::vec3 right();

	AABB box;
	glm::vec3 position;

private:

	

	void collisionTest(World& world,
		const glm::vec3& velocity,
		float dt);

	void keyBoardInput(const uint8_t* keyState);
	void mouseInput(int xoff, int yoff);


	Camera* mcamera;
	glm::vec3 m_velocity;

	

	bool m_isOnGround = false;
	bool m_isInLiquid = false;
	bool m_isFlying = false;
};