#include "EntityFactory.h"

EntityFactory::EntityFactory(Level* level, EntityManager* entityManager, sf::View* view): level(level), entityManager(entityManager), view(view) {
}

void EntityFactory::createEntity(EntityType type, sf::Vector2f position) {
	switch (type)
	{
	case PLAYER:
		new Player(position, 150, level->getLevelRaw(), level->getSizeX(), 5.f, 15.f, this->entityManager);
		break;
	case MEDUSA:
		new MedusaHeadSpawner(position.y, level->getLevelRaw(), level->getSizeX(), 6.f, 4.f, 7.f, this->entityManager, this->view);
		break;
	case SKELETON:
		new SkeletonSpawner(position, level->getLevelRaw(), level->getSizeX(), 1.f, 500, 2500, this->entityManager, this->view);
		break;
	case ZOMBIE:
		new ZombieSpawner(position, level->getLevelRaw(), level->getSizeX(), 3.f, 500.f, this->entityManager, this->view);
		break;
	case MUMMY:
		break;
	case REAPER:
		new Reaper(position, level->getLevelRaw(), level->getSizeX(), 5.f, this->entityManager);
		break;
	default:
		break;
	}

}