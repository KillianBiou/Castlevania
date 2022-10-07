#include "Mummy.h"

Mummy::Mummy(sf::Vector2f pos, const int* currentLevel, const int levelXSize, float speedFactor, EntityManager* entityManager) : Monster("images/Mummy.png", pos, 64, 156, "Mummy", 150, currentLevel, levelXSize, speedFactor, 0.f, entityManager, NULL) {
	this->hp = 10;
	this->maxHp = 10;
	this->animator->setAnimations({ {IDLE, 1}, {RUNNING, 3}, {HURT, 2}, {DEATH, 3} });

	this->specialDrop = true;
	this->timeBetweenAttacks = 3000;
	this->attackClock = sf::Clock();

	if (!this->projectileTexture.loadFromFile("images/MummyProjectile.png")) {
		std::cout << "Error while loading : " << "images/MummyProjectile.png" << std::endl;
	}

	this->scoreOnDeath = 400;
}

const void Mummy::update() {
	if (this->hp <= this->maxHp / 2) {
		if (!this->isHurt)
		{
			this->setColor(sf::Color::Yellow);
		}
		if (!this->enraged) {
			this->enrage();
		}
	}

	this->updateAll();
	if (this->entityManager->xDistToPlayer(this->getPosition().x) < 1000) {
		if (this->attackClock.getElapsedTime().asMilliseconds() >= this->timeBetweenAttacks) {
			int direction = this->entityManager->xDistToPlayer(this->getPosition().x) < 0 ? -1 : 1;
			SinProjectile* temp = new SinProjectile(this->projectileTexture, 64, 64, this->getPosition() + sf::Vector2f(0.f, -64.f), 5.f * direction, 5.f, 5.f, 2);
			this->entityManager->addProjectile(temp);
			this->attackClock.restart();
		}
		this->goToward();
	}
	else {
		this->moveDirection = NONE;
	}
	this->animate();
}

void Mummy::enrage() {
	this->enraged = true;
	this->speedFactor *= 1.5;
	this->timeBetweenAttacks /= 2;
}

void Mummy::animate() {
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

void Mummy::goToward() {
	float distToTarget = this->getPosition().x - this->entityManager->playerPosition().x;

	if (distToTarget < -50) {
		this->moveDirection = RIGHT;
		this->setScale(-1.f, 1.f);
	}
	else if (distToTarget > 50) {
		this->moveDirection = LEFT;
		this->setScale(1.f, 1.f);
	}
}

const void Mummy::taskDeletion() {
	this->~Mummy();
}

Mummy::~Mummy() {
	this->weaponUpgrade = new WeaponUpgrade(this->currentLevel, this->levelXSize, 1);
	this->entityManager->addCollectible(this->weaponUpgrade);
	this->weaponUpgrade->setPosition(this->getPosition());
}