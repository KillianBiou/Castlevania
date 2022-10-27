#include "Animator.h"

Animator::Animator(Entity* entity, int frameDelay): frameDelay(frameDelay) {
	this->entity = entity;
	this->nbFrame = nbFrame;

	this->animationClock = sf::Clock();
	this->currentFrame = 0;

	this->spriteRect = sf::IntRect(0, 0, entity->getSpriteSizeX(), entity->getSpriteSizeY());
	this->entity->setTextureRect(this->spriteRect);
	this->lock = false;
	this->isDead = false;
}

void Animator::animate() {
	// Fetch the frame to display
	int nextFrame = this->animationClock.getElapsedTime().asMilliseconds() / (this->currentAnimation == ATTACK ? this->entity->getTimePerAttack() / 4 : this->frameDelay);

	// If we reach the end of the animation 
	if (nextFrame >= this->nbFrame[this->currentAnimation]) {
		// Restart from the beginning
		this->currentFrame = 0;
		this->spriteRect.left = 0;
		this->animationClock.restart();
		// Indicate to trigger an attack
		if (this->currentAnimation == ATTACK) {
			this->entity->attack(true);
		}
		// Flicker in red for player feedback
		if (this->currentAnimation == HURT) {
			this->entity->damageFlicker();
		}
		// Kill the entity
		if (this->currentAnimation == DEATH) {
			this->entity->taskDeletion();
			this->isDead = true;
		}
	}
	// If we are on a new frame, draw it
	else if (nextFrame != this->currentFrame) {
		this->currentFrame = nextFrame;
		this->spriteRect.left = this->currentFrame * this->entity->getSpriteSizeX();
		// Advance in phase for the player's attack
		if (this->currentAnimation == ATTACK) {
			this->entity->attack(true);
		}
		if (this->currentAnimation == DEATH && (nextFrame == 2 || nextFrame == 3)) {
			this->spriteRect.width = this->entity->getSpriteSizeX() * 2;
			if (nextFrame == 3) {
				this->spriteRect.left += this->entity->getSpriteSizeX();
			}
		}
	}
	if (!this->isDead) {
		this->entity->setTextureRect(this->spriteRect);
	}
}

void Animator::playAnimation(Animation animation) {
	// Play the animation only if it is available for the current entity
	if (animation != this->currentAnimation && !(this->nbFrame.find(animation) == this->nbFrame.end())) {
		this->animationClock.restart();
		this->currentAnimation = animation;
		this->spriteRect.top = this->entity->getSpriteSizeY() * this->currentAnimation;
		this->spriteRect.left =  0;
		this->spriteRect.width = this->entity->getSpriteSizeX();
	}
}

void Animator::setAnimations(std::map<Animation, int> nbFrame) {
	this->nbFrame = nbFrame;
}

void Animator::lockAnimation(bool state) {
	this->lock = state;
}

Animation Animator::getCurrentAnimation() {
	return this->currentAnimation;
}