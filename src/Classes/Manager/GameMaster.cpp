#include "GameMaster.h"

GameMaster::GameMaster() {
	// Base state is on the menu
	this->currentState = MENU;

	this->gameManager = new GameManager(EASY, this);
	this->menuManager = new MenuManager(this);
}

void GameMaster::update(sf::RenderTarget* renderTarget) {
	switch (this->currentState)
	{
	case MENU:
		this->menuManager->update(renderTarget);
		break;
	case GAME:
		this->gameManager->update(renderTarget);
		break;
	}
}

const void GameMaster::processInput(sf::Event event, sf::RenderTarget* target) {
	switch (this->currentState)
	{
	case MENU:
		this->menuManager->processInput(event, target);
		break;
	case GAME:
		this->gameManager->processInput(event, target);
		break;
	}
}

void GameMaster::loadLvl(LevelId id) {
	switch (id) {
	case LEVEL1:
		this->gameManager->loadLevel(id);
		break;
	case LEVEL2:
		this->gameManager->loadLevel(id);
		this->gameManager->getEntityManager()->getPlayer()->changeWeapon(new Weapon("images/Whip2.png", 2, 250, "sfx/whip2.ogg"));
		break;
	case MISSINGLVL:
		this->gameManager->loadLevel(id);
		break;
	}
}


void GameMaster::changeState(GameState state) {
	this->currentState = state;
	if (state == GAME) {
		delete this->gameManager;
		this->gameManager = new GameManager(EASY, this);
		this->gameManager->startGame();
	}
	if (state == MENU) {
		delete this->menuManager;
		this->menuManager = new MenuManager(this);
	}
}