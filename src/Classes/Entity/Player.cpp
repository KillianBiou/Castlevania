#include "Player.h"
#include "../Manager/Animator.h"
#include "../Manager/EntityManager.h"

Player::Player(std::string texturePath, sf::Vector2f pos, int frameDelay, const int* currentLevel, const int levelXSize, float speedFactor, float jumpFactor, EntityManager* entityManager) : Entity(texturePath, pos, 64, 128, frameDelay, currentLevel, levelXSize, speedFactor, jumpFactor, entityManager) {
	this->weapon = new Weapon("images/Whip.png", 1);
	this->spriteSizeXAttack1 = 128;
	this->spriteSizeYAttack1 = 128;
	this->spriteSizeXAttack2 = 241;
	this->spriteSizeYAttack2 = 128;

	this->maxHp = 5;
	this->hp = this->maxHp;
	this->name = "Player";

	this->invulnerabilityClock = sf::Clock();
	this->invulnerabilityTime = 1000.f;
	entityManager->setPlayer(this);
}

void const Player::drawChild(sf::RenderWindow* renderWindow) {
	renderWindow->draw(*this->weapon);
	//renderWindow->draw(this->hitboxWeapon);
}

void const Player::attack(bool advance) {
	if (this->animator->getCurrentAnimation() == HURT || this->dead) {
		return;
	}
	if (((!advance && this->weapon->getCurrentPhase() == 0) || advance)) {
		if (!this->isGrounded) {
			this->animator->lockAnimation(false);
		}
		switch (this->weapon->getCurrentPhase()) {
		case 0:
			this->animator->playAnimation(ATTACK);
			this->freeze = true;
			this->animator->lockAnimation(true);
			this->weapon->phase0(this->side == LEFT ? false : true);
			this->weapon->setPosition(this->getPosition().x - this->spriteSizeX / 2.f + 64, this->getPosition().y - this->spriteSizeY / 2.f);
			if (this->side == RIGHT) {
				this->weapon->move(-64.f, 0.f);
			}
			break;
		case 1:
			this->weapon->phase1(this->side == LEFT ? false : true);
			break;
		case 2:
			this->weapon->phase2(this->side == LEFT ? false : true);
			this->weapon->move(-176.f * this->side * -1, 0.f);
			break;
		case 3:
			this->weapon->phase3(this->side == LEFT ? false : true);
			this->freeze = false;
			this->animator->lockAnimation(false);
			this->animator->playAnimation(IDLE);
			this->setHorizontalMovement(NONE);
			this->weapon->move(176.f * this->side * -1, 0.f);
			
			for (Entity* entity : this->entityManager->detectCollision(this->hitboxWeapon.getGlobalBounds())) {
				std::cout << "Hit : " << entity->getName() << std::endl;
				entity->takeDamage(this->weapon->getDamage());
			}


			break;
		}
	}
}

void Player::update() {
	Entity::update();
	this->updateHitboxWeapon();
}

void Player::takeDamage(int amount) {
	if (!this->isInvulnerable()) {
		Entity::takeDamage(amount);
		this->animator->lockAnimation(true);
		invulnerabilityClock.restart();
	}
}

void Player::updateHitboxWeapon() {
	if (side == RIGHT) {
		this->hitboxWeapon.setPosition(this->getPosition() + sf::Vector2f(this->spriteSizeX / 2.f, -24.f));
		this->hitboxWeapon.setSize(sf::Vector2f(112.f, 24.f));
	}
	else {
		this->hitboxWeapon.setPosition(this->getPosition() - sf::Vector2f(this->spriteSizeX / 2.f, 24.f));
		this->hitboxWeapon.setSize(sf::Vector2f(-112.f, 24.f));
	}
}

Weapon* Player::getWeapon() {
	return this->weapon;
}

sf::RectangleShape Player::gethitboxWeapon() {
	return this->hitboxWeapon;
}

bool Player::isInvulnerable() {
	return this->invulnerabilityClock.getElapsedTime().asMilliseconds() < this->invulnerabilityTime;
}

const void Player::taskDeletion() {
	this->freeze = true;
	this->dead = true;
}