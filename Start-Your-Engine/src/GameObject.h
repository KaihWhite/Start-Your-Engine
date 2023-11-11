#pragma once
#include "glm/glm.hpp"
#include "renderer.h"
#include "texture.h"
#include "Animation.h"
#include <GLFW/glfw3.h>
#include <unordered_map>


class GameObject
{
public:
	std::unordered_map<std::string, Animation*> animations;
	std::string currentAnimation = "idle";

	glm::vec2 position, size, velocity;
	float rotation;
	glm::vec3 color;

	// TODO: do something with these
	bool collidable, gravity;

	GameObject(glm::vec2 pos, glm::vec2 size, glm::vec3 color, glm::vec2 velocity, float rotation, std::unordered_map<std::string, Animation*> animations);
	~GameObject();

	void init(bool gravity, bool collidable);

	void update(float dt);

	void physics(float dt);

	void draw(Renderer& renderer);

};