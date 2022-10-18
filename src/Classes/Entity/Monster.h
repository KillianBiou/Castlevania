#pragma once
#include <stdlib.h>
#include <time.h> 
#include "Entity.h"
#include "../Manager/Animator.h"
#include "../Collectible/Heart.h"
#include "../Collectible/HPUp.h"

class Spawner;

class Monster: public Entity
{
protected:
	Spawner* spawner;
	bool specialDrop;

public:
	Monster(std::string texturePath, sf::Vector2f pos, int sizeX, int sizeY, std::string name, int frameDelay, float speedFactor, float jumpFactor, EntityManager* entityManager, Spawner* spawner);
	void const drawChild(sf::RenderWindow* renderWindow);

	virtual void const update() = 0;

	void const attack(bool advance);
	void const taskDeletion();
	const sf::Vector2f cameraTracking();

	~Monster();
};

