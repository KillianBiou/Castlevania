#pragma once
#include "../Tilemap.h"

enum EntityType;

class Level: public sf::Drawable {
private:
	const int* levelRaw;
	Tilemap tilemap;
	std::multimap<EntityType, sf::Vector2f> entityMap;

	sf::Texture backgroundTexture;
	sf::Sprite backgroundImage;

	const int sizeX;
	const int sizeY;

public:
	Level(const int* level, const int sizeX, const int sizeY, std::multimap<EntityType, sf::Vector2f> entityMap, std::string backgroundImagePath, std::string tilesetPath);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	const int* getLevelRaw();
	std::multimap<EntityType, sf::Vector2f>* getEntityMap();
	const int getSizeX();
	const int getSizeY();
};