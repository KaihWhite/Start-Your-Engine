#include "Camera2DSystem.h"
#include <GLFW/glfw3.h>

Camera2DSystem::Camera2DSystem(float width, float height)
	: camera(0,width, height, 0), targetPosition(glm::vec3(0.0f,0.0f,0.0f))
{
	this->minX = 0/ 1.5;
	this->maxX = width/ 1.5;
	this->minY = 0/ 1.5;
	this->maxY = -height/1.5;
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
void Camera2DSystem::follow (float targetX, float targetY, float dt) {
	this->targetPosition = glm::vec3(targetX, targetY, 0.0f);
	this->camera.cameraPosition = glm::mix(this->camera.cameraPosition, targetPosition , this->camera.cameraSpeed * dt);
	camera.updateProjectionViewMatrix();
}
// transitions the camera to a specific location
void Camera2DSystem::transitionTo(float positionX, float positionY,float transitionSpeed, float dt)
{
	glm::vec3 position = glm::vec3(positionX, positionY, 0.0f);
	this->camera.cameraPosition = glm::mix(this->camera.cameraPosition, position, transitionSpeed * dt);
	camera.updateProjectionViewMatrix();
}

void Camera2DSystem::lookAheadCameraMovement(float offsetX, float offsetY, float offsetSpeed,float dt) {
	this->camera.offset.x = glm::clamp(this->camera.offset.x, this->minX, this->maxX);
	this->camera.offset.y = glm::clamp(this->camera.offset.y, this->minY, this->maxY);
	 
	this->camera.offset.x = glm::mix(this->camera.offset.x, offsetX, offsetSpeed * dt);
	this->camera.offset.y = glm::mix(this->camera.offset.y, offsetY, offsetSpeed * dt);

	camera.updateProjectionViewMatrix();
}

