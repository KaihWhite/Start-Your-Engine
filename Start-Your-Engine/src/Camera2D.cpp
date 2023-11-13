#include "Camera2D.h"
#include <glm/ext/quaternion_common.hpp>

/*
kunga ngochetsang
*/
Camera2D::Camera2D(float left, float right, float bottom, float top) {
	this->projectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
	this->viewMatrix = glm::mat4(1.0f);
}

glm::mat4 Camera2D::getPVMatrix() {
	return this->projectionMatrix * this->viewMatrix;
}
void Camera2D::setCameraPosition(glm::vec2 pos) {
	this->cameraPosition = glm::vec3(pos.x, -pos.y, 0.0f) * this->cameraSpeed;
	moveCamera();
}
void Camera2D::moveCamera() {
	this->viewMatrix = glm::inverse(glm::translate(glm::mat4(1.0f), this->cameraPosition));
}

void Camera2D::setCameraSpeed(float speed) {
	this->cameraSpeed = speed;
}