#pragma once
#include "../Tilemap.h"

enum EntityType;

// Class that represent a level
class Level: public sf::Drawable {
private:
	// Int array representing the level
	const int* levelRaw;
	// Tilemap, with the vertex array of the level
	Tilemap tilemap;
	// The multimap with all the Spawner location for instanciation
	std::multimap<EntityType, sf::Vector2f> entityMap;

	sf::Texture backgroundTexture;
	sf::Sprite backgroundImage;

	const int sizeX;
	const int sizeY;

public:
	Level(const int* level, const int sizeX, const int sizeY, std::multimap<EntityType, sf::Vector2f> entityMap, std::string backgroundImagePath, std::string tilesetPath);
	
	// Render the background image then the tilemap
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	const int* getLevelRaw();
	std::multimap<EntityType, sf::Vector2f>* getEntityMap();
	const int getSizeX();
	const int getSizeY();
};