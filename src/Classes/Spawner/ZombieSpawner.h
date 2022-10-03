#pragma once
#include "Spawner.h"
#include "../Entity/Zombie.h"

class ZombieSpawner: public Spawner
{
private:
	float speedFactor;
	Zombie* currentInstance;

	float distToSpawn;

	sf::View* view;
public:
	ZombieSpawner(sf::Vector2f pos, const int* level, const int xSize, float speedFactor, float distToSpawn, EntityManager* entityManager, sf::View* view);

	void spawnEntity();
	void const update();
	void const onMobDeath();

};

