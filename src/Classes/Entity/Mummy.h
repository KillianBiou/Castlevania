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

	bool bossStarted = false;

	sf::Clock attackClock;

	sf::Vector2f cameraLock;

	void enrage();
	void animate();
	void goToward();
	void startBoss();

public:
	Mummy(sf::Vector2f pos, const int* currentLevel, const int levelXSize, float speedFactor, EntityManager* entityManager);
	const void update();

	const sf::Vector2f cameraTracking();

	const void taskDeletion();
	~Mummy();
};
