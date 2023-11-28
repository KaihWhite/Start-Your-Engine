#pragma once

#include"Camera2D.h"
class Camera2DSystem
{

public:
	Camera2DSystem(float width, float height);
	void setBoundaries(float minX, float maxX, float minY, float maxY);
	Camera2D& getCamera();
	// camera effects
	void follow(float targetX, float targetY, float dt);
	void lookAheadCameraMovement(float offsetX, float offsetY, float offsetSpeed, float dt);
	void transitionTo(float positionX, float positionY, float transtionSpeed, float dt);

private:
	Camera2D camera;
	glm::vec3 targetPosition;
	float minX, maxX, minY, maxY; 
	
};

