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

	sf::Clock attackClock;

public:
	Mummy(sf::Vector2f pos, const int* currentLevel, const int levelXSize, float speedFactor, EntityManager* entityManager);
	const void update();
	void goToward();

	void animate();

	const void taskDeletion();
	~Mummy();
};
