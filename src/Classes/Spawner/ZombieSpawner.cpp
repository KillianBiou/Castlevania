#include "ZombieSpawner.h"

ZombieSpawner::ZombieSpawner(sf::Vector2f pos, const int* level, const int xSize, float speedFactor, float distToSpawn, EntityManager* entityManager, sf::View* view) : Spawner(pos, level, xSize, entityManager), speedFactor(speedFactor), view(view), distToSpawn(distToSpawn) {
	this->entityManager->addSpawner(this);

	this->timeForRespawn = 1000.f;

	this->minX = 0;
	this->maxX = xSize * 64;
}

void ZombieSpawner::spawnEntity() {
	MoveDirection direction = RIGHT;
	float xSpawn = this->minX;

	if (this->entityManager->xDistToPlayer(this->getPosition().x) < 0) {
		direction = LEFT;
		xSpawn = this->maxX;
	}
	if(canSpawn)
		this->currentInstance = new Zombie(sf::Vector2f(xSpawn, this->getPosition().y), this->level, this->xSize, this->speedFactor, direction, this->entityManager, this);
}

void const ZombieSpawner::update() {
	this->minX = this->view->getCenter().x - this->view->getSize().x / 2;
	this->maxX = this->view->getCenter().x + this->view->getSize().x / 2;
	if (this->currentInstance != NULL) {
		if (this->currentInstance->getPosition().x < minX || this->currentInstance->getPosition().x > this->maxX) {
			this->currentInstance->taskDeletion();
		}
	}
	else {
		if (this->respawnClock.getElapsedTime().asMilliseconds() > this->timeForRespawn && abs(this->entityManager->xDistToPlayer(this->getPosition().x)) < this->distToSpawn) {
			this->spawnEntity();
		}
	}
}

void const ZombieSpawner::onMobDeath() {
	delete this->currentInstance;
	this->currentInstance = NULL;
	this->respawnClock.restart();
}