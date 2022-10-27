#include "Weapon.h"
#include "../Entity/Entity.h"

Weapon::Weapon(std::string spritesheetPath, int damage, float timePerAttack, std::string soundPath): damage(damage), timePerAttack(timePerAttack) {
    if (!this->spritesheet.loadFromFile(spritesheetPath)) {
        std::cout << "Error while loading : " << spritesheetPath << std::endl;
    }
    
    this->attackSound.loadFromFile(soundPath);

    this->setTexture(this->spritesheet);
    this->textureRect = sf::IntRect(0, 0, 0, 0);
    this->setTextureRect(this->textureRect);
}

// Move the sprite behind the player for synchronisation with player
void Weapon::phase0(bool reverse) {
    std::cout << "Phase 0\n";
    this->textureRect = sf::IntRect(0, 0, 64, 128);
    this->setTextureRect(this->textureRect);
    // Invert the sprite for the player's direction
    if (reverse) {
        this->setScale(-1.f, 1.f);
    }
    else {
        this->setScale(1.f, 1.f);
    }

    this->currentPhase = 1;
}

// Keep sprite behind player and change the frame
void Weapon::phase1(bool reverse) {
    std::cout << "Phase 1\n";
    this->textureRect = sf::IntRect(64, 0, 64, 128);
    this->setTextureRect(this->textureRect);
    // Invert the sprite for the player's direction
    if (reverse) {
        this->setScale(-1.f, 1.f);
    }
    else {
        this->setScale(1.f, 1.f);
    }

    this->currentPhase = 2;
}

// Change the sprite to the attacking one
void Weapon::phase2(bool reverse) {
    std::cout << "Phase 2\n";
    this->textureRect = sf::IntRect(128, 0, 112, 128);
    this->setTextureRect(this->textureRect);
    // Invert the sprite for the player's direction
    if (reverse) {
        this->setScale(-1.f, 1.f);
    }
    else {
        this->setScale(1.f, 1.f);
    }

    this->currentPhase = 3;
}

// Repetition of phase 3, necessary for a longer attack time
void Weapon::phase3(bool reverse) {
    std::cout << "Phase 3\n";

    this->currentPhase = 4;
}

// Attack finished, make the sprite invisible
void Weapon::phase4(bool reverse) {
    std::cout << "Phase 4\n";
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

sf::SoundBuffer* Weapon::getAttackSound() {
    return &this->attackSound;
}