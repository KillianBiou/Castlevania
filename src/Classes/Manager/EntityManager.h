#pragma once
#include "../Entity/Entity.h"
#include "../Entity/Monster.h"
#include "../Entity/MedusaHead.h"
#include "../Entity/Player.h"
#include "../Entity/Skeleton.h"
#include "../Entity/Zombie.h"
#include "../Misc/Score.h"
#include "../Projectiles/Projectile.h"
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
	std::vector<Projectile*> projectileList;
	std::vector<Monster*> monstersList;
	std::vector<Spawner*> spawnerList;

	sf::View* view;

	void debugDrawPlayer(sf::RenderWindow* renderWindow);
	void debugDrawMonsters(sf::RenderWindow* renderWindow);

public:
	EntityManager(Score* score, sf::View* view);
	std::vector<Entity*> detectCollisionMonster(sf::FloatRect boundary);
	std::vector<Projectile*> detectCollisionProjectile(sf::FloatRect boundary);

	void setPlayer(Player* player);
	void addSpawner(Spawner* spawner);
	void addMonster(Monster* monster);
	void addProjectile(Projectile* projectile);
	void removeMonster(Monster* monster);
	void removeProjectile(Projectile* projectile);

	void drawAllEntities(sf::RenderWindow* renderWindow);
	void updateAllEntities();

	void clearOutOfBoundsProjectiles();

	sf::Vector2f playerPosition();
	float xDistToPlayer(float xPos);
	void addScore(int amount);

	void debugDraw(sf::RenderWindow* renderWindow);
};