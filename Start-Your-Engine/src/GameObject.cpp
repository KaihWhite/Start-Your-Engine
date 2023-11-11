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
	/*
		Set current frame for animations by texture sampling with the fragment shader.
		Check shaders/fragAnim.fs
	*/
	ResourceManager::GetShader("anim").SetInteger("currentFrame", (int)(10 * glfwGetTime()) % animations[currentAnimation]->getTotalFrames());

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