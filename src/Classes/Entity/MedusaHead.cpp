#include "MedusaHead.h"
#include "../Manager/EntityManager.h"

MedusaHead::MedusaHead(std::string name, sf::Vector2f pos, const int* currentLevel, const int levelXSize, float speedFactor, float amplitude, float frequency, EntityManager* entityManager, Spawner* spawner) : Monster("images/MedusaHead.png", pos, 64, 64, "Medusa", 100000, currentLevel, levelXSize, speedFactor, 0, entityManager, spawner), amplitude(amplitude), frequency(frequency) {
	this->affectedByGravity = false;
	this->hp = 1;
	this->animator->setAnimations({ {IDLE, 1}, {DEATH, 0} });

	this->scoreOnDeath = 50;

	this->sinClock = sf::Clock();
	this->deathSound.loadFromFile("sfx/medusaDeath.wav");
}

const void MedusaHead::update() {
	this->move(-this->speedFactor, std::sin(this->sinClock.getElapsedTime().asSeconds() * this->frequency) * this->amplitude);
	this->animator->animate();
}