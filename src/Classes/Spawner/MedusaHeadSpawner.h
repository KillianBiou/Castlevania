#pragma once
#include <stdlib.h>
#include <time.h> 
#include "Spawner.h"
#include "../Entity/MedusaHead.h"

class MedusaHeadSpawner: public Spawner
{
private:
	float speedFactor;
	float amplitude;
	float frequency;
	MedusaHead* currentInstance;
	sf::View* view;


public:
	MedusaHeadSpawner(sf::Vector2f pos, const int* level, const int xSize, float speedFactor, float amplitude, float frequency, EntityManager* entityManager, sf::View* view);

	void spawnEntity();
	void const update();
	void const onMobDeath();
	void const drawEntity(sf::RenderWindow* renderWindow);
};

