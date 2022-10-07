#include "Reaper.h"

Reaper::Reaper(sf::Vector2f pos, const int* currentLevel, const int levelXSize, float speedFactor, EntityManager* entityManager) : Monster("images/Reaper.png", pos, 128, 159, "Reaper", 150, currentLevel, levelXSize, speedFactor, 0.f, entityManager, NULL) {
	this->hp = 10;
	this->maxHp = 10;
	this->animator->setAnimations({ {IDLE, 1}, {HURT, 2}, {DEATH, 3} });
	this->animator->playAnimation(IDLE);

	this->specialDrop = true;

	if (!this->projectileTexture.loadFromFile("images/Scythe.png")) {
		std::cout << "Error while loading : " << "images/Scythe.png" << std::endl;
	}

	this->scoreOnDeath = 1000;
}

const void Reaper::update() {
	this->animate();
	animator->animate();
	//std::cout << this->getTextureRect().left << ", " << this->getTextureRect().top << std::endl;
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
	this->weaponUpgrade = new WeaponUpgrade(this->currentLevel, this->levelXSize, 2);
	this->entityManager->addCollectible(this->weaponUpgrade);
	this->weaponUpgrade->setPosition(this->getPosition());
}