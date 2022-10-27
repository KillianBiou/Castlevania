#pragma once
#include <SFML/Graphics.hpp>
#include "Projectile.h"

// Class that represent a projectile that goes straight toward a target
class StraightProjectile : public Projectile
{
private:
	float speed;
	sf::Vector2f direction;

public:
	StraightProjectile(sf::Texture spritesheet, int xSize, int ySize, sf::Vector2f position, float speed, sf::Vector2f targetPos, int nbFrame);

	const void moveTick();
};