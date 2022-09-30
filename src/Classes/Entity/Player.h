#pragma once
#include "Entity.h"
#include "../Misc/Weapon.h"

class Player: public Entity
{
private:
	Weapon* weapon;
	bool isAttacking;
	sf::RectangleShape hitboxWeapon;
	sf::Clock invulnerabilityClock;

	float invulnerabilityTime;

	std::string debugAnim;

	sf::Vector2f weaponPositionModifier = sf::Vector2f(0.f, 0.f);

	bool dead = false;

	void updateHitboxWeapon();

public:
	Player(std::string texturePath, sf::Vector2f pos, int frameDelay, const int* currentLevel, const int levelXSize, float speedFactor, float jumpFactor, EntityManager* entityManager);
	void const drawChild(sf::RenderWindow* renderWindow);
	void update();

	void updateAnim();

	void const attack(bool advance);
	void const taskDeletion();
	void takeDamage(int amount);

	Weapon* getWeapon();
	sf::RectangleShape gethitboxWeapon();
	bool isInvulnerable();
};

