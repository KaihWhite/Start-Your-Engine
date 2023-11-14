#pragma once
#include "GameObject.h"
#include "glm/glm.hpp"

class Player : public GameObject
{
public:

	Player(glm::vec2 pos, glm::vec2 size, glm::vec3 color, glm::vec2 velocity, float rotation, std::unordered_map<std::string, Animation*> animations);

	void move(glm::vec2 velocity);
};


//TODO: I need to allow the player object to have an array of animations/sprites that it can switch between
// currently the player class only takes one Texture2D object
