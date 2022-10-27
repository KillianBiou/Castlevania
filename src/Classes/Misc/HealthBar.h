#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "../Entity/Entity.h"

// Class that represent the player's healthbar
class HealthBar: public sf::Transformable, public sf::Drawable
{
private:
	sf::Font font;
	Entity* entity;
	sf::Text text;

	sf::IntRect filledHeartRect;
	sf::IntRect emptyHeartRect;

	sf::Texture heartTexture;

	std::vector<sf::Sprite> hearts;

	void updateHeart();

public:
	HealthBar(std::string fontPath);
	// Set the player target to draw the mana
	void setEntity(Entity* entity);
	// Update loop
	void update();
	// Render the manabar to the specified render target
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

