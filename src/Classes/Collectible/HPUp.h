#pragma once
#include "Collectible.h"

class HPUp : public Collectible
{
public:
	HPUp(const int* level, const int X_SIZE);

	const void onPickup(Player* player);

};

