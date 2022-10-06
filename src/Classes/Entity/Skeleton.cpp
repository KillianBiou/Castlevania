#include "Skeleton.h"

Skeleton::Skeleton(sf::Vector2f pos, const int* currentLevel, const int levelXSize, float speedFactor, float targetDistToPlayer, int attackCooldown, EntityManager* entityManager, Spawner* spawner) : Monster("images/Skeleton.png", pos, 64, 128, "Skeleton", 100, currentLevel, levelXSize, speedFactor, 0, entityManager, spawner) {
	this->hp = 3;
	this->animator->setAnimations({ {IDLE, 1}, {RUNNING, 2}, {HURT, 2}, {DEATH, 2} });

	if (!this->boneTexture.loadFromFile("images/Bone.png")) {
		std::cout << "Error while loading : " << "images/Bone.png" << std::endl;
	}

	currentProjectile = NULL;

	this->attackClock = sf::Clock();

	this->targetDistToPlayer = targetDistToPlayer;
	this->attackCooldown = attackCooldown;

	this->scoreOnDeath = 200;
}



void const Skeleton::update() {
	float distToPlayer = this->entityManager->xDistToPlayer(this->getPosition().x);
	this->positionTarget = this->entityManager->playerPosition() + sf::Vector2f(distToPlayer < 0.f ? this->targetDistToPlayer : -this->targetDistToPlayer, 0.f);

	this->setScale(distToPlayer < 0 ? -1.f : 1.f, 1.f);

	if (abs(distToPlayer) < this->targetDistToPlayer * 1.5) {
		this->goToward();
		if (this->attackClock.getElapsedTime().asMilliseconds() > this->attackCooldown) {
			this->attackClock.restart();
			this->attack();
		}
	}
	else {
		this->moveDirection = NONE;
	}
	this->updateAll();
	if (!this->dead) {
		this->animate();
	}
}

void Skeleton::attack() {
	currentProjectile = new ParabolicProjectile(this->boneTexture, 64, 64, this->getPosition(), 0.5f, this->entityManager->xDistToPlayer(this->getPosition().x), 3);
	this->entityManager->addProjectile(currentProjectile);
}

void Skeleton::animate() {
	Animation tempAnim = IDLE;
	if (this->moveDirection != NONE) {
		tempAnim = RUNNING;
	}
	if (this->isHurt) {
		tempAnim = HURT;
	}
	if (this->hp <= 0) {
		tempAnim = DEATH;
	}
	this->animator->playAnimation(tempAnim);
}

void Skeleton::goToward() {
	float distToTarget = this->getPosition().x - this->positionTarget.x;

	if (distToTarget > -5 && distToTarget < 5) {
		this->moveDirection = NONE;
	}
	else if (distToTarget < 0) {
		this->moveDirection = RIGHT;
	}
	else if (distToTarget > 0) {
		this->moveDirection = LEFT;
	}
}