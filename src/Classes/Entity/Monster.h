#pragma once
#include "Entity.h"
#include "../Manager/Animator.h"

class Spawner;

class Monster: public Entity
{
protected:
	Spawner* spawner;

public:
	Monster(std::string texturePath, sf::Vector2f pos, int sizeX, int sizeY, std::string name, int frameDelay, const int* currentLevel, const int levelXSize, float speedFactor, float jumpFactor, EntityManager* entityManager, Spawner* spawner);
	void const drawChild(sf::RenderWindow* renderWindow);

	void const attack(bool advance);
	void const taskDeletion();

	~Monster();
};

