#pragma once
#include <SFML/Graphics.hpp>
#include "../Manager/EntityManager.h"

// Abstact class representing a spawner
class Spawner: public sf::Transformable
{
protected:
	// A pointer toward the current level
	const int* level;
	const int xSize;

	sf::Clock respawnClock;
	float timeForRespawn;

	float minX;
	float maxX;

	bool canSpawn = true;

	EntityManager* entityManager;

public:
	Spawner(sf::Vector2f pos, const int* level, int xSize, EntityManager* entityManager);
	// A virtual fonction for the update loop
	virtual void const update() = 0;
	// A virtual fonction triggered when the instanciated monster die
	virtual void const onMobDeath() = 0;
	// Deactivate / Activate the spawner
	void const switchSpawn();
};

