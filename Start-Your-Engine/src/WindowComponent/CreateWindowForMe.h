#pragma once

/**
	by kunga ngochetsang
*/
#include<glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
class CreateWindowForMe
{
private:
	std::string windowName;
	unsigned int width;
	unsigned int height;
	GLFWwindow* window;

	void creatingWindow();
	void checkingWindowFailure();
protected:

public:
	CreateWindowForMe(std::string , unsigned int , unsigned int );
	void activateWindow();
	void setWindowColorBackground(float,float,float,float);
	GLFWwindow* giveMeWindow();
	void keyCallback(GLFWwindow*, int, int,int, int);
	void activateBasickeyboardInputs();
	void pressEscToExit();
	void terminateWindow();
	
};

