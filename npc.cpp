// Created by Kaih White
#include "npc.h"

NPC::NPC(std::string name, glm::vec2 pos, glm::vec2 size, glm::vec3 color, std::unordered_map<std::string, Animation*> animations, b2World* world, std::string type, bool dynam)
	: GameObject(name, pos, size, color, animations, world, type, dynam)
{
}

NPC::~NPC()
{
}

// TODO: implement simple movement for NPC. If there is no player, the NPC will move in a random direction. If there is a player, the NPC will move towards the player.
void NPC::move()
{
	b2Vec2 velocity = this->body->GetLinearVelocity();
	float desiredVelocity = 0.0f;
	float jumpImpulse = 0.0f;
	this->currentAnimation = "idle";

	if (this->playerInRange)
	{
		desiredVelocity = pathfind(this->playerPos);
	}
	if else (this->path.size() > 0)
	{
		// move towards the first point in the path
		if (direction) {
			if (glm::distance(this->position, this->path[0]) < 0.1f)
			{
				this->direction = false;
			}
			else
			{
				// move towards the first point in the path
				desiredVelocity = pathfind(this->path[0]);
			}
		}
		else {
			if (glm::distance(this->position, this->path[1]) < 0.1f)
			{
				this->direction = true;
			}
			else
			{
				// move towards the second point in the path
				desiredVelocity = pathfind(this->path[1]);
			}
		}
	}
	else
	{
		// move in a random direction
		glm::vec2 randomDirection = glm::vec2(rand() % 100 - 50, rand() % 100 - 50);
		desiredVelocity = pathfind(randomDirection);
	}

	// Calculate the change in velocity needed for the desired movement.
	float velocityChange = desiredVelocity - velocity.x;
	// Calculate the impulse required to achieve the velocity change.
	float impulse = this->body->GetMass() * velocityChange;
	// Apply the impulse to the center of the player's body.
	this->body->ApplyLinearImpulseToCenter(b2Vec2(impulse, jumpImpulse), true);
}

void NPC::checkPlayer(glm::vec2 pos)
{
	if (glm::distance(this->position, pos) < this->maxDistanceToPlayer)
	{
		this->playerPos = pos;
		this->playerInRange = true;
	}
	else
	{
		this->playerInRange = false;
	}
}

void NPC::setMaxDistanceToPlayer(int distance)
{
	this->maxDistanceToPlayer = distance;
}

void NPC::setPath(glm::vec2 start, glm::vec2 end)
{
	this->path[0] = start;
	this->path[1] = end;
}

float NPC::pathfind(glm::vec2 point)
{
	float desiredVelocity = 0.0f;
	if (point.x > this->position.x)
	{
		desiredVelocity = 2.0f;
		this->currentAnimation = "run";
	}
	else if (point.x < this->position.x)
	{
		desiredVelocity = -2.0f;
		this->currentAnimation = "run";
	}
	return desiredVelocity;
}
