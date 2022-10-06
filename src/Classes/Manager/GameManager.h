#pragma once
#include <vector>

enum Difficulty {
	EASY,
	MEDIUM,
	HARD
};

class GameManager {
private:
	std::vector<int> pointsToHpUp;

public:
	GameManager(Difficulty difficulty);

	bool isNextBuffReached(int score);
};