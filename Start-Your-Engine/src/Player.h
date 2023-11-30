#pragma once
#include "GameObject.h"
#include "glm/glm.hpp"

class Player : public GameObject
{
public:
	bool onPlatform;
	
	Player(glm::vec2 pos, glm::vec2 size, glm::vec3 color, std::unordered_map<std::string, Animation*> animations, b2World* world, bool dynam = false);
	void move(bool Keys[1024]);
};


//TODO: I need to allow the player object to have an array of animations/sprites that it can switch between
// currently the player class only takes one Texture2D object
