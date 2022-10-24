#include "Entity.h"
#include "../Manager/Animator.h"
#include "../Manager/EntityManager.h"
#include "../Manager/GameManager.h"


Entity::Entity(std::string texturePath, sf::Vector2f position, int sizeX, int sizeY, int frameDelay, float speedFactor, float jumpFactor, EntityManager* entityManager):
               spriteSizeX(sizeX), spriteSizeY(sizeY), frameDelay(frameDelay), speedFactor(speedFactor), jumpFactor(jumpFactor) {
    this->name = "Entity";
    if (!this->texture.loadFromFile(texturePath)) {
        std::cout << "Error while loading : " << texturePath << std::endl;
    }
    this->setTexture(this->texture);
    this->textureRect = sf::IntRect(0, 0, this->spriteSizeX, this->spriteSizeY);

    this->scoreOnDeath = 0;

    this->animator = new Animator(this, this->frameDelay);

    this->blockageLeft = false;
    this->blockageRight = false;
    this->moveDirection = NONE;
    this->gravityFactor = .070f;
    this->side = RIGHT;
    this->freeze = false;
    this->isHurt = false;
    this->affectedByGravity = true;
    this->timePerAttack = 1;

    this->setOrigin(sizeX / 2, sizeY / 2);
    this->entityManager = entityManager;
    this->setPosition(position);
}

void Entity::updateAll() {
    this->applyGravity();
    this->moveCollisionPoint();
    this->checkCollision();
    this->moveTick();
    animator->animate();
}

void Entity::playSfx(sf::SoundBuffer* sound) {
    this->entityManager->getGameManager()->getSoundManager()->playSoundEffect(sound);
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
    this->move(lateralMovement, 0.f);
    if (affectedByGravity) {
        this->move(0.f, this->verticalVelocity);
    }
}

void Entity::moveCollisionPoint() {
    sf::Vector2f center = this->getOrigin();
    this->groundedPoint = this->getPosition() + sf::Vector2f(-(this->spriteSizeX / 5.f) * 2.f, this->spriteSizeY / 2.f );
    this->groundedPointBis = this->getPosition() + sf::Vector2f((this->spriteSizeX / 5.f) * 2.f, this->spriteSizeY / 2.f);
    this->rightBoundPointBis = this->groundedPointBis + sf::Vector2f(5.f, -3.f);
    this->rightBoundPointPrime = this->getPosition() + sf::Vector2f(this->spriteSizeX / 2.f, 0.f);
    this->topBoundPoint = this->getPosition() + sf::Vector2f(-(this->spriteSizeX / 5.f) * 2.f, -this->spriteSizeY / 2.f);
    this->topBoundPointBis = this->getPosition() + sf::Vector2f((this->spriteSizeX / 5.f) * 2.f, -this->spriteSizeY / 2.f);
    this->rightBoundPoint = this->topBoundPointBis + sf::Vector2f(3.f, 3.f);
    this->leftBoundPoint = this->topBoundPoint + sf::Vector2f(-3.f, 3.f);
    this->leftBoundPointBis = this->groundedPoint + sf::Vector2f(-5.f, -3.f);
    this->leftBoundPointPrime = this->getPosition() + sf::Vector2f(-this->spriteSizeX / 2.f, 0.f);
}

