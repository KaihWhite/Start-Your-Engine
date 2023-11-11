/*
Give credit to the author of LearnOpenGL.com Joey de Vries
*/
#include "game.h"
#include <unordered_map>
#include <iostream>


/*
    TODO: create an animation object which stores a sprite sheet with its uniform -- totalFrames.
        totalFrames will need to be set every time a new animation is to be played; create a function
        to do this or have the renderer do it by overloading the renderer to take the animation type.
        I'll likely need to revamp the game object class to store multiple animations.
        Within the game object class, within the render function, I should determine there which animation
        is to be played instead of switching the animation.
*/


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

    std::unordered_map<std::string, Animation*> animations = {
    	{"idle", idle}
    };


    /* create player game object */
    player = new Player(glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 400.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f), 0.0f, animations);
}

void Game::Update(float dt)
{
    player->update(dt);
}

void Game::ProcessInput(float dt)
{

}

void Game::Render(float currentFrame)
{
    /*
        Set current frame for character animations by texture sampling with the fragment shader.
        Check shaders/fragAnim.fs
    */
    ResourceManager::GetShader("anim").SetInteger("currentFrame", (int)(10 * currentFrame) % player->getTotalFrames());
    player->draw(*renderer);
}