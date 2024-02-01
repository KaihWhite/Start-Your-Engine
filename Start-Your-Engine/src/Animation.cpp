// Made by Kaih White
#include "Animation.h"
#include <iostream>

Animation::Animation(std::string spriteSheet, unsigned int totalFrames)
	: spriteSheet(spriteSheet), totalFrames(totalFrames)
{
}

Animation::~Animation() {
}

Texture2D Animation::getSpriteSheet() {
	ResourceManager::GetShader("anim").Use().SetInteger("totalFrames", this->totalFrames);
	return ResourceManager::GetTexture(spriteSheet);
}

unsigned int Animation::getTotalFrames() {
	return totalFrames;
}

std::string Animation::getSpriteSheetName() {
	return spriteSheet;
}