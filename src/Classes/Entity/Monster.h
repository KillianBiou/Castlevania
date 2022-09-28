#pragma once
#include "Entity.h"

class Monster: public Entity
{

public:
	Monster(std::string texturePath, std::string name, int frameDelay, const int* currentLevel, const int levelXSize, float speedFactor, float jumpFactor, EntityManager* entityManager);
	void const drawChild(sf::RenderWindow* renderWindow);

	void const attack(bool advance);
	void const taskDeletion();

	~Monster();
};

