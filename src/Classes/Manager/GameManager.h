#pragma once
#include <vector>
#include "EntityManager.h"
#include "Camera.h"
#include "InputManager.h"
#include "SoundManager.h"
#include "../Misc/Level.h"
#include "../Misc/EntityFactory.h"

enum Difficulty {
	EASY,
	MEDIUM,
	HARD
};

enum LevelId {
	LEVEL1 = 0,
	LEVEL2 = 1,
	MISSINGLVL = 2,
	TUTORIAL = 3
};

class GameMaster;

class GameManager: public InputManager {
private:
	GameMaster* gameMaster;

	Level* level;
	LevelId currentLvlId;
	EntityManager* entityManager;
	Camera* camera;
	SoundManager* soundManager;

	bool leftHeld;
	bool rightHeld;

	sf::Clock* endCutsceneClock;
	sf::Clock* deathClock;
	sf::Clock* fadeOutClock;

	std::vector<int> pointsToHpUp;

	sf::Texture cutsceneBG;
	sf::Texture cutsceneCastle;
	sf::Texture cutsceneCull;
	sf::Texture textClear;
	sf::Texture fadeOutTexture;
	sf::Sprite cutsceneBGS;
	sf::Sprite cutsceneCastleS;
	sf::Sprite cutsceneCullS;
	sf::Sprite textClearS;
	sf::Sprite fadeOutSprite;

	sf::Font font;
	sf::Text deathText;

	sf::SoundBuffer castleCrush;
	sf::SoundBuffer victoryMusic;
	sf::SoundBuffer gameOver;
	bool startedSfx = false;
	bool victoryMusicStarted = false;

	void loadEntities();

public:
	GameManager(Difficulty difficulty, GameMaster* gameMaster);

	void update(sf::RenderTarget* renderTarget);
	void loadLevel(LevelId id);

	void startGame();

	const void processInput(sf::Event event, sf::RenderTarget* target);

	bool isNextBuffReached(int score);

	void fadeOut();
	void fadeDeath();
	void playEndCutscene();

	Level* getLevel();
	Camera* getCamera();
	SoundManager* getSoundManager();
	EntityManager* getEntityManager();
};