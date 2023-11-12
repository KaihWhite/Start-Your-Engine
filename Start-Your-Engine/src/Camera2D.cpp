#include "Camera2D.h"


Camera2D::Camera2D(float left, float right, float bottom, float top) {
	this->projectionMatrix = glm::ortho(left,right,bottom,top,-1.0f,1.0f);
	this->viewMatrix = glm::mat4(1.0f);
}

glm::mat4 Camera2D::getPVMatrix() {
	return this->projectionMatrix * this->viewMatrix;
}
