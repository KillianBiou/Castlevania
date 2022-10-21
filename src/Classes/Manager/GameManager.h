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
	TUTORIAL = 2
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

	std::vector<int> pointsToHpUp;

	sf::Texture cutsceneBG;
	sf::Texture cutsceneCastle;
	sf::Texture cutsceneCull;
	sf::Texture textClear;
	sf::Sprite cutsceneBGS;
	sf::Sprite cutsceneCastleS;
	sf::Sprite cutsceneCullS;
	sf::Sprite textClearS;

	sf::SoundBuffer castleCrush;
	sf::SoundBuffer victoryMusic;
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

	void playEndCutscene();

	Level* getLevel();
	Camera* getCamera();
	SoundManager* getSoundManager();
	EntityManager* getEntityManager();
};