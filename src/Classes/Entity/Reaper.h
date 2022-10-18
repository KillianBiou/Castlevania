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

	sf::Vector2f cameraLock;

	sf::Vector2f movementVector;

	bool bossStarted;

	float timeBetweenAttacks;

	sf::Music bossTheme;

	void animate();
	void moveBoundary();
	void moveTick();
	void checkCollision();
	void startBoss();

public:
	Reaper(sf::Vector2f pos, float speedFactor, EntityManager* entityManager);

	const void update();
	const void taskDeletion();
	const sf::Vector2f cameraTracking();
	
	~Reaper();
};