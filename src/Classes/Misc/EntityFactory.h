#pragma once
#include "../Manager/EntityManager.h"
#include "../Entity/Player.h"
#include "../Entity/MedusaHead.h"
#include "../Entity/Skeleton.h"
#include "../Entity/Zombie.h"
#include "../Entity/Mummy.h"
#include "../Entity/Reaper.h"
#include "../Misc/Level.h"

enum EntityType {
	PLAYER,
	MEDUSA,
	SKELETON,
	ZOMBIE,
	MUMMY,
	REAPER
};

class EntityFactory {
private:
	EntityManager* entityManager;
	Level* level;

public:
	EntityFactory(Level* level, EntityManager* gameManager);

	void createEntity(EntityType type, sf::Vector2f position);
};