#include "Weapon.h"
#include "../Entity/Entity.h"

Weapon::Weapon(std::string spritesheetPath, int damage, float timePerAttack): damage(damage), timePerAttack(timePerAttack) {
    if (!this->spritesheet.loadFromFile(spritesheetPath)) {
        std::cout << "Error while loading : " << spritesheetPath << std::endl;
    }
    this->setTexture(this->spritesheet);
    this->textureRect = sf::IntRect(0, 0, 0, 0);
    this->setTextureRect(this->textureRect);
}

void Weapon::phase0(bool reverse) {
    std::cout << "Phase 0\n";
    this->textureRect = sf::IntRect(0, 0, 64, 128);
    this->setTextureRect(this->textureRect);
    if (reverse) {
        this->setScale(-1.f, 1.f);
    }
    else {
        this->setScale(1.f, 1.f);
    }

    this->currentPhase = 1;
}

void Weapon::phase1(bool reverse) {
    std::cout << "Phase 1\n";
    this->textureRect = sf::IntRect(64, 0, 64, 128);
    this->setTextureRect(this->textureRect);
    if (reverse) {
        this->setScale(-1.f, 1.f);
    }
    else {
        this->setScale(1.f, 1.f);
    }

    this->currentPhase = 2;
}

void Weapon::phase2(bool reverse) {
    std::cout << "Phase 2\n";
    this->textureRect = sf::IntRect(128, 0, 112, 128);
    this->setTextureRect(this->textureRect);
    if (reverse) {
        this->setScale(-1.f, 1.f);
    }
    else {
        this->setScale(1.f, 1.f);
    }

    this->currentPhase = 3;
}

void Weapon::phase3(bool reverse) {
    std::cout << "Phase 3\n";
    this->textureRect = sf::IntRect(0, 0, 0, 0);
    this->setTextureRect(this->textureRect);
    if (reverse) {
        this->setScale(-1.f, 1.f);
    }
    else {
        this->setScale(1.f, 1.f);
    }

    this->currentPhase = 0;
}

int Weapon::getCurrentPhase() {
    return this->currentPhase;
}

int Weapon::getDamage() {
    return this->damage;
}

float Weapon::getTimePerAttack() {
    return this->timePerAttack;
}