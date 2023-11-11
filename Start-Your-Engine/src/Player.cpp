#include "Player.h"

Player::Player(glm::vec2 pos, glm::vec2 size, glm::vec3 color, glm::vec2 velocity, float rotation, std::unordered_map<std::string, Animation*> animations)
	: GameObject(pos, size, color, velocity, rotation, animations)
{
}

void Player::move(glm::vec2 velocity) {
	this->velocity.x = velocity.x;
}
