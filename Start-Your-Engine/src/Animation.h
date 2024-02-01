// Made by Kaih White
#pragma once
#include "texture.h"
#include "resource_manager.h"

class Animation {

	std::string spriteSheet;
	unsigned int totalFrames;

public:

	Animation(std::string spriteSheet, unsigned int totalFrames);
	~Animation();

	Texture2D getSpriteSheet();

	unsigned int getTotalFrames();
	std::string getSpriteSheetName();
};