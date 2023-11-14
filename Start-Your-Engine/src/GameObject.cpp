#include "GameObject.h"

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, glm::vec3 color, std::unordered_map<std::string, Animation*> animations, b2World* world, bool dynam = false)
	: color(color), animations(animations)
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