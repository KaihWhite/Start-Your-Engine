/*
	by kunga ngohetsang

*/

#include "Tile2DMap.h"
//constructor
Tile2DMap::Tile2DMap(glm::vec2 pos, glm::vec2 size, glm::vec3 color, std::unordered_map<std::string, Animation*> animations, b2World* world, std::string type, std::unordered_set<std::string> sounds, bool dynam)
	: GameObject("worldMap", pos, size, color, animations, world, type, sounds, dynam), tileMap(size.x, std::vector<Tile2D>(size.y))
{

}
