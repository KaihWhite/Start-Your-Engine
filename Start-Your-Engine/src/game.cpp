
#include "game.h"
#include <unordered_map>



Game::Game(unsigned int width, unsigned int height)
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{
}

Game::~Game()
{
    delete this->player;
    delete this->platform1;
    delete this->platform2;
    delete this->renderer;
    delete this->world;
}

void Game::Init(unsigned int width, unsigned int height)
{
    /* load shaders */
    ResourceManager::LoadShader("Start-Your-Engine/shaders/sprite.vs", "Start-Your-Engine/shaders/fragAnim.fs", nullptr, "anim");


    /* configure shaders with image and projection uniforms */
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("anim").Use().SetInteger("image", 0);
    ResourceManager::GetShader("anim").SetMatrix4("projection", projection);


    /* create renderer */
    renderer = new Renderer(ResourceManager::GetShader("anim"));


    /* load textures */
    ResourceManager::LoadTexture("Start-Your-Engine/textures/idle.png", true, "idle");
    ResourceManager::LoadTexture("Start-Your-Engine/textures/run cycle 48x48.png", true, "run");
    ResourceManager::LoadTexture("Start-Your-Engine/textures/player jump 48x48.png", true, "jump");
    ResourceManager::LoadTexture("Start-Your-Engine/textures/awesomeface.png", true, "awesomeface");

    /* create animations */
    Animation* idle = new Animation("idle", 10);
    Animation* run = new Animation("run", 8);
    Animation* jump = new Animation("jump", 3);
    Animation* ground1 = new Animation("awesomeface", 1);
    Animation* ground2 = new Animation("awesomeface", 1);

    // Should I allocate these maps on the heap?
    std::unordered_map<std::string, Animation*> player_animations = {
    	{"idle", idle}, {"run", run}, {"jump", jump}
    };
    std::unordered_map<std::string, Animation*> platform_animations1 = {
        {"idle", ground1}
    };
    std::unordered_map<std::string, Animation*> platform_animations2 = {
        {"idle", ground2}
    };

    /* create physics world */
    b2Vec2 gravity(0.0f, 9.8f); // positive Y for things to fall down in openGL G = 9.8
    world = new b2World(gravity);

    /* create player game object */
    player = new Player(glm::vec2(4.0f, 4.0f), glm::vec2(3.0f, 4.0f), glm::vec3(1.0f, 1.0f, 1.0f), player_animations, world, true);
    // Create platform object
    platform1 = new GameObject(glm::vec2(5.0f, 7.0f), glm::vec2(10.0f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), platform_animations1, world, false);
    platform2 = new GameObject(glm::vec2(12.0f, 5.0f), glm::vec2(4.0f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), platform_animations2, world, false);

    /* add game objects to gameObjects vector */
    this->gameObjects.push_back(player);
    //this->gameObjects.push_back(ground);
    // Add platform to game objects
    this->gameObjects.push_back(platform1);
    this->gameObjects.push_back(platform2);
}

void Game::Update()
{
    /* update physics world:
        This function moves the world objects according to physics */
    world->Step(this->timeStep, this->velocityIterations, this->positionIterations);

    // Update player movement based on key inputs
    this->player->move(this->Keys);

    for (auto& gameObject : gameObjects)
    {
		gameObject->update();
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