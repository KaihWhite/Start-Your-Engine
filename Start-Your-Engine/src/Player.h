// Made by Kaih White
// Edits added by Chonglin Guan and Kunga Ngochetsang

#pragma once
#include "GameObject.h"
#include "glm/glm.hpp"
#include "renderer.h"
#include "Camera2DSystem.h"
class Player : public GameObject
{
	Camera2DSystem          *cameraMan;
	float					deltaTime;
	float					previousTime;
	glm::vec2				offset;
public:
	

	Player(glm::vec2 pos, glm::vec2 size, glm::vec3 color, std::unordered_map<std::string, Animation*> animations, b2World* world, Camera2DSystem* cameraMan, bool dynam = false);
	void updateCamera();
	void move(bool Keys[1024], float timeStep);

	~Player();
	bool onPlatform;
	bool isJumping;
	float jumpPressDuration;
	float maxJumpTime; // Duration of the jump in seconds
	
};


//TODO: I need to allow the player object to have an array of animations/sprites that it can switch between
// currently the player class only takes one Texture2D object
