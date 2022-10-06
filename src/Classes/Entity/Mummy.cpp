#include "Mummy.h"

Mummy::Mummy(sf::Vector2f pos, const int* currentLevel, const int levelXSize, float speedFactor, EntityManager* entityManager) : Monster("images/Mummy.png", pos, 64, 192, "Mummy", 150, currentLevel, levelXSize, speedFactor, 0.f, entityManager, NULL) {
	this->hp = 10;
	this->animator->setAnimations({ {IDLE, 1}, {RUNNING, 3}, {DEATH, 3} });

	this->specialDrop = true;

	this->scoreOnDeath = 350;
	this->animator->playAnimation(RUNNING);
}

void Mummy::update() {
	std::cout << "dzefezf\n";
}

const void Mummy::taskDeletion() {
	this->~Mummy();
}

Mummy::~Mummy() {
	this->weaponUpgrade = new WeaponUpgrade(this->currentLevel, this->levelXSize, 1);
	this->entityManager->addCollectible(this->weaponUpgrade);
	this->weaponUpgrade->setPosition(this->getPosition());
}