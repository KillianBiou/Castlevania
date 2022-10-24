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
	bool teleportToTarget = false;

	int levelXSize;
	int levelYSize;

	float clamp(float value, float min, float max);

public:
	Camera();
	void trackTarget(sf::RenderTarget* renderTarget);
	void reset();

	sf::View* getView();
	void setEntityManager(EntityManager* entityManager);
	void setTarget(Entity* entity);
	void teleport();
	sf::Vector2f getTargetPos();

	Score* getScore();
	HealthBar* getHealthBar();
	ManaBar* getManaBar();

};