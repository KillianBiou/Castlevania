#pragma once
#include "../Entity/Entity.h"
#include "../Entity/Monster.h"
#include "../Entity/MedusaHead.h"
#include "../Entity/Player.h"
#include "../Misc/Score.h"
#include <vector>

template<typename Base, typename T>
inline bool instanceof(const T* ptr) {
	return dynamic_cast<const Base*>(ptr) != nullptr;
}

class Spawner;

class EntityManager
{
private:
	Player* player;
	Score* score;
	std::vector<Monster*> monstersList;
	std::vector<Spawner*> spawnerList;

	void debugDrawPlayer(sf::RenderWindow* renderWindow);
	void debugDrawMonsters(sf::RenderWindow* renderWindow);

public:
	EntityManager(Score* score);
	std::vector<Entity*> detectCollision(sf::FloatRect boundary);

	void setPlayer(Player* player);
	void addSpawner(Spawner* spawner);
	void addMonster(Monster* monster);
	void removeMonster(Monster* monster);

	void drawAllEntities(sf::RenderWindow* renderWindow);
	void updateAllEntities();

	void addScore(int amount);

	void debugDraw(sf::RenderWindow* renderWindow);
};