#include "GameManager.h"
#include "MenuManager.h"

// Enumaration that list all possible game state
enum GameState {
	MENU,
	GAME
};

// Class that manage the menu and the game
class GameMaster: public InputManager {
private:
	GameState currentState;

	// Game
	GameManager* gameManager;
	// Menu
	MenuManager* menuManager;

public:
	GameMaster();

	// Update loop
	void update(sf::RenderTarget* renderTarget);
	// Change the current gamestate
	void changeState(GameState state);

	// Load the target level
	void loadLvl(LevelId id);

	// Override to process user input
	const void processInput(sf::Event event, sf::RenderTarget* target);

};