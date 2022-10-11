#pragma once
#include "EntityManager.h"

class Camera {
private:
	EntityManager* entityManager;
	sf::View* view;
	sf::RenderTarget* renderTarget;

	Entity *target;

	float width;
	float height;

	const int levelXSize;
	const int levelYSize;

	float clamp(float value, float min, float max);

public:
	Camera(const int levelXSize, const int levelYSize, sf::RenderTarget* renderTarget);
	void trackTarget();

	sf::View* getView();
	void setEntityManager(EntityManager* entityManager);
	void setTarget(Entity* entity);
};