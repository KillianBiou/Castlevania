#include "EntityManager.h"
#include "../Spawner/Spawner.h"
#include "Camera.h"
#include "GameManager.h"


EntityManager::EntityManager(Camera* camera, GameManager* gameManager): gameManager(gameManager) {
    this->score = camera->getScore();
    this->cameraView = camera->getView();
}

std::vector<Entity*> EntityManager::detectCollisionMonster(sf::FloatRect boundary) {
	std::vector<Entity*> collidedList = std::vector<Entity*>();
	for (int i = 0; i < this->monstersList.size(); i++) {
		Monster* currentMonster = this->monstersList.at(i);
		if (boundary.intersects(currentMonster->getGlobalBounds())) {
			collidedList.push_back(currentMonster);
		}
	}

	return collidedList;
}

std::vector<Projectile*> EntityManager::detectCollisionProjectile(sf::FloatRect boundary) {
    std::vector<Projectile*> collidedList = std::vector<Projectile*>();
    for (int i = 0; i < this->projectileList.size(); i++) {
        Projectile* currentProjectile = this->projectileList.at(i);
        if (boundary.intersects(currentProjectile->getGlobalBounds())) {
            collidedList.push_back(currentProjectile);
        }
    }

    return collidedList;
}

std::vector<Projectile*> EntityManager::detectCollisionAllyProjectile(sf::FloatRect boundary) {
    std::vector<Projectile*> collidedList = std::vector<Projectile*>();
    for (int i = 0; i < this->allyProjectileList.size(); i++) {
        Projectile* currentProjectile = this->allyProjectileList.at(i);
        if (boundary.intersects(currentProjectile->getGlobalBounds())) {
            collidedList.push_back(currentProjectile);
        }
    }

    return collidedList;
}

std::vector<Collectible*> EntityManager::detectCollisionCollectibles(sf::FloatRect boundary) {
    std::vector<Collectible*> collidedList = std::vector<Collectible*>();
    for (int i = 0; i < this->collectibleList.size(); i++) {
        Collectible* currentCollectible = this->collectibleList.at(i);
        if (boundary.intersects(currentCollectible->getGlobalBounds())) {
            collidedList.push_back(currentCollectible);
        }
    }

    return collidedList;
}

bool EntityManager::verifyScore() {
    if (this->gameManager->isNextBuffReached(this->score->getScore())) {
        return true;
    }
    return false;
}

void EntityManager::setPlayer(Player* player) {
	this->player = player;
}

void EntityManager::addMonster(Monster* monster) {
	this->monstersList.push_back(monster);
}

void EntityManager::addSpawner(Spawner* spawner) {
    this->spawnerList.push_back(spawner);
}

void EntityManager::addCollectible(Collectible* collectible) {
    this->collectibleList.push_back(collectible);
}

void EntityManager::addProjectile(Projectile* projectile) {
    this->projectileList.push_back(projectile);
}

void EntityManager::addAllyProjectile(Projectile* projectile) {
    this->allyProjectileList.push_back(projectile);
}

void EntityManager::removeMonster(Monster* monster) {
    this->monstersList.erase(std::remove(this->monstersList.begin(), this->monstersList.end(), monster), this->monstersList.end());
}

void EntityManager::removeProjectile(Projectile* projectile) {
    this->projectileList.erase(std::remove(this->projectileList.begin(), this->projectileList.end(), projectile), this->projectileList.end());
}

void EntityManager::removeAllyProjectile(Projectile* projectile) {
    this->allyProjectileList.erase(std::remove(this->allyProjectileList.begin(), this->allyProjectileList.end(), projectile), this->allyProjectileList.end());
}

void EntityManager::removeCollectible(Collectible* collectible) {
    this->collectibleList.erase(std::remove(this->collectibleList.begin(), this->collectibleList.end(), collectible), this->collectibleList.end());
}

void EntityManager::updateAllEntities() {
    // Clear all projectiles that are out of screen bounds
    this->clearOutOfBoundsProjectiles();
	if(player)
        player->update();
	for (int i = 0; i < monstersList.size(); i++) {
        // Check for collision with an allied projectile
        for (Projectile* projectile : this->detectCollisionAllyProjectile(monstersList.at(i)->getGlobalBounds())) {
            if(abs(this->player->getPosition().x - projectile->getPosition().x) < 1200)
                monstersList.at(i)->takeDamage(1);
            this->removeAllyProjectile(projectile);
        }
        // Update if the monsters is close enough to player
        if (this->cull(monstersList.at(i)->getPosition())) {
            monstersList.at(i)->update();
        }
	}
    // Update all spawners
    for (Spawner* spawner : this->spawnerList) {
        spawner->update();
    }
    // Update all collectibles
    for (Collectible* collectible : this->collectibleList) {
        collectible->update();
    }
    // Update all projectiles
    for (Projectile* projectile : projectileList) {
        projectile->update();
    }
    for (Projectile* projectile : allyProjectileList) {
        projectile->update();
    }
    // Player collision with enemies if invulnerabily time is over
    if (!player->isInvulnerable()) {
        for (Entity* entity : this->detectCollisionMonster(player->getGlobalBounds())) {
            player->takeDamage(1);
        }
        for (Projectile* projectile : this->detectCollisionProjectile(player->getGlobalBounds())) {
            player->takeDamage(1);
        }
    }
    // Check for collectibles pickup
    for (Collectible* collectible : this->detectCollisionCollectibles(player->getGlobalBounds())) {
        collectible->onPickup(this->player);
        this->removeCollectible(collectible);
    }
}

