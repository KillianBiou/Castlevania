#include "MedusaHeadSpawner.h"

MedusaHeadSpawner::MedusaHeadSpawner(float y, const int* level, const int xSize, float speedFactor, float amplitude, float frequency, EntityManager* entityManager, sf::View* view) : Spawner(sf::Vector2f(0, y), level, xSize, entityManager), speedFactor(speedFactor), amplitude(amplitude), frequency(frequency), view(view) {
	this->spawnEntity();
	this->entityManager->addSpawner(this);

	this->timeForRespawn = 1000.f;

	this->minX = 0;
	this->maxX = xSize * 64;
}

// Spawn the medusa head
void MedusaHeadSpawner::spawnEntity() {
	if(canSpawn)
		this->currentInstance = new MedusaHead("Medusahead 1", this->getPosition(), this->speedFactor, this->amplitude, this->frequency, this->entityManager, this);
}

// Update loop for the medusa head spawner behavior
void const MedusaHeadSpawner::update() {
	this->minX = this->view->getCenter().x - this->view->getSize().x / 2;
	this->maxX = this->view->getCenter().x + this->view->getSize().x / 2;

	// Lock the spawner to the right of the screen
	this->setPosition(maxX, this->getPosition().y);
	if (this->currentInstance != NULL) {
		// Delete if the medusa head is out of screen (Reach left border)
		if (this->currentInstance->getPosition().x < minX || this->currentInstance->getPosition().x > this->maxX) {
			this->currentInstance->taskDeletion();
		}
	}
	else {
		// Spawn if time elapsed since last death is reached
		if (this->respawnClock.getElapsedTime().asMilliseconds() > this->timeForRespawn) {
			this->spawnEntity();
		}
	}
}
void const MedusaHeadSpawner::onMobDeath() {
	delete this->currentInstance;
	this->currentInstance = NULL;
	this->respawnClock.restart();
}