#include "Animation.h"
#include <iostream>

Animation::Animation(const char* spriteSheet, unsigned int totalFrames)
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