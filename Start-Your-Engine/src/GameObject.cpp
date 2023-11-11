#include "GameObject.h"

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, glm::vec3 color, glm::vec2 velocity, float rotation, std::unordered_map<std::string, Animation*> animations)
	: position(pos), size(size), color(color), velocity(velocity), rotation(rotation), animations(animations)
{
}

void GameObject::init(bool collidable = false, bool gravity = false) {
	this->collidable = collidable;
	this->gravity = gravity;
}

void GameObject::draw(Renderer& renderer)
{
	Texture2D sprite = animations[currentAnimation]->getSpriteSheet();
    renderer.RenderSprite(sprite, this->position, this->size, this->rotation, this->color);
}

void GameObject::update(float dt)
{

	// velocity + vector

	this->position += this->velocity * dt;

	//Apply collisions

	//Apply gravity if gravity is needed
	if (this->velocity.y < 1.0f) {
		//this->velocity.y += 10.0f;
	}
}

unsigned short GameObject::getTotalFrames() {
	return animations[currentAnimation]->getTotalFrames();
}

// TODO: create a init function that sets whether the object is collidable or feels gravity