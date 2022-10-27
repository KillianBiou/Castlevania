#pragma once
#include <SFML/Graphics.hpp>
#include "Projectile.h"

// Class that represent a projectile that goes follow a sin waves
class SinProjectile : public Projectile
{
private:
	sf::Clock sinClock;

	float amplitude;
	float frequency;
	float speed;

public:
	SinProjectile(sf::Texture spritesheet, int xSize, int ySize, sf::Vector2f position, float speed, float amplitude, float frequency, int nbFrame);

	const void moveTick();
};

