#pragma once
#include "Monster.h"

class MedusaHead: public Monster
{
private:
	sf::Clock sinClock;
	float amplitude;
	float frequency;

public:
	MedusaHead(std::string name, sf::Vector2f pos, const int* currentLevel, const int levelXSize, float speedFactor, float amplitude, float frequency, EntityManager* entityManager, Spawner* spawner);
	void update();

};

