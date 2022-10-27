#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Audio.hpp>

class Entity;

// Class that represent the player weapon
class Weapon: public sf::Sprite
{
private:
	sf::Texture spritesheet;
	sf::IntRect textureRect;
	sf::Sprite triggerredWeapon;

	sf::SoundBuffer attackSound;

	int damage;
	float timePerAttack;

	int currentPhase;

public:
	Weapon(std::string spritesheetPath, int damage, float timePerAttack, std::string soundPath);

	// The phase system is used to synchronise with the player's animation
	// Frame 1
	void phase0(bool reverse);
	// Frame 2
	void phase1(bool reverse);
	// Frame 3
	void phase2(bool reverse);
	// Frame 4
	void phase3(bool reverse);
	// Attack finished, no drawing
	void phase4(bool reverse);

	int getCurrentPhase();
	int getDamage();
	float getTimePerAttack();
	sf::SoundBuffer* getAttackSound();
};

