#include "Camera2D.h"



/**
*	This is the camera constructor that creates a basic projection matrix 
*	using the glm ortho, create a basic view matrix, establishes initial 
*	class variables, and calculates the projection view matrix.
*	@param: left		((left normal vector value if the projection)
*	@param: right		(right normal vector value if the projection)
*	@param: bottom		(bottom normal vector value if the projection)
*	@param: top			(top right normal vector value if the projection)
*
*/
Camera2D::Camera2D(float left, float right, float bottom, float top) {
	this->projectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
	//this->cameraPosition = glm::vec3(right/2, bottom/2, 0.0f);
	this->cameraPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	this->cameraSpeed = 2.0f;
	this->zoomFactor = 1.0f;
	//this->cameraRotationFactor = 0.0f;
	this->offset = glm::vec3(0.0f, 0.0f, 0.0f);

	updateProjectionViewMatrix();
	
}

/**
*	This is the camera function that updates the projection view matrix.
*	It takes into account the camera position and offset in terms of scale/
*	zoom factor, and the zoom factor to scale the game objects size.
*
*/
void Camera2D::updateProjectionViewMatrix() {
	//starting base matrix
	glm::mat4 trans = glm::mat4(1.0f);
	// moves the camera center in terms of position and offset in terms of scale in the xy plane
	trans = glm::inverse(glm::translate(trans,
		(this->cameraPosition + this->offset)* this->zoomFactor));
	// rotate the camera in terms of z axis given the ritating factor
	//trans = glm::rotate(trans, this->cameraRotationFactor, glm::vec3(0.0f, 0.0f, 1.0f));
	// scaling/sooming in and out the xy plane 
	this->viewMatrix = glm::scale(trans, glm::vec3(zoomFactor, zoomFactor, 0.0f));
	// combines the projection and view matrix together into one  
	this->projectionViewMatrix = this->projectionMatrix * this->viewMatrix;
}

/**
*	This is the camera function that returns the calculated projection view matrix.
*	@return:	this->projectionViewMatrix.  type : glm::mat4
* 
*/
glm::mat4 Camera2D::getProjectionViewMatrix() {
	return this->projectionViewMatrix;
}

/**
*	This is the camera function that scales the objects in the camera's view biggier
*	or smaller to achieve the effects of camera zoom in and out in respective of the
*	x and y plane
*   @param:	zoomFactor		type: float		scaling factor for the camera
*	@param:	dt				type: float		delta time
*/
void Camera2D::zoomCamera(float zoomFactor, float dt) {
	this->zoomFactor = glm::mix(this->zoomFactor, zoomFactor,this->cameraSpeed * dt);
	updateProjectionViewMatrix();
}

//void Camera2D::rotateCamera(float rotate, float dt) {
//	this->cameraRotationFactor = glm::mix(this->cameraRotationFactor, rotate, this->cameraSpeed*dt);
//	updateProjectionViewMatrix();
//}






 /*void Camera2D::setCameraPostion(glm::vec3 cPos) {
	 this->cameraPosition = cPos;
}*/

 //void Camera2D::setCameraSpeed(float speed) {
	// this->cameraSpeed = speed;
 //}

 /*float Camera2D::getCameraSpeed() {
	return this->cameraSpeed;
 }*/