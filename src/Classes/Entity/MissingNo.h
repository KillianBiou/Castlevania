#pragma once
#include "Monster.h"
#include "../Manager/EntityManager.h"
#include "../Collectible/WeaponUpgrade.h"
#include "../Projectiles/StraightProjectile.h"

class MissingNo : public Monster {
private:
	sf::Texture projectileTexture;
	WeaponUpgrade* weaponUpgrade;

	sf::Clock attackClock;
	sf::Clock touchdownCooldown;

	sf::Vector2f cameraLock;

	sf::Vector2f movementVector;

	sf::Vector2f scytheV1;
	sf::Vector2f scytheV2;
	sf::Vector2f scytheV3;
	sf::Vector2f scytheV4;
	sf::Vector2f scytheV5;
	sf::Vector2f scytheV6;

	bool bossStarted;
	bool firstAttack = true;

	float timeBetweenAttacks;

	sf::Music bossTheme;

	void animate();
	void moveBoundary();
	void moveTick();
	void checkCollision();
	void startBoss();

public:
	MissingNo(sf::Vector2f pos, float speedFactor, EntityManager* entityManager);

	const void update();
	const void taskDeletion();
	const sf::Vector2f cameraTracking();

	~MissingNo();
};