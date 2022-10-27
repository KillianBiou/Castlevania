#include "Mummy.h"
#include "../Manager/GameManager.h"

Mummy::Mummy(sf::Vector2f pos, float speedFactor, EntityManager* entityManager) : Monster("images/Mummy.png", pos, 64, 156, "Mummy", 150, speedFactor, 0.f, entityManager, NULL) {
	this->hp = 10;
	this->maxHp = 10;
	this->animator->setAnimations({ {IDLE, 1}, {RUNNING, 3}, {HURT, 2}, {DEATH, 3} });

	this->manaOnDeath = 10;

	this->cameraLock = this->getPosition();

	// Drop a weapon upgrade on death
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
	// When tracked by camera, camera should be locked where the boss was instancied
	return this->cameraLock;
}

const void Mummy::update() {
	// Check if need to enrage
	if (this->hp <= this->maxHp / 2) {
		if (!this->isHurt)
		{
			this->setColor(sf::Color::Yellow);
		}
		if (!this->enraged) {
			this->enrage();
		}
	}

	// Update physics and animation
	this->updateAll();
	// Start the boss combat if player is nearby
	if (abs(this->entityManager->xDistToPlayer(this->getPosition().x)) < 500) {
		if(!this->bossStarted)
			this->startBoss();
	}
	// If boss started, Follow attack pattern
	if (this->bossStarted) {
		// Instanciate a sin projectile
		if (this->attackClock.getElapsedTime().asMilliseconds() >= this->timeBetweenAttacks) {
			int direction = this->entityManager->xDistToPlayer(this->getPosition().x) < 0 ? -1 : 1;
			SinProjectile* temp = new SinProjectile(this->projectileTexture, 64, 64, this->getPosition() + sf::Vector2f(0.f, -64.f), 5.f * direction, 5.f, 5.f, 2);
			this->entityManager->addProjectile(temp);
			this->attackClock.restart();
		}
		// Go toward player
		this->goToward();
	}
	
	this->animate();
}

void Mummy::enrage() {
	this->enraged = true;
	this->timeBetweenAttacks /= 2;
}

void Mummy::startBoss() {
	this->bossStarted = true;
	this->entityManager->startBossCombat(this);
	this->entityManager->getGameManager()->getSoundManager()->playBossMusic(&this->bossTheme);
}

void Mummy::animate() {
	// Play the correct animation
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

	// Always go straight for the player
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
	// Drop a weapon upgrade Level 2
	Level* currentLevel = this->entityManager->getGameManager()->getLevel();
	this->entityManager->endBossCombat();
	this->entityManager->getGameManager()->getSoundManager()->endBossMusic(&this->bossTheme);
	this->weaponUpgrade = new WeaponUpgrade(currentLevel->getLevelRaw(), currentLevel->getSizeX(), 1);
	this->entityManager->addCollectible(this->weaponUpgrade);
	this->weaponUpgrade->setPosition(this->getPosition());
}