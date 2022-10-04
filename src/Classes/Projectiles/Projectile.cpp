#include "Projectile.h"

Projectile::Projectile(sf::Texture spritesheet, int xSize, int ySize, sf::Vector2f position, float gravity, float distance, int nbFrame) : spritesheet(spritesheet), nbFrame(nbFrame), xSize(xSize), ySize(ySize) {
	this->setPosition(position);
	this->setTexture(this->spritesheet);
	this->textureRect = sf::IntRect(0, 0, xSize, ySize);

	this->gravity = gravity;
	this->distance = distance;

	this->yVelocity = -this->gravity * 35;
	this->frameToGround = (2 * this->yVelocity) / this->gravity;
	this->xVelocity = -(this->distance / this->frameToGround);
}

void Projectile::update() {
	this->animate();
	this->moveTick();
}

void Projectile::moveTick() {
	this->move(xVelocity, yVelocity);
	this->yVelocity += gravity;
}

void Projectile::animate() {
	if (this->animationClock.getElapsedTime().asMilliseconds() > 100) {
		if (this->textureRect.left == (this->nbFrame - 1) * this->xSize) {
			this->textureRect.left = 0;
		}
		else {
			this->textureRect.left += this->xSize;
		}
		this->animationClock.restart();
	}

	this->setTextureRect(this->textureRect);
}

Projectile::~Projectile() {
	std::cout << "destroyed" << std::endl;
}