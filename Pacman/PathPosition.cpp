#include "PathPosition.h"
#include "MyGame.h"

PathPosition::PathPosition()
{
	this->map = nullptr;
}

PathPosition::~PathPosition()
{
}

void PathPosition::Start()
{
	this->map = MyGame::Instance->GetMap();
}

void PathPosition::Update(const float dt)
{
}

unsigned int PathPosition::GetTilePosX() const
{
	float tileMapSizeX = (float)map->GetSizeX() - 1;
	float distBetweenTiles = map->GetDistBetweenTiles();
	unsigned int x = (unsigned int)(gameObject->pos.X / distBetweenTiles + tileMapSizeX / 2.0f);
	return x;
}

unsigned int PathPosition::GetTilePosY() const
{
	float tileMapSizeY = (float)map->GetSizeY() - 1;
	float distBetweenTiles = map->GetDistBetweenTiles();
	unsigned int y = (unsigned int)(gameObject->pos.Y / distBetweenTiles + tileMapSizeY / 2.0f);
	return y;
}

Vector2f PathPosition::GetTileWorldPos(const unsigned int x, const unsigned int y) const
{
	float mapSizeX = (float)map->GetSizeX() - 1;
	float mapSizeY = (float)map->GetSizeY() - 1;
	float distBetweenTiles = map->GetDistBetweenTiles();

	float xF = (float)x;
	float yF = (float)y;

	Vector2f pos;
	pos.X = (xF - mapSizeX / 2.0f) * distBetweenTiles;
	pos.Y = (yF - mapSizeY / 2.0f) * distBetweenTiles;
	return pos;
}

void PathPosition::SetPos(const unsigned int x, const unsigned int y)
{
	gameObject->pos = GetTileWorldPos(x, y);
}
