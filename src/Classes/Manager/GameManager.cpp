#include "GameManager.h"

GameManager::GameManager(Level* level, Difficulty difficulty, std::multimap<EntityType, sf::Vector2f>* entityList): level(level) {
	this->camera = new Camera(this->level->getSizeX(), this->level->getSizeY());
	this->entityManager = new EntityManager(this->camera, this);

	EntityFactory tempFactory(this->level, this->entityManager, this->camera->getView());

    std::cout << entityList->size() << std::endl;
	for (std::pair<EntityType, sf::Vector2f> entry : *entityList) {
		tempFactory.createEntity(entry.first, entry.second);
	}
	this->camera->setTarget(this->entityManager->getPlayer());
    this->camera->getHealthBar()->setEntity(this->entityManager->getPlayer());
	
	switch (difficulty)
	{
	case EASY:
		this->pointsToHpUp = { 200, 400, 600, 800 };
		break;
	case MEDIUM:
		this->pointsToHpUp = { 400, 800, 1200, 1600 };
		break;
	case HARD:
		this->pointsToHpUp = { 800, 1600, 2400, 3200 };
		break;
	default:
		break;
	}
}

void GameManager::update(sf::RenderTarget* renderTarget) {
	this->entityManager->updateAllEntities();

	renderTarget->draw(*this->level);

	entityManager->drawAllEntities(renderTarget);

    this->camera->trackTarget(renderTarget);
}

const void GameManager::processInput(sf::Event event, sf::RenderTarget* target) {
    switch (event.type) {
    case sf::Event::Closed:
        ((sf::RenderWindow*)target)->close();
        break;
    case sf::Event::Resized:
        break;
    case sf::Event::KeyPressed:
        switch (event.key.code) {
        case sf::Keyboard::Q:
            this->entityManager->getPlayer()->setHorizontalMovement(LEFT);
            this->leftHeld = true;
            break;
        case sf::Keyboard::S:
            break;
        case sf::Keyboard::D:
            this->rightHeld = true;
            this->entityManager->getPlayer()->setHorizontalMovement(RIGHT);
            break;
        case sf::Keyboard::Space:
            this->entityManager->getPlayer()->setVerticalMovement(UP);
            break;
        case sf::Keyboard::E:
            this->entityManager->getPlayer()->attack(false);
            break;
        case sf::Keyboard::Num1:
            break;
        case sf::Keyboard::Num2:
            break;
        case sf::Keyboard::Num3:
            break;
        }
        break;

    case sf::Event::KeyReleased:
        switch (event.key.code) {
        case sf::Keyboard::Q:
            this->leftHeld = false;
            if (rightHeld) {
                this->entityManager->getPlayer()->setHorizontalMovement(RIGHT);
            }
            else {
                this->entityManager->getPlayer()->setHorizontalMovement(NONE);
            }
            break;
        case sf::Keyboard::S:
            break;
        case sf::Keyboard::D:
            this->rightHeld = false;
            if (leftHeld) {
                this->entityManager->getPlayer()->setHorizontalMovement(LEFT);
            }
            else {
                this->entityManager->getPlayer()->setHorizontalMovement(NONE);
            }
            break;
        }
        break;
    }
}


bool GameManager::isNextBuffReached(int score) {
	if (this->pointsToHpUp.size() != 0 && score >= this->pointsToHpUp.at(0)) {
		this->pointsToHpUp.erase(this->pointsToHpUp.begin());
		return true;
	}
	return false;
}

Level* GameManager::getLevel() {
	return this->level;
}

Camera* GameManager::getCamera() {
    return this->camera;
}