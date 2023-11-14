
#include "game.h"
#include <unordered_map>
#include <iostream>


Game::Game(unsigned int width, unsigned int height)
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{
}

Game::~Game()
{
    delete this->player;
    delete this->renderer;
}

void Game::Init(unsigned int width, unsigned int height)
{
    /* load shaders */
    ResourceManager::LoadShader("shaders/sprite.vs", "shaders/fragAnim.fs", nullptr, "anim");


    /* configure shaders with image and projection uniforms */
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("anim").Use().SetInteger("image", 0);
    ResourceManager::GetShader("anim").SetMatrix4("projection", projection);


    /* create renderer */
    renderer = new Renderer(ResourceManager::GetShader("anim"));


    /* load textures */
    ResourceManager::LoadTexture("textures/idle.png", true, "idle");

    /* create animations */
    Animation* idle = new Animation("idle", 10);

    // Should I allocate these maps on the heap?
    std::unordered_map<std::string, Animation*> player_animations = {
    	{"idle", idle}
    };

    std::unordered_map<std::string, Animation*> ground = {
    };

    /* create physics world */
    b2Vec2 gravity(0.0f, 9.8f); // Y is positive down becuase positive Y is down in OpenGL
    world = new b2World(gravity);

    /* create a static ground body
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, 10.0f);
    b2Body* groundBody = world->CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;
    groundBox.SetAsBox(50.0f, 10.0f);
    groundBody->CreateFixture(&groundBox, 0.0f); */

    GameObject* ground = new GameObject(glm::vec2(0.0f, 10.0f), glm::vec2(50.0f, 10.0f), glm::vec3(1.0f, 1.0f, 1.0f), ground, world);


    /* create player game object */
    player = new Player(glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 400.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f), 0.0f, player_animations);

    /* add game objects to gameObjects vector */
    gameObjects.push_back(player);
    gameObjects.push_back(ground);
}

void Game::Update(float& dt)
{
    /* update physics world:
        This function moves the world objects according to physics */
    world->Step(timeStep, velocityIterations, positionIterations);

    for (auto& gameObject : gameObjects)
    {
		gameObject->update(dt);
	}

    // player->update(dt);
}

void Game::ProcessInput(float& dt)
{

}

void Game::Render()
{
    /*
        Render every game object here
    */
    for (auto& gameObject : gameObjects)
    {
        gameObject->draw(*renderer);
    }

    // player->draw(*renderer);
}