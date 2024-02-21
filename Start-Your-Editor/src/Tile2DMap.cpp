/*
	by kunga ngohetsang

*/

#include "Tile2DMap.h"
//constructor
Tile2DMap::Tile2DMap(int tileMapWidth, int tileMapHeight, int tileSize):
	tileMapWidth(tileMapWidth), tileMapHeight(tileMapHeight), tileSize(tileSize)
{
	tiles.resize(tileMapWidth, std::vector<Tile2D>(tileMapHeight));
}
