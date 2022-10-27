#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Projectile : public sf::Sprite
{
protected:
	int nbFrame;

	int xSize;
	int ySize;
	
	sf::Texture spritesheet;
	sf::Clock animationClock;
	sf::IntRect textureRect;

public:
	Projectile(sf::Texture spritesheet, int xSize, int ySize, sf::Vector2f position, int nbFrame);

	// Update loop
	const void update();
	// The logic for the projectile movement
	virtual const void moveTick() = 0;
	// The animator
	const void animate();
};

