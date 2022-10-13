#include "Reaper.h"

Reaper::Reaper(sf::Vector2f pos, const int* currentLevel, const int levelXSize, float speedFactor, EntityManager* entityManager) : Monster("images/Reaper.png", pos, 128, 159, "Reaper", 150, currentLevel, levelXSize, speedFactor, 0.f, entityManager, NULL) {
	this->hp = 10;
	this->maxHp = 10;
	this->animator->setAnimations({ {IDLE, 1}, {HURT, 2}, {DEATH, 3} });
	this->animator->playAnimation(IDLE);

	this->cameraLock = this->getPosition();

	this->timeBetweenAttacks = 2000;
	this->attackClock = sf::Clock();
	this->touchdownCooldown = sf::Clock();

	this->movementVector = sf::Vector2f(speedFactor, -speedFactor);

	this->specialDrop = true;

	if (!this->projectileTexture.loadFromFile("images/Scythe.png")) {
		std::cout << "Error while loading : " << "images/Scythe.png" << std::endl;
	}

	this->scoreOnDeath = 1000;
}

const void Reaper::update() {
	this->animate();
	animator->animate();
	this->moveCollisionPoint();

	if (abs(this->entityManager->xDistToPlayer(this->getPosition().x)) < 500) {
		if (!this->bossStarted)
			this->startBoss();
	}
	if (this->bossStarted) {
		if (this->attackClock.getElapsedTime().asMilliseconds() >= this->timeBetweenAttacks) {
			int direction = this->entityManager->xDistToPlayer(this->getPosition().x) < 0 ? -1 : 1;
			StraightProjectile* temp = new StraightProjectile(this->projectileTexture, 64, 64, this->getPosition() + sf::Vector2f(0.f, -64.f), 5.f, this->entityManager->playerPosition(), 2);
			this->entityManager->addProjectile(temp);
			this->attackClock.restart();
		}
		if (touchdownCooldown.getElapsedTime().asMilliseconds() >= 5000 && this->entityManager->isOnScreen(this->getPosition())) {
			this->checkCollision();
			this->moveTick();
		}
	}
}

void Reaper::moveTick() {
	this->move(this->movementVector);
}

void Reaper::startBoss() {
	this->bossStarted = true;
	this->entityManager->startBossCombat(this);
}

const sf::Vector2f Reaper::cameraTracking() {
	return this->cameraLock;
}

void Reaper::checkCollision() {
	sf::View* view = this->entityManager->getView();

	if (!this->entityManager->isOnScreen(this->topBoundPoint) || !this->entityManager->isOnScreen(this->groundedPoint)) {
		this->movementVector.y *= -1;
	}
	if (!this->entityManager->isOnScreen(this->rightBoundPointBis) || !this->entityManager->isOnScreen(this->leftBoundPointBis)) {
		this->movementVector.x *= -1;
	}

	int xCollision = int(this->groundedPoint.x / 64);
	int yCollision = int(this->groundedPoint.y / 64);
	int xCollisionBis = int(this->groundedPointBis.x / 64);
	int yCollisionBis = int(this->groundedPointBis.y / 64);
	if ((this->currentLevel[xCollision + yCollision * levelXSize] != 0 && this->currentLevel[xCollisionBis + yCollisionBis * levelXSize] != 0) && this->isGrounded == false) {
		this->movementVector.y *= -1;
		this->touchdownCooldown.restart();
		this->setPosition(this->getPosition().x, yCollision * 64 - spriteSizeY / 2.f);

	}
	else if ((this->currentLevel[xCollision + yCollision * levelXSize] == 0 && this->currentLevel[xCollisionBis + yCollisionBis * levelXSize] == 0) && this->isGrounded == true) {
		this->setIsGrounded(false);
	}
}

void Reaper::animate() {
	Animation tempAnim = IDLE;
	if (this->isHurt) {
		tempAnim = HURT;
	}
	if (this->hp <= 0) {
		tempAnim = DEATH;
	}
	this->animator->playAnimation(tempAnim);
}

const void Reaper::taskDeletion() {
	this->~Reaper();
}

Reaper::~Reaper() {
	this->entityManager->endBossCombat();
	this->weaponUpgrade = new WeaponUpgrade(this->currentLevel, this->levelXSize, 2);
	this->entityManager->addCollectible(this->weaponUpgrade);
	this->weaponUpgrade->setPosition(this->getPosition());
}