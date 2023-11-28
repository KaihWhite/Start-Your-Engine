#pragma once
#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
class Camera2D
{
public:
	//constructor of the camera
	Camera2D(float left, float right, float bottom, float top);
	void updateProjectionViewMatrix();
	glm::mat4 getProjectionViewMatrix();
	void moveCamera(glm::vec2 direction, float dt);
	void rotateCamera(float rotate, float dt);
	void zoomCamera(float zoomFactor,float dt);
	//void setCameraPostion(glm::vec3 cPos);
	//void setCameraSpeed(float speed);
	//float getCameraSpeed();
private:
	glm::mat4 projectionViewMatrix;
	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;
public:
	// components of the camera 
	glm::vec3 cameraPosition;
	glm::vec3 direction,offset;
	float cameraSpeed;
	float cameraRotationFactor;
	float zoomFactor;
	 
};

