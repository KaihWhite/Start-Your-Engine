// Created by Kaih White
#pragma once
#include "GameObject.h"
#include "glm/glm.hpp"
#include <string>
#include <unordered_map>
#include "box2d/box2d.h"

class Npc : public GameObject
{
	glm::vec2 position;
	glm::vec2 path;
	bool direction;

public:
	Npc(std::string name, glm::vec2 pos, glm::vec2 size, glm::vec3 color, std::unordered_map<std::string, Animation*> animations, b2World* world, std::string type, std::unordered_set<std::string> sounds, bool dynam = false);
	~Npc();
	void move(bool direction);
	void update();
	void setPath(glm::vec2 path);
	void kill();
};