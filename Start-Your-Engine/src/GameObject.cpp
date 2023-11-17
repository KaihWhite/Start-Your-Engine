#include "GameObject.h"

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, glm::vec3 color, glm::vec2 velocity, float rotation, Texture2D sprite)
	: position(pos), size(size), color(color), velocity(velocity), rotation(rotation), Sprite(sprite)
{
}

void GameObject::init(bool collidable = false, bool gravity = false) {
	this->collidable = collidable;
	this->gravity = gravity;
}

void GameObject::draw(Renderer& renderer)
{
    renderer.RenderSprite(this->Sprite, this->position, this->size, this->rotation, this->color);
}

void GameObject::update(float dt)
{
	this->position += this->velocity * dt;

	//Apply collisions

	//Apply gravity if gravity is needed
	if (this->velocity.y < 1.0f) {
		this->velocity.y += 10.0f;
	}
}

// TODO: create a init function that sets whether the object is collidable or feels gravity