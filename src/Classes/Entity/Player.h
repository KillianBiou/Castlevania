#pragma once
#include "Entity.h"
#include "../Misc/Weapon.h"
#include "../Projectiles/StraightProjectile.h"
#include "../Projectiles/ParabolicProjectile.h"

// Class representing the player
class Player: public Entity
{
private:
	Weapon* weapon;
	sf::Texture knifeTexture;
	sf::Texture axeTexture;

	int manaMax;
	int mana;

	bool isAttacking;
	sf::RectangleShape hitboxWeapon;
	sf::Clock invulnerabilityClock;
	sf::Clock specialClock;
	int specialCooldown = 500;

	float invulnerabilityTime;

	std::string debugAnim;

	sf::Vector2f weaponPositionModifier = sf::Vector2f(0.f, 0.f);

	bool dead = false;

	std::vector<Entity*> alreadyHit;

	sf::SoundBuffer jumpSound;

	void updateHitboxWeapon();
	void die();

public:
	Player(sf::Vector2f pos, int frameDelay, float speedFactor, float jumpFactor, EntityManager* entityManager);
	void const drawChild(sf::RenderTarget* renderTarget);
	
	// Update loop
	void update();

	// Animation checking
	void updateAnim();

	void const attack(bool advance);
	void const taskDeletion();
	void takeDamage(int amount);
	void jump();
	
	// Special attacks
	void specialOne();
	void specialTwo();

	void addHp(int amount);
	void addMaxHp(int amount);

	void addMana(int amount);

	void setMaxHp(int amount);

	const sf::Vector2f cameraTracking();

	void changeWeapon(Weapon* weapon);
	void triggerEnd();

	Weapon* getWeapon();
	EntityManager* getEntityManager();
	sf::RectangleShape gethitboxWeapon();

	int getMana();
	int getMaxMana();

	bool isInvulnerable();
};

