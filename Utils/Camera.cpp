#include "Camera.h"

Camera::Camera() {
	this->position = glm::vec2(0, 0);
	this->viewMatrix = glm::lookAt(glm::vec3(0, 0, 1), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
}

Camera::~Camera() {

}

const glm::vec2 &Camera::getPosition() const {
	return position;
}

const GLfloat Camera::getPositionX() const {
	return this->position.x;
}

const GLfloat Camera::getPositionY() const {
	return this->position.y;
}


void Camera::setPosition(const glm::vec2 &position) {
	this->viewMatrix = glm::lookAt(glm::vec3(position, 1), glm::vec3(position, -1), glm::vec3(0, 1, 0));
	Camera::position = position;
}

void Camera::setPosition(GLfloat x, GLfloat y) {
	setPosition(glm::vec2(x, y));
	this->viewMatrix = glm::lookAt(glm::vec3(this->position, 1), glm::vec3(this->position, -1), glm::vec3(0, 1, 0));
}

glm::mat4 Camera::getViewMatrix() {
	return this->viewMatrix;
}

void Camera::translate(glm::vec2 vector) {
	this->position += vector;
	this->viewMatrix = glm::lookAt(glm::vec3(this->position, 1), glm::vec3(this->position, -1), glm::vec3(0, 1, 0));
}

void Camera::translate(GLfloat x, GLfloat y) {
	translate(glm::vec2(x, y));
}
