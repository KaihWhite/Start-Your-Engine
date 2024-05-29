// Made by Kaih White
//contributed by kunga
#pragma once
#include "glm/glm.hpp"
#include "renderer.h"
#include "texture.h"
#include "Animation.h"
#include "GLFW/glfw3.h"
#include <unordered_map>
#include <unordered_set>
#include "box2d/box2d.h"
//#include "game.h"

enum ObjectType {
	PLAYER,
	OBJECT,
	NPCOBJECT
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
	std::unordered_map<ObjectType, std::string> objectTypeInString;
	std::unordered_map<std::string, Animation*> animations;
	std::string currentAnimation = "idle";

	std::unordered_set<std::string> sounds;
	std::string currentSound;
	glm::vec3 color;
	glm::vec2 size;

	bool rigidBodyType;

	b2Body* body;

	GameObject(std::string name, glm::vec2 pos, glm::vec2 size, glm::vec3 color, std::unordered_map<std::string, Animation*> animations, b2World* world, std::string type, std::unordered_set<std::string> sounds, bool dynam = false);
	~GameObject();

	std::string getobjectTypeString(ObjectType type);
	virtual void move(bool direction);
	virtual void update();
	// Collision box properties
	bool hasCustomCollisionBox = false;
	int collisionBoxShape;
	float collisionBoxWidth;
	float collisionBoxHeight;

	// Method to apply the collision box
	void applyCollisionBox();
	
	void update();
	void destroyBodyFixture();
	void resize();
	void physics(float dt);

	/* Graphic functions	*/
	Texture2D getCurrentTexture2D();
	
	void addAnimation(std::string spriteSheet, int totalFrames);
	void addAnimation(std::string key, std::string spriteSheet, int totalFrames);
	void deleteAnimation(const std::string spriteSheet);
	void setAsCurrentAnimation(const std::string spriteSheet);
	std::string getCurrentAnimation();
	std::unordered_map<std::string, Animation*>  retrieveAllAnimations();
	void deleteAllAnimation();
	void draw(Renderer& renderer);


	/* converts physics body's position to renderer coordinates */
	glm::vec2 getPosition();
	glm::vec2 getLocation();
	glm::vec2 metersToPixels(glm::vec2 v);
	glm::vec2 pixelsToMeters(glm::vec2 v);
};
