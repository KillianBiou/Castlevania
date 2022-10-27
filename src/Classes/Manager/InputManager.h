#pragma once
#include <SFML/Graphics.hpp>

// Interface that represent a class that can take input from user
class InputManager {
public:
	// Process an event with the given render target in case
	const void virtual processInput(sf::Event event, sf::RenderTarget* target) = 0;
};