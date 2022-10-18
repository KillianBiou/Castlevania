#include "Level.h"
#include "EntityFactory.h";

Level::Level(const int* level, const int sizeX, const int sizeY, std::multimap<EntityType, sf::Vector2f> entityMap, std::string backgroundImagePath) : levelRaw(level), sizeX(sizeX), sizeY(sizeY), entityMap(entityMap) {
	this->tilemap = Tilemap();
	this->tilemap.load("images/Platform.png", 64, level, sizeX, sizeY);

	if (!this->backgroundTexture.loadFromFile(backgroundImagePath)) {
		std::cout << "Error while loading : " << backgroundImagePath << std::endl;
	}
	this->backgroundImage = sf::Sprite();
	backgroundImage.setTexture(backgroundTexture);
	backgroundImage.setPosition(0.f, 64.f);

}

void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->backgroundImage);
	target.draw(this->tilemap);
}

const int Level::getSizeX() {
	return this->sizeX;
}

const int Level::getSizeY() {
	return this->sizeY;
}

const int* Level::getLevelRaw() {
	return this->levelRaw;
}

std::multimap<EntityType, sf::Vector2f>* Level::getEntityMap() {
	return &this->entityMap;
}