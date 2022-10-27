#pragma once
#include "../Manager/EntityManager.h"
#include "../Entity/Player.h"
#include "../Spawner/MedusaHeadSpawner.h"
#include "../Spawner/SkeletonSpawner.h"
#include "../Spawner/ZombieSpawner.h"
#include "../Entity/Mummy.h"
#include "../Entity/Reaper.h"
#include "../Entity/MissingNo.h"
#include "../Misc/Level.h"

// Enumeration to represent all the different type of monster if the game
enum EntityType {
	PLAYER,
	MEDUSA,
	SKELETON,
	ZOMBIE,
	MUMMY,
	REAPER,
	MISSINGNO
};

// An utilitary class only for instanciating all the spawner/player 
class EntityFactory {
private:
	EntityManager* entityManager;
	Level* level;
	sf::View* view;

public:
	EntityFactory(Level* level, EntityManager* gameManager, sf::View* view);

	// Generate a spawner/player at given location
	void createEntity(EntityType type, sf::Vector2f position);
};