#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "InputManager.h"

class MenuManager: public InputManager {
private:
	int currentPosision = 0;
	int maxPosition = 2;
	int currentOpacity = 255;

	sf::Texture cursorTexture;
	sf::Texture backgroundTexture;
	sf::Sprite cursorSprite;
	sf::Sprite backgroundImage;

	sf::Texture thunderTexture;
	sf::Sprite thunderEffect;

	sf::Font font;

	sf::Music music;
	sf::SoundBuffer thunderBuffer;
	sf::Sound thunder;

	std::map<int, sf::Vector2f> cursorMap;

	sf::Text playButton;
	sf::Text selectLevel;
	sf::Text exitButton;

	sf::Color currentColor;
	sf::Clock* fadeOutClock;
	bool stopFadeOut = false;
	bool blockInput = false;

	void processSelection(sf::RenderTarget* renderTarget);

public:
	MenuManager(std::string test);

	bool update(sf::RenderTarget* renderTarget);
	void draw(sf::RenderTarget* renderTarget);
	const void processInput(sf::Event event, sf::RenderTarget* target);
};