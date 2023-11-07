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

	bool collidable, gravity;

	GameObject(glm::vec2 pos, glm::vec2 size, glm::vec3 color, glm::vec2 velocity, float rotation, Texture2D sprite);

	void init(bool gravity, bool collidable);

	void update(float dt);

	void phyics(float dt);

	void draw(Renderer& renderer);

};