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

#include "GameObject.h"
#include "Player.h"

class Level {
public:

    static void saveToJSON(const std::string& filename, std::vector<GameObject*> gameObjects);
    static std::vector<GameObject*> loadFromJSON(const std::string& filename, b2World* world);

private:
    Level() { };
};

