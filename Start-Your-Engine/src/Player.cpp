// By Chonglin Guan

#include "Player.h"

Player::Player(glm::vec2 pos, glm::vec2 size, glm::vec3 color, std::unordered_map<std::string, Animation*> animations, b2World* world, bool dynam)
	: GameObject(pos, size, color, animations, world, dynam)
{
    onPlatform = false;
    isJumping = false;
    jumpPressDuration = 0.0f;
    maxJumpTime = 0.6f;
}

void Player::move(bool Keys[1024], float dt) {
    b2Vec2 velocity = this->body->GetLinearVelocity();
    float desiredVelocity = 0.0f;
    float jumpImpulse = 0.0f;
    currentAnimation = "idle";

    if (Keys[GLFW_KEY_A]) {
        desiredVelocity = -2.0f; // Move left
        currentAnimation = "run";
        
    }
    if (Keys[GLFW_KEY_D]) {
        desiredVelocity = 2.0f; // Move right
        currentAnimation = "run";
        
    }
    /*if (Keys[GLFW_KEY_W] && onPlatform) {
        jumpImpulse = -4.0f; // Jump
        currentAnimation = "jump";
    }*/
    if (Keys[GLFW_KEY_W] && onPlatform && !isJumping) {
        isJumping = true;
        jumpPressDuration = 0.0f;
    }

    if (isJumping) {
        jumpPressDuration += dt;
        if (jumpPressDuration < maxJumpTime) {
            jumpImpulse = -4.0f;
            currentAnimation = "jump";
        }
        else {
            isJumping = false; // End jump after max duration
        }
    }

    // Apply a horizontal force for movement
    // Calculate the change in velocity needed for the desired movement.
    float velocityChange = desiredVelocity - velocity.x;
    // Calculate the impulse required to achieve the velocity change.
    float impulse = this->body->GetMass() * velocityChange;
    // Apply the impulse to the center of the player's body.
    this->body->ApplyLinearImpulseToCenter(b2Vec2(impulse, jumpImpulse), true);
}
