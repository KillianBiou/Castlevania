#pragma once
#include <SFML/graphics.hpp>
#include <iostream>

// Class responsible for score tracking and drawing
class Score: public sf::Transformable, public sf::Drawable
{
	sf::Font font;
	sf::Text text;
	int score;

public:
	Score(std::string fontPath);

	// Add the specified amount to the score
	void addScore(int amount);

	void update();
	// Draw the score to the specified render target
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	int getScore();
};

