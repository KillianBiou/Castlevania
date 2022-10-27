#include "HealthBar.h"

HealthBar::HealthBar(std::string fontPath): entity(entity) {
    if (!this->font.loadFromFile(fontPath)) {
        std::cout << "Error while loading : " << fontPath << std::endl;
    }
    if (!this->heartTexture.loadFromFile("images/Heart.png")) {
        std::cout << "Error while loading : " << "images/Heart.png" << std::endl;
    }

    this->filledHeartRect = sf::IntRect(0, 0, 63, 63);
    this->emptyHeartRect = sf::IntRect(63, 0, 63, 63);

    this->text.setFont(this->font);
    this->text.setCharacterSize(63);
}

void HealthBar::updateHeart() {
    // If the player have more max hp than displayed on the bar, add more
    while (this->hearts.size() < this->entity->getMaxHp()) {
        this->hearts.push_back(sf::Sprite(this->heartTexture, filledHeartRect));
    }

    // Set the corresponding texture for filled/empty hp depending on target's current hp
    for (int i = 0; i < this->hearts.size(); i++) {
        sf::Sprite* currentSprite = &hearts.at(i);
        if (i < this->entity->getHp()) {
            currentSprite->setTextureRect(this->filledHeartRect);
        }
        else {
            currentSprite->setTextureRect(this->emptyHeartRect);
        }

        // Put the hp bar to the right place
        currentSprite->setPosition(this->getPosition() + sf::Vector2f(this->text.getGlobalBounds().width + 20 + 65 * i, 10.f));
    }
}

void HealthBar::setEntity(Entity* entity) {
    this->entity = entity;
    this->text.setString(this->entity->getName());
}

void HealthBar::update() {
    if (this->entity) {
        this->text.setPosition(this->getPosition() + sf::Vector2f(10.f, 5.f));
        this->updateHeart();
    }
}

void HealthBar::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(this->text);
    for (sf::Sprite heart : this->hearts) {
        target.draw(heart);
    }
}