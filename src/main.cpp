#include <SFML/Graphics.hpp>
#include <iostream>
#include "Classes/Manager/GameMaster.h"
#include <algorithm>

// Main entry point
int main() {
    // Création of a 1920*1080 window
    sf::RenderWindow drawingWindow(sf::VideoMode(1920, 1080), "Castlevania 2022", sf::Style::Close);

    drawingWindow.setFramerateLimit(60);

    GameMaster* gameMaster = new GameMaster();

    // Window loop
    while (drawingWindow.isOpen()) {
        sf::Event event;
        // Event loop
        while (drawingWindow.pollEvent(event)) {
            gameMaster->processInput(event, &drawingWindow);
        }

        // Clear - Draw - Display cycle
        drawingWindow.clear(sf::Color::Black);

        gameMaster->update(&drawingWindow);

        drawingWindow.display();
    }
}