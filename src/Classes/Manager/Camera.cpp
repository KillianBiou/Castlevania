#include "Camera.h"

Camera::Camera(const int levelXSize, const int levelYSize) : levelXSize(levelXSize), levelYSize(levelYSize) {
	this->view = new sf::View(sf::FloatRect(0, 500, 1920, 1080));

	this->score = new Score("font/Pixel.ttf");
	this->healthBar = new HealthBar("font/Pixel.ttf");
}

float Camera::clamp(float value, float min, float max) {
	return std::max(min, std::min(value, max));
}

void Camera::trackTarget(sf::RenderTarget* renderTarget) {
	if (target) {
		sf::Vector2f targetPos = this->target->cameraTracking();
		targetPos.x = clamp(targetPos.x, this->view->getSize().x / 2, this->levelXSize * 64 - this->view->getSize().x / 2);
		targetPos.y = clamp(targetPos.y, this->view->getSize().y / 2, this->levelYSize * 64 - this->view->getSize().y / 2);
		
		sf::Vector2f direction = sf::Vector2f(targetPos.x - view->getCenter().x, targetPos.y - view->getCenter().y);
		float magnitude = sqrt(direction.x * direction.x + direction.y * direction.y);
		if (magnitude > 10) {
			direction.x = (direction.x / magnitude) * 10.f;
			direction.y = (direction.y / magnitude) * 10.f;
			this->view->move(direction);
		}
		else {
			this->view->setCenter(targetPos);
		}

		renderTarget->setView(*this->view);
	}
	this->healthBar->setPosition(view->getCenter().x - view->getSize().x / 2, view->getCenter().y - view->getSize().y / 2);
	this->score->setPosition(view->getCenter().x - view->getSize().x / 2, view->getCenter().y - view->getSize().y / 2 + 70);
	
	this->healthBar->update();
	this->score->update();

	renderTarget->draw(*this->healthBar);
	renderTarget->draw(*this->score);
}

sf::View* Camera::getView() {
	return this->view;
}

void Camera::setEntityManager(EntityManager* entityManager) {
	this->entityManager = entityManager;
}

void Camera::setTarget(Entity* target) {
	if (firstInitialisation){
		float x = clamp(target->getPosition().x, this->view->getSize().x / 2, this->levelXSize * 64 - this->view->getSize().x / 2);
		float y = clamp(target->getPosition().y, this->view->getSize().y / 2, this->levelYSize * 64 - this->view->getSize().y / 2);
		this->view->setCenter(sf::Vector2f(x, y));
	}
	this->target = target;
	this->firstInitialisation = false;
}

Score* Camera::getScore() {
	return this->score;
}

HealthBar* Camera::getHealthBar() {
	return this->healthBar;
}