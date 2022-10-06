#include "Collectible.h"

Collectible::Collectible(std::string texturePath, sf::IntRect textureRect, const int* level, const int X_SIZE): level(level), X_SIZE(X_SIZE) {
    if (!this->texture.loadFromFile(texturePath)) {
        std::cout << "Error while loading : " << texturePath << std::endl;
    }
    this->setTexture(this->texture);
    this->setTextureRect(textureRect);
}

void Collectible::moveGroundedPoint() {
    this->groundedPoint1 = this->getPosition() + sf::Vector2f(-(this->getTextureRect().width / 5.f) * 2.f, this->getTextureRect().height * this->getScale().y);
    this->groundedPoint2 = this->getPosition() + sf::Vector2f((this->getTextureRect().width / 5.f) * 2.f, this->getTextureRect().height * this->getScale().y);
}

void Collectible::checkGrounded() {
    int xCollision = int(this->groundedPoint1.x / 64);
    int yCollision = int(this->groundedPoint1.y / 64);
    int xCollisionBis = int(this->groundedPoint2.x / 64);
    int yCollisionBis = int(this->groundedPoint2.y / 64);
    if ((this->level[xCollision + yCollision * this->X_SIZE] != 0 || this->level[xCollisionBis + yCollisionBis * this->X_SIZE] != 0) && this->isGrounded == false) {
        this->isGrounded = true;
    }
    else if ((this->level[xCollision + yCollision * this->X_SIZE] == 0 && this->level[xCollisionBis + yCollisionBis * this->X_SIZE] == 0) && this->isGrounded == true) {
        this->isGrounded =false;
    }
}

void Collectible::moveTick() {
    if (!this->isGrounded) {
        this->move(0.f, 1.f);
    }
}

void Collectible::update() {
    this->moveGroundedPoint();
    this->checkGrounded();
    this->moveTick();
}