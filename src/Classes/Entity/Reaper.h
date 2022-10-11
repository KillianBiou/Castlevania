#pragma once
#include "Monster.h"
#include "../Manager/EntityManager.h"
#include "../Collectible/WeaponUpgrade.h"
#include "../Projectiles/StraightProjectile.h"

class Reaper : public Monster {
private:
	sf::Texture projectileTexture;
	WeaponUpgrade* weaponUpgrade;

	sf::Clock attackClock;
	sf::Clock touchdownCooldown;

	sf::Vector2f movementVector;

	float timeBetweenAttacks;

	void animate();
	void moveBoundary();
	void moveTick();
	void checkCollision();

public:
	Reaper(sf::Vector2f pos, const int* currentLevel, const int levelXSize, float speedFactor, EntityManager* entityManager);

	const void update();
	const void taskDeletion();
	~Reaper();
};