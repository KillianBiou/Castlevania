#include "HealthBar.h"

HealthBar::HealthBar(std::string fontPath, Entity* entity): entity(entity) {
    if (!this->font.loadFromFile(fontPath)) {
        std::cout << "Error while loading : " << fontPath << std::endl;
    }
    if (!this->heartTexture.loadFromFile("images/Heart.png")) {
        std::cout << "Error while loading : " << "images/Heart.png" << std::endl;
    }

    this->filledHeartRect = sf::IntRect(0, 0, 63, 63);
    this->emptyHeartRect = sf::IntRect(63, 0, 63, 63);

    
    for (int i = 0; i < this->entity->getMaxHp(); i++) {
        this->hearts.push_back(sf::Sprite(this->heartTexture, filledHeartRect));
    }

    this->text.setFont(this->font);
    this->text.setCharacterSize(63);
    this->text.setString(this->entity->getName());
}

void HealthBar::updateHeart() {
    for (int i = 0; i < this->hearts.size(); i++) {
        sf::Sprite* currentSprite = &hearts.at(i);
        if (i < this->entity->getHp()) {
            currentSprite->setTextureRect(this->filledHeartRect);
        }
        else {
            currentSprite->setTextureRect(this->emptyHeartRect);
        }

        currentSprite->setPosition(this->getPosition() + sf::Vector2f(this->text.getGlobalBounds().width + 20 + 65 * i, 10.f));
    }
}

void HealthBar::update() {
    this->text.setPosition(this->getPosition() + sf::Vector2f(10.f, 5.f));
    this->updateHeart();
}

void HealthBar::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(this->text);
    for (sf::Sprite heart : this->hearts) {
        target.draw(heart);
    }
}