#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <list>
#include <numeric>
#include <SFML/Window/Keyboard.hpp>
#include "InputManager.h"

class GameMaster;
enum LevelId;

// Class that represent the main menu
class MenuManager: public InputManager {
private:
	GameMaster* gameMaster;

	int currentPosition = 0;
	int maxPosition = 2;
	int currentTutorial = 0;
	int currentOpacity = 255;

	bool end = false;

	// Easter egg tracker (Hint : Konami code)
	std::list<sf::Keyboard::Key> inputBuffer;

	LevelId exitCode;

	sf::Texture cursorTexture;
	sf::Texture backgroundTexture;
	sf::Texture lvl1Texture;
	sf::Texture lvl2Texture;
	sf::Sprite cursorSprite;
	sf::Sprite backgroundImage;

	sf::Sprite lvl1Image;
	sf::Sprite lvl2Image;

	sf::Text lvl1Description;
	sf::Text lvl2Description;

	sf::Texture tuto1Texture;
	sf::Texture tuto2Texture;
	sf::Texture tuto3Texture;

	sf::Sprite tuto1Sprite;
	sf::Sprite tuto2Sprite;
	sf::Sprite tuto3Sprite;

	sf::Texture thunderTexture;
	sf::Sprite thunderEffect;

	sf::Font font;

	sf::Music music;
	sf::SoundBuffer thunderBuffer;
	sf::SoundBuffer evilLaught;
	sf::Sound thunder;
	sf::Sound evilLaughtS;

	std::map<int, sf::Vector2f> cursorMap;
	std::map<int, sf::Vector2f> cursorMapLevelS;

	sf::Text playButton;
	sf::Text selectLevel;
	sf::Text exitButton;

	sf::Text backButton;

	sf::Color currentColor;
	sf::Color thunderColor;
	sf::Clock* fadeOutClock;
	
	bool stopFadeOut = false;
	bool blockInput = false;
	bool levelSelection = false;

	// Process the selection according to current state
	void processSelection(sf::RenderTarget* renderTarget);
	// Trigger the easter egg's function
	void konamiCode();
	// Exit main menu and start the game
	void exit();

public:
	MenuManager(GameMaster* gameMaster);

	// Update loop
	bool update(sf::RenderTarget* renderTarget);
	// Render all the sprite with the specified render target
	void draw(sf::RenderTarget* renderTarget);

	// Maybe outdated, note sure 
	void reset();
	
	// Override to process the keyboard input
	const void processInput(sf::Event event, sf::RenderTarget* target);
};