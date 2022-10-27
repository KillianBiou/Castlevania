#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "../Entity/Player.h"

// Class that represent the player's manabar
class ManaBar : public sf::Transformable, public sf::Drawable
{
private:
	sf::Font font;
	Player* player;
	sf::Text text;

	sf::IntRect filledManaRect;
	sf::IntRect emptyManaRect;

	sf::Texture manaTexture;

	std::vector<sf::Sprite> mana;

	void updateMana();

public:
	ManaBar(std::string fontPath);
	// Set the player target to draw the mana
	void setPlayer(Player* player);
	// Update loop
	void update();
	// Render the manabar to the specified render target
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

