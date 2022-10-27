#include "EntityFactory.h"
#include "../Manager/GameManager.h"

EntityFactory::EntityFactory(Level* level, EntityManager* entityManager, sf::View* view): level(level), entityManager(entityManager), view(view) {
}

void EntityFactory::createEntity(EntityType type, sf::Vector2f position) {
	switch (type)
	{
	// Create a player only if no player exist already else way, move it to the target 
	case PLAYER:
		if (entityManager->getPlayer()) {
			entityManager->getPlayer()->setPosition(position);
		}
		else {
			new Player(position, 150, 5.f, 18.f, this->entityManager);
		}
		break;
	case MEDUSA:
		new MedusaHeadSpawner(position.y, level->getLevelRaw(), level->getSizeX(), rand() % 4 + 4, 5, 5, this->entityManager, this->view);
		break;
	case SKELETON:
		new SkeletonSpawner(position, level->getLevelRaw(), level->getSizeX(), 1.f, 500, 2500, this->entityManager, this->view);
		break;
	case ZOMBIE:
		new ZombieSpawner(position, level->getLevelRaw(), level->getSizeX(), 3.f, 500.f, this->entityManager, this->view);
		break;
	case MUMMY:
		new Mummy(position, 1.f, this->entityManager);
		break;
	case REAPER:
		new Reaper(position, 5.f, this->entityManager);
		break;
	case MISSINGNO:
		new MissingNo(position, 8.f, this->entityManager);
		break;
	default:
		break;
	}

}