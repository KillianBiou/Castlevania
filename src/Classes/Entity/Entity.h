#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

class EntityManager;
class GameManager;
class Animator;

// An enumeration that list all the possible movement direction
enum MoveDirection
{
	NONE = 0,
	LEFT = -1,
	RIGHT = 1,
	UP = -1,
	DOWN = 1
};

// An abstract class representing an Entity
// <!> Contains a lot of outdated code
class Entity: public sf::Sprite
{
protected:
	int maxHp;
	int hp;
	std::string name;

	int spriteSizeX;
	int spriteSizeY;
	int spriteSizeXAttack1;
	int spriteSizeYAttack1;
	int spriteSizeXAttack2;
	int spriteSizeYAttack2;

	sf::Vector2f groundedPoint;
	sf::Vector2f groundedPointBis;
	sf::Vector2f rightBoundPoint;
	sf::Vector2f rightBoundPointBis;
	sf::Vector2f rightBoundPointPrime;
	sf::Vector2f leftBoundPoint;
	sf::Vector2f leftBoundPointBis;
	sf::Vector2f leftBoundPointPrime;
	sf::Vector2f topBoundPoint;
	sf::Vector2f topBoundPointBis;
	sf::Vector2f debugPoint;

	MoveDirection moveDirection;
	MoveDirection side;

	float timePerAttack;

	bool blockageRight;
	bool blockageLeft;

	bool toBeDeleted;
	int scoreOnDeath;

	int manaOnDeath = 1;

	float verticalVelocity;
	float speedFactor;
	float jumpFactor;
	float gravityFactor;

	bool isGrounded;
	bool freeze;
	bool isAttack;
	bool isHurt;
	bool affectedByGravity;

	bool dead = false;

	EntityManager* entityManager;

	sf::Texture texture;
	sf::IntRect textureRect;

	Animator* animator;
	int frameDelay;

	sf::SoundBuffer hitSound;
	sf::SoundBuffer deathSound;

	// Function
	void applyGravity();
	void checkCollision();
	void moveTick();
	void die();
	void playSfx(sf::SoundBuffer* sound);

public:
	Entity(std::string texturePath, sf::Vector2f position, int sizeX, int sizeY, int frameDelay, 
		float speedFactor, float jumpFactor, EntityManager* entityManager);

	// Update loop
	void updateAll();
	// Move the collision point
	void moveCollisionPoint();

	virtual void const attack(bool advance) = 0;
	// Inflict the given amount of damage
	void takeDamage(int amount);
	virtual const sf::Vector2f cameraTracking() = 0;
	// Red flickering when taking damage
	void damageFlicker();

	int getSpriteSizeX();
	int getSpriteSizeY();
	int getSpriteSizeXAttack1();
	int getSpriteSizeYAttack1();
	int getSpriteSizeXAttack2();
	int getSpriteSizeYAttack2();

	int getHp();
	int getMaxHp();

	float getTimePerAttack();

	// Accesseur
	void setIsGrounded(bool state);
	void setVerticalMovement(MoveDirection direction);
	void setHorizontalMovement(MoveDirection direction);
	MoveDirection getSide();
	MoveDirection getMoveDirection();
	sf::Vector2f getGroundedPoint();
	sf::Vector2f getGroundedPointBis();
	sf::Vector2f getRightBoundPoint();
	sf::Vector2f getRightBoundPointBis();
	sf::Vector2f getRightBoundPointPrime();
	sf::Vector2f getLeftBoundPoint();
	sf::Vector2f getLeftBoundPointBis();
	sf::Vector2f getLeftBoundPointPrime();
	sf::Vector2f getTopBoundPoint();
	sf::Vector2f getTopBoundPointBis();
	bool getFreeze();
	std::string getName();
	virtual const void taskDeletion() = 0;

	~Entity();
};

