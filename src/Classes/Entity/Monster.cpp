#include "Monster.h"
#include "../Manager/EntityManager.h"
#include "../Manager/GameManager.h"
#include "../Spawner/Spawner.h"


Monster::Monster(std::string texturePath, sf::Vector2f pos, int sizeX, int sizeY, std::string name, int frameDelay, float speedFactor, float jumpFactor, EntityManager* entityManager, Spawner* spawner) : Entity(texturePath, pos, sizeX, sizeY, frameDelay, speedFactor, jumpFactor, entityManager), spawner(spawner) {
	entityManager->addMonster((Monster*)this);
	this->maxHp = 5;
	this->hp = this->maxHp;
	this->name = name;

	this->specialDrop = false;

	this->side = RIGHT;

	this->deathSound.loadFromFile("sfx/medusaDeath.wav");
}

void const Monster::drawChild(sf::RenderWindow* renderWindow) {

}

void const Monster::attack(bool advance) {

}

const sf::Vector2f Monster::cameraTracking() {
	// By default, camera tracking should follow the monster position
	return this->getPosition();
}

Monster::~Monster() {
	Level* currentLevel = this->entityManager->getGameManager()->getLevel();
	// If the monster don't have special drops
	if (!this->specialDrop) {
		// Verify if next milestone is reached
		if (this->entityManager->verifyScore() && this->dead) {
			// Drop an HpUp
			Collectible* temp = new HPUp(currentLevel->getLevelRaw(), currentLevel->getSizeX());
			temp->setPosition(this->getPosition());
			this->entityManager->addCollectible(temp);
		}
		else {
			// If the player killed the mob
			if (this->dead) {
				// 50% chance to drop an heart
				if (rand() % 2 == 0) {
					Collectible* temp = new Heart(currentLevel->getLevelRaw(), currentLevel->getSizeX());
					temp->setPosition(this->getPosition());
					this->entityManager->addCollectible(temp);
				}
			}
		}
	}
	this->entityManager->removeMonster(this);
}

// Prepare the deletion of the monster
const void Monster::taskDeletion() {
	this->spawner->onMobDeath();
}