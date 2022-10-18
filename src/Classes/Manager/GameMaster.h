#include "GameManager.h"
#include "MenuManager.h"

enum GameState {
	MENU,
	GAME
};

class GameMaster: public InputManager {
private:
	GameState currentState;

	GameManager* gameManager;
	MenuManager* menuManager;

public:
	GameMaster();

	void update(sf::RenderTarget* renderTarget);
	void changeState(GameState state);

	void loadLvl(LevelId id);

	const void processInput(sf::Event event, sf::RenderTarget* target);

};