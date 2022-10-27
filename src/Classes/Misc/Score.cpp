#include "Score.h"

Score::Score(std::string fontPath) {
    if (!this->font.loadFromFile(fontPath)) {
        std::cout << "Error while loading : " << fontPath << std::endl;
    }

    this->score = 0;

    this->text.setFont(this->font);
    this->text.setCharacterSize(32);
    this->text.setString("Score : " + std::to_string(this->score));
}

void Score::addScore(int amount) {
    this->score += amount;
    this->text.setString("Score : " + std::to_string(this->score));
}

// Update loop
void Score::update() {
    // Keep the score display to its place
    this->text.setPosition(this->getPosition() + sf::Vector2f(10.f, 5.f));
}

void Score::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(this->text);
}

int Score::getScore() {
    return this->score;
}