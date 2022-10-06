#pragma once
#include "Monster.h"
#include "../Manager/EntityManager.h"
#include "../Collectible/WeaponUpgrade.h"
#include "../Projectiles/SinProjectile.h"

class Mummy : public Monster {
private:
	WeaponUpgrade* weaponUpgrade;
	float timeBetweenAttacks;

	sf::Texture projectileTexture;
	bool enraged = false;

	sf::Clock attackClock;

	void enrage();
	void animate();
	void goToward();

public:
	Mummy(sf::Vector2f pos, const int* currentLevel, const int levelXSize, float speedFactor, EntityManager* entityManager);
	const void update();

	const void taskDeletion();
	~Mummy();
};
