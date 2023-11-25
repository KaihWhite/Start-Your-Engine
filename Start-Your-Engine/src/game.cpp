
#include "game.h"
#include <unordered_map>



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
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("anim").Use().SetInteger("image", 0);
    ResourceManager::GetShader("anim").SetMatrix4("projection", projection);


    /* create renderer */
    renderer = new Renderer(ResourceManager::GetShader("anim"));


    /* load textures */
    ResourceManager::LoadTexture("Start-Your-Engine/textures/idle.png", true, "idle");
    //ResourceManager::LoadTexture("", true, "ground");

    /* create animations */
    Animation* idle = new Animation("idle", 10);
    //Animation* groundAnim = new Animation("ground", 1);

    // Should I allocate these maps on the heap?
    std::unordered_map<std::string, Animation*> player_animations = {
    	{"idle", idle}
    };

    /*std::unordered_map<std::string, Animation*> groundSprite = {
        {"idle", groundAnim}
    };*/

    /* create physics world */
    //b2Vec2 gravity(0.0f, 9.8f); // positive Y for things to fall down in openGL
    b2Vec2 gravity(0.0f, 0.0f);
    world = new b2World(gravity);

    /* create a static ground body
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, 10.0f);
    b2Body* groundBody = world->CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;
    groundBox.SetAsBox(50.0f, 10.0f);
    groundBody->CreateFixture(&groundBox, 0.0f); */

    //GameObject* ground = new GameObject(glm::vec2(0.0f, 10.0f), glm::vec2(50.0f, 10.0f), glm::vec3(1.0f, 1.0f, 1.0f), groundSprite, world);


    /* create player game object */
    player = new Player(glm::vec2(4.0f, 4.0f), glm::vec2(3.0f, 4.0f), glm::vec3(1.0f, 1.0f, 1.0f), player_animations, world, true);

    /* add game objects to gameObjects vector */
    this->gameObjects.push_back(player);
    //this->gameObjects.push_back(ground);
}

void Game::Update()
{
    /* update physics world:
        This function moves the world objects according to physics */
    world->Step(this->timeStep, this->velocityIterations, this->positionIterations);

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