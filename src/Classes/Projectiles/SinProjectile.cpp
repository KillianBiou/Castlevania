#include "SinProjectile.h"

SinProjectile::SinProjectile(sf::Texture spritesheet, int xSize, int ySize, sf::Vector2f position, float speed, float amplitude, float frequency, int nbFrame) : Projectile(spritesheet, xSize, ySize, position, nbFrame) {
	this->amplitude = amplitude;
	this->frequency = frequency;
	this->speed = speed;

	this->sinClock = sf::Clock();
}

const void SinProjectile::moveTick() {
	// Move along the sin wave
	this->move(this->speed, std::sin(this->sinClock.getElapsedTime().asSeconds() * this->frequency) * this->amplitude);
}