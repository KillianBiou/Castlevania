#pragma once
#include "../Entity/Player.h"

// Enumeration that list all the possible animation (Indicate their line in the spritesheet too)
enum Animation {
	IDLE = 0,
	RUNNING = 1,
	JUMPING = 2,
	ATTACK = 3,
	HURT = 4,
	DEATH = 5
}; 

// Class that is responsible of animating an Entity
class Animator
{
private:
	std::map<Animation, int> nbFrame = { {IDLE, 1} };

	Entity* entity;
	sf::Clock animationClock;
	Animation currentAnimation;
	int currentFrame;
	int frameDelay;
	sf::IntRect spriteRect;

	bool isDead;
	bool lock;

public:
	Animator(Entity* entity, int frameDelay);

	// Set the number of frame per animation
	void setAnimations(std::map<Animation, int> nbFrame);

	// Animation loop
	void animate();
	// Play a given animation
	void playAnimation(Animation animation);
	// Outdated ? 
	void lockAnimation(bool state);

	Animation getCurrentAnimation();
};

