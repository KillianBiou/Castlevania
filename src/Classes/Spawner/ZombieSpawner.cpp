#include "ZombieSpawner.h"

ZombieSpawner::ZombieSpawner(sf::Vector2f pos, const int* level, const int xSize, float speedFactor, float distToSpawn, EntityManager* entityManager, sf::View* view) : Spawner(pos, level, xSize, entityManager), speedFactor(speedFactor), view(view), distToSpawn(distToSpawn) {
	this->entityManager->addSpawner(this);

	this->timeForRespawn = 1000.f;

	this->minX = 0;
	this->maxX = xSize * 64;
}

// Spawn the zombie at the edge of the screen 
void ZombieSpawner::spawnEntity() {
	MoveDirection direction = RIGHT;
	// If player is at the right of the spawner's position, spawn the zombie to the left edge
	float xSpawn = this->minX;

	// If player is at the left of the spawner's position, spawn the zombie to the right edge
	if (this->entityManager->xDistToPlayer(this->getPosition().x) < 0) {
		direction = LEFT;
		xSpawn = this->maxX;
	}
	// If the spawner is not disabled
	if(canSpawn)
		this->currentInstance = new Zombie(sf::Vector2f(xSpawn, this->getPosition().y), this->speedFactor, direction, this->entityManager, this);
}

// Update loop for the zombie spawner behavior
void const ZombieSpawner::update() {
	this->minX = this->view->getCenter().x - this->view->getSize().x / 2;
	this->maxX = this->view->getCenter().x + this->view->getSize().x / 2;
	// If a zombie is instanciated
	if (this->currentInstance != NULL) {
		// Delete the zombie if out of screen
		if (this->currentInstance->getPosition().x < minX || this->currentInstance->getPosition().x > this->maxX) {
			this->currentInstance->taskDeletion();
		}
	}
	else {
		// If the player is nearby and time since last instance death is long enough, spawn a zombie
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