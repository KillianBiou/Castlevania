#include "Monster.h"
#include "../Manager/EntityManager.h"
#include "../Spawner/Spawner.h"

Monster::Monster(std::string texturePath, sf::Vector2f pos, int sizeX, int sizeY, std::string name, int frameDelay, const int* currentLevel, const int levelXSize, float speedFactor, float jumpFactor, EntityManager* entityManager, Spawner* spawner) : Entity(texturePath, pos, sizeX, sizeY, frameDelay, currentLevel, levelXSize, speedFactor, jumpFactor, entityManager), spawner(spawner) {
	entityManager->addMonster((Monster*)this);
	this->maxHp = 5;
	this->hp = this->maxHp;
	this->name = name;
	this->animator->setAnimations({ {IDLE, 1}, {RUNNING, 3}, {JUMPING, 1}, {ATTACK, 3}, {HURT, 2}, {DEATH, 4} });

	this->side = RIGHT;
}

void const Monster::drawChild(sf::RenderWindow* renderWindow) {

}

const void Monster::attack(bool advance) {

}

Monster::~Monster() {
	this->entityManager->removeMonster(this);
}


const void Monster::taskDeletion() {
	this->spawner->onMobDeath();
}