void Entity::checkCollision() {
    Level* currentLevel = this->entityManager->getGameManager()->getLevel();
    // Ground Check
    int xCollision = int(this->groundedPoint.x / 64);
    int yCollision = int(this->groundedPoint.y / 64);
    int xCollisionBis = int(this->groundedPointBis.x / 64);
    int yCollisionBis = int(this->groundedPointBis.y / 64);
    if (((currentLevel->getLevelRaw()[xCollision + yCollision * currentLevel->getSizeX()] != 0 || currentLevel->getLevelRaw()[xCollisionBis + yCollisionBis * currentLevel->getSizeX()] != 0) && this->isGrounded == false) &&
        ((currentLevel->getLevelRaw()[xCollision + yCollision * currentLevel->getSizeX()] != 3 || currentLevel->getLevelRaw()[xCollisionBis + yCollisionBis * currentLevel->getSizeX()] != 3) && this->isGrounded == false) &&
        ((currentLevel->getLevelRaw()[xCollision + yCollision * currentLevel->getSizeX()] != 4 || currentLevel->getLevelRaw()[xCollisionBis + yCollisionBis * currentLevel->getSizeX()] != 4) && this->isGrounded == false)) {
        this->setIsGrounded(true);
        this->setVerticalMovement(NONE);
        this->setPosition(this->getPosition().x, yCollision * 64 - spriteSizeY / 2.f);

    }
    else if (((currentLevel->getLevelRaw()[xCollision + yCollision * currentLevel->getSizeX()] == 0 && currentLevel->getLevelRaw()[xCollisionBis + yCollisionBis * currentLevel->getSizeX()] == 0) && this->isGrounded == true) ||
             ((currentLevel->getLevelRaw()[xCollision + yCollision * currentLevel->getSizeX()] == 4 && currentLevel->getLevelRaw()[xCollisionBis + yCollisionBis * currentLevel->getSizeX()] == 4) && this->isGrounded == true)) {
        this->setIsGrounded(false);
    }

    // Top Check
    xCollision = int(this->topBoundPoint.x / 64);
    yCollision = int(this->topBoundPoint.y / 64);
    xCollisionBis = int(this->topBoundPointBis.x / 64);
    yCollisionBis = int(this->topBoundPointBis.y / 64);
    if ((currentLevel->getLevelRaw()[xCollision + yCollision * currentLevel->getSizeX()] != 0 || currentLevel->getLevelRaw()[xCollisionBis + yCollisionBis * currentLevel->getSizeX()] != 0)) {
        this->verticalVelocity = 0.f;
        this->move(0.f, 5.f);
    }

    // Right Check
    xCollision = int(this->rightBoundPoint.x / 64);
    yCollision = int(this->rightBoundPoint.y / 64);
    xCollisionBis = int(this->rightBoundPointBis.x / 64);
    yCollisionBis = int(this->rightBoundPointBis.y / 64);
    int xCollisionPrime = int(this->rightBoundPointPrime.x / 64);
    int yCollisionPrime = int(this->rightBoundPointPrime.y / 64);
    if (((currentLevel->getLevelRaw()[xCollision + yCollision * currentLevel->getSizeX()] != 0 || currentLevel->getLevelRaw()[xCollisionBis + yCollisionBis * currentLevel->getSizeX()] != 0 || currentLevel->getLevelRaw()[xCollisionPrime + yCollisionPrime * currentLevel->getSizeX()] != 0) && this->moveDirection == RIGHT)) {
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
    xCollisionPrime = int(this->leftBoundPointPrime.x / 64);
    yCollisionPrime = int(this->leftBoundPointPrime.y / 64);
    if (((currentLevel->getLevelRaw()[xCollision + yCollision * currentLevel->getSizeX()] != 0 || currentLevel->getLevelRaw()[xCollisionBis + yCollisionBis * currentLevel->getSizeX()] != 0 || currentLevel->getLevelRaw()[xCollisionPrime + yCollisionPrime * currentLevel->getSizeX()] != 0) && this->moveDirection == LEFT)) {
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
        this->playSfx(&this->hitSound);
        this->damageFlicker();
    }
}

void Entity::damageFlicker() {
    this->isHurt = !this->isHurt;
    if (this->isHurt) {
        this->setColor(sf::Color::Red);
    }
    else {
        this->setColor(sf::Color::White);
    }
}


void Entity::die() {
    this->playSfx(&this->deathSound);
    this->entityManager->getPlayer()->addMana(this->manaOnDeath);
    this->entityManager->addScore(this->scoreOnDeath);
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
            this->side = direction;
            this->setScale(side, 1.f);
        }
    }
}

void Entity::setVerticalMovement(MoveDirection direction) {
    if (this->isGrounded && !this->freeze) {
        this->verticalVelocity = direction * jumpFactor;
    }
    else if (direction == NONE) {
        this->verticalVelocity = direction * jumpFactor;
    }
}

void Entity::setIsGrounded(bool state) {
    this->isGrounded = state;
}

MoveDirection Entity::getMoveDirection() {
    return this->moveDirection;
}

MoveDirection Entity::getSide() {
    return this->side;
}

int Entity::getHp() {
    return this->hp;
}
int Entity::getMaxHp() {
    return this->maxHp;
}

float Entity::getTimePerAttack() {
    return this->timePerAttack;
}

sf::Vector2f Entity::getGroundedPoint() {
    return this->groundedPoint;
}

sf::Vector2f Entity::getGroundedPointBis() {
    return this->groundedPointBis;
}

sf::Vector2f Entity::getRightBoundPoint() {
    return this->rightBoundPoint;
}

sf::Vector2f Entity::getRightBoundPointBis() {
    return this->rightBoundPointBis;
}

sf::Vector2f Entity::getRightBoundPointPrime() {
    return this->rightBoundPointPrime;
}

sf::Vector2f Entity::getLeftBoundPoint() {
    return this->leftBoundPoint;
}

sf::Vector2f Entity::getLeftBoundPointBis() {
    return this->leftBoundPointBis;
}

sf::Vector2f Entity::getLeftBoundPointPrime() {
    return this->leftBoundPointPrime;
}

sf::Vector2f Entity::getTopBoundPoint() {
    return this->topBoundPoint;
}

sf::Vector2f Entity::getTopBoundPointBis() {
    return this->topBoundPointBis;
}

bool Entity::getFreeze() {
    return this->freeze;
}

std::string Entity::getName() {
    std::cout << this->name << std::endl;
    return this->name;
}

Entity::~Entity() {
}