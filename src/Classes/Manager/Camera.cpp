#include "Camera.h"

Camera::Camera(const int levelXSize, const int levelYSize) : levelXSize(levelXSize), levelYSize(levelYSize) {
	this->view = new sf::View(sf::FloatRect(0, 0, 1920, 1080));
}

float Camera::clamp(float value, float min, float max) {
	return std::max(min, std::min(value, max));
}

void Camera::trackTarget(sf::RenderTarget* renderTarget) {
	if (target) {
		sf::Vector2f targetPos = this->target->cameraTracking();
		this->view->setCenter(clamp(targetPos.x, this->view->getSize().x / 2, this->levelXSize * 64 - this->view->getSize().x / 2),
			clamp(targetPos.y, this->view->getSize().y / 2, this->levelYSize * 64 - this->view->getSize().y / 2));
		renderTarget->setView(*this->view);
	}
}

sf::View* Camera::getView() {
	return this->view;
}

void Camera::setEntityManager(EntityManager* entityManager) {
	this->entityManager = entityManager;
}

void Camera::setTarget(Entity* target) {
	this->target = target;
}

Score* Camera::getScore() {
	return this->score;
}