#pragma once
#include "Monster.h"
#include "../Manager/EntityManager.h"
#include "../Projectiles/ParabolicProjectile.h"

// Class represeting a skeleton
class Skeleton: public Monster
{
private:
	float targetDistToPlayer;
	sf::Vector2f positionTarget;
	sf::Clock attackClock;
	int attackCooldown;

	bool canGoLeft = true;
	bool canGoRight = true;

	sf::Texture boneTexture;
	Projectile* currentProjectile;

	void attack();
	void goToward();
public:
	Skeleton(sf::Vector2f pos, float speedFactor, float targetDistToPlayer, int attackCooldown, EntityManager* entityManager, Spawner* spawner);
	
	void const update();
	
	void animate();
};

