#include "Entity.h"
#include "../Manager/Animator.h"
#include "../Manager/EntityManager.h"

Entity::Entity(std::string texturePath, sf::Vector2f position, int sizeX, int sizeY, int frameDelay, const int* currentLevel, const int levelXSize, float speedFactor, float jumpFactor, EntityManager* entityManager):
               spriteSizeX(sizeX), spriteSizeY(sizeY), frameDelay(frameDelay), currentLevel(currentLevel), levelXSize(levelXSize), speedFactor(speedFactor), jumpFactor(jumpFactor) {

    if (!this->texture.loadFromFile(texturePath)) {
        std::cout << "Error while loading : " << texturePath << std::endl;
    }
    this->setTexture(this->texture);
    this->textureRect = sf::IntRect(0, 0, this->spriteSizeX, this->spriteSizeY);

    this->animator = new Animator(this, frameDelay);

    this->blockageLeft = false;
    this->blockageRight = false;
    this->moveDirection = NONE;
    this->gravityFactor = .055f;
    this->side = RIGHT;
    this->freeze = false;

    this->setOrigin(sizeX / 2, sizeY / 2);
    this->entityManager = entityManager;
}

void Entity::update() {
    this->applyGravity();
    this->moveTick();
    this->moveCollisionPoint();
    this->checkCollision();
    animator->animate();
}

void Entity::applyGravity() {
    if (!this->isGrounded) {
        this->verticalVelocity += this->gravityFactor * 9.81f;
    }
}

void Entity::moveTick() {
    float lateralMovement = 0.f;

    if (((this->moveDirection == RIGHT && !this->blockageRight) || (this->moveDirection == LEFT && !this->blockageLeft))) {
        lateralMovement = this->moveDirection * this->speedFactor;
    }
    if (freeze) {
        lateralMovement = 0.f;
    }
    this->move(lateralMovement, this->verticalVelocity);
}

void Entity::moveCollisionPoint() {
    sf::Vector2f center = this->getOrigin();
    this->groundedPoint = this->getPosition() + sf::Vector2f(0.f, this->spriteSizeY / 2.f);
    this->rightBoundPoint = this->getPosition() + sf::Vector2f(this->spriteSizeX / 2.f, (-this->spriteSizeY / 8.f) * 3);
    this->rightBoundPointBis = this->getPosition() + sf::Vector2f(this->spriteSizeX / 2.f, (this->spriteSizeY / 8.f) * 3);
    this->leftBoundPoint = this->getPosition() + sf::Vector2f(-this->spriteSizeX / 2.f, (-this->spriteSizeY / 8.f) * 3);
    this->leftBoundPointBis = this->getPosition() + sf::Vector2f(-this->spriteSizeX / 2.f, (this->spriteSizeY / 8.f) * 3);
    this->topBoundPoint = this->getPosition() + sf::Vector2f(0.f, -this->spriteSizeY / 2.f);
}

void Entity::checkCollision() {
    // Ground Check
    int xCollision = int(this->groundedPoint.x / 64);
    int yCollision = int(this->groundedPoint.y / 64);
    if (this->currentLevel[xCollision + yCollision * levelXSize] != 0) {
        this->setIsGrounded(true);
        this->setVerticalMovement(NONE);
        this->setPosition(this->getPosition().x, yCollision * 64 - spriteSizeY / 2.f);

    }
    else {
        this->setIsGrounded(false);
    }

    // Top Check
    xCollision = int(this->topBoundPoint.x / 64);
    yCollision = int(this->topBoundPoint.y / 64);
    if (this->currentLevel[xCollision + yCollision * levelXSize] != 0) {
        this->verticalVelocity = 0.f;
        this->move(0.f, 1.f);
    }

    // Right Check
    xCollision = int(this->rightBoundPoint.x / 64);
    yCollision = int(this->rightBoundPoint.y / 64);
    int xCollisionBis = int(this->rightBoundPointBis.x / 64);
    int yCollisionBis = int(this->rightBoundPointBis.y / 64);
    if ((this->currentLevel[xCollision + yCollision * levelXSize] != 0 || this->currentLevel[xCollisionBis + yCollisionBis * levelXSize] != 0) && this->moveDirection == RIGHT) {
        this->blockageRight = true;
    }
    else {
        this->blockageRight = false;
    }

    // Left Check
    xCollision = int(this->leftBoundPoint.x / 64);
    yCollision = int(this->leftBoundPoint.y / 64);
    xCollisionBis = int(this->leftBoundPointBis.x / 64);
    yCollisionBis = int(this->leftBoundPointBis.y / 64);
    if ((this->currentLevel[xCollision + yCollision * levelXSize] != 0 || this->currentLevel[xCollisionBis + yCollisionBis * levelXSize] != 0) && this->moveDirection == LEFT) {
        this->blockageLeft = true;
    }
    else {
        this->blockageLeft = false;
    }
}

void Entity::takeDamage(int amount) {
    this->hp -= amount;
    std::cout << this->name << " : lost " << amount << "hp (" << this->hp << "/" << this->maxHp << ")\n";
    if (this->hp <= 0) {
        this->die();
    }
    else {
        this->animator->playAnimation(HURT);
    }
}

void Entity::die() {
    this->dead = true;
    this->animator->playAnimation(DEATH);
}

int Entity::getSpriteSizeX() {
    return this->spriteSizeX;
}

int Entity::getSpriteSizeY() {
    return this->spriteSizeY;
}

int Entity::getSpriteSizeXAttack1() {
    return this->spriteSizeXAttack1;
}

int Entity::getSpriteSizeYAttack1() {
    return this->spriteSizeYAttack1;
}


int Entity::getSpriteSizeXAttack2() {
    return this->spriteSizeXAttack2;
}

int Entity::getSpriteSizeYAttack2() {
    return this->spriteSizeYAttack2;
}


void Entity::setHorizontalMovement(MoveDirection direction) {
    if (!this->freeze) {
        this->moveDirection = direction;
        if ((direction == RIGHT) || (direction == LEFT)) {
            this->animator->playAnimation(RUNNING);
            this->side = direction;
            this->setScale(side, 1.f);
        }
        else {
            this->animator->playAnimation(IDLE);
        }
    }
}

void Entity::setVerticalMovement(MoveDirection direction) {
    if (this->isGrounded && !this->freeze) {
        this->verticalVelocity = direction * jumpFactor;
    }
}

void Entity::setIsGrounded(bool state) {
    if (state == true && this->isGrounded == false) {
        this->animator->lockAnimation(false);
        this->animator->playAnimation(IDLE);
    }
    else if (state == false && this->isGrounded == true) {
        this->animator->playAnimation(JUMPING);
        this->animator->lockAnimation(true);
    }
    this->isGrounded = state;
}

MoveDirection Entity::getMoveDirection() {
    return this->moveDirection;
}

MoveDirection Entity::getSide() {
    return this->side;
}

sf::Vector2f Entity::getGroundedPoint() {
    return this->groundedPoint;
}

sf::Vector2f Entity::getRightBoundPoint() {
    return this->rightBoundPoint;
}

sf::Vector2f Entity::getRightBoundPointBis() {
    return this->rightBoundPointBis;
}

sf::Vector2f Entity::getLeftBoundPoint() {
    return this->leftBoundPoint;
}

sf::Vector2f Entity::getLeftBoundPointBis() {
    return this->leftBoundPointBis;
}

sf::Vector2f Entity::getTopBoundPoint() {
    return this->topBoundPoint;
}

bool Entity::getFreeze() {
    return this->freeze;
}

std::string Entity::getName() {
    return this->name;
}