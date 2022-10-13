#include "Monster.h"
#include "../Manager/EntityManager.h"
#include "../Spawner/Spawner.h"


Monster::Monster(std::string texturePath, sf::Vector2f pos, int sizeX, int sizeY, std::string name, int frameDelay, const int* currentLevel, const int levelXSize, float speedFactor, float jumpFactor, EntityManager* entityManager, Spawner* spawner) : Entity(texturePath, pos, sizeX, sizeY, frameDelay, currentLevel, levelXSize, speedFactor, jumpFactor, entityManager), spawner(spawner) {
	srand(time(NULL));
	entityManager->addMonster((Monster*)this);
	this->maxHp = 5;
	this->hp = this->maxHp;
	this->name = name;

	this->specialDrop = false;

	this->side = RIGHT;
}

void const Monster::drawChild(sf::RenderWindow* renderWindow) {

}

void const Monster::attack(bool advance) {

}

const sf::Vector2f Monster::cameraTracking() {
	return this->getPosition();
}

Monster::~Monster() {
	if (!this->specialDrop) {
		if (this->entityManager->verifyScore()) {
			Collectible* temp = new HPUp(this->currentLevel, this->levelXSize);
			temp->setPosition(this->getPosition());
			this->entityManager->addCollectible(temp);
		}
		else {
			if (this->dead) {
				if (rand() % 2 == 0) {
					Collectible* temp = new Heart(this->currentLevel, this->levelXSize);
					temp->setPosition(this->getPosition());
					this->entityManager->addCollectible(temp);
				}
			}
		}
	}
	this->entityManager->removeMonster(this);
}


const void Monster::taskDeletion() {
	this->spawner->onMobDeath();
}