/*
	by kunga ngohetsang

*/
#pragma once
#include <vector>
#include "Tile2D.h"
#include "Game.h"


class Tile2DMap : GameObject
{
private:
	// here the game object size is the map width and height
	int tileSize; // size in pixels of each tile size
	std::vector<std::vector<Tile2D>> tileMap;

public:
	//constructor
	Tile2DMap(glm::vec2 pos, glm::vec2 size, glm::vec3 color, std::unordered_map<std::string, Animation*> animations, b2World* world, std::string type, bool dynam);
	// tileMap functions
};

