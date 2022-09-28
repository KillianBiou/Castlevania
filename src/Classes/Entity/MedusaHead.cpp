#include "MedusaHead.h"

MedusaHead::MedusaHead(std::string name, sf::Vector2f pos, int frameDelay, const int* currentLevel, const int levelXSize, float speedFactor, float jumpFactor, EntityManager* entityManager) : Monster("images/MedusaHead.png", pos, 64, 64, "Medusa", frameDelay, currentLevel, levelXSize, speedFactor, jumpFactor, entityManager) {
	this->affectedByGravity = false;
}