#include "ManaBar.h"

ManaBar::ManaBar(std::string fontPath) {
    if (!this->font.loadFromFile(fontPath)) {
        std::cout << "Error while loading : " << fontPath << std::endl;
    }
    if (!this->manaTexture.loadFromFile("images/Mana.png")) {
        std::cout << "Error while loading : " << "images/Mana.png" << std::endl;
    }

    this->filledManaRect = sf::IntRect(0, 0, 63, 63);
    this->emptyManaRect = sf::IntRect(63, 0, 63, 63);

    this->text.setFont(this->font);
    this->text.setCharacterSize(63);
}

void ManaBar::updateMana() {
    // If the player have more max mana than displayed on the bar, add more
    while (this->mana.size() < this->player->getMaxMana()) {
        this->mana.push_back(sf::Sprite(this->manaTexture, this->filledManaRect));
    }

    // Set the corresponding texture for filled/empty mana depending on target's current mana
    for (int i = 0; i < this->mana.size(); i++) {
        sf::Sprite* currentSprite = &mana.at(i);
        if (i < this->player->getMana()) {
            currentSprite->setTextureRect(this->filledManaRect);
        }
        else {
            currentSprite->setTextureRect(this->emptyManaRect);
        }
        // Put the mana bar to the right place
        currentSprite->setPosition(this->getPosition() + sf::Vector2f(this->text.getGlobalBounds().width + 20 + 65 * i, 10.f));
    }
}

void ManaBar::setPlayer(Player* player) {
    this->player = player;
    this->text.setString(this->player->getName());
}

void ManaBar::update() {
    if (this->player) {
        this->text.setPosition(this->getPosition() + sf::Vector2f(10.f, 5.f));
        this->updateMana();
    }
}

void ManaBar::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (sf::Sprite mana : this->mana) {
        target.draw(mana);
    }
}