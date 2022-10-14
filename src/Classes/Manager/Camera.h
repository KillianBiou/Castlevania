#pragma once
#include "EntityManager.h"
#include "../Misc/Score.h"
#include "../Misc/HealthBar.h"
#include "../Misc/ManaBar.h"

class Camera {
private:
	EntityManager* entityManager;
	sf::View* view;

	Entity *target;

	Score* score;
	HealthBar* healthBar;
	ManaBar* manaBar;

	float width;
	float height;

	bool firstInitialisation = true;

	const int levelXSize;
	const int levelYSize;

	float clamp(float value, float min, float max);

public:
	Camera(const int levelXSize, const int levelYSize);
	void trackTarget(sf::RenderTarget* renderTarget);

	sf::View* getView();
	void setEntityManager(EntityManager* entityManager);
	void setTarget(Entity* entity);

	Score* getScore();
	HealthBar* getHealthBar();
	ManaBar* getManaBar();
};