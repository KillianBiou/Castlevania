#pragma once
#include "Spawner.h"
#include "../Entity/Skeleton.h"

class SkeletonSpawner : public Spawner
{
private:
	float speedFactor;
	float targetDistToPlayer;
	float attackCooldown;

	Skeleton* currentInstance;

	sf::View* view;
public:
	SkeletonSpawner(sf::Vector2f pos, const int* level, const int xSize, float speedFactor, float targetDistToPlayer, float attackCooldown, EntityManager* entityManager, sf::View* view);

	void spawnEntity();
	void const update();
	void const onMobDeath();

};

