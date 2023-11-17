#include "Player.h"

Player::Player(glm::vec2 pos, glm::vec2 size, glm::vec3 color, std::unordered_map<std::string, Animation*> animations, b2World* world, bool dynam)
	: GameObject(pos, size, color, animations, world, dynam)
{
}

void Player::move(bool Keys[1024]) {
	
}
