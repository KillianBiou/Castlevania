#pragma once
#include <vector>
#include "EntityManager.h"
#include "Camera.h"
#include "InputManager.h"
#include "../Misc/Level.h"
#include "../Misc/EntityFactory.h"

enum Difficulty {
	EASY,
	MEDIUM,
	HARD
};

class GameManager: public InputManager {
private:
	Level* level;
	EntityManager* entityManager;
	Camera* camera;

	bool leftHeld;
	bool rightHeld;

	std::vector<int> pointsToHpUp;

public:
	GameManager(Level* level, Difficulty difficulty, std::map<EntityType, sf::Vector2f>* entityList);

	void update(sf::RenderTarget* renderTarget);

	const void processInput(sf::Event event, sf::RenderTarget* target);

	bool isNextBuffReached(int score);

	Level* getLevel();
	Camera* getCamera();
};