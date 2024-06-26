// Made by Kaih White
// Controls edited by Chonglin Guan

#include "Player.h"
#include "game.h"

#include<iostream>
Player::Player(glm::vec2 pos, glm::vec2 size, glm::vec3 color, std::unordered_map<std::string, Animation*> animations, b2World* world, Camera2DSystem* cameraMan, std::string type, std::unordered_set<std::string> sounds, bool dynam)
	: GameObject("player", pos, size, color, animations, world, type, sounds, dynam), cameraMan(cameraMan), deltaTime(0.0f), previousTime(0.0f)
{
    offset = glm::vec2(0.0f, 0.0f);
    onPlatform = false;
    isJumping = false;
    jumpPressDuration = 0.0f;
    maxJumpTime = 0.6f;
}

Player::~Player()
{
}


void Player::move(bool Keys[1024], float timeStep) {
   b2Vec2 velocity = this->body->GetLinearVelocity();
    float desiredVelocity = 0.0f;
    float jumpImpulse = 0.0f;
    currentAnimation = "idle";
    this->cameraMan->lookAheadCameraMovement(offset.x, offset.y, 1.0f, deltaTime);

    if (Keys[GLFW_KEY_SPACE]) {
        if (onPlatform && !isJumping) {
            isJumping = true;
            jumpPressDuration = 0.0f;
           
        }
        if (isJumping) {
           
            jumpPressDuration += timeStep;
            if (jumpPressDuration < maxJumpTime) {
                jumpImpulse = -5.0f;
                currentAnimation = "jump";
                Game::playSound("jump");
                
            }
            else {
                isJumping = false; // End jump after max duration
            }
        }
    }
    
    if (Keys[GLFW_KEY_W]) {
        //player->move(glm::vec2(0.0f, 100.0f));
       //this->cameraMan->moveCameraOffset(glm::vec2(0.0f, -100.0f), deltaTime);
       //this->cameraMan->offsetCameraMovement(0.0f,-100.0f, 0.5f, deltaTime);
       //this->cameraMan->getCamera().moveCameraOffset(glm::vec2(0.0f,-100.0f ), deltaTime);
        offset.y = -300.0f;
        offset.x = 0.0f;
        this->cameraMan->lookAheadCameraMovement(offset.x, offset.y, 1.0f, deltaTime);
        //this->cameraMan->moveCameraOffset(glm::vec2(offset.x, offset.y), deltaTime);

    }
    if (Keys[GLFW_KEY_D]) {
        desiredVelocity = 3.0f; // Move right
        currentAnimation = "run";
        
        //Game::playSound(this->currentRunSound);
        
        //player->move(glm::vec2(-100.0f, 0.0f));
        //this->cameraMan->moveCameraOffset(glm::vec2(100.0f, 0.0f), deltaTime);
        //this->cameraMan->offsetCameraMovement(100.0f, 0.0f,0.5f,  deltaTime);
        //this->cameraMan->getCamera().moveCameraOffset(glm::vec2(100.0f, 0.0f), deltaTime);
        //this->cameraMan->moveCameraOffset(glm::vec2(-100.0f, 0.0f), deltaTime);

        offset.x = 300.0f;
        offset.y = 0.0f;
        this->cameraMan->lookAheadCameraMovement(offset.x, offset.y, 1.0f, deltaTime);
        //this->cameraMan->moveCameraOffset(glm::vec2(offset.x, offset.y), deltaTime);
    }
    if (Keys[GLFW_KEY_F]) {
        //player->move(glm::vec2(-100.0f, 0.0f));
        this->cameraMan->moveCamera(glm::vec2(300.0f, 0.0f), deltaTime);
        //this->cameraMan->offsetCameraMovement(100.0f, 0.0f,0.5f,  deltaTime);
        //this->cameraMan->getCamera().moveCameraOffset(glm::vec2(100.0f, 0.0f), deltaTime);
        this->cameraMan->lookAheadCameraMovement(offset.x, offset.y, 1.0f, deltaTime);
       /* offset.x = 200.0f;
        offset.y = 0.0f;
        this->cameraMan->offsetCameraMovement(offset.x, offset.y, 0.5f, deltaTime);*/
    }
    if (Keys[GLFW_KEY_A]) {

        desiredVelocity = -3.0f; // Move left
        currentAnimation = "run";
        //Game::playSound(this->currentRunSound);
        
        //player->move(glm::vec2(100.0f, 0.0f));

        //this->cameraMan->offsetCameraMovement(-100.0f, 0.0f,0.5f,  deltaTime);
        //this->cameraMan->getCamera().moveCameraOffset(glm::vec2(-100.0f, 0.0f), deltaTime);

        offset.x = -300.0f;
        offset.y = 0.0f;
        this->cameraMan->lookAheadCameraMovement(offset.x, offset.y, 1.0f, deltaTime);
        //this->cameraMan->moveCameraOffset(glm::vec2(offset.x, offset.y), deltaTime);

    }
    if (Keys[GLFW_KEY_S]) {
        //player->move(glm::vec2(0.0f, -100.0f));
        //this->cameraMan->moveCameraOffset(glm::vec2(0.0f, 100.0f), deltaTime);
        //this->cameraMan->offsetCameraMovement(0.0f, 100.0f, 0.5f, deltaTime);
        
        //this->cameraMan->getCamera().moveCameraOffset(glm::vec2(0.0f, 100.0f), deltaTime);
       
        offset.x = 0.0f;
        offset.y = 300.0f;
        this->cameraMan->lookAheadCameraMovement(offset.x, offset.y, 1.0f, deltaTime);
        //this->cameraMan->moveCameraOffset(glm::vec2(offset.x, offset.y), deltaTime);
    }
        //this->cameraMan->lookAheadCameraMovement(getPosition().x,getPosition().y,2.0f, deltaTime);
        //this->cameraMan->moveCameraOffset(glm::vec2(offset.x, offset.y), deltaTime);

    
    
    // Apply a horizontal force for movement
    // Calculate the change in velocity needed for the desired movement.
    float velocityChange = desiredVelocity - velocity.x;
    // Calculate the impulse required to achieve the velocity change.
    float impulse = this->body->GetMass() * velocityChange;
    // Apply the impulse to the center of the player's body.
    this->body->ApplyLinearImpulseToCenter(b2Vec2(impulse, jumpImpulse), true);
}


void Player::updateCamera()
{
	//std::cout << this->body->GetPosition().x << "," << this->body->GetPosition().y << std::endl;
	float currentTime = glfwGetTime();
	this->deltaTime = currentTime - this->previousTime;
	this->previousTime = currentTime; 
	cameraMan->follow(this->body->GetPosition().x*100, this->body->GetPosition().y*100, 1.5f, this->deltaTime);
    // this passes the pvmatrix to the shader
	ResourceManager::GetShader("anim").SetMatrix4("projectionView", cameraMan->getCamera().getProjectionViewMatrix());
	
   
}
