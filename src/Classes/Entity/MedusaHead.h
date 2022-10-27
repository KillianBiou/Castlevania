#pragma once
#include "Monster.h"

// Class that represent a medusa head
class MedusaHead: public Monster
{
private:
	sf::Clock sinClock;
	float amplitude;
	float frequency;

public:
	MedusaHead(std::string name, sf::Vector2f pos, float speedFactor, float amplitude, float frequency, EntityManager* entityManager, Spawner* spawner);
	const void update();

};

