#pragma once
#include "Monster.h"
#include "../Manager/EntityManager.h"
#include "../Collectible/WeaponUpgrade.h"
#include "../Projectiles/StraightProjectile.h"

// Class representing the boss of the first level
class Reaper : public Monster {
private:
	sf::Texture projectileTexture;
	WeaponUpgrade* weaponUpgrade;

	sf::Clock attackClock;
	sf::Clock touchdownCooldown;

	sf::Vector2f cameraLock;

	sf::Vector2f movementVector;

	sf::Vector2f scytheV1;
	sf::Vector2f scytheV2;

	bool bossStarted;
	bool firstAttack = true;

	float timeBetweenAttacks;

	sf::Music bossTheme;

	void animate();
	void moveTick();
	// Check for screen border collision
	void checkCollision();
	// Trigger music, camera tracking, and spawner deactivation
	void startBoss();

public:
	Reaper(sf::Vector2f pos, float speedFactor, EntityManager* entityManager);

	const void update();
	const void taskDeletion();
	const sf::Vector2f cameraTracking();
	
	~Reaper();
};