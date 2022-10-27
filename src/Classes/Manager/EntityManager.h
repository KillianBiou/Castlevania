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

// Outdated ? Can be used to know the class of an object (Was used for polymorphism)
template<typename Base, typename T>
inline bool instanceof(const T* ptr) {
	return dynamic_cast<const Base*>(ptr) != nullptr;
}

class Spawner;
class Camera;
class GameManager;

// Class that is responsible for entity management (Movement, draw)
class EntityManager
{
private:
	Player* player;
	Score* score;
	GameManager* gameManager;

	sf::View* cameraView;

	// All the vector of different entities
	std::vector<Projectile*> projectileList;
	std::vector<Projectile*> allyProjectileList;
	std::vector<Monster*> monstersList;
	std::vector<Spawner*> spawnerList;
	std::vector<Collectible*> collectibleList;

	// Function to debug draw the target collider
	void debugDrawPlayer(sf::RenderWindow* renderWindow);
	void debugDrawMonsters(sf::RenderWindow* renderWindow);

public:

	EntityManager(Camera* camera, GameManager* gameManager);

	void setPlayer(Player* player);
	// Add to a list
	void addSpawner(Spawner* spawner);
	void addMonster(Monster* monster);
	void addProjectile(Projectile* projectile);
	void addAllyProjectile(Projectile* projectile);
	void addCollectible(Collectible* collectible);
	
	// Return a list of all the colliding object with a given float rect
	std::vector<Entity*> detectCollisionMonster(sf::FloatRect boundary);
	std::vector<Projectile*> detectCollisionProjectile(sf::FloatRect boundary);
	std::vector<Projectile*> detectCollisionAllyProjectile(sf::FloatRect boundary);
	std::vector<Collectible*> detectCollisionCollectibles(sf::FloatRect boundary);

	bool verifyScore();

	// Remove from a list
	void removeMonster(Monster* monster);
	void removeProjectile(Projectile* projectile);
	void removeAllyProjectile(Projectile* projectile);
	void removeCollectible(Collectible* collectible);

	// Render all entities with the render target
	void drawAllEntities(sf::RenderTarget* renderTarget);
	void updateAllEntities();

	void clear();

	void startBossCombat(Monster* target);
	void endBossCombat();

	void clearOutOfBoundsProjectiles();

	sf::Vector2f playerPosition();
	float xDistToPlayer(float xPos);
	float yDistToPlayer(float yPos);
	bool isOnScreen(sf::Vector2f pos, float offset);
	bool cull(sf::Vector2f pos);
	void addScore(int amount);

	Player* getPlayer();
	sf::View* getView();
	GameManager* getGameManager();

	void debugDraw(sf::RenderWindow* renderWindow);
};