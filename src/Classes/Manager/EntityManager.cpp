#include "EntityManager.h"
#include "../Spawner/Spawner.h"

EntityManager::EntityManager() {
}

std::vector<Entity*> EntityManager::detectCollision(sf::FloatRect boundary) {
	std::vector<Entity*> collidedList = std::vector<Entity*>();
	for (int i = 0; i < this->monstersList.size(); i++) {
		Monster* currentMonster = this->monstersList.at(i);
		if (boundary.intersects(currentMonster->getGlobalBounds())) {
			collidedList.push_back(currentMonster);
		}
	}

	return collidedList;
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

void EntityManager::removeMonster(Monster* monster) {
    this->monstersList.erase(std::remove(this->monstersList.begin(), this->monstersList.end(), monster), this->monstersList.end());
}

void EntityManager::updateAllEntities() {
	player->update();
	for (int i = 0; i < monstersList.size(); i++) {
        Monster* currentMonster = monstersList.at(i);
        if (instanceof<MedusaHead>(currentMonster)) {
            ((MedusaHead*)currentMonster)->update();
        }
        else {
            currentMonster->update();
        }
	}
    for (Spawner* spawner : this->spawnerList) {
        spawner->update();
    }
    if (!player->isInvulnerable()) {
        for (Entity* entity : this->detectCollision(player->getGlobalBounds())) {
            player->takeDamage(1);
            //std::cout << "Player collide with : " << entity->getName() << std::endl;
        }
    }
}

void EntityManager::drawAllEntities(sf::RenderWindow* renderWindow) {
	renderWindow->draw(*player);
	player->drawChild(renderWindow);
	for (int i = 0; i < monstersList.size(); i++) {
		renderWindow->draw(*monstersList.at(i));
	}
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