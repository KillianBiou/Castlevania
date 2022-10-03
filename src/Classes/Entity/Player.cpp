#include "Player.h"
#include "../Manager/Animator.h"
#include "../Manager/EntityManager.h"

Player::Player(std::string texturePath, sf::Vector2f pos, int frameDelay, const int* currentLevel, const int levelXSize, float speedFactor, float jumpFactor, EntityManager* entityManager) : Entity(texturePath, pos, 64, 128, frameDelay, currentLevel, levelXSize, speedFactor, jumpFactor, entityManager) {
	this->weapon = new Weapon("images/Whip.png", 1);
	this->spriteSizeXAttack1 = 128;
	this->spriteSizeYAttack1 = 128;
	this->spriteSizeXAttack2 = 241;
	this->spriteSizeYAttack2 = 128;

	this->animator->setAnimations({ {IDLE, 1}, {RUNNING, 3}, {JUMPING, 1}, {ATTACK, 3}, {HURT, 2}, {DEATH, 4} });

	this->maxHp = 5;
	this->hp = this->maxHp;
	this->name = "Belmon";

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
		switch (this->weapon->getCurrentPhase()) {
		case 0:
			this->isAttacking = true;
			this->freeze = true;
			this->weapon->phase0(this->side == LEFT ? false : true);
			this->weapon->setPosition(this->getPosition().x - this->spriteSizeX / 2.f + 64, this->getPosition().y - this->spriteSizeY / 2.f);
			if (this->side == RIGHT) {
				this->weapon->move(-64.f, 0.f);
				this->weaponPositionModifier = sf::Vector2f(-32.f, -64.f);
			}
			else {
				this->weaponPositionModifier = sf::Vector2f(32.f, -64.f);
			}
			break;
		case 1:
			this->weapon->phase1(this->side == LEFT ? false : true);
			break;
		case 2:
			this->weapon->phase2(this->side == LEFT ? false : true);
			this->weapon->move(-176.f * this->side * -1, 0.f);
			this->weaponPositionModifier.x += -176.f * this->side * -1;
			break;
		case 3:
			this->weapon->phase3(this->side == LEFT ? false : true);
			this->freeze = false;
			this->setHorizontalMovement(NONE);
			this->weapon->move(176.f * this->side * -1, 0.f);
			this->weaponPositionModifier.x += 176.f * this->side * -1;
			
			for (Entity* entity : this->entityManager->detectCollision(this->hitboxWeapon.getGlobalBounds())) {
				std::cout << "Hit : " << entity->getName() << std::endl;
				entity->takeDamage(this->weapon->getDamage());
			}
			this->isAttacking = false;
			break;
		}
	}
}

void Player::update() {
	Entity::update();
	this->updateAnim();
	this->updateHitboxWeapon();
}

void Player::updateAnim() {
	this->debugAnim = "IDLE";
	Animation tempAnim = IDLE;
	if(this->moveDirection != NONE){
		this->debugAnim = "RUNNING";
		tempAnim = RUNNING;
	}
	if (this->verticalVelocity != 0) {
		this->debugAnim = "JUMPING";
		tempAnim = JUMPING;
	}
	if (this->isHurt) {
		this->debugAnim = "HURT";
		tempAnim = HURT;
	}
	if (this->isAttacking) {
		this->debugAnim = "ATTACKING";
		tempAnim = ATTACK;
	}
	if (this->hp <= 0) {
		this->debugAnim = "DEATH";
		tempAnim = DEATH;
	}

	this->animator->playAnimation(tempAnim);
}

void Player::takeDamage(int amount) {
	if (!this->isInvulnerable()) {
		Entity::takeDamage(amount);
		invulnerabilityClock.restart();
	}
}

void Player::updateHitboxWeapon() {
	if (side == RIGHT) {
		this->hitboxWeapon.setPosition(this->getPosition() + sf::Vector2f(this->spriteSizeX / 2.f, -24.f));
		this->hitboxWeapon.setSize(sf::Vector2f(112.f, 24.f));
		this->weapon->setPosition(this->getPosition() + this->weaponPositionModifier);
	}
	else {
		this->hitboxWeapon.setPosition(this->getPosition() - sf::Vector2f(this->spriteSizeX / 2.f, 24.f));
		this->hitboxWeapon.setSize(sf::Vector2f(-112.f, 24.f));
		this->weapon->setPosition(this->getPosition() + this->weaponPositionModifier);
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
	this->weapon->setTextureRect(sf::IntRect(0, 0, 0, 0));
	this->freeze = true;
	this->dead = true;
}