// Made by Kaih White
#pragma once
#include "glm/glm.hpp"
#include "renderer.h"
#include "texture.h"
#include "Animation.h"
#include "GLFW/glfw3.h"
#include <unordered_map>
#include <unordered_set>
#include "box2d/box2d.h"

enum ObjectType {
	PLAYER,
	OBJECT,
	NPC,
	TILEMAP 
};

enum RigidBodyType {
	STATIC,
	DYNAMIC

};

class GameObject
{
public:
	std::string name;

	ObjectType type;

	std::unordered_map<std::string, Animation*> animations;
	std::string currentAnimation = "idle";

	std::unordered_set<std::string> sounds;

	glm::vec3 color;
	glm::vec2 size;

	bool rigidBodyType;

	b2Body* body;

	GameObject(std::string name, glm::vec2 pos, glm::vec2 size, glm::vec3 color, std::unordered_map<std::string, Animation*> animations, b2World* world, std::string type, std::unordered_set<std::string> sounds, bool dynam = false);
	~GameObject();

	
	void update();
	void destroyBodyFixture();
	void resize();
	void physics(float dt);

	/* Graphic functions	*/
	Texture2D getCurrentTexture2D();
	void renderBox(Renderer& renderer);
	void unRenderBox(Renderer& renderer);
	void addAnimation(std::string spriteSheet, int totalFrames);
	void deleteAnimation(const std::string spriteSheet);
	void setAsCurrentAnimation(const std::string spriteSheet);
	std::string getCurrentAnimation();
	std::unordered_map<std::string, Animation*>  retrieveAllAnimations();
	void deleteAllAnimation();
	void draw(Renderer& renderer);

	/* animation functions that manages the animations of the  */
	 

	/* converts physics body's position to renderer coordinates */
	glm::vec2 getPosition();
	glm::vec2 getLocation();
	glm::vec2 metersToPixels(glm::vec2 v);
	glm::vec2 pixelsToMeters(glm::vec2 v);
};
