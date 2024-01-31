#include <iostream>
#include <glad/glad.h>
#include "GLFW/glfw3.h"

#pragma once
class FrameBuffer
{
public:
	FrameBuffer() {};

	void setupConfig(unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT);
	void startBind();
	void endBind();
	unsigned int gettextureID();
	void destroy();
	
private:
	unsigned int imguiframebufferID;
	unsigned int imguitexturebufferID;
};

