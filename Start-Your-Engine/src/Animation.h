// Made by Kaih White
#pragma once
#include "texture.h"
#include "resource_manager.h"

class Animation {

	const char* spriteSheet;
	unsigned int totalFrames;

public:

	Animation(const char* spriteSheet, unsigned int totalFrames);
	~Animation();

	Texture2D getSpriteSheet();

	unsigned int getTotalFrames();
};