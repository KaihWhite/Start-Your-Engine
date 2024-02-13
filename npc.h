#pragma once
#include "GameObject.h"
#include "glm/glm.hpp"
#include <string>
#include <unordered_map>
#include "Animation.h"
#include "box2d/box2d.h"

class NPC : public GameObject
{
	bool isPlayerNear;
public:
	NPC(std::string name, glm::vec2 pos, glm::vec2 size, glm::vec3 color, std::unordered_map<std::string, Animation*> animations, b2World* world, std::string type, bool dynam = false);
	~NPC();
	void move();
	void checkPlayer();
};