#include "Camera2D.h"


Camera2D::Camera2D(float left, float right, float bottom, float top) {
	this->projectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
	this->viewMatrix = glm::mat4(1.0f);
	this->cameraPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	this->cameraSpeed = 1.0f;
	this->zoomFactor = 1.0f;
	this->cameraRotationFactor = 0.0f;
	this->offset = glm::vec3(0.0f, 0.0f, 0.0f);
	this->projectionViewMatrix = this->projectionMatrix * this->viewMatrix;
	
}

void Camera2D::updateProjectionViewMatrix() {
	glm::mat4 trans = glm::mat4(1.0f); 
	trans = glm::inverse(glm::translate(trans, this->cameraPosition + this->offset));
	trans = glm::rotate(trans, this->cameraRotationFactor, glm::vec3(0.0f,0.0f, 1.0f));
	this->viewMatrix = glm::scale(trans,glm::vec3(zoomFactor, zoomFactor, 0.0f));
	this->projectionViewMatrix = this->projectionMatrix * this->viewMatrix;
}
 
void Camera2D::moveCamera(glm::vec2 directionPosition, float dt) {
	this->cameraPosition.x += directionPosition.x * this->cameraSpeed * dt;
	this->cameraPosition.y += directionPosition.y * this->cameraSpeed * dt;
	updateProjectionViewMatrix();
} 
void Camera2D::rotateCamera(float rotate, float dt) {
	this->cameraRotationFactor = glm::mix(this->cameraRotationFactor, rotate, this->cameraSpeed*dt);
	updateProjectionViewMatrix();
}

void Camera2D::zoomCamera(float zoomFactor, float dt) {
	this->zoomFactor = glm::mix(this->zoomFactor, zoomFactor,this->cameraSpeed * dt);
	updateProjectionViewMatrix();
}

glm::mat4 Camera2D::getProjectionViewMatrix() {
	return this->projectionViewMatrix;
}


 /*void Camera2D::setCameraPostion(glm::vec3 cPos) {
	 this->cameraPosition = cPos;
}*/

 //void Camera2D::setCameraSpeed(float speed) {
	// this->cameraSpeed = speed;
 //}

 /*float Camera2D::getCameraSpeed() {
	return this->cameraSpeed;
 }*/