#pragma once
#include "Collectible.h"

// Class representing an Heart (Heal) collectible
class Heart: public Collectible
{
public:
	Heart(const int* level, const int X_SIZE);

	// Override 
	const void onPickup(Player* player);
};

