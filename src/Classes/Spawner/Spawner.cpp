#include "Spawner.h"

Spawner::Spawner(sf::Vector2f pos, const int* level, int xSize, EntityManager* entityManager) : level(level), xSize(xSize), entityManager(entityManager) {
	this->setPosition(pos);
	this->nbInstaciatedMonster = 0;
	this->respawnClock = sf::Clock();
}