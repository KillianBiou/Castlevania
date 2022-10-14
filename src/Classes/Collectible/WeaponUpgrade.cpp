#include "WeaponUpgrade.h"
#include "../Manager/GameManager.h"

WeaponUpgrade::WeaponUpgrade(const int* level, const int X_SIZE, int upgradeLevel) : Collectible("images/Collectibles.png", sf::IntRect(32 + upgradeLevel * 32, 0, 32, 32), level, X_SIZE) {
	this->setScale(1.5f, 1.5f);
	switch (upgradeLevel)
	{
	case 1:
		this->weapon = new Weapon("images/Whip2.png", 2, 250, "sfx/whip2.ogg");
		break;
	case 2:
		this->weapon = new Weapon("images/Whip3.png", 3, 150, "sfx/whip3.ogg");
		break;
	default:
		this->weapon = new Weapon("images/Whip2.png", 2, 250, "sfx/whip2.ogg");
		break;
	}
}

const void WeaponUpgrade::onPickup(Player* player) {
	player->getEntityManager()->getGameManager()->getSoundManager()->playSoundEffect(&this->pickupSound);
	player->changeWeapon(this->weapon);
	this->setTextureRect(sf::IntRect(0, 0, 0, 0));
}