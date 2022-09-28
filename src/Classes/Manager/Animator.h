#pragma once
#include "../Entity/Player.h"

enum Animation {
	IDLE = 0,
	RUNNING = 1,
	JUMPING = 2,
	ATTACK = 3,
	HURT = 4,
	DEATH = 5
}; 

class Animator
{
private:
	std::map<Animation, int> nbFrame = { {IDLE, 1}, {RUNNING, 3}, {JUMPING, 1}, {ATTACK, 3}, {HURT, 2}, {DEATH, 4} };

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

	void animate();
	void playAnimation(Animation animation);
	void lockAnimation(bool state);

	Animation getCurrentAnimation();
};