bool EntityManager::cull(sf::Vector2f pos) {
    // Check if the given pos is not too far of the player
    if (abs(this->xDistToPlayer(pos.x)) < 2000 && abs(this->yDistToPlayer(pos.y)) < 1000) {
        return true;
    }
    return false;
}

void EntityManager::clearOutOfBoundsProjectiles() {
    float xMin = (this->cameraView->getCenter().x - this->cameraView->getSize().x / 2) - 250;
    float xMax = (xMin + this->cameraView->getSize().x) + 250;
    float yMin = (this->cameraView->getCenter().y - this->cameraView->getSize().y / 2) - 250;
    float yMax = (yMin + this->cameraView->getSize().y) + 250;

    sf::FloatRect tempCollider(sf::Vector2f(xMin, yMin), sf::Vector2f(this->cameraView->getSize().x + 192, this->cameraView->getSize().y + 192));
    for (Projectile* projectile : this->projectileList) {
        if (!projectile->getGlobalBounds().intersects(tempCollider)) {
            Projectile* temp = projectile;
            this->removeProjectile(projectile);
        }
    }
    for (Projectile* projectile : this->allyProjectileList) {
        std::cout << "dfopzak,dpazo\n";
        if (!projectile->getGlobalBounds().intersects(tempCollider)) {
            std::cout << "deleted\n";
            Projectile* temp = projectile;
            projectile->setPosition(0.f, -9000.f);
            this->removeAllyProjectile(projectile);
            delete temp;
        }
    }

}

void EntityManager::drawAllEntities(sf::RenderTarget* renderTarget) {
    renderTarget->draw(*player);
	player->drawChild(renderTarget);
    for (int i = 0; i < monstersList.size(); i++) {
        renderTarget->draw(*monstersList.at(i));
	}
    for (int i = 0; i < projectileList.size(); i++) {
        renderTarget->draw(*projectileList.at(i));
    }
    for (int i = 0; i < projectileList.size(); i++) {
        renderTarget->draw(*projectileList.at(i));
    }
    for (int i = 0; i < allyProjectileList.size(); i++) {
        renderTarget->draw(*allyProjectileList.at(i));
    }
    for (int i = 0; i < collectibleList.size(); i++) {
        renderTarget->draw(*collectibleList.at(i));
    }
}

sf::Vector2f EntityManager::playerPosition() {
    return this->player->getPosition();
}

float EntityManager::xDistToPlayer(float xPos) {
    return this->player->getPosition().x - xPos;
}
 
float EntityManager::yDistToPlayer(float yPos) {
    return this->player->getPosition().y - yPos;
}

bool EntityManager::isOnScreen(sf::Vector2f pos, float offset) {
    float xMin = (this->cameraView->getCenter().x - this->cameraView->getSize().x / 2) - offset;
    float yMin = (this->cameraView->getCenter().y - this->cameraView->getSize().y / 2) - offset;

    sf::FloatRect tempCollider(sf::Vector2f(xMin, yMin), sf::Vector2f(this->cameraView->getSize().x + offset, this->cameraView->getSize().y + offset));

    if (!tempCollider.contains(pos)) {
        return false;
    }
    return true;
}

void EntityManager::startBossCombat(Monster* target) {
    this->gameManager->getCamera()->setTarget(target);
    for (Spawner* spawner : this->spawnerList) {
        spawner->switchSpawn();
    }
}

void EntityManager::endBossCombat() {
    this->gameManager->getCamera()->setTarget(this->player);
    this->projectileList.clear();
    for (Spawner* spawner : this->spawnerList) {
        spawner->switchSpawn();
    }
}

void EntityManager::clear() {
    this->monstersList.clear();
    this->projectileList.clear();
    this->allyProjectileList.clear();
    this->spawnerList.clear();
    this->collectibleList.clear();
}

void EntityManager::addScore(int amount) {
    this->score->addScore(amount);
}

