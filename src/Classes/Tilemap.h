#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

// Class that represent one level drawable with a given tileset
class Tilemap : public sf::Drawable
{
private:
	sf::Texture tileset;
	// Vertex array
	sf::VertexArray vArray;

public:
	// Load and instanciate a tilemap with a raw array and a tileset
	void load(std::string tilesetPath, int tileSize, const int* map, const int numberXTiles, const int numberYTiles);
	// Draw the vertex array with a render target
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::VertexArray* getVertexArray();
};

