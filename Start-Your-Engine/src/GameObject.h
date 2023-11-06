#pragma once
#include "glm/glm.hpp"
#include "renderer.h"
#include "texture.h"


class GameObject
{
public:
	Texture2D Sprite;
	glm::vec2 position, size, velocity;
	float rotation;
	glm::vec3 color;

	GameObject(glm::vec2 pos, glm::vec2 size, glm::vec3 color, glm::vec2 velocity, float rotation, Texture2D sprite);

	void update(float dt);

	void draw(Renderer& renderer);

};