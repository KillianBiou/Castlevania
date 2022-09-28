#pragma once
#include "../Entity/Entity.h"
#include "../Entity/Monster.h"
#include "../Entity/Player.h"
#include <vector>

class EntityManager
{
private:
	Player* player;
	std::vector<Monster*> monstersList;

	void debugDrawPlayer(sf::RenderWindow* renderWindow);
	void debugDrawMonsters(sf::RenderWindow* renderWindow);

public:
	EntityManager();
	std::vector<Entity*> detectCollision(sf::FloatRect boundary);

	void setPlayer(Player* player);
	void addMonster(Monster* monster);
	void removeMonster(Monster* monster);

	void drawAllEntities(sf::RenderWindow* renderWindow);
	void updateAllEntities();

	void debugDraw(sf::RenderWindow* renderWindow);
};