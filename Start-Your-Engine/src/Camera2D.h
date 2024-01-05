/*
	by Kunga Ngochetsang
*/
#pragma once
#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>

/**
*	CLASS DESCRIPTION:
*	This Camera class creates an orthographic camera 
*	by using the glm ortho.This also uses glm scale
*	to zoom in and out.This uses glm translate to 
*	move the camera position and camera offset, 
*	both respective in terms of the scale/zoom factor.
*	This camera works with the view and projection 
*	matrix manupulation, so later the resultant matrix
*	can be sent to the shader via uniform.
*
*/

class Camera2D
{
	//	*	CLASS VARIABLES 
private: 
	
	// Variables for manupulating respective matrices and storing it
	glm::mat4		projectionViewMatrix;
	glm::mat4		projectionMatrix;
	glm::mat4		viewMatrix;

public:

	//	Variables of camera components so camera system can use
	glm::vec3		cameraPosition;
	glm::vec3		direction;
	glm::vec3		offset;
	float			cameraSpeed;
	float			cameraRotationFactor;
	float			zoomFactor;


	//	*	CLASS FUNCTIONS	(active)
public:
	//	Constructor
	Camera2D(float left, float right, float bottom, float top);

	//	View matrix manupulation fuctions
	void updateProjectionViewMatrix();
	glm::mat4 getProjectionViewMatrix();
	
	//	camera manupulation fuctions
	void zoomCamera(float zoomFactor,float dt);


	//    *    CLASS FUNCTIONS	(future if needed)
	//void rotateCamera(float rotate, float dt);
	//void resize(float width,float height);
	//void setCameraSpeed(float speed);
	//float getCameraSpeed();

};

