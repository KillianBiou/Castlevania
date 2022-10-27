#pragma once
#include "../Entity/Player.h"
#include <SFML/Graphics.hpp>
#include <iostream>

// Abstract class that represent a collectible
class Collectible: public sf::Sprite
{
protected:
	sf::Texture texture;
	sf::Vector2f groundedPoint1;
	sf::Vector2f groundedPoint2;

	const int* level;
	const int X_SIZE;

	sf::SoundBuffer pickupSound;

	bool isGrounded = false;

	void moveGroundedPoint();
	void checkGrounded();
	void moveTick();

public:
	Collectible(std::string texturePath, sf::IntRect textureRect, const int* level, const int X_SIZE);
	// Update loop
	void update();

	// Virtual function that execute code when picked by player
	virtual const void onPickup(Player* player) = 0;
};

