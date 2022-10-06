#include "Zombie.h"

Zombie::Zombie(sf::Vector2f pos, const int* currentLevel, const int levelXSize, float speedFactor, MoveDirection direction, EntityManager* entityManager, Spawner* spawner) : Monster("images/Zombie.png", pos, 64, 128, "Zombie", 100, currentLevel, levelXSize, speedFactor, 0, entityManager, spawner) {
	this->hp = 2;
	this->animator->setAnimations({ {IDLE, 1}, {RUNNING, 2}, {DEATH, 0} });

	this->animator->playAnimation(RUNNING);

	this->doubleSpeed = false;

	this->scoreOnDeath = 100;
	this->setHorizontalMovement(direction);
}

void const Zombie::update() {
	this->updateAll();
	if (!this->dead) {
		this->animator->animate();
	}
	if (this->hp == 1 && !doubleSpeed) {
		this->speedFactor *= 1.25f;
		this->doubleSpeed = true;
	}
}