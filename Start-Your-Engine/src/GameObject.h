#pragma once
#include "glm/glm.hpp"
#include "renderer.h"
#include "texture.h"
#include "Animation.h"
#include "GLFW/glfw3.h"
#include <unordered_map>
#include "box2d/box2d.h"


class GameObject
{
public:
	std::unordered_map<std::string, Animation*> animations;
	std::string currentAnimation = "idle";

	glm::vec3 color;
	glm::vec2 size;

	b2Body* body;


	GameObject(glm::vec2 pos, glm::vec2 size, glm::vec3 color, std::unordered_map<std::string, Animation*> animations, b2World* world, bool dynam = false);
	~GameObject();

	void update(float dt);

	void physics(float dt);

	void draw(Renderer& renderer);

};
