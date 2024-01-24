// Made by Kaih White
#pragma once
#include "document.h"
#include "prettywriter.h" // for stringify JSON
#include "filereadstream.h"
#include "filewritestream.h"
#include "reader.h"
#include <cstdio>
#include <vector>

#include "GameObject.h" // Include your GameObject class

class Level {
public:

    static void saveToJSON(const std::string& filename, std::vector<GameObject*> gameObjects);
    static std::vector<GameObject*> loadFromJSON(const std::string& filename);

private:
    Level() { };
};

