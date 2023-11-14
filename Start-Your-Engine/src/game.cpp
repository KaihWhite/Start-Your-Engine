
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
    std::unordered_map<std::string, Animation*> animations = {
    	{"idle", idle}
    };


    /* create player game object */
    player = new Player(glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 400.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f), 0.0f, animations);
}

void Game::Update(float& dt)
{
    player->update(dt);
}

void Game::ProcessInput(float& dt)
{

}

void Game::Render()
{
    /*
        Render every game object here
    */
    player->draw(*renderer);
}