// Created by Kaih White
#include "npc.h"

NPC::NPC(std::string name, glm::vec2 pos, glm::vec2 size, glm::vec3 color, std::unordered_map<std::string, Animation*> animations, b2World* world, std::string type, std::unordered_set<std::string> sounds, bool dynam)
	: GameObject(name, pos, size, color, animations, world, type, sounds, dynam)
{
}

NPC::~NPC()
{
}

// TODO: check if anythign is in the way, reverse direction if so, and then move
void NPC::update()
{
	move();
}

void NPC::move() 
{
	b2Vec2 velocity = this->body->GetLinearVelocity();
	float desiredVelocity = direction ? 2.0f : -2.0f;
	float jumpImpulse = 0.0f;
	

	// Calculate the change in velocity needed for the desired movement.
	float velocityChange = desiredVelocity - velocity.x;
	// Calculate the impulse required to achieve the velocity change.
	float impulse = this->body->GetMass() * velocityChange;
	// Apply the impulse to the center of the player's body.
	this->body->ApplyLinearImpulseToCenter(b2Vec2(impulse, jumpImpulse), true);
}

