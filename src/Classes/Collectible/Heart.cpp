#include "Heart.h"
#include "../Manager/GameManager.h"


Heart::Heart(const int* level, const int X_SIZE) : Collectible("images/Collectibles.png", sf::IntRect(0, 0, 32, 32), level, X_SIZE) {
}

const void Heart::onPickup(Player* player) {
	player->getEntityManager()->getGameManager()->getSoundManager()->playSoundEffect(&this->pickupSound);
	player->addHp(1);
	this->setTextureRect(sf::IntRect(0, 0, 0, 0));
}