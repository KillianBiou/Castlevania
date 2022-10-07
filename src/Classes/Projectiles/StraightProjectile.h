#pragma once
#include <SFML/Graphics.hpp>
#include "Projectile.h"

class StraightProjectile : public Projectile
{
private:
	float speed;

public:
	StraightProjectile(sf::Texture spritesheet, int xSize, int ySize, sf::Vector2f position, float speed, int nbFrame);

	const void moveTick();
};