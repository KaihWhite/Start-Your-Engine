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
}