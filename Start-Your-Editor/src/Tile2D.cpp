/*
	by kunga ngochetsang

*/

#include "Tile2D.h"
Tile2D::Tile2D() {
	TileId = -1;
	tileTexture = Texture2D();
	tileBody = NULL;
}
Tile2D::Tile2D(int id, Texture2D texture , b2Body* body) :
	TileId(id), tileTexture(texture), tileBody(body)
{

}
Tile2D::~Tile2D() {
	this->tileBody->GetWorld()->DestroyBody(tileBody);
}


// tile id functions
void Tile2D::setTileId(int id) {
	this->TileId = id;
}
int Tile2D::getTileId()
{
	return this->TileId;
}

// texture id functions
void  Tile2D::setTileTexture(Texture2D texture) {
	this->tileTexture = texture;
}
Texture2D Tile2D::getTileTexture()
{
	return tileTexture;
}

// b2body def functions
void Tile2D::setBody(b2Body* body)
{
	this->tileBody = body;
}
b2Body* Tile2D::getBody() {
	return this->tileBody;
}
