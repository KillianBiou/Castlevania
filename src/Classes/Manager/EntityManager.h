#pragma once
#include "../Entity/Entity.h"
#include "../Entity/Monster.h"
#include "../Entity/MedusaHead.h"
#include "../Entity/Player.h"
#include "../Entity/Skeleton.h"
#include "../Entity/Zombie.h"
#include "../Misc/Score.h"
#include "../Projectiles/Projectile.h"
#include "../Collectible/Collectible.h"
#include "../Collectible/Heart.h"
#include "../Collectible/HPUp.h"
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
	std::vector<Collectible*> collectibleList;

	sf::View* view;

	void debugDrawPlayer(sf::RenderWindow* renderWindow);
	void debugDrawMonsters(sf::RenderWindow* renderWindow);

public:

	EntityManager(Score* score, sf::View* view);
	std::vector<Entity*> detectCollisionMonster(sf::FloatRect boundary);
	std::vector<Projectile*> detectCollisionProjectile(sf::FloatRect boundary);
	std::vector<Collectible*> detectCollisionCollectibles(sf::FloatRect boundary);

	void setPlayer(Player* player);
	void addSpawner(Spawner* spawner);
	void addMonster(Monster* monster);
	void addProjectile(Projectile* projectile);
	void addCollectible(Collectible* collectible);

	void removeMonster(Monster* monster);
	void removeProjectile(Projectile* projectile);
	void removeCollectible(Collectible* collectible);

	void drawAllEntities(sf::RenderWindow* renderWindow);
	void updateAllEntities();

	void clearOutOfBoundsProjectiles();

	sf::Vector2f playerPosition();
	float xDistToPlayer(float xPos);
	void addScore(int amount);

	void debugDraw(sf::RenderWindow* renderWindow);
};