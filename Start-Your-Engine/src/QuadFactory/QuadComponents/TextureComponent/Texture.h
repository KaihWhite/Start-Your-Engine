#pragma once
#include<GLFW/glfw3.h>
#include <stb_image.h>
class Texture
{
public:
	unsigned int textureID;
	int width, height, nrChannels;
	unsigned char* data;
	Texture(const char*);
	unsigned char* loadTexture(const char*);
	void generateTexture();
	void use();
};


