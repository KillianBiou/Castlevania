#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "../Entity/Entity.h"

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
	HealthBar(std::string fontPath, Entity* entity);
	void update();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

