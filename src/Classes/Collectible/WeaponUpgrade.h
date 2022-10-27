#pragma once
#include "Collectible.h"
#include "../Misc/Weapon.h"

// Class representing a weapon upgrade collectible
class WeaponUpgrade : public Collectible
{
private:
	Weapon* weapon;
	int lvl;

public:
	WeaponUpgrade(const int* level, const int X_SIZE, int upgradeLevel);

	// Override
	const void onPickup(Player* player);
};

