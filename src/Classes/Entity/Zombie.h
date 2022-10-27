#pragma once
#include "Monster.h"

// Class representing a zombie
class Zombie : public Monster
{
private:
	bool doubleSpeed;

public:
	Zombie(sf::Vector2f pos, float speedFactor, MoveDirection moveDirection, EntityManager* entityManager, Spawner* spawner);
	void const update();
};

