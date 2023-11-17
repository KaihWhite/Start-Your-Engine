#include "Camera2D.h"
#include <glm/ext/quaternion_common.hpp>
#include <iostream>

/*
kunga ngochetsang


	THIS IS THE CAMERA CLASS THAT MANUPULATES THE VIEW
	AND PROJECTION MATRIX TO MOVE THE CAMERA
*/


Camera2D::Camera2D(float left, float right, float bottom, float top) {
	this->projectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
	this->viewMatrix = glm::mat4(1.0f);
	this->cameraPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	this->cameraSpeed = 2.5f;
	this->projectionViewMatrix = this->projectionMatrix * this->viewMatrix;
}

glm::mat4 Camera2D::getProjectionViewMatrix() {
	return this->projectionViewMatrix;
}

void Camera2D::setCameraPostion(glm::vec2 pos) {
	this->cameraPosition = glm::vec3(pos.x, pos.y, 0.0f);
	updateProjectionViewMatrix();
}

void Camera2D::lockCameraPosition(float& targetX, float& targetY, float dt) {
	this->targetPosition = glm::vec3(targetX, targetY, 0.0f);
	cameraPosition = glm::mix(cameraPosition, targetPosition, cameraSpeed * dt);
	updateProjectionViewMatrix();
}
void Camera2D::moveCamera(glm::vec2 direction, float dt) {
	this->cameraPosition.x += direction.x *this->cameraSpeed * dt;
	this->cameraPosition.y += direction.y * this->cameraSpeed * dt;
	updateProjectionViewMatrix();
}
void Camera2D::setCameraSpeed(float& speed) {
	this->cameraSpeed = speed;
}

void Camera2D::setZoomlevel() {
	//this->projectionMatrix = glm::ortho(left);
}

void Camera2D::updateProjectionViewMatrix() {
	this->viewMatrix = glm::inverse(glm::translate(glm::mat4(1.0f), this->cameraPosition));
	this->projectionViewMatrix = this->projectionMatrix * this->viewMatrix;
}

glm::vec3 Camera2D::getCameraPostion() {
	return this->cameraPosition;
}

