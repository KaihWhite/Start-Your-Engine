#pragma once
/*
kunga ngochetsang
*/
#include"Player.h"
#include <glm/ext/matrix_transform.hpp>
class Camera2D
{

public:
	//constructes a camera object
	Camera2D(float left, float right, float bottom, float top);
	// get methods that gets the ProjectionView matrix data
	glm::mat4 getProjectionViewMatrix();
	// gets the camera position
	glm::vec3 getCameraPostion();

	// locks the camera target to the target's position
	void setCameraPostion(glm::vec2);
	// work in progress
	void lockCameraPosition(float& targetX, float& targetY, float dt);
	void moveCamera(glm::vec2 direction,float dt);
	void setCameraSpeed(float& speed);
	void setZoomlevel();
private:
	// updates the matrix of the view and the projectionViewMatrix
	void updateProjectionViewMatrix();

private:
	// internal matrix data of the camera send to the vertex shader
	glm::mat4 projectionViewMatrix;
	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;

	// position of the camera
	glm::vec3 cameraPosition;

	// work in progress
	glm::vec3 targetPosition;
	float cameraSpeed;

};

