// Made by Kaih White
//contributed by kunga
#ifndef GAME_H
#define GAME_H

#define WITH_WINMM

#include "Player.h"
#include "renderer.h"
#include "resource_manager.h"
#include "glm/glm.hpp"
#include "Animation.h"
#include "box2d/box2d.h"
#include "SoundPlayer.h"
#include "soloud.h"
#include "soloud_wav.h"
#include <vector>
#include <random>
#include <map>
#include "npc.h"

// Represents the current state of the game
enum GameState {
    GAME_ACTIVE,
    GAME_EDITOR,
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
    static SoLoud::Soloud* soundEngine;
    Player                  *player;
    Renderer                *renderer;
    b2World                 *world;
    Camera2DSystem          *cameraMan;
    bool                    playerExists;
    std::map<int, GameObject*> gameObjects;
    std::vector< int> renderGameObjectsList;
    float timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 8;
    int32 positionIterations = 3;


    // constructor/destructor
    Game(unsigned int width, unsigned int height);
    ~Game();

    // initialize game state (load all shaders/textures/levels)
    void Init(unsigned int width, unsigned int height);

    void initLevel(std::pair<std::vector<int>, std::map<int, GameObject*>>level);

    Animation* loadAnimation(const char* file, bool alpha, std::string name, int numFrames);

    // adds the game object to the level
    void addGameObject(std::string name, ObjectType type, RigidBodyType rtype, std::unordered_map<std::string, Animation*> animations, std::unordered_set<std::string> sounds, glm::vec3 color, glm::vec2 size, glm::vec2 pos);
    void addPlayerObject(glm::vec2 pos, glm::vec2 size, glm::vec3 color, std::unordered_map<std::string, Animation*> animations, std::string type, std::unordered_set<std::string> sounds, bool dynam);
    void addNPCObject(std::string name, glm::vec2 pos, glm::vec2 size, glm::vec3 color, std::unordered_map<std::string, Animation*> animations, std::string type, std::unordered_set<std::string> sounds, bool dynam);
 
    // removes the game object from the level
    void removeGameObject(int key);

    void removeAllGameObject();
    // updates a game object in the level
    void updateGameObject(int key, std::string name, ObjectType type, RigidBodyType rtype, std::unordered_map<std::string, Animation*> animations, std::unordered_set<std::string> sounds, glm::vec3 color, glm::vec2 size, glm::vec2 pos);

    // Only allows for one player
    void addPlayer(Camera2DSystem* cameraMan, std::unordered_map<std::string, Animation*> animations, std::unordered_set<std::string> sounds, glm::vec3 color, glm::vec2 size, glm::vec2 pos);

    void updatePlayer(std::unordered_map<std::string, Animation*> animations, std::unordered_set<std::string> sounds, glm::vec3 color, glm::vec2 size, glm::vec2 pos);

    static int generateUniqueKey(std::map<int, GameObject*> map);

    // plays a sound
    static void playSound(std::string sound);
    // game loop
    void ProcessInput(float& dt);
    void Update();
    void updateWorldCamera();
    void Render();
};

#endif