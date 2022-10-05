#pragma once
#include "Collectible.h"

class Heart: public Collectible
{
public:
	Heart(const int* level, const int X_SIZE);

	const void onPickup(Player* player);

};