Player* EntityManager::getPlayer() {
    return this->player;
}

void EntityManager::debugDraw(sf::RenderWindow* renderWindow) {
    this->debugDrawPlayer(renderWindow);
    this->debugDrawMonsters(renderWindow);
}

void EntityManager::debugDrawPlayer(sf::RenderWindow* renderWindow) {
    sf::CircleShape shape(3);
    shape.setPosition(player->getGroundedPoint());
    shape.setFillColor(sf::Color::Green);
    renderWindow->draw(shape);

    sf::CircleShape shapeBis(3);
    shapeBis.setPosition(player->getGroundedPointBis());
    shapeBis.setFillColor(sf::Color::Green);
    renderWindow->draw(shapeBis);

    sf::CircleShape shapeR(3);
    shapeR.setPosition(player->getRightBoundPoint());
    shapeR.setFillColor(sf::Color::Red);
    renderWindow->draw(shapeR);

    sf::CircleShape shapeRB(3);
    shapeRB.setPosition(player->getRightBoundPointBis());
    shapeRB.setFillColor(sf::Color::Red);
    renderWindow->draw(shapeRB);

    sf::CircleShape shapeRP(3);
    shapeRP.setPosition(player->getRightBoundPointPrime());
    shapeRP.setFillColor(sf::Color::Red);
    renderWindow->draw(shapeRP);

    sf::CircleShape shapeL(3);
    shapeL.setPosition(player->getLeftBoundPoint());
    shapeL.setFillColor(sf::Color::Red);
    renderWindow->draw(shapeL);

    sf::CircleShape shapeLB(3);
    shapeLB.setPosition(player->getLeftBoundPointBis());
    shapeLB.setFillColor(sf::Color::Red);
    renderWindow->draw(shapeLB);

    sf::CircleShape shapeLP(3);
    shapeLP.setPosition(player->getLeftBoundPointPrime());
    shapeLP.setFillColor(sf::Color::Red);
    renderWindow->draw(shapeLP);

    sf::CircleShape shapeU(3);
    shapeU.setPosition(player->getTopBoundPoint());
    shapeU.setFillColor(sf::Color::Red);
    renderWindow->draw(shapeU);

    sf::CircleShape shapeUB(3);
    shapeUB.setPosition(player->getTopBoundPointBis());
    shapeUB.setFillColor(sf::Color::Red);
    renderWindow->draw(shapeUB);
}

void EntityManager::debugDrawMonsters(sf::RenderWindow* renderWindow) {
    for (Monster* monster : monstersList) {
        sf::CircleShape shape(3);
        shape.setPosition(monster->getGroundedPoint());
        shape.setFillColor(sf::Color::Green);
        renderWindow->draw(shape);

        sf::CircleShape shapeBis(3);
        shapeBis.setPosition(monster->getGroundedPointBis());
        shapeBis.setFillColor(sf::Color::Green);
        renderWindow->draw(shapeBis);

        sf::CircleShape shapeR(3);
        shapeR.setPosition(monster->getRightBoundPoint());
        shapeR.setFillColor(sf::Color::Red);
        renderWindow->draw(shapeR);

        sf::CircleShape shapeRB(3);
        shapeRB.setPosition(monster->getRightBoundPointBis());
        shapeRB.setFillColor(sf::Color::Red);
        renderWindow->draw(shapeRB);

        sf::CircleShape shapeRP(3);
        shapeRP.setPosition(monster->getRightBoundPointPrime());
        shapeRP.setFillColor(sf::Color::Red);
        renderWindow->draw(shapeRP);

        sf::CircleShape shapeL(3);
        shapeL.setPosition(monster->getLeftBoundPoint());
        shapeL.setFillColor(sf::Color::Red);
        renderWindow->draw(shapeL);

        sf::CircleShape shapeLB(3);
        shapeLB.setPosition(monster->getLeftBoundPointBis());
        shapeLB.setFillColor(sf::Color::Red);
        renderWindow->draw(shapeLB);

        sf::CircleShape shapeLP(3);
        shapeLP.setPosition(monster->getLeftBoundPointPrime());
        shapeLP.setFillColor(sf::Color::Red);
        renderWindow->draw(shapeLP);

        sf::CircleShape shapeU(3);
        shapeU.setPosition(monster->getTopBoundPoint());
        shapeU.setFillColor(sf::Color::Green);
        renderWindow->draw(shapeU);

        sf::CircleShape shapeUB(3);
        shapeUB.setPosition(monster->getTopBoundPointBis());
        shapeUB.setFillColor(sf::Color::Red);
        renderWindow->draw(shapeUB);
    }
}

sf::View* EntityManager::getView() {
    return this->cameraView;
}

GameManager* EntityManager::getGameManager() {
    return this->gameManager;
}
