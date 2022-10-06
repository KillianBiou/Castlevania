#pragma once
#include "Collectible.h"
#include "../Misc/Weapon.h"

class WeaponUpgrade : public Collectible
{
private:
	Weapon* weapon;

public:
	WeaponUpgrade(const int* level, const int X_SIZE, int upgradeLevel);

	const void onPickup(Player* player);
};

