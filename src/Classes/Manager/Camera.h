#pragma once
#include "EntityManager.h"
#include "../Misc/Score.h"

class Camera {
private:
	EntityManager* entityManager;
	sf::View* view;

	Entity *target;

	Score* score;

	float width;
	float height;

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
};