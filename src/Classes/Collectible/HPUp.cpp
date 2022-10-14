#include "HPUp.h"
#include "../Manager/GameManager.h"


HPUp::HPUp(const int* level, const int X_SIZE) : Collectible("images/Collectibles.png", sf::IntRect(32, 0, 32, 32), level, X_SIZE) {
}

const void HPUp::onPickup(Player* player) {
	player->getEntityManager()->getGameManager()->getSoundManager()->playSoundEffect(&this->pickupSound);
	player->addMaxHp(1);
	this->setTextureRect(sf::IntRect(0, 0, 0, 0));
}