#include "Projectile.h"

Projectile::Projectile(sf::Texture spritesheet, int xSize, int ySize, sf::Vector2f position, int nbFrame) : spritesheet(spritesheet), nbFrame(nbFrame), xSize(xSize), ySize(ySize) {
	this->setPosition(position);
	this->setTexture(this->spritesheet);
	this->textureRect = sf::IntRect(0, 0, xSize, ySize);
}

const void Projectile::update() {
	this->animate();
	this->moveTick();
}

const void Projectile::animate() {
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