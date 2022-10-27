#pragma once
#include "EntityManager.h"
#include "../Misc/Score.h"
#include "../Misc/HealthBar.h"
#include "../Misc/ManaBar.h"

// Class that control the view of the game
class Camera {
private:
	EntityManager* entityManager;
	sf::View* view;

	// The target to follow
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

	// Clamp a value between a minimum and a maximum
	float clamp(float value, float min, float max);

public:
	Camera();
	// Track the current target (Equivalent of update loop)
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