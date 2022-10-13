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
#include "Classes/Entity/Reaper.h"
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
#include "Classes/Manager/Camera.h"
#include "Classes/Misc/Level.h"
#include "Classes/Projectiles/StraightProjectile.h"
#include <algorithm>

float clip(float n, float lower, float upper) {
    return std::max(lower, std::min(n, upper));
}

const int level1[] =
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

const int lvl1XSize = 60;
const int lvl1ySize = 24;

std::multimap<EntityType, sf::Vector2f> lvl1EntityMap{
    {PLAYER, sf::Vector2f(256, 1080)},
    {MEDUSA, sf::Vector2f(0, 1000)},
    {MEDUSA, sf::Vector2f(0, 500)},
    {MEDUSA, sf::Vector2f(0, 1500)},
    {ZOMBIE, sf::Vector2f(1000, 1080)},
    {SKELETON, sf::Vector2f(500, 1080)},
    {MUMMY, sf::Vector2f(2000, 1000)}
};

/*int main()
{
    sf::RenderWindow drawingWindow(sf::VideoMode(1920, 1080), "Drawing windows", sf::Style::Close);
    auto desktop = sf::VideoMode::getDesktopMode();
    
    bool a = true;

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

    Score score("font/Pixel.ttf");

    Camera camera(X_SIZE, Y_SIZE, &drawingWindow);

    GameManager gameManager(EASY);
    EntityManager entityManager(&score, &camera, &gameManager);

    Player player("images/Belmon.png", sf::Vector2f(256, 1080), 150, level, X_SIZE, 5.f, 15.f, &entityManager);

    camera.setTarget(&player);

    /*MedusaHeadSpawner ms1(sf::Vector2f(1200, 1080), level, X_SIZE, 6.f, 4.f, 7.f, &entityManager, &view);
    MedusaHeadSpawner ms2(sf::Vector2f(800, 900), level, X_SIZE, 4.f, 6.f, 8.f, &entityManager, &view);
    MedusaHeadSpawner ms3(sf::Vector2f(800, 600), level, X_SIZE, 7.f, 5.f, 7.f, &entityManager, &view);
    MedusaHeadSpawner ms4(sf::Vector2f(800, 300), level, X_SIZE, 3.f, 3.f, 3.f, &entityManager, &view);

    //SkeletonSpawner sks1(sf::Vector2f(2000, 1080), level, X_SIZE, 1.f, 500, 2500, &entityManager, &view);
    //SkeletonSpawner sks2(sf::Vector2f(1000, 1080), level, X_SIZE, 1.f, 500, 2500, &entityManager, &view);
    //SkeletonSpawner sks3(sf::Vector2f(1500, 1080), level, X_SIZE, 1.f, 500, 2500, &entityManager, &view);
    //SkeletonSpawner sks4(sf::Vector2f(2500, 1080), level, X_SIZE, 1.f, 500, 2500, &entityManager, &view);

    // ZombieSpawner zs1(sf::Vector2f(1000, 1080), level, X_SIZE, 3.f, 500.f, &entityManager, &view);
    //ZombieSpawner zs2(sf::Vector2f(1000, 1080), level, X_SIZE, 4.f, 200.f, &entityManager, &view);
    //ZombieSpawner zs3(sf::Vector2f(1500, 1080), level, X_SIZE, 7.f, 200.f, &entityManager, &view);
    //ZombieSpawner zs4(sf::Vector2f(2000, 1080), level, X_SIZE, 3.f, 200.f, &entityManager, &view);

    //Mummy mummy(sf::Vector2f(2000, 1080), level, X_SIZE, 1.f, &entityManager);
    Reaper reaper(sf::Vector2f(1000, 1080), level, X_SIZE, 5.f, &entityManager);

    HealthBar playerHealth("font/Pixel.ttf", &player);

    sf::Texture tex;
    if (!tex.loadFromFile("images/Scythe.png")) {
        std::cout << "Error while loading : " << "images/Scythe.png" << std::endl;
    }

    Tilemap map;
    map.load("images/Platform.png", 64, level, X_SIZE, Y_SIZE);

    Level l(level, X_SIZE, Y_SIZE, "images/Background1.png");

    while (drawingWindow.isOpen()) {
        sf::Event event;
        while (drawingWindow.pollEvent(event)) {
            
        }

        drawingWindow.clear(sf::Color::Black);

        l.update(&drawingWindow);

        drawingWindow.display();

        // Update Camera
        camera.trackTarget();

        // Update HUD
        sf::View* view = camera.getView();
        playerHealth.setPosition(view->getCenter().x - view->getSize().x / 2, view->getCenter().y - view->getSize().y / 2);
        score.setPosition(view->getCenter().x - view->getSize().x / 2, view->getCenter().y - view->getSize().y / 2 + 70);

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

        // Debug
        entityManager.debugDraw(&drawingWindow);

        //Display
        drawingWindow.display();
    }
}*/

int main() {
    sf::RenderWindow drawingWindow(sf::VideoMode(1920, 1080), "Drawing windows", sf::Style::Close);
    auto desktop = sf::VideoMode::getDesktopMode();

    drawingWindow.setFramerateLimit(60);

    Level l(level1, lvl1XSize, lvl1ySize, "images/Background1.png");

    GameManager gameManager(&l, EASY, &lvl1EntityMap);

    while (drawingWindow.isOpen()) {
        sf::Event event;
        while (drawingWindow.pollEvent(event)) {
            gameManager.processInput(event, &drawingWindow);
        }

        drawingWindow.clear(sf::Color::Black);

        gameManager.update(&drawingWindow);

        drawingWindow.display();
    }
}