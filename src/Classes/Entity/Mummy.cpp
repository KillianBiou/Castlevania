#include "Mummy.h"
#include "../Manager/GameManager.h"

Mummy::Mummy(sf::Vector2f pos, const int* currentLevel, const int levelXSize, float speedFactor, EntityManager* entityManager) : Monster("images/Mummy.png", pos, 64, 156, "Mummy", 150, currentLevel, levelXSize, speedFactor, 0.f, entityManager, NULL) {
	this->hp = 10;
	this->maxHp = 10;
	this->animator->setAnimations({ {IDLE, 1}, {RUNNING, 3}, {HURT, 2}, {DEATH, 3} });

	this->manaOnDeath = 10;

	this->cameraLock = this->getPosition();

	this->specialDrop = true;
	this->timeBetweenAttacks = 3000;
	this->attackClock = sf::Clock();

	if (!this->projectileTexture.loadFromFile("images/MummyProjectile.png")) {
		std::cout << "Error while loading : " << "images/MummyProjectile.png" << std::endl;
	}

	this->scoreOnDeath = 400;
	this->hitSound.loadFromFile("sfx/pHurt.wav");
	this->deathSound.loadFromFile("sfx/reaperDeath.wav");
	this->bossTheme.openFromFile("music/deathTheme.ogg");
}

const sf::Vector2f Mummy::cameraTracking() {
	return this->cameraLock;
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
	if (abs(this->entityManager->xDistToPlayer(this->getPosition().x)) < 500) {
		if(!this->bossStarted)
			this->startBoss();
	}
	if (this->bossStarted) {
		if (this->attackClock.getElapsedTime().asMilliseconds() >= this->timeBetweenAttacks) {
			int direction = this->entityManager->xDistToPlayer(this->getPosition().x) < 0 ? -1 : 1;
			SinProjectile* temp = new SinProjectile(this->projectileTexture, 64, 64, this->getPosition() + sf::Vector2f(0.f, -64.f), 5.f * direction, 5.f, 5.f, 2);
			this->entityManager->addProjectile(temp);
			this->attackClock.restart();
		}
		this->goToward();
	}
	
	this->animate();
}

void Mummy::enrage() {
	this->enraged = true;
	//this->speedFactor *= 1.5;
	this->timeBetweenAttacks /= 2;
}

void Mummy::startBoss() {
	this->bossStarted = true;
	this->entityManager->startBossCombat(this);
	this->entityManager->getGameManager()->getSoundManager()->playBossMusic(&this->bossTheme);
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
	this->entityManager->endBossCombat();
	this->entityManager->getGameManager()->getSoundManager()->endBossMusic(&this->bossTheme);
	this->weaponUpgrade = new WeaponUpgrade(this->currentLevel, this->levelXSize, 1);
	this->entityManager->addCollectible(this->weaponUpgrade);
	this->weaponUpgrade->setPosition(this->getPosition());
}