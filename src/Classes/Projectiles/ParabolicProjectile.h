#pragma once
#include <SFML/Graphics.hpp>
#include "Projectile.h"

class ParabolicProjectile : public Projectile
{
private:
	float xVelocity;
	float yVelocity;
	float gravity;
	float distance;
	int frameToGround;

public:
	ParabolicProjectile(sf::Texture spritesheet, int xSize, int ySize, sf::Vector2f position, float gravity, float distance, int nbFrame);

	const void moveTick();
};

