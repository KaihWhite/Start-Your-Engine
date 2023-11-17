#include "Player.h"
#include <GLFW/glfw3.h>

Player::Player(glm::vec2 pos, glm::vec2 size, glm::vec3 color, glm::vec2 velocity, float rotation, Texture2D sprite)
	: GameObject(pos, size, color, velocity, rotation, sprite)
{

}

void Player::move(glm::vec2 velocity) {
	this->velocity.x = velocity.x;
	this->velocity.y = velocity.y;
}
