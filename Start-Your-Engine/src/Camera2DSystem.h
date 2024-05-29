#pragma once

#include"Camera2D.h"
class Camera2DSystem
{
	//	*	CLASS VARIABLES 

public: 
	bool			enableFollow;
	bool			enableLookahead;
private:
	Camera2D		camera;
	glm::vec3		targetPosition;
	float			minX, maxX, minY, maxY; 
	

	//	*	CLASS FUNCTIONS	(active)

public:
	//	Constructor
	Camera2DSystem(float width, float height);

	void setBoundaries(float minX, float maxX, float minY, float maxY);
	Camera2D& getCamera();
	void updateCamera();

	// basic camera movement
	void moveCamera(glm::vec2 direction, float dt);
	void zoomCamera(float zoomFactor, float dt);
	void moveCameraOffset(glm::vec2 directionPosition, float dt);
	
	// camera effects
	void lookAheadCameraMovement(float offsetX, float offsetY, float offsetSpeed, float dt);
	void follow(float targetX, float targetY, float followSpeed, float dt);
	void transitionTo(float positionX, float positionY, float transtionSpeed, float dt);


	//    *    CLASS FUNCTIONS    (inactive)
	
};
