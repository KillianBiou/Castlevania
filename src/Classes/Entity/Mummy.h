#pragma once
#include "Monster.h"
#include "../Manager/EntityManager.h"
#include "../Collectible/WeaponUpgrade.h"

class Mummy : public Monster {
private:
	WeaponUpgrade* weaponUpgrade;

public:
	Mummy(sf::Vector2f pos, const int* currentLevel, const int levelXSize, float speedFactor, EntityManager* entityManager);
	void update();

	const void taskDeletion();
	~Mummy();
};
