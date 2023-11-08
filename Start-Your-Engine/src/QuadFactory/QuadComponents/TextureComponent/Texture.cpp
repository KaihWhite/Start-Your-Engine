#include <glad/glad.h>
#include<GLFW/glfw3.h>
#include <stb_image.h>
#include "Texture.h"
#include <iostream>



Texture::Texture(const char* imageLocatiion) {
	 this->data = loadTexture(imageLocatiion);
	 generateTexture();
}

unsigned char* Texture::loadTexture(const char* imageLocatiion) {
	stbi_set_flip_vertically_on_load(true);
	return stbi_load(imageLocatiion, &this->width, &this->height, &this->nrChannels, 0);
}

void Texture::generateTexture() {
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	
	if (this->data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, this->data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(this->data);
}

void Texture::use() {
	glBindTexture(GL_TEXTURE_2D, this->textureID);
}
