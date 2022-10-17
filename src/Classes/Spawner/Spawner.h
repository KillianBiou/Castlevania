#pragma once
#include <SFML/Graphics.hpp>
#include "../Manager/EntityManager.h"

class Spawner: public sf::Transformable
{
protected:
	int nbInstaciatedMonster;
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
	virtual void const update() = 0;
	virtual void const onMobDeath() = 0;
	void const switchSpawn();
};

