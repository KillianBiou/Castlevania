#pragma once
#include <SFML/Graphics.hpp>
#include "../Manager/Animator.h"
class Projectile : public sf::Sprite
{
private:
	int nbFrame;

	float xVelocity;
	float yVelocity;
	float gravity;
	float distance;
	int frameToGround;

	int xSize;
	int ySize;
	
	sf::Texture spritesheet;
	sf::Clock animationClock;
	sf::IntRect textureRect;

public:
	Projectile(sf::Texture spritesheet, int xSize, int ySize, sf::Vector2f position, float gravity, float distance, int nbFrame);

	void update();
	void moveTick();
	void animate();

	~Projectile();
};

