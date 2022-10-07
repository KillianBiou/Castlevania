#include "StraightProjectile.h"

StraightProjectile::StraightProjectile(sf::Texture spritesheet, int xSize, int ySize, sf::Vector2f position, float speed, int nbFrame) : Projectile(spritesheet, xSize, ySize, position, nbFrame) {
	this->speed = speed;
}

const void StraightProjectile::moveTick() {
	this->animate();
}