// Made by Kaih White
#include "game.h"
#include <unordered_map>
#include "ContactListener.h"



Game::Game(unsigned int width, unsigned int height)
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{
}

Game::~Game()
{
    delete this->player;
    delete this->renderer;
    delete this->world;
}

void Game::Init(unsigned int width, unsigned int height)
{
    /* load shaders */
    ResourceManager::LoadShader("Start-Your-Engine/shaders/sprite.vs", "Start-Your-Engine/shaders/fragAnim.fs", nullptr, "anim");


    /* configure shaders with image and projection uniforms */
    //glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, -1.0f, 1.0f);
    Camera2DSystem* cameraMan = new Camera2DSystem(static_cast<float>(width), static_cast<float>(height));
    ResourceManager::GetShader("anim").Use().SetInteger("image", 0);
    ResourceManager::GetShader("anim").SetMatrix4("projectionView", cameraMan->getCamera().getProjectionViewMatrix());


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


    // Initialize and Set the Contact Listener
    ContactListener* contactListener = new ContactListener();
    world->SetContactListener(contactListener);
}

void Game::Update()
{
    /* update physics world:
        This function moves the world objects according to physics */
    world->Step(this->timeStep, this->velocityIterations, this->positionIterations);

    // Update player movement based on key inputs
    this->player->move(this->Keys, this->timeStep);

    for (auto& gameObject : gameObjects)
    {
		gameObject->update();
	}
    
    this->player->updateCamera();
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
    
}

void Game::initLevel(std::vector<GameObject*> level)
{
	this->gameObjects = level;
}