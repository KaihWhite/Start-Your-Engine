#pragma once
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
class Camera2D
{
public:
	Camera2D(float left,float right, float bottom,float top);
	glm::mat4 getPVMatrix();
private:
	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;
};

