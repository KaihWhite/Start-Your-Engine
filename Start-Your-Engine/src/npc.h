// Created by Kaih White
#pragma once
#include "GameObject.h"
#include "glm/glm.hpp"
#include <string>
#include <unordered_map>
#include "box2d/box2d.h"

class NPC : public GameObject
{
	int maxDistanceToPlayer;
	bool playerInRange;
	glm::vec2 playerPos;
	glm::vec2 position;
	glm::vec2 path;
	bool direction;

	float pathfind(glm::vec2 point);

public:
	NPC(std::string name, glm::vec2 pos, glm::vec2 size, glm::vec3 color, std::unordered_map<std::string, Animation*> animations, b2World* world, std::string type, bool dynam = false);
	~NPC();
	void move();
	void setMaxDistanceToPlayer(int distance);
	void checkPlayer(glm::vec2 pos);
	void setPath(float start, float end);
};