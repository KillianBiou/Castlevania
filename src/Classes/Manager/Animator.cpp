#include "Animator.h"

Animator::Animator(Entity* entity, int frameDelay): frameDelay(frameDelay) {
	this->entity = entity;
	this->nbFrame = nbFrame;

	this->animationClock = sf::Clock();
	this->currentAnimation = IDLE;
	this->currentFrame = 0;

	this->spriteRect = sf::IntRect(0, entity->getSpriteSizeY(), entity->getSpriteSizeX(), entity->getSpriteSizeY());
	this->entity->setTextureRect(this->spriteRect);
	this->lock = false;
	this->isDead = false;
}

void Animator::animate() {
	int nextFrame = this->animationClock.getElapsedTime().asMilliseconds() / (this->currentAnimation == ATTACK ? this->entity->getTimePerAttack() / 3 : this->frameDelay);

	if (nextFrame >= this->nbFrame[this->currentAnimation]) {

		this->currentFrame = 0;
		this->spriteRect.left = 0;
		this->animationClock.restart();
		if (this->currentAnimation == ATTACK) {
			this->entity->attack(true);
		}
		if (this->currentAnimation == HURT) {
			this->entity->damageFlicker();
		}
		if (this->currentAnimation == DEATH) {
			this->entity->taskDeletion();
			this->isDead = true;
		}
	}
	else if (nextFrame != this->currentFrame) {
		this->currentFrame = nextFrame;
		this->spriteRect.left = this->currentFrame * this->entity->getSpriteSizeX();
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

	//std::cout << this->spriteRect.width << ", " << this->spriteRect.left << std::endl;
	if (!this->isDead) {
		this->entity->setTextureRect(this->spriteRect);
	}
}

void Animator::playAnimation(Animation animation) {
	//std::cout << animation << std::endl;
	if (animation != this->currentAnimation) {
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