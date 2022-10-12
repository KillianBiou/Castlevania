#pragma once
#include <vector>
#include "EntityManager.h"
#include "Camera.h"
#include "../Misc/Level.h"
#include "../Misc/EntityFactory.h"

enum Difficulty {
	EASY,
	MEDIUM,
	HARD
};

class GameManager {
private:
	Level* level;
	EntityManager* entityManager;
	Camera* camera;

	std::vector<int> pointsToHpUp;

public:
	GameManager(Level* level, Difficulty difficulty, std::map<EntityType, sf::Vector2f>* entityList);

	void update(sf::RenderTarget* renderTarget);

	bool isNextBuffReached(int score);

	Level* getLevel();
};