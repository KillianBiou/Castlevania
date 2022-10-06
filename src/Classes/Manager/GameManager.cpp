#include "GameManager.h"

GameManager::GameManager(Difficulty difficulty) {
	switch (difficulty)
	{
	case EASY:
		this->pointsToHpUp = { 200, 400, 600, 800 };
		break;
	case MEDIUM:
		this->pointsToHpUp = { 400, 800, 1200, 1600 };
		break;
	case HARD:
		this->pointsToHpUp = { 800, 1600, 2400, 3200 };
		break;
	default:
		break;
	}
}

bool GameManager::isNextBuffReached(int score) {
	if (this->pointsToHpUp.size() != 0 && score >= this->pointsToHpUp.at(0)) {
		this->pointsToHpUp.erase(this->pointsToHpUp.begin());
		return true;
	}
	return false;
}
