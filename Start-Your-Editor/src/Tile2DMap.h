/*
	by kunga ngohetsang

*/
#pragma once
#include "Tile2D.h"
#include <vector>

class Tile2DMap
{
private:
	int tileMapWidth, tileMapHeight; // tile map width and height
	int tileSize; // size in pixels of each tile size
	std::vector<std::vector<Tile2D>> tiles;

public:
	//constructor
	Tile2DMap(int tileMapWidth, int tileMapHeight, int tileSize);
	// tileMap functions
};

