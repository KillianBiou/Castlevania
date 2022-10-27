#include "Camera.h"
#include "GameManager.h"

Camera::Camera() {
	this->view = new sf::View(sf::FloatRect(0, 500, 1920, 1080));

	this->score = new Score("font/Pixel.ttf");
	this->healthBar = new HealthBar("font/Pixel.ttf");
	this->manaBar = new ManaBar("font/Pixel.ttf");
}

float Camera::clamp(float value, float min, float max) {
	return std::max(min, std::min(value, max));
}

void Camera::trackTarget(sf::RenderTarget* renderTarget) {
	if (!this->entityManager) {
		return;
	}
	this->levelXSize = this->entityManager->getGameManager()->getLevel()->getSizeX();
	this->levelYSize = this->entityManager->getGameManager()->getLevel()->getSizeY();
	if (target) {
		// Clamp the view within the level (Dont display part of outside the level)
		sf::Vector2f targetPos = this->target->cameraTracking();
		targetPos.x = clamp(targetPos.x, this->view->getSize().x / 2, this->levelXSize * 64 - this->view->getSize().x / 2);
		targetPos.y = clamp(targetPos.y, this->view->getSize().y / 2, this->levelYSize * 64 - this->view->getSize().y / 2);
		
		// Teleport the player isnteed of a smooth travling
		if (this->teleportToTarget) {
			this->view->setCenter(targetPos);
			this->teleportToTarget = false;
		}
		else {
			// Do a travelling toward target position
			sf::Vector2f direction = sf::Vector2f(targetPos.x - view->getCenter().x, targetPos.y - view->getCenter().y);
			float magnitude = sqrt(direction.x * direction.x + direction.y * direction.y);
			if (magnitude > 10) {
				direction.x = (direction.x / magnitude) * 15.f;
				direction.y = (direction.y / magnitude) * 15.f;
				this->view->move(direction);
			}
			// If the target pos is not too far, teleport to it
			else {
				this->view->setCenter(targetPos);
			}
		}

		renderTarget->setView(*this->view);
	}
	// Set HUD position
	this->healthBar->setPosition(view->getCenter().x - view->getSize().x / 2, view->getCenter().y - view->getSize().y / 2);
	this->manaBar->setPosition(view->getCenter().x - view->getSize().x / 2, view->getCenter().y - view->getSize().y / 2 + 70);
	this->score->setPosition(view->getCenter().x - view->getSize().x / 2, view->getCenter().y - view->getSize().y / 2 + 140);
	
	this->healthBar->update();
	this->manaBar->update();
	this->score->update();

	renderTarget->draw(*this->healthBar);
	renderTarget->draw(*this->manaBar);
	renderTarget->draw(*this->score);
}

sf::View* Camera::getView() {
	return this->view;
}

void Camera::setEntityManager(EntityManager* entityManager) {
	this->entityManager = entityManager;
}

void Camera::setTarget(Entity* target) {
	// On game startup, teleport the camera straight to the player
	if (firstInitialisation){
		float x = clamp(target->getPosition().x, this->view->getSize().x / 2, this->levelXSize * 64 - this->view->getSize().x / 2);
		float y = clamp(target->getPosition().y, this->view->getSize().y / 2, this->levelYSize * 64 - this->view->getSize().y / 2);
		this->view->setCenter(sf::Vector2f(x, y));
		teleportToTarget = true;
	}
	this->target = target;
	this->firstInitialisation = false;
}

void Camera::reset() {
	this->target = nullptr;
}

void Camera::teleport() {
	this->teleportToTarget = true;
}

sf::Vector2f Camera::getTargetPos() {
	sf::Vector2f targetPos = this->target->cameraTracking();
	targetPos.x = clamp(targetPos.x, this->view->getSize().x / 2, this->levelXSize * 64 - this->view->getSize().x / 2);
	targetPos.y = clamp(targetPos.y, this->view->getSize().y / 2, this->levelYSize * 64 - this->view->getSize().y / 2);
	return targetPos;
}

Score* Camera::getScore() {
	return this->score;
}

HealthBar* Camera::getHealthBar() {
	return this->healthBar;
}

ManaBar* Camera::getManaBar() {
	return this->manaBar;
}