#include <SFML/Graphics.hpp>
#include <iostream>
#include "Classes/Manager/GameMaster.h"
#include <algorithm>

int main() {
    sf::RenderWindow drawingWindow(sf::VideoMode(1920, 1080), "Drawing windows", sf::Style::Close);
    drawingWindow.setTitle("Castlevania 2022");
    auto desktop = sf::VideoMode::getDesktopMode();

    srand(time(NULL));
    bool continueLoop = true;

    drawingWindow.setFramerateLimit(60);

    GameMaster* gameMaster = new GameMaster();

    while (drawingWindow.isOpen()) {
        sf::Event event;
        while (drawingWindow.pollEvent(event)) {
            gameMaster->processInput(event, &drawingWindow);
        }

        drawingWindow.clear(sf::Color::Black);

        gameMaster->update(&drawingWindow);

        drawingWindow.display();
    }
}