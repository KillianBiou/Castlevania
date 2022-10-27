#include "SkeletonSpawner.h"

SkeletonSpawner::SkeletonSpawner(sf::Vector2f pos, const int* level, const int xSize, float speedFactor, float targetDistToPlayer, float attackCooldown, EntityManager* entityManager, sf::View* view) : Spawner(pos, level, xSize, entityManager), speedFactor(speedFactor), view(view), targetDistToPlayer(targetDistToPlayer), attackCooldown(attackCooldown) {
	this->entityManager->addSpawner(this);
	this->spawnEntity();
}

// Spawn the skeleton
void SkeletonSpawner::spawnEntity() {
	if(canSpawn)
		this->currentInstance = new Skeleton(this->getPosition(), this->speedFactor, this->targetDistToPlayer, this->attackCooldown, this->entityManager, this);
}

// Update loop for the skeleton spawner behavior
void const SkeletonSpawner::update() {
	float xMin = this->view->getCenter().x - this->view->getSize().x / 2 - 128;
	float yMin = this->view->getCenter().y - this->view->getSize().y / 2 - 128;

	sf::FloatRect tempCollider(sf::Vector2f(xMin, yMin), sf::Vector2f(this->view->getSize().x + 128, this->view->getSize().y + 128));
	// Spawn an skeleton if the spawner is out of the screen
	if (currentInstance == NULL && !tempCollider.contains(this->getPosition())) {
		this->spawnEntity();
	}
}

void const SkeletonSpawner::onMobDeath() {
	delete this->currentInstance;
	this->currentInstance = NULL;
}