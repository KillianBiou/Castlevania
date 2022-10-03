#pragma once
#include "Monster.h"

class Zombie : public Monster
{
private:
	bool doubleSpeed;

public:
	Zombie(sf::Vector2f pos, const int* currentLevel, const int levelXSize, float speedFactor, MoveDirection moveDirection, EntityManager* entityManager, Spawner* spawner);
	void update();
};

