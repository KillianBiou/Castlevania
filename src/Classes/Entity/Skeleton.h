#pragma once
#include "Monster.h"
#include "../Manager/EntityManager.h"
#include "../Projectiles/Projectile.h"


class Skeleton: public Monster
{
private:
	float targetDistToPlayer;
	sf::Vector2f positionTarget;
	sf::Clock attackClock;
	int attackCooldown;

	sf::Texture boneTexture;
	Projectile* currentProjectile;

	void attack();
	void goToward();
public:
	Skeleton(sf::Vector2f pos, const int* currentLevel, const int levelXSize, float speedFactor, float targetDistToPlayer, int attackCooldown, EntityManager* entityManager, Spawner* spawner);
	void update();
	void animate();
};

