#pragma once
#include <SFML/Graphics.hpp>

class InputManager {
public:
	const void virtual processInput(sf::Event event, sf::RenderTarget* target) = 0;
};