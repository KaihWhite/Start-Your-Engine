// Made by Kaih White
#include "game.h"
#include <unordered_map>
#include "ContactListener.h"



Game::Game(unsigned int width, unsigned int height)
    : State(GAME_EDITOR), Keys(), Width(width), Height(height), player(nullptr), renderer(nullptr), world(nullptr), cameraMan(nullptr)
{
}

Game::~Game()
{
    delete this->player;
    delete this->renderer;
    delete this->world;
    delete this->cameraMan;
    /*
    for (auto& gameObject : gameObjects)
    {
		delete gameObject.second;
	}
    */
}

void Game::Init(unsigned int width, unsigned int height)
{
    /* load shaders */
    ResourceManager::LoadShader("Start-Your-Engine/shaders/sprite.vs", "Start-Your-Engine/shaders/fragAnim.fs", nullptr, "anim");


    /* configure shaders with image and projection uniforms */
    //glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, -1.0f, 1.0f);
    this->cameraMan = new Camera2DSystem(static_cast<float>(width), static_cast<float>(height));
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

    if (this->player != nullptr && State == GameState::GAME_ACTIVE)
    {
        // Update player movement based on key inputs
        this->player->move(this->Keys, this->timeStep);

        this->player->updateCamera();
	}
    if (this->player != nullptr && State == GameState::GAME_EDITOR)
    {
        // Update player movement based on key inputs
        this->player->move(this->Keys, this->timeStep);

        this->player->updateCamera();
    }
    if (!gameObjects.empty())
    {
        for (auto& gameObject : gameObjects)
        {
            gameObject.second->update();
        }
	}
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
        gameObject.second->draw(*renderer);
    }
    
}

void Game::initLevel(std::unordered_map<int, GameObject*> level)
{
    for (auto& gameObject : gameObjects)
    {
        delete gameObject.second;
    }
	this->gameObjects = level;
    for (auto& gameObject : level)
    {
        if (gameObject.second->type == ObjectType::PLAYER)
        {
			this->player = (Player*)gameObject.second;
            return;
		}
	}
}

void Game::addGameObject(std::string name, ObjectType type, RigidBodyType rtype, std::unordered_map<std::string, Animation*> animations, glm::vec3 color, glm::vec2 size, glm::vec2 pos)
{
    GameObject* gameObject = new GameObject(name, pos, size, color, animations, this->world, type == ObjectType::OBJECT ? "Object" : "Npc", rtype);
    int key = Game::generateUniqueKey(this->gameObjects);
    this->gameObjects[key] = gameObject;
}

void Game::removeGameObject(int key)
{
    if (this->gameObjects[key]->type == ObjectType::PLAYER)
    {
		this->player = nullptr;
	}
	delete this->gameObjects[key];
	this->gameObjects.erase(key);
}

void Game::updateGameObject(int key, std::string name, ObjectType type, RigidBodyType rtype, std::unordered_map<std::string, Animation*> animations, glm::vec3 color, glm::vec2 size, glm::vec2 pos)
{
    this->gameObjects[key]->name = name;
	this->gameObjects[key]->animations = animations;
	this->gameObjects[key]->color = color;
	this->gameObjects[key]->size = size;
	this->gameObjects[key]->rigidBodyType = rtype;
	this->gameObjects[key]->body->SetTransform(b2Vec2(pos.x, pos.y), 0.0f);
	this->gameObjects[key]->type = type;
}

void Game::addPlayer(Camera2DSystem* cameraMan, std::unordered_map<std::string, Animation*> animations, glm::vec3 color, glm::vec2 size, glm::vec2 pos)
{
	Player* player = new Player(pos, size, color, animations, this->world, cameraMan, "Player", true);
	this->player = player;
    int key = Game::generateUniqueKey(this->gameObjects);
    this->gameObjects[key] = player;
}

void Game::updatePlayer(std::unordered_map<std::string, Animation*> animations, glm::vec3 color, glm::vec2 size, glm::vec2 pos)
{
	this->player->animations = animations;
	this->player->color = color;
	this->player->size = size;
	this->player->body->SetTransform(b2Vec2(pos.x, pos.y), 0.0f);
}

Animation* Game::loadAnimation(const char* file, bool alpha, std::string name, int numFrames)
{
    ResourceManager::LoadTexture(file, alpha, name);
	return new Animation(name, numFrames);
}

int Game::generateUniqueKey(std::unordered_map<int, GameObject*> map)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr(1, 100);
	int unique_key = distr(gen);
    while (map.find(unique_key) != map.end()) {
		unique_key = distr(gen);
	}
    return unique_key;
}
