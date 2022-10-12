#pragma once
#include "../Tilemap.h"

class Level: public sf::Drawable {
private:
	const int* levelRaw;
	Tilemap tilemap;

	sf::Texture backgroundTexture;
	sf::Sprite backgroundImage;

	const int sizeX;
	const int sizeY;

public:
	Level(const int* level, const int sizeX, const int sizeY, std::string backgroundImagePath);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	const int* getLevelRaw();
	const int getSizeX();
	const int getSizeY();
};