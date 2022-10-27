#include "MissingNo.h"
#include "../Manager/GameManager.h"

MissingNo::MissingNo(sf::Vector2f pos, float speedFactor, EntityManager* entityManager) : Monster("images/MissingNo.png", pos, 64, 149, "MissingNo", 150, speedFactor, 0.f, entityManager, NULL) {
	this->hp = 999;
	this->maxHp = 999;
	this->animator->setAnimations({ {IDLE, 2}, {HURT, 2}, {DEATH, 1} });
	this->animator->playAnimation(IDLE);

	this->manaOnDeath = 10;

	this->cameraLock = this->getPosition();

	// Six Projectile spawn location
	this->scytheV1 = this->getPosition() + sf::Vector2f(500.f, -300.f);
	this->scytheV2 = this->getPosition() + sf::Vector2f(-500.f, -300.f);
	this->scytheV3 = this->getPosition() + sf::Vector2f(600.f, -150.f);
	this->scytheV4 = this->getPosition() + sf::Vector2f(-600.f, -150.f);
	this->scytheV5 = this->getPosition() + sf::Vector2f(700.f, 0.f);
	this->scytheV6 = this->getPosition() + sf::Vector2f(-700.f, 0.f);

	this->timeBetweenAttacks = 2000;
	this->attackClock = sf::Clock();
	this->touchdownCooldown = sf::Clock();

	this->movementVector = sf::Vector2f(speedFactor, -speedFactor);

	this->specialDrop = true;

	if (!this->projectileTexture.loadFromFile("images/missingProjectile.png")) {
		std::cout << "Error while loading : " << "images/missingProjectile.png" << std::endl;
	}

	this->scoreOnDeath = 1000;

	this->hitSound.loadFromFile("sfx/pHurt.wav");
	this->bossTheme.openFromFile("music/missingNoTheme.ogg");
	this->deathSound.loadFromFile("sfx/reaperDeath.wav");
}

const void MissingNo::update() {
	this->animate();
	animator->animate();
	this->moveCollisionPoint();

	if (abs(this->entityManager->xDistToPlayer(this->getPosition().x)) < 500 && abs(this->entityManager->yDistToPlayer(this->getPosition().y)) < 500) {
		if (!this->bossStarted)
			this->startBoss();
	}
	if (this->bossStarted) {
		if (this->attackClock.getElapsedTime().asMilliseconds() >= std::max(this->timeBetweenAttacks * ((float)this->hp / this->maxHp), 800.f)) {
			int direction = this->entityManager->xDistToPlayer(this->getPosition().x) < 0 ? -1 : 1;
			StraightProjectile* temp = new StraightProjectile(this->projectileTexture, 64, 64, this->scytheV2 + sf::Vector2f(0.f, -64.f), 10.f, this->entityManager->playerPosition(), 2);
			StraightProjectile* temp2 = new StraightProjectile(this->projectileTexture, 64, 64, this->scytheV1, 10.f, this->entityManager->playerPosition(), 2);
			StraightProjectile* temp3 = new StraightProjectile(this->projectileTexture, 64, 64, this->scytheV4, 10.f, this->entityManager->playerPosition(), 2);
			StraightProjectile* temp4 = new StraightProjectile(this->projectileTexture, 64, 64, this->scytheV3, 10.f, this->entityManager->playerPosition(), 2);
			StraightProjectile* temp5 = new StraightProjectile(this->projectileTexture, 64, 64, this->scytheV6, 10.f, this->entityManager->playerPosition(), 2);
			StraightProjectile* temp6 = new StraightProjectile(this->projectileTexture, 64, 64, this->scytheV5, 10.f, this->entityManager->playerPosition(), 2);
			this->entityManager->addProjectile(temp);
			this->entityManager->addProjectile(temp2);
			this->entityManager->addProjectile(temp3);
			this->entityManager->addProjectile(temp4);
			this->entityManager->addProjectile(temp5);
			this->entityManager->addProjectile(temp6);
			this->attackClock.restart();
		}
		if (this->firstAttack || touchdownCooldown.getElapsedTime().asMilliseconds() >= 5000 && this->entityManager->isOnScreen(this->getPosition(), 0)) {
			this->checkCollision();
			this->moveTick();
		}
	}
}

void MissingNo::moveTick() {
	this->move(this->movementVector);
}

void MissingNo::startBoss() {
	this->bossStarted = true;
	this->entityManager->startBossCombat(this);
	this->entityManager->getGameManager()->getSoundManager()->playBossMusic(&this->bossTheme);
}

const sf::Vector2f MissingNo::cameraTracking() {
	return this->cameraLock;
}

void MissingNo::checkCollision() {
	Level* currentLevel = this->entityManager->getGameManager()->getLevel();
	sf::View* view = this->entityManager->getView();

	if (!this->entityManager->isOnScreen(this->topBoundPoint, 0) || !this->entityManager->isOnScreen(this->groundedPoint, 0)) {
		this->movementVector.y *= -1;
	}
	if (!this->entityManager->isOnScreen(this->rightBoundPointBis, 0) || !this->entityManager->isOnScreen(this->leftBoundPointBis, 0)) {
		this->movementVector.x *= -1;
	}
}

void MissingNo::animate() {
	Animation tempAnim = IDLE;
	if (this->isHurt) {
		tempAnim = HURT;
	}
	if (this->hp <= 0) {
		tempAnim = DEATH;
	}
	this->animator->playAnimation(tempAnim);
}

const void MissingNo::taskDeletion() {
	this->~MissingNo();
}

MissingNo::~MissingNo() {
	Level* currentLevel = this->entityManager->getGameManager()->getLevel();
	this->entityManager->endBossCombat();
	this->entityManager->getGameManager()->getSoundManager()->endBossMusic(&this->bossTheme);
	this->weaponUpgrade = new WeaponUpgrade(currentLevel->getLevelRaw(), currentLevel->getSizeX(), 2);
	this->entityManager->addCollectible(this->weaponUpgrade);
	this->weaponUpgrade->setPosition(this->getPosition());
}