// Made by Kaih White
#pragma once
#include "document.h"
#include "prettywriter.h" // for stringify JSON
#include "filereadstream.h"
#include "filewritestream.h"
#include "reader.h"
#include "glm/glm.hpp"
#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <random>

#include "GameObject.h"
#include "Player.h"

class Level {
public:

    static void saveToJSON(const std::string& filename, std::unordered_map<int, GameObject*> gameObjects);
    static std::unordered_map<int, GameObject*> loadFromJSON(const std::string& filename, b2World* world, Camera2DSystem* cameraMan);

private:
    Level() { };
};

