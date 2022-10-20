#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "InputManager.h"

class GameMaster;
enum LevelId;


class MenuManager: public InputManager {
private:
	GameMaster* gameMaster;

	int currentPosition = 0;
	int maxPosition = 2;
	int currentOpacity = 255;

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
	sf::Sound thunder;

	std::map<int, sf::Vector2f> cursorMap;
	std::map<int, sf::Vector2f> cursorMapLevelS;

	sf::Text playButton;
	sf::Text selectLevel;
	sf::Text exitButton;

	sf::Text backButton;

	sf::Color currentColor;
	sf::Clock* fadeOutClock;
	
	bool stopFadeOut = false;
	bool blockInput = false;
	bool levelSelection = false;

	void processSelection(sf::RenderTarget* renderTarget);
	void exit();

public:
	MenuManager(GameMaster* gameMaster);

	bool update(sf::RenderTarget* renderTarget);
	void draw(sf::RenderTarget* renderTarget);
	
	const void processInput(sf::Event event, sf::RenderTarget* target);
};