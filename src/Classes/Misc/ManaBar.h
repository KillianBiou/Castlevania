#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "../Entity/Player.h"

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
	void setPlayer(Player* player);
	void update();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

