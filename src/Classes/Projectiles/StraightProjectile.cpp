#include "StraightProjectile.h"

StraightProjectile::StraightProjectile(sf::Texture spritesheet, int xSize, int ySize, sf::Vector2f position, float speed, sf::Vector2f targetPos, int nbFrame) : Projectile(spritesheet, xSize, ySize, position, nbFrame) {
	this->speed = speed;

	this->direction = sf::Vector2f(targetPos.x - position.x, targetPos.y - position.y);
	float magnitude = sqrt(direction.x * direction.x + direction.y * direction.y);
	this->direction.x = (direction.x / magnitude) * speed;
	this->direction.y = (direction.y / magnitude) * speed;
	std::cout << "(" << this->direction.x << ", " << this->direction.y << ")\n";
}

const void StraightProjectile::moveTick() {
	this->animate();
	this->move(this->direction);
}