#include <SFML/Graphics.hpp>
#include <iostream>
#include "Classes/Tilemap.h"
#include "Classes/Entity/Entity.h"
#include "Classes/Entity/Player.h"
#include "Classes/Entity/Monster.h"
#include "Classes/Entity/MedusaHead.h"
#include "Classes/Entity/Zombie.h"
#include "Classes/Entity/Skeleton.h"
#include "Classes/Entity/Mummy.h"
#include "Classes/Manager/EntityManager.h"
#include "Classes/Spawner/MedusaHeadSpawner.h"
#include "Classes/Spawner/ZombieSpawner.h"
#include "Classes/Spawner/SkeletonSpawner.h"
#include "Classes/Misc/HealthBar.h"
#include "Classes/Misc/Score.h"
#include "Classes/Collectible/Heart.h"
#include "Classes/Collectible/HPUp.h"
#include "Classes/Collectible/WeaponUpgrade.h"
#include "Classes/Manager/GameManager.h"
#include <algorithm>

float clip(float n, float lower, float upper) {
    return std::max(lower, std::min(n, upper));
}

int main()
{
    sf::RenderWindow drawingWindow(sf::VideoMode(640, 360), "Drawing windows", sf::Style::Close);
    auto desktop = sf::VideoMode::getDesktopMode();
    
    sf::FloatRect viewArea(0, 0, 640, 360);
    sf::View view = sf::View(viewArea);

    sf::Sprite backgroundImage1;
    sf::Texture bgImage1Texture;
    if (!bgImage1Texture.loadFromFile("images/Background1.png")) {
        std::cout << "Error while loading : " << "images/Background1.png" << std::endl;
    }
    backgroundImage1.setTexture(bgImage1Texture);
    backgroundImage1.setPosition(0.f, 64.f);

    drawingWindow.setFramerateLimit(60);
    const int X_SIZE = 60;
    const int Y_SIZE = 24;

    int width = 640;
    int height = 360;

    bool leftHeld = false;
    bool rightHeld = false;
    const int level[] =
    {
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 1  , 1, 1, 1, 1, 1, 1, 1, 1, 1, 1  , 1, 1, 1, 1, 1, 1, 1, 1, 1, 1  , 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 1  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 1  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 1  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 1, 1, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 1  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 1, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 1  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 1, 1, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 1  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 1, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1  , 1, 1, 1, 1, 1, 1, 1, 1, 1, 1  , 1, 1, 1, 1, 1, 1, 1, 1, 1, 1  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 1, 1, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 1, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

        1, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 1, 1, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 1, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 1, 1, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 1, 1, 0, 0, 0, 0, 0, 0,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 1, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 1, 1, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 1, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1  , 1, 1, 1, 1, 1, 1, 1, 1, 1, 1  , 1, 1, 1, 1, 1, 1, 1, 1, 1, 1  , 1, 1, 1, 1, 1, 1, 1, 1, 1, 1  , 1, 1, 1, 1, 1, 1, 1, 1, 1, 1  , 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,

        2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
    };

    Score score("font/Pixel.ttf");

    GameManager gameManager(EASY);
    EntityManager entityManager(&score, &view, &gameManager);

    Player player("images/Belmon.png", sf::Vector2f(256, 1080), 150, level, X_SIZE, 5.f, 15.f, &entityManager);

    //MedusaHeadSpawner ms1(sf::Vector2f(1200, 1080), level, X_SIZE, 6.f, 4.f, 7.f, &entityManager, &view);
    //MedusaHeadSpawner ms2(sf::Vector2f(800, 900), level, X_SIZE, 4.f, 6.f, 8.f, &entityManager, &view);
    //MedusaHeadSpawner ms3(sf::Vector2f(800, 600), level, X_SIZE, 7.f, 5.f, 7.f, &entityManager, &view);
    //MedusaHeadSpawner ms4(sf::Vector2f(800, 300), level, X_SIZE, 3.f, 3.f, 3.f, &entityManager, &view);

    SkeletonSpawner sks1(sf::Vector2f(2000, 1080), level, X_SIZE, 1.f, 500, 2500, &entityManager, &view);

    //ZombieSpawner zs1(sf::Vector2f(1000, 1080), level, X_SIZE, 3.f, 500.f, &entityManager, &view);
    //ZombieSpawner zs2(sf::Vector2f(1000, 1080), level, X_SIZE, 4.f, 200.f, &entityManager, &view);
    //ZombieSpawner zs3(sf::Vector2f(1500, 1080), level, X_SIZE, 7.f, 200.f, &entityManager, &view);
    //ZombieSpawner zs4(sf::Vector2f(2000, 1080), level, X_SIZE, 3.f, 200.f, &entityManager, &view);

    Mummy mummy(sf::Vector2f(1000, 1080), level, X_SIZE, 1.f, &entityManager);

    HealthBar playerHealth("font/Pixel.ttf", &player);

    /*WeaponUpgrade collectible(level, X_SIZE, 1);
    collectible.setPosition(player.getPosition() + sf::Vector2f(100.f, 0.f));
    entityManager.addCollectible(&collectible);
    WeaponUpgrade collectible2(level, X_SIZE, 2);
    collectible2.setPosition(player.getPosition() + sf::Vector2f(300.f, 0.f));
    entityManager.addCollectible(&collectible2);*/

    Tilemap map;
    map.load("images/Platform.png", 64, level, X_SIZE, Y_SIZE);

    while (drawingWindow.isOpen()) {
        sf::Event event;
        while (drawingWindow.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                drawingWindow.close();
                break;
            case sf::Event::Resized:
                viewArea.width = event.size.width;
                viewArea.height = event.size.height;
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
                case sf::Keyboard::Num1:
                    width = 640;
                    height = 360;
                    viewArea.width = width;
                    viewArea.height = height;
                    drawingWindow.setSize(sf::Vector2u(width, height));
                    drawingWindow.setPosition(sf::Vector2i(desktop.width / 2 - width / 2, desktop.height / 2 - height / 2));
                    break;
                case sf::Keyboard::Num2:
                    width = 1280;
                    height = 720;
                    viewArea.width = width;
                    viewArea.height = height;
                    drawingWindow.setSize(sf::Vector2u(width, height));
                    drawingWindow.setPosition(sf::Vector2i(desktop.width / 2 - width / 2, desktop.height / 2 - height / 2));
                    break;
                case sf::Keyboard::Num3:
                    width = 1920;
                    height = 1080;
                    viewArea.width = width;
                    viewArea.height = height;
                    drawingWindow.setSize(sf::Vector2u(width, height));
                    drawingWindow.setPosition(sf::Vector2i(desktop.width / 2 - width / 2, desktop.height / 2 - height / 2));
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

        // Update Camera
        view = sf::View(viewArea);
        float xPos = clip(player.getPosition().x, 0 + view.getSize().x / 2, X_SIZE * 64 - view.getSize().x / 2);
        float yPos = clip(player.getPosition().y, 0 + view.getSize().y / 2, Y_SIZE * 64 - view.getSize().y / 2);
        view.setCenter(xPos, yPos);
        drawingWindow.setView(view);

        // Update HUD
        playerHealth.setPosition(view.getCenter().x - view.getSize().x / 2, view.getCenter().y - view.getSize().y / 2);
        score.setPosition(view.getCenter().x - view.getSize().x / 2, view.getCenter().y - view.getSize().y / 2 + 70);

        // Clear
        drawingWindow.clear(sf::Color::Cyan);

        // Update Entities
        entityManager.updateAllEntities();
        playerHealth.update();
        score.update();

        // Draw
        drawingWindow.draw(backgroundImage1);
        drawingWindow.draw(map);
        entityManager.drawAllEntities(&drawingWindow);

        drawingWindow.draw(playerHealth);
        drawingWindow.draw(score);
        /*drawingWindow.draw(collectible);
        drawingWindow.draw(collectible2);*/

        // Debug
        entityManager.debugDraw(&drawingWindow);

        //Display
        drawingWindow.display();
    }
}