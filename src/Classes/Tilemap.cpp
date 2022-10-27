#include "Tilemap.h"


void Tilemap::load(std::string tilesetPath, int tileSize, const int* map, const int numberXTiles, const int numberYTiles) {

	if (!this->tileset.loadFromFile(tilesetPath)) {
		std::cout << "Error while loading : " << tilesetPath << std::endl;
		return;
	}

	this->vArray.setPrimitiveType(sf::Quads);
	this->vArray.resize(numberXTiles * numberYTiles * 4);

	// Fill the vertex array with the corresponding quad texture corresponding to the ID of the block
	for (int x = 0; x < numberXTiles; x++) {
		for (int y = 0; y < numberYTiles; y++) {
			int currentMapPosition = map[x + y * numberXTiles];

			int tilesetXCoordinate = currentMapPosition % (this->tileset.getSize().x / tileSize);
			int tilesetYCoordinate = currentMapPosition / (this->tileset.getSize().x / tileSize);

			sf::Vertex* quad = &this->vArray[(x + y * numberXTiles) * 4];

			quad[0].position = sf::Vector2f(x * tileSize, y * tileSize);
			quad[1].position = sf::Vector2f((x + 1) * tileSize, y * tileSize);
			quad[2].position = sf::Vector2f((x + 1) * tileSize, (y + 1) * tileSize);
			quad[3].position = sf::Vector2f(x * tileSize, (y + 1) * tileSize);

			quad[0].texCoords = sf::Vector2f(tilesetXCoordinate * tileSize, tilesetYCoordinate * tileSize);
			quad[1].texCoords = sf::Vector2f((tilesetXCoordinate + 1) * tileSize, tilesetYCoordinate * tileSize);
			quad[2].texCoords = sf::Vector2f((tilesetXCoordinate + 1) * tileSize, (tilesetYCoordinate + 1) * tileSize);
			quad[3].texCoords = sf::Vector2f(tilesetXCoordinate * tileSize, (tilesetYCoordinate + 1) * tileSize);
		}
	}
}

void Tilemap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the tileset texture
	states.texture = &this->tileset;

	// draw the vertex array
	target.draw(this->vArray, states);
}

sf::VertexArray* Tilemap::getVertexArray() {
	return &this->vArray;
}