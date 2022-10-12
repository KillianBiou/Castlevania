#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Tilemap : public sf::Drawable
{
private:
	sf::Texture tileset;
	sf::VertexArray vArray;

public:
	void load(std::string tilesetPath, int tileSize, const int* map, const int numberXTiles, const int numberYTiles);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::VertexArray* getVertexArray();
};

