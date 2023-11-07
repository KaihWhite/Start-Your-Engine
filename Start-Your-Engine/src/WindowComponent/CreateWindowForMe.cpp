/**
	by kunga ngochetsang
*/
#include "CreateWindowForMe.h"
#include <glad/glad.h>
#include<GLFW/glfw3.h>
#include <string>
#include <iostream>


CreateWindowForMe::CreateWindowForMe(std::string wName,unsigned int w,unsigned int h) {
	CreateWindowForMe::width = w;
	CreateWindowForMe::height = h;
	CreateWindowForMe::windowName = wName;
	CreateWindowForMe::creatingWindow();
}

void CreateWindowForMe::creatingWindow() {

	// glfw initialize and version setup for opengl 3.3 as fixed
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// creating the glfw window
	window = glfwCreateWindow(width, height, windowName.c_str(), NULL, NULL);
	checkingWindowFailure();
	
	activateWindow();
	// loads the pointer functions from glfw
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
	}
}

void CreateWindowForMe::checkingWindowFailure() {
	if (window == NULL) {
		std::cout << "Failed to create a glfw window" << std::endl;
		glfwTerminate();
	}
}


void CreateWindowForMe::activateWindow() {
	// making the window as our current thread
	glfwMakeContextCurrent(window);
	
}

GLFWwindow* CreateWindowForMe::giveMeWindow() {
	return CreateWindowForMe::window;
}
void CreateWindowForMe::setWindowColorBackground(float r,float g, float b,float a) {
	glClearColor(r,g,b,a);
	glClear(GL_COLOR_BUFFER_BIT);
}
void CreateWindowForMe::pressEscToExit() {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

 void CreateWindowForMe::activateBasickeyboardInputs(){
	 pressEscToExit();
}
 void CreateWindowForMe::keyCallback(GLFWwindow* w,int key, int scancode,int action, int mod) {

 }
void CreateWindowForMe::terminateWindow() {
	glfwTerminate();
}