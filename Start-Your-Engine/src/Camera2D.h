#pragma once
/*
kunga ngochetsang
*/

#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
class Camera2D
{
public:
	Camera2D(float left, float right, float bottom, float top);
	glm::mat4 getPVMatrix();
	void setCameraPosition(glm::vec2);
	void moveCamera();
	void setCameraSpeed(float speed);
private:
	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;
	glm::vec3 cameraPosition;
	float cameraSpeed; 

};

