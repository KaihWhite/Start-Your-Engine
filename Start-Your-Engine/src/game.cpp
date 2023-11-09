/*
Give credit to the author of LearnOpenGL.com Joey de Vries
*/
#include "game.h"
#include "resource_manager.h"
#include "renderer.h"

Game::Game(unsigned int width, unsigned int height)
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{

}

Game::~Game()
{

}

void Game::Init()
{
    /* load shaders */
    ResourceManager::LoadShader("shaders/sprite.vs", "shaders/sprite.fs", nullptr, "sprite");
    ResourceManager::LoadShader("shaders/sprite.vs", "shaders/fragAnim.fs", nullptr, "anim");


    /* configure shaders with uniforms */
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(SCR_WIDTH), static_cast<float>(SCR_HEIGHT), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);

    ResourceManager::GetShader("anim").Use().SetInteger("image", 0);
    ResourceManager::GetShader("anim").SetMatrix4("projection", projection);
    ResourceManager::GetShader("anim").SetInteger("currentFrame", 0);
    ResourceManager::GetShader("anim").SetInteger("totalFrames", 10);


    /* create renderer */
    //Renderer *renderer = new Renderer(ResourceManager::GetShader("sprite"));
    Renderer* animRenderer = new Renderer(ResourceManager::GetShader("anim"));


    /* load textures */
    //ResourceManager::LoadTexture("textures/awesomeface.png", true, "face");
    ResourceManager::LoadTexture("textures/idle.png", true, "idle");
}

void Game::Update(float dt)
{

}

void Game::ProcessInput(float dt)
{

}

void Game::Render()
{

}