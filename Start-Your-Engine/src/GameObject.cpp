#include "GameObject.h"
#include <iostream>

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, glm::vec3 color, std::unordered_map<std::string, Animation*> animations, b2World* world, bool dynam)
	: color(color), animations(animations), size(size)
{
	b2BodyDef bodyDef;
	bodyDef.type = dynam ? b2_staticBody : b2_dynamicBody;
	bodyDef.position.Set(pos.x, pos.y);
	body = world->CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	// TODO: make a function that converts units from pixels to meters and vice versa. I have no idea what this will look like yet
	dynamicBox.SetAsBox(size.x / 2.0f, size.y / 2.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	body->CreateFixture(&fixtureDef);
}

GameObject::~GameObject()
{
	for (auto& animation : this->animations)
	{
		delete animation.second;
	}
	this->animations.clear();

	this->body->GetWorld()->DestroyBody(body);
}


void GameObject::draw(Renderer& renderer)
{
	/*
		Set current frame for animations by texture sampling with the fragment shader.
		Check shaders/fragAnim.fs
	*/
	ResourceManager::GetShader("anim").SetInteger("currentFrame", (int)(10 * glfwGetTime()) % animations[currentAnimation]->getTotalFrames());

	Texture2D sprite = animations[currentAnimation]->getSpriteSheet();

    renderer.RenderSprite(sprite, this->metersToPixels(this->getPosition()), this->metersToPixels(this->size), this->body->GetAngle(), this->color);
}

void GameObject::update(float dt)
{
	
}

glm::vec2 GameObject::getPosition() {


	std::cout << "size x: " << this->size.x << std::endl;
	std::cout << "original x: " << this->body->GetPosition().x << std::endl;
	std::cout << "original y: " << this->body->GetPosition().y << std::endl;

	std::cout << "shifted x:" << this->body->GetPosition().x - ((this->size.x) / 2) << std::endl;
	std::cout << "shifted y:" << this->body->GetPosition().y - ((this->size.y) / 2) << std::endl;

	std::cout << "\n" << std::endl;

	return glm::vec2(this->body->GetPosition().x - ((this->size.x) / 2), this->body->GetPosition().y - ((this->size.y) / 2));
}

glm::vec2 GameObject::metersToPixels(glm::vec2 v) {
	return glm::vec2(v.x * 100, v.y * 100);
}

glm::vec2 GameObject::pixelsToMeters(glm::vec2 v) {
	return glm::vec2(v.x / 100, v.y / 100);
}