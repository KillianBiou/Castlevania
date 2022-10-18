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
	LEVEL2 = 1
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

	std::vector<int> pointsToHpUp;

	void loadEntities();

public:
	GameManager(Difficulty difficulty, GameMaster* gameMaster);

	void update(sf::RenderTarget* renderTarget);
	void loadLevel(LevelId id);

	void startGame();

	const void processInput(sf::Event event, sf::RenderTarget* target);

	bool isNextBuffReached(int score);

	Level* getLevel();
	Camera* getCamera();
	SoundManager* getSoundManager();
	EntityManager* getEntityManager();
};