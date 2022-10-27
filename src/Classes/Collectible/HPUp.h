#pragma once
#include "Collectible.h"

// Class representing an HPUp (Max hp + 1) collectible
class HPUp : public Collectible
{
public:
	HPUp(const int* level, const int X_SIZE);

	// Override
	const void onPickup(Player* player);

};

