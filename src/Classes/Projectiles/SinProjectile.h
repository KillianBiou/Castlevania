#pragma once
#include <SFML/Graphics.hpp>
#include "Projectile.h"

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

