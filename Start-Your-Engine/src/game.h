// Made by Kaih White
#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "renderer.h"
#include "resource_manager.h"
#include "glm/glm.hpp"
#include "Animation.h"
#include "box2d/box2d.h"

#include <vector>

// Represents the current state of the game
enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

// Game holds all game-related state and functionality.
// Combines all game-related data into a single class for
// easy access to each of the components and manageability.
class Game
{
public:
    // game state
    GameState               State;
    bool                    Keys[1024];
    unsigned int            Width; 
    unsigned int            Height;
    Player                  *player;
    Renderer                *renderer;
   
    std::vector<GameObject*> gameObjects;
    b2World                 *world;

    float timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 8;
    int32 positionIterations = 3;




    // constructor/destructor
    Game(unsigned int width, unsigned int height);
    ~Game();
    // initialize game state (load all shaders/textures/levels)
    void Init(unsigned int width, unsigned int height);

    // TODO: is there a beneifit to passing this by reference over value
    void initLevel(std::vector<GameObject*>& level);

    // game loop
    void ProcessInput(float& dt);
    void Update();
    void Render();
};

#endif