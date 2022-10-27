#pragma once
#include "Monster.h"
#include "../Manager/EntityManager.h"
#include "../Collectible/WeaponUpgrade.h"
#include "../Projectiles/SinProjectile.h"

// Class representing the boss of the first level
class Mummy : public Monster {
private:
	WeaponUpgrade* weaponUpgrade;
	float timeBetweenAttacks;

	sf::Texture projectileTexture;
	bool enraged = false;

	bool bossStarted = false;

	sf::Clock attackClock;

	sf::Vector2f cameraLock;

	sf::Music bossTheme;

	// At half HP, enrage (x2 attack speed)
	void enrage();
	void animate();
	// Go toward player
	void goToward();
	// Trigger music, camera tracking, and spawner deactivation
	void startBoss();

public:
	Mummy(sf::Vector2f pos, float speedFactor, EntityManager* entityManager);
	const void update();

	const sf::Vector2f cameraTracking();

	const void taskDeletion();
	~Mummy();
};
