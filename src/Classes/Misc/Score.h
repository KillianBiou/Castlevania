#pragma once
#include <SFML/graphics.hpp>
#include <iostream>

class Score: public sf::Transformable, public sf::Drawable
{
	sf::Font font;
	sf::Text text;
	int score;

public:
	Score(std::string fontPath);

	void addScore(int amount);

	void update();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	int getScore();
};

