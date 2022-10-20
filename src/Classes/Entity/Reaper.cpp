#include "Reaper.h"
#include "../Manager/GameManager.h"

Reaper::Reaper(sf::Vector2f pos, float speedFactor, EntityManager* entityManager) : Monster("images/Reaper.png", pos, 128, 159, "Reaper", 150, speedFactor, 0.f, entityManager, NULL) {
	this->hp = 10;
	this->maxHp = 10;
	this->animator->setAnimations({ {IDLE, 1}, {HURT, 2}, {DEATH, 3} });
	this->animator->playAnimation(IDLE);

	this->manaOnDeath = 10;

	this->cameraLock = this->getPosition();

	this->scytheV1 = this->getPosition() + sf::Vector2f(300.f, -150.f);
	this->scytheV2 = this->getPosition() + sf::Vector2f(-300.f, -150.f);

	this->timeBetweenAttacks = 2000;
	this->attackClock = sf::Clock();
	this->touchdownCooldown = sf::Clock();

	this->movementVector = sf::Vector2f(speedFactor, -speedFactor);

	this->specialDrop = true;

	if (!this->projectileTexture.loadFromFile("images/Scythe.png")) {
		std::cout << "Error while loading : " << "images/Scythe.png" << std::endl;
	}

	this->scoreOnDeath = 1000;

	this->hitSound.loadFromFile("sfx/pHurt.wav");
	this->bossTheme.openFromFile("music/deathTheme.ogg");
	this->deathSound.loadFromFile("sfx/reaperDeath.wav");
}

const void Reaper::update() {
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
			StraightProjectile* temp = new StraightProjectile(this->projectileTexture, 64, 64, this->scytheV2 + sf::Vector2f(0.f, -64.f), 5.f, this->entityManager->playerPosition(), 2);
			StraightProjectile* temp2 = new StraightProjectile(this->projectileTexture, 64, 64, this->scytheV1, 5.f, this->entityManager->playerPosition(), 2);
			this->entityManager->addProjectile(temp);
			this->entityManager->addProjectile(temp2);
			this->attackClock.restart();
		}
		if (this->firstAttack || touchdownCooldown.getElapsedTime().asMilliseconds() >= 5000 && this->entityManager->isOnScreen(this->getPosition())) {
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
	this->entityManager->getGameManager()->getSoundManager()->playBossMusic(&this->bossTheme);
}

const sf::Vector2f Reaper::cameraTracking() {
	return this->cameraLock;
}

void Reaper::checkCollision() {
	Level* currentLevel = this->entityManager->getGameManager()->getLevel();
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
	if ((currentLevel->getLevelRaw()[xCollision + yCollision * currentLevel->getSizeX()] == 1 && currentLevel->getLevelRaw()[xCollisionBis + yCollisionBis * currentLevel->getSizeX()] == 1) && this->isGrounded == false) {
		this->movementVector.y *= -1;
		this->touchdownCooldown.restart();
		this->firstAttack = false;
		this->setPosition(this->getPosition().x, yCollision * 64 - spriteSizeY / 2.f);

	}
	else if ((currentLevel->getLevelRaw()[xCollision + yCollision * currentLevel->getSizeX()] == 0 && currentLevel->getLevelRaw()[xCollisionBis + yCollisionBis * currentLevel->getSizeX()] == 0) && this->isGrounded == true) {
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
	Level* currentLevel = this->entityManager->getGameManager()->getLevel();
	this->entityManager->endBossCombat();
	this->entityManager->getGameManager()->getSoundManager()->endBossMusic(&this->bossTheme);
	this->weaponUpgrade = new WeaponUpgrade(currentLevel->getLevelRaw(), currentLevel->getSizeX(), 2);
	this->entityManager->addCollectible(this->weaponUpgrade);
	this->weaponUpgrade->setPosition(this->getPosition());
}