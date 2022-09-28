#include <SFML/Graphics.hpp>
#include <iostream>
#include "Classes/Tilemap.h"
#include "Classes/Entity/Entity.h"
#include "Classes/Entity/Player.h"
#include "Classes/Entity/Monster.h"
#include "Classes/Entity/MedusaHead.h"
#include "Classes/Manager/EntityManager.h"

int main()
{
    sf::RenderWindow drawingWindow(sf::VideoMode(640, 640), "Drawing windows");
    drawingWindow.setVerticalSyncEnabled(true);
    const int X_SIZE = 10;
    const int Y_SIZE = 10;
    bool leftHeld = false;
    bool rightHeld = false;
    const int level[] =
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        0, 0, 0, 1, 0, 0, 0, 0, 1, 2,
        0, 0, 0, 0, 0, 0, 0, 1, 2, 2,
        0, 0, 0, 0, 0, 0, 1, 2, 2, 2,
        1, 1, 1, 1 ,1, 1, 2, 2, 2, 2,
        2, 2, 2, 2, 2 ,2, 2, 2, 2, 2,
        2, 2, 2, 2, 2 ,2, 2, 2, 2, 2,
        2, 2, 2, 2, 2 ,2, 2, 2, 2, 2,
        2, 2, 2, 2, 2 ,2, 2, 2, 2, 2,
    };

    EntityManager entityManager;

    Player player("images/Belmon.png", sf::Vector2f(60, 50), 150, level, X_SIZE, 5.f, 15.f, &entityManager);
    Monster mob1("images/Belmon.png", sf::Vector2f(160, 50), 64, 128, "Monster 1", 150, level, X_SIZE, 5.f, 15.f, &entityManager);
    Monster mob2("images/Belmon.png", sf::Vector2f(260, 50), 64, 128, "Monster 2", 150, level, X_SIZE, 5.f, 15.f, &entityManager);
    Monster mob2("images/Belmon.png", sf::Vector2f(360, 50), 64, 128, "Monster 6", 150, level, X_SIZE, 5.f, 15.f, &entityManager);

    Tilemap map;
    map.load("images/TilesetTest.png", 64, level, 10, 10);

    while (drawingWindow.isOpen()) {
        sf::Event event;
        while (drawingWindow.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                drawingWindow.close();
                break;
            case sf::Event::KeyPressed:
                switch (event.key.code) {
                case sf::Keyboard::Q:
                    player.setHorizontalMovement(LEFT);
                    leftHeld = true;
                    break;
                case sf::Keyboard::S:
                    break;
                case sf::Keyboard::D:
                    rightHeld = true;
                    player.setHorizontalMovement(RIGHT);
                    break;
                case sf::Keyboard::Space:
                    player.setVerticalMovement(UP);
                    break;
                case sf::Keyboard::E:
                    player.attack(false);
                    break;
                }
                break;

            case sf::Event::KeyReleased:
                switch (event.key.code) {
                case sf::Keyboard::Q:
                    leftHeld = false;
                    if (rightHeld) {
                        player.setHorizontalMovement(RIGHT);
                    }
                    else {
                        player.setHorizontalMovement(NONE);
                    }
                    break;
                case sf::Keyboard::S:
                    break;
                case sf::Keyboard::D:
                    rightHeld = false;
                    if (leftHeld) {
                        player.setHorizontalMovement(LEFT);
                    }
                    else {
                        player.setHorizontalMovement(NONE);
                    }
                    break;
                }
                break;
            }
        }

        // Clear
        drawingWindow.clear(sf::Color::Cyan);

        // Update Entities
        entityManager.updateAllEntities();

        // Draw
        drawingWindow.draw(map);
        entityManager.drawAllEntities(&drawingWindow);

        // Debug
        entityManager.debugDraw(&drawingWindow);

        //Display
        drawingWindow.display();
    }
}