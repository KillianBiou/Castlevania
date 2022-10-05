#pragma once
#include "../Entity/Player.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Collectible: public sf::Sprite
{
private:
	sf::Texture texture;
	sf::Vector2f groundedPoint1;
	sf::Vector2f groundedPoint2;

	const int* level;
	const int X_SIZE;

	bool isGrounded = false;

	void moveGroundedPoint();
	void checkGrounded();
	void moveTick();

public:
	Collectible(std::string texturePath, sf::IntRect textureRect, const int* level, const int X_SIZE);
	void update();

	virtual const void onPickup(Player* player) = 0;
};

