#include "Player.h"
#include "../Manager/Animator.h"
#include "../Manager/EntityManager.h"
#include "../Manager/GameManager.h"

Player::Player(sf::Vector2f pos, int frameDelay, float speedFactor, float jumpFactor, EntityManager* entityManager) : Entity("images/Belmon.png", pos, 64, 128, frameDelay, speedFactor, jumpFactor, entityManager) {
	this->weapon = new Weapon("images/Whip1.png", 1, 400, "sfx/whip1.ogg");

	if (!this->knifeTexture.loadFromFile("images/Knife.png")) {
		std::cout << "Error while loading : " << "images/Knife.png" << std::endl;
	}
	if (!this->axeTexture.loadFromFile("images/Axe.png")) {
		std::cout << "Error while loading : " << "images/Axe.png" << std::endl;
	}

	this->timePerAttack = this->weapon->getTimePerAttack();
	this->spriteSizeXAttack1 = 128;
	this->spriteSizeYAttack1 = 128;
	this->spriteSizeXAttack2 = 241;
	this->spriteSizeYAttack2 = 128;

	this->manaMax = 10;
	this->mana = this->manaMax;

	this->animator->setAnimations({ {IDLE, 1}, {RUNNING, 3}, {JUMPING, 1}, {ATTACK, 4}, {HURT, 2}, {DEATH, 4} });

	this->maxHp = 3;
	this->hp = this->maxHp;
	this->name = "Belmon";

	this->jumpSound = sf::SoundBuffer();
	this->jumpSound.loadFromFile("sfx/jump.wav");
	this->hitSound.loadFromFile("sfx/pHurt.wav");

	this->specialClock = sf::Clock();
	this->invulnerabilityClock = sf::Clock();
	this->invulnerabilityTime = 1000.f;
	entityManager->setPlayer(this);
}

void const Player::drawChild(sf::RenderTarget* renderTarget) {
	renderTarget->draw(*this->weapon);
	//renderWindow->draw(this->hitboxWeapon);
}

const sf::Vector2f Player::cameraTracking() {
	return this->getPosition();
}

EntityManager* Player::getEntityManager() {
	return this->entityManager;
}

void const Player::attack(bool advance) {
	if (this->animator->getCurrentAnimation() == HURT || this->dead) {
		return;
	}
	if (((!advance && this->weapon->getCurrentPhase() == 0) || advance)) {
		switch (this->weapon->getCurrentPhase()) {
		case 0:
			this->entityManager->getGameManager()->getSoundManager()->playSoundEffect(this->weapon->getAttackSound());
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

			for (Entity* entity : this->entityManager->detectCollisionMonster(this->hitboxWeapon.getGlobalBounds())) {
				std::cout << "Hit : " << entity->getName() << std::endl;
				this->alreadyHit.push_back(entity);
				entity->takeDamage(this->weapon->getDamage());
			}
			break;
		case 4:
			this->weapon->phase4(this->side == LEFT ? false : true);
			this->freeze = false;
			this->setHorizontalMovement(NONE);
			this->weapon->move(176.f * this->side * -1, 0.f);
			this->weaponPositionModifier.x += 176.f * this->side * -1;
			
			for (Entity* entity : this->entityManager->detectCollisionMonster(this->hitboxWeapon.getGlobalBounds())) {
				if(std::find(this->alreadyHit.begin(), this->alreadyHit.end(), entity) == this->alreadyHit.end()) {
					std::cout << entity->getName() << std::endl;
					std::cout << "Hit : " << entity->getName() << std::endl;
					entity->takeDamage(this->weapon->getDamage());
				}
			}
			this->alreadyHit.clear();
			this->isAttacking = false;
			break;
		}
	}
}

void Player::specialOne() {
	if (this->mana >= 1 && this->specialClock.getElapsedTime().asMilliseconds() >= this->specialCooldown) {
		std::cout << "Knife" << std::endl;
		this->specialClock.restart();
		this->mana--;
		StraightProjectile* temp = new StraightProjectile(this->knifeTexture, 64, 64, this->getPosition(), 15.f, sf::Vector2f(this->getPosition().x + 10 * this->getScale().x, this->getPosition().y), 1);
		temp->setOrigin(32, 32);
		temp->setScale(-this->getScale().x, 1.f);
		this->entityManager->addAllyProjectile(temp);
	}
}

void Player::specialTwo() {
	if (this->mana >= 1 && this->specialClock.getElapsedTime().asMilliseconds() >= this->specialCooldown) {
		std::cout << "Axe" << std::endl;
		this->specialClock.restart();
		this->mana--;
		ParabolicProjectile* temp = new ParabolicProjectile(this->axeTexture, 64, 64, this->getPosition() - sf::Vector2f(0.f, this->spriteSizeY / 2), 0.65f, 500 *  this->getScale().x, 4);
		temp->setOrigin(32, 32);
		temp->setScale(-this->getScale().x, 1.f);
		this->entityManager->addAllyProjectile(temp);
	}
}

void Player::update() {
	this->updateAll();
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
		if (!this->dead && this->hp <= 0) {
			this->die();
		}
	}
}

void Player::jump() {
	if (this->isGrounded)
		this->playSfx(&this->jumpSound);
	this->setVerticalMovement(UP);
}

void Player::changeWeapon(Weapon* weapon) {
	delete this->weapon;
	this->weapon = weapon;
	this->timePerAttack = weapon->getTimePerAttack();
}

void Player::triggerEnd() {
	this->entityManager->getGameManager()->fadeOut();
}

void Player::addHp(int amount) {
	if (this->hp + amount <= this->maxHp) {
		this->hp += amount;
	}
}

void Player::addMaxHp(int amount) {
	if (this->maxHp + amount <= 10) {
		this->maxHp += amount;
	}
	this->hp = this->maxHp;
}

void Player::addMana(int amount) {
	this->mana += amount;
	if (this->mana > this->manaMax) {
		this->mana = this->manaMax;
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

void Player::die() {
	Entity::die();
	this->entityManager->getGameManager()->fadeDeath();
}

void Player::setMaxHp(int amount) {
	this->maxHp = amount;
	this->hp = amount;
}

Weapon* Player::getWeapon() {
	return this->weapon;
}

sf::RectangleShape Player::gethitboxWeapon() {
	return this->hitboxWeapon;
}

int Player::getMana() {
	return this->mana;
}

int Player::getMaxMana() {
	return this->manaMax;
}

bool Player::isInvulnerable() {
	return this->invulnerabilityClock.getElapsedTime().asMilliseconds() < this->invulnerabilityTime;
}

const void Player::taskDeletion() {
	this->weapon->setTextureRect(sf::IntRect(0, 0, 0, 0));
	this->freeze = true;
	this->dead = true;
}