// Made by Kaih White
#include "GameObject.h"
#include <iostream>
#include "game.h"

//#include "ContactListener.h"


GameObject::GameObject(std::string name, glm::vec2 pos, glm::vec2 size, glm::vec3 color, std::unordered_map<std::string, Animation*> animations, b2World* world, std::string type, std::unordered_set<std::string>  sounds, bool dynam)
	: name(name), color(color), animations(animations), size(size), rigidBodyType(dynam ? RigidBodyType::DYNAMIC : RigidBodyType::STATIC), type(type == "Player" ? ObjectType::PLAYER : type == "Object" ? ObjectType::OBJECT : ObjectType::NPCOBJECT), sounds(sounds)
{
	b2BodyDef bodyDef;
	bodyDef.type = dynam ? b2_dynamicBody : b2_staticBody;
	bodyDef.position.Set(pos.x, pos.y);
	bodyDef.fixedRotation = true; // Disable rotation
	body = world->CreateBody(&bodyDef);
	/*BodyUserData* userData = new BodyUserData();
	userData->object = this;
	userData->objectType = "GameObject";  // Or more specific type
	body->GetUserData().pointer = reinterpret_cast<uintptr_t>(userData);*/
	// Updated way to set user data in Box2D
	body->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);

	/*b2PolygonShape dynamicBox;
	// TODO: make a function that converts units from pixels to meters and vice versa. I have no idea what this will look like yet
	dynamicBox.SetAsBox(size.x / 2.0f, size.y / 2.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;

	body->CreateFixture(&fixtureDef);

	

	this->currentSound = "idle";
	body->CreateFixture(&fixtureDef);*/
	objectTypeInString = {
	{PLAYER, "PLAYER"},
	{OBJECT, "OBJECT"},
	{NPCOBJECT, "NPC"}
	};
	// Apply default fixture if no custom collision box exists
    if (!hasCustomCollisionBox) {
        b2PolygonShape dynamicBox;
        dynamicBox.SetAsBox(size.x / 2.0f, size.y / 2.0f);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &dynamicBox;
        fixtureDef.density = 1.0f;
        body->CreateFixture(&fixtureDef);
    }
}
    
GameObject::~GameObject()
{
	// destroy the body fixthre 
	this->destroyBodyFixture();
	this->deleteAllAnimation();
	

	//this->body->GetWorld()->DestroyBody(body);
	//delete reinterpret_cast<BodyUserData*>(body->GetUserData().pointer);
}

std::string GameObject::getobjectTypeString(ObjectType type )
{
	return objectTypeInString.at(type);
}



void GameObject::addAnimation(std::string spriteSheet, int totalFrames)
{	//set the the newly added animation as the current if the map is empty
	if (this->animations.empty()) {
		animations.insert(std::make_pair(spriteSheet, new Animation(spriteSheet, totalFrames)));
		this->setAsCurrentAnimation(spriteSheet);
	}
	else {
		//other wise it just adds 
		animations.insert(std::make_pair(spriteSheet, new Animation(spriteSheet, totalFrames)));
	}
	
}
void GameObject::addAnimation(std::string key, std::string spriteSheet, int totalFrames)
{	//set the the newly added animation as the current if the map is empty
	if (this->animations.empty()) {
		animations.insert(std::make_pair(key, new Animation(spriteSheet, totalFrames)));
		this->setAsCurrentAnimation(spriteSheet);
	}
	else {
		//other wise it just adds 
		animations.insert(std::make_pair(key, new Animation(spriteSheet, totalFrames)));
	}

}

void GameObject::deleteAnimation(const std::string spriteSheet)
{	//check if its not empty
	if (!animations.empty()) {
		for (const auto& pair : this->animations) {
			//in case of more than one animations
			if (pair.second->getSpriteSheetName() != spriteSheet) {
				this->setAsCurrentAnimation(pair.first);
				delete animations[spriteSheet];
				animations.erase(spriteSheet);
				break;
			}
			//in case of the one spritesheet
			else {
				delete animations[spriteSheet];
				animations.erase(spriteSheet);
				this->setAsCurrentAnimation("");
				break;
			}
		}
	}
}
	

void GameObject::setAsCurrentAnimation(const std::string spriteSheet)
{
	if (animations.find(spriteSheet) != animations.end()) {
		this->currentAnimation = spriteSheet;
		this->animations["idle"] = animations[spriteSheet]; // Update the "idle" animation
	}
}

std::string GameObject::getCurrentAnimation()
{
	return this->currentAnimation;
}



