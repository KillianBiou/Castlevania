#pragma once
#include "Collectible.h"
#include "../Misc/Weapon.h"

class WeaponUpgrade : public Collectible
{
private:
	Weapon* weapon;
	int lvl;

public:
	WeaponUpgrade(const int* level, const int X_SIZE, int upgradeLevel);

	const void onPickup(Player* player);
};

