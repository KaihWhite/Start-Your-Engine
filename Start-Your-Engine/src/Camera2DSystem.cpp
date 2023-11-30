/*
	by kunga ngochetsang
*/

#include "Camera2DSystem.h"
#include <GLFW/glfw3.h>
Camera2DSystem::Camera2DSystem(float width, float height)
	: camera(-width, width, height, -height), targetPosition(glm::vec3(0.0f, 0.0f, 0.0f))
{
	this->minX = width * 0.25;
	this->maxX = width * 0.75;
	this->minY = height * 0.75;
	this->maxY = height * 0.25;

}
Camera2D& Camera2DSystem::getCamera() {
	return this->camera;
}

void Camera2DSystem::setBoundaries(float minX, float maxX, float minY, float maxY) {
	this->minX = minX;
	this->maxX = maxX;
	this->minY = minY;
	this->maxY = maxY;
}

// camera effects
// camera follows the movement of a player or a character
void Camera2DSystem::follow(float targetX, float targetY, float followSpeed, float dt) {
	this->targetPosition = glm::vec3(targetX, targetY, 0.0f);
	glm::vec3 difference = this->targetPosition - this->camera.cameraPosition;
	float interpolationfactor = followSpeed * dt;
	
	this->camera.cameraPosition = this->camera.cameraPosition + difference * interpolationfactor;
	
	//this->camera.cameraPosition = glm::mix(this->camera.cameraPosition, targetPosition, this->camera.cameraSpeed * dt);
	camera.updateProjectionViewMatrix();
}
// transitions the camera to a specific location
void Camera2DSystem::transitionTo(float positionX, float positionY, float transitionSpeed, float dt)
{
	glm::vec3 position = glm::vec3(positionX, positionY, 0.0f);
	this->camera.cameraPosition = glm::mix(this->camera.cameraPosition, position, transitionSpeed * dt);
	camera.updateProjectionViewMatrix();
}
void Camera2DSystem::offsetCameraMovement(float offsetX, float offsetY, float offsetSpeed, float dt) {

	glm::vec3 targetOffset = glm::vec3(offsetX, offsetY, 0.0f);
	glm::vec3 difference = targetOffset - this->camera.offset;
	glm::vec3 interpolatedCameraPosition = this->camera.offset + difference * dt;
	this->camera.offset = interpolatedCameraPosition;
	camera.updateProjectionViewMatrix();
	//this->camera.moveCameraOffset(glm::vec2(offsetX, offsetY),dt);
}

void Camera2DSystem::lookAheadCameraMovement(float offsetX, float offsetY, float offsetSpeed, float dt) {
	
	glm::vec3 targetOffset = glm::vec3(offsetX, offsetY, 0.0f);
	glm::vec3 difference = targetOffset - this->camera.offset;
	glm::vec3 interpolatedCameraPosition = this->camera.offset + difference * offsetSpeed * dt;
	this->camera.offset = interpolatedCameraPosition;
	camera.updateProjectionViewMatrix();
}
void Camera2DSystem::moveCamera(glm::vec2 directionPosition, float dt) {
	
	this->camera.cameraPosition.x += directionPosition.x * this->camera.cameraSpeed * dt;
	this->camera.cameraPosition.y += directionPosition.y * this->camera.cameraSpeed * dt;
	camera.updateProjectionViewMatrix();
}
void Camera2DSystem::moveCameraOffset(glm::vec2 directionPosition, float dt) {
	
	this->camera.offset.x = glm::clamp(this->camera.offset.x, this->minX, this->maxX);
	this->camera.offset.y = glm::clamp(this->camera.offset.y, this->minY, this->maxY);
	this->camera.offset.x += directionPosition.x * this->camera.cameraSpeed * dt;
	this->camera.offset.y += directionPosition.y * this->camera.cameraSpeed * dt;
	camera.updateProjectionViewMatrix();
}
