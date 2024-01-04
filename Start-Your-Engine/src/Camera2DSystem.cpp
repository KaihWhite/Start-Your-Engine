/*
	by kunga ngochetsang
*/

#include "Camera2DSystem.h"
#include <GLFW/glfw3.h>

/**	
* this is the constructor of Camera2DSystem that initalizes the camera
* object and the target position and the bounds of the camera movement
*
*/
Camera2DSystem::Camera2DSystem(float width, float height)
	: camera(-width, width, height, -height), targetPosition(glm::vec3(0.0f, 0.0f, 0.0f))
{
	this->minX = -width * 0.75;
	this->maxX = width * 0.75;
	this->minY = height * 0.75;
	this->maxY = -height * 0.75;

} 

/**
* this is the Camera2DSystem Function that retrieves the camera position
*	@return the camera
*/
Camera2D& Camera2DSystem::getCamera() {
	return this->camera;
}

/**
* this is the Camera2DSystem Function that sets the camera bounds
* 
*/
void Camera2DSystem::setBoundaries(float minX, float maxX, float minY, float maxY) {
	this->minX = minX;
	this->maxX = maxX;
	this->minY = minY;
	this->maxY = maxY;
}

// camera effects
/**
*	This is the camerasystem function that follows the movement of a player or a character
*	It takes in target x and y position  along with the follow speed and delta time
*	@param	targetX		the x position of the target						type: float
*   @param	targetY		the y position of the target						type: float
*	@param	speed		the speed of the camera that follows the target		type: float
*	@param	deltaTime	the delta time 										type: float
*/ 
void Camera2DSystem::follow(float targetX, float targetY, float followSpeed, float dt) {
	this->targetPosition = glm::vec3(targetX, targetY, 0.0f);
	glm::vec3 difference = this->targetPosition - this->camera.cameraPosition;
	float interpolationfactor = followSpeed * dt;
	
	this->camera.cameraPosition = this->camera.cameraPosition + difference * interpolationfactor;
	
	//this->camera.cameraPosition = glm::mix(this->camera.cameraPosition, targetPosition, this->camera.cameraSpeed * dt);
	camera.updateProjectionViewMatrix();
}
// transitions the camera to a specific location
/**
*	This is the camerasystem function that transitions the camera to a specific location 
*   @param    positionX			the x position of the target                        type: float
*	@param    positionY			the y position of the target                        type: float
*	@param    transitionSpeed   the duration of the transition                        type: float
*	@param    dt       the delta time 										type: float
*/
void Camera2DSystem::transitionTo(float positionX, float positionY, float transitionSpeed, float dt)
{
	glm::vec3 position = glm::vec3(positionX, positionY, 0.0f);
	this->camera.cameraPosition = glm::mix(this->camera.cameraPosition, position, transitionSpeed * dt);
	camera.updateProjectionViewMatrix();
}
/**
*	This is the camerasystem function that shifts the camera's offset from the target position
*   so that the player can see objects infront of the player
*   @param    positionX			the x position of the target                        type: float
*	@param    positionY			the y position of the target                        type: float
*	@param    transitionSpeed   the duration of the transition                        type: float
*	@param    dt       the delta time 										type: float
*/
void Camera2DSystem::lookAheadCameraMovement(float offsetX, float offsetY, float offsetSpeed, float dt) {
	
	glm::vec3 targetOffset = glm::vec3(offsetX, offsetY, 0.0f);
	glm::vec3 difference = targetOffset - this->camera.offset;
	glm::vec3 interpolatedCameraPosition = this->camera.offset + difference * offsetSpeed * dt;
	this->camera.offset = interpolatedCameraPosition;
	camera.updateProjectionViewMatrix();
}


//camera movement
/**
*   This is the camrasystem function that moves the camera position in a direction by 
*	updating camera position with the given camera speed and delta time
*   @param    directionPosition		vector position of the direction of the canera        type: float
*	@param    dt	                delta time 										type: float
*/
void Camera2DSystem::moveCamera(glm::vec2 directionPosition, float dt) {
	
	this->camera.cameraPosition.x += directionPosition.x * this->camera.cameraSpeed * dt;
	this->camera.cameraPosition.y += directionPosition.y * this->camera.cameraSpeed * dt;
	camera.updateProjectionViewMatrix();
}

/**
*   This is the camrasystem function that moves the camera offset in a direction by
*    updating camera offset with the given camera speed and delta time
*   @param    directionPosition        vector position of the direction of the canera   type: float
*	@param    dt	                   delta time 										type: float
*/
void Camera2DSystem::moveCameraOffset(glm::vec2 directionPosition, float dt) {
	
	this->camera.offset.x = glm::clamp(this->camera.offset.x, this->minX, this->maxX);
	this->camera.offset.y = glm::clamp(this->camera.offset.y, this->minY, this->maxY);
	this->camera.offset.x += directionPosition.x * this->camera.cameraSpeed * dt;
	this->camera.offset.y += directionPosition.y * this->camera.cameraSpeed * dt;
	camera.updateProjectionViewMatrix();
}
