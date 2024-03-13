/*
	by kunga ngochetsang

*/

#include <box2d/box2d.h>
#include<texture.h>
#pragma once
class Tile2D
{
	// variables
private:
	int TileId;
	int TileSize;
	bool renderit;
	Texture2D tileTexture;
	b2Body* tileBody;

	// functions
public:
	// default
	Tile2D();
	// Constructor
	Tile2D(int id, Texture2D texture, b2Body* body);
	// Destructor
	~Tile2D(); 

	//funtions

	//getter/setter
	void setTileId(int id);
	int getTileId();
	void setTileTexture(Texture2D texture);
	Texture2D getTileTexture();
	void setBody(b2Body* body);
	b2Body* getBody();
};

