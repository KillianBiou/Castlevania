#include "Monster.h"
#include "../Manager/EntityManager.h"

Monster::Monster(std::string texturePath, std::string name, int frameDelay, const int* currentLevel, const int levelXSize, float speedFactor, float jumpFactor, EntityManager* entityManager) : Entity(texturePath, sf::Vector2f(100.f, 100.f), 64, 128, frameDelay, currentLevel, levelXSize, speedFactor, jumpFactor, entityManager) {
	entityManager->addMonster(this);
	this->maxHp = 5;
	this->hp = this->maxHp;
	this->name = name;

	this->side = RIGHT;
}

void const Monster::drawChild(sf::RenderWindow* renderWindow) {

}

const void Monster::attack(bool advance) {

}

Monster::~Monster() {
	delete(this->animator);
	this->entityManager->removeMonster(this);
}


const void Monster::taskDeletion() {
	this->entityManager->removeMonster(this);
}