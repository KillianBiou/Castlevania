#include "Spawner.h"

Spawner::Spawner(sf::Vector2f pos, const int* level, int xSize, EntityManager* entityManager) : level(level), xSize(xSize), entityManager(entityManager) {
	this->setPosition(pos);
	this->respawnClock = sf::Clock();
}

void const Spawner::switchSpawn() {
	if (!this->canSpawn) {
		this->canSpawn = true;
	}
	else {
		this->onMobDeath();
		this->canSpawn = false;
	}
}