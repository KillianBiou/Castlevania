#include "EntityFactory.h"

EntityFactory::EntityFactory(Level* level, EntityManager* entityManager): level(level), entityManager(entityManager) {
}

void EntityFactory::createEntity(EntityType type, sf::Vector2f position) {
	std::cout << type << ", (" << position.x << ", " << position.y << ")\n";
	switch (type)
	{
	case PLAYER:
		new Player(position, 150, level->getLevelRaw(), level->getSizeX(), 5.f, 15.f, entityManager);
		break;
	case MEDUSA:
		break;
	case SKELETON:
		break;
	case ZOMBIE:
		break;
	case MUMMY:
		break;
	case REAPER:
		break;
	default:
		break;
	}

}