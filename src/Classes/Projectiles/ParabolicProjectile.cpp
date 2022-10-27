#include "ParabolicProjectile.h"

ParabolicProjectile::ParabolicProjectile(sf::Texture spritesheet, int xSize, int ySize, sf::Vector2f position, float gravity, float distance, int nbFrame) : Projectile(spritesheet, xSize, ySize, position, nbFrame) {
	this->setPosition(position);
	this->setTexture(this->spritesheet);
	this->textureRect = sf::IntRect(0, 0, xSize, ySize);

	this->gravity = gravity;
	this->distance = distance;

	// Calculation of the necessary velocity to reach target a y = 0
	this->yVelocity = -this->gravity * 35;
	this->frameToGround = (2 * this->yVelocity) / this->gravity;
	this->xVelocity = -(this->distance / this->frameToGround);
}

const void ParabolicProjectile::moveTick() {
	this->move(xVelocity, yVelocity);
	// Applying gravity
	this->yVelocity += gravity;
}