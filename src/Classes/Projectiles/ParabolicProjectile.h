#pragma once
#include <SFML/Graphics.hpp>
#include "Projectile.h"

// Class that represent a projectile that follow a parabolic trajectory, reaching y = 0 at target
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

