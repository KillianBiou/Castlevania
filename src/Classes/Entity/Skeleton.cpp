#include "Skeleton.h"
#include "../Manager/GameManager.h"

Skeleton::Skeleton(sf::Vector2f pos, float speedFactor, float targetDistToPlayer, int attackCooldown, EntityManager* entityManager, Spawner* spawner) : Monster("images/Skeleton.png", pos, 64, 128, "Skeleton", 100, speedFactor, 0, entityManager, spawner) {
	this->hp = 3;
	this->animator->setAnimations({ {IDLE, 1}, {RUNNING, 2}, {HURT, 2}, {DEATH, 2} });

	this->manaOnDeath = 3;

	if (!this->boneTexture.loadFromFile("images/Bone.png")) {
		std::cout << "Error while loading : " << "images/Bone.png" << std::endl;
	}

	currentProjectile = NULL;

	this->attackClock = sf::Clock();

	this->targetDistToPlayer = targetDistToPlayer;
	this->attackCooldown = attackCooldown;

	this->scoreOnDeath = 200;

	this->hitSound.loadFromFile("sfx/pHurt.wav");
	this->deathSound.loadFromFile("sfx/skeletonDeath.wav");
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
	Level* currentLevel = this->entityManager->getGameManager()->getLevel();
	float distToTarget = this->getPosition().x - this->positionTarget.x;

	int xCollision = int(this->groundedPoint.x / 64);
	int yCollision = int(this->groundedPoint.y / 64);
	int xCollisionBis = int(this->groundedPointBis.x / 64);
	int yCollisionBis = int(this->groundedPointBis.y / 64);

	if ((currentLevel->getLevelRaw()[xCollision + yCollision * currentLevel->getSizeX()] != 0)) {
		this->canGoLeft = true;
	}
	else {
		this->canGoLeft = false;
	}
	if ((currentLevel->getLevelRaw()[xCollisionBis + yCollisionBis * currentLevel->getSizeX()] != 0)) {
		this->canGoRight = true;
	}
	else {
		this->canGoRight = false;
	}

	if (distToTarget > -5 && distToTarget < 5) {
		this->moveDirection = NONE;
	}
	else if (distToTarget < 0 && this->canGoRight) {
		this->moveDirection = RIGHT;
	}
	else if (distToTarget > 0 && this->canGoLeft) {
		this->moveDirection = LEFT;
	}
	else {
		this->moveDirection = NONE;
	}
}