std::unordered_map<std::string, Animation*>  GameObject::retrieveAllAnimations()
{
	return this->animations;
}

void GameObject::deleteAllAnimation()
{
	for (auto pair:this->animations) {
		delete animations[pair.first];
	}
	animations.clear();
}

void GameObject::draw(Renderer& renderer)
{
	/*
		Set current frame for animations by texture sampling with the fragment shader.
		Check shaders/fragAnim.fs
	*/
	if (!this->animations.empty()) {

		ResourceManager::GetShader("anim").SetInteger("currentFrame", (int)(10 * glfwGetTime()) % animations[currentAnimation]->getTotalFrames());

		Texture2D sprite = animations[currentAnimation]->getSpriteSheet();
		//bool flip = dynamic_cast<Player*>(this) ? !dynamic_cast<Player*>(this)->facingRight : false;
		renderer.RenderSprite(sprite, this->metersToPixels(this->getPosition()), this->metersToPixels(this->size), this->body->GetAngle(), this->color);
	}
	
}
 
Texture2D GameObject::getCurrentTexture2D()
{
	return this->animations[currentAnimation]->getSpriteSheet();
}


void GameObject::move()
{

}
void GameObject::update()
{

}

void GameObject::destroyBodyFixture()
{
	// destroy the one and only fixture of the body
	for (b2Fixture* fixture = body->GetFixtureList(); fixture != nullptr; fixture = fixture->GetNext()) {
		body->DestroyFixture(fixture);
		break;
	}
}

void GameObject::resize()
{
	destroyBodyFixture();
	// this creates a new fixture for the body when it is resizes

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(size.x / 2.0f, size.y / 2.0f);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	body->CreateFixture(&fixtureDef);
}

glm::vec2 GameObject::getPosition() {

	/*
	std::cout << "size x: " << this->size.x << std::endl;
	std::cout << "original x: " << this->body->GetPosition().x << std::endl;
	std::cout << "original y: " << this->body->GetPosition().y << std::endl;

	std::cout << "shifted x:" << this->body->GetPosition().x - ((this->size.x) / 2) << std::endl;
	std::cout << "shifted y:" << this->body->GetPosition().y - ((this->size.y) / 2) << std::endl;

	std::cout << "\n" << std::endl;
	*/
	
	return glm::vec2(this->body->GetPosition().x - ((this->size.x) / 2)
		, this->body->GetPosition().y - ((this->size.y) / 2));
}

glm::vec2 GameObject::getLocation()
{
	return glm::vec2(this->body->GetPosition().x , this->body->GetPosition().y);
}

glm::vec2 GameObject::metersToPixels(glm::vec2 v) {
	return glm::vec2(v.x * 100, v.y * 100);
}

glm::vec2 GameObject::pixelsToMeters(glm::vec2 v) {
	return glm::vec2(v.x / 100, v.y / 100);
}

void GameObject::applyCollisionBox() {
	if (!body) return;

	// Remove existing fixture
	if (body->GetFixtureList()) {
		body->DestroyFixture(body->GetFixtureList());
	}

	// Create new fixture based on stored shape and size
	b2FixtureDef fixtureDef;
	fixtureDef.density = 1.0f; // Set the fixture density
	// More properties like friction and restitution can be set here as needed

	switch (collisionBoxShape) {
	case 0: { // Rectangle
		b2PolygonShape boxShape;
		boxShape.SetAsBox(collisionBoxWidth / 2.0f, collisionBoxHeight / 2.0f);
		fixtureDef.shape = &boxShape;
		body->CreateFixture(&fixtureDef);
		break;
	}
	case 1: { // Circle
		b2CircleShape circleShape;
		circleShape.m_radius = collisionBoxWidth / 2.0f; // Use Width as Radius
		fixtureDef.shape = &circleShape;
		body->CreateFixture(&fixtureDef);
		break;
	}
	case 2: { // Triangle
		b2PolygonShape polygonShape;
		b2Vec2 vertices[3];
		vertices[0].Set(0.0f, -collisionBoxHeight / 2.0f); // Top vertex
		vertices[1].Set(-collisionBoxWidth / 2.0f, collisionBoxHeight / 2.0f); // Bottom left
		vertices[2].Set(collisionBoxWidth / 2.0f, collisionBoxHeight / 2.0f); // Bottom right
		polygonShape.Set(vertices, 3);
		fixtureDef.shape = &polygonShape;
		body->CreateFixture(&fixtureDef);
		break;
	}
	}
}