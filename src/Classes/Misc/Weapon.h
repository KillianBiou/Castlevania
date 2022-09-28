#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Entity;

class Weapon: public sf::Sprite
{
private:
	sf::Texture spritesheet;
	sf::IntRect textureRect;
	sf::Sprite triggerredWeapon;

	int damage;

	int currentPhase;

public:
	Weapon(std::string spritesheetPath, int damage);

	void phase0(bool reverse);
	void phase1(bool reverse);
	void phase2(bool reverse);
	void phase3(bool reverse);

	int getCurrentPhase();
	int getDamage();
};

