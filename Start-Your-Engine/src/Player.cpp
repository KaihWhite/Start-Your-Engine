#include "Player.h"
#include <GLFW/glfw3.h>

Player::Player(glm::vec2 pos, glm::vec2 size, glm::vec3 color, glm::vec2 velocity, float rotation, Texture2D sprite)
	: GameObject(pos, size, color, velocity, rotation, sprite)
{
}

void Player::Move(glm::vec2 direction, float deltaTime) {
    float speed = 100.0f; // Adjust speed as needed
    this->velocity = direction * speed;
    this->position += this->velocity * deltaTime; // Update position based on velocity
}