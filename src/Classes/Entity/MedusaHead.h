#pragma once
#include "Monster.h"

class MedusaHead: public Monster
{
public:
	MedusaHead(std::string name, sf::Vector2f pos, int frameDelay, const int* currentLevel, const int levelXSize, float speedFactor, float jumpFactor, EntityManager* entityManager);
};

