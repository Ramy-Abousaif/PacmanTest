#include "PathmapTile.h"
#include "Vector2f.h"

PathmapTile::PathmapTile(unsigned int sizeX, unsigned int sizeY, float distBetweenTiles)
{
	if (sizeX < 1 || sizeY < 1)
		return;

	this->rows = sizeY;
	this->columns = sizeX;
	this->distBetweenTiles = distBetweenTiles;
	this->map = new Tile[rows * columns];
}

PathmapTile::~PathmapTile()
{
	delete[] map;
}

Vector2f PathmapTile::GetTileWorldPos(const unsigned int x, const unsigned int y) const
{
	float tileMapSizeX = (float)GetSizeX() - 1;
	float tileMapSizeY = (float)GetSizeY() - 1;
	float Xf = (float)x;
	float Yf = (float)y;
	Vector2f position;
	position.X = (Xf - tileMapSizeX / 2.0f) * distBetweenTiles;
	position.Y = (Yf - tileMapSizeY / 2.0f) * distBetweenTiles;
	return position;
}

void PathmapTile::SetTile(unsigned int x, unsigned int y, Tile& tile)
{
	if (!IsPosValid(x, y))
		return;

	tile.x = x;
	tile.y = y;
	map[x + columns * y] = tile;
}

Tile* PathmapTile::GetTile(unsigned int x, unsigned int y) const
{
	if (!IsPosValid(x, y))
		return nullptr;

	return &map[x + columns * y];
}

unsigned int PathmapTile::GetSizeX() const
{
	return columns;
}

unsigned int PathmapTile::GetSizeY() const
{
	return rows;
}

bool PathmapTile::IsPosValid(const unsigned int x, const unsigned int y) const
{
	return (x < columns && y < rows);
}

unsigned int PathmapTile::WorldPosToTilePosX(const float x)
{
	float tileMapSizeX = (float)GetSizeX() - 1;
	return (unsigned int)((x / distBetweenTiles) + tileMapSizeX / 2.0f);
}

unsigned int PathmapTile::WorldPosToTilePosY(const float y)
{
	float tileMapSizeY = (float)GetSizeY() - 1;
	return (unsigned int)((y / distBetweenTiles) + tileMapSizeY / 2.0f);
}

float PathmapTile::GetDistBetweenTiles() const
{
	return this->distBetweenTiles;
}

void PathmapTile::SetDistBetweenTiles(const float distBetweenTiles)
{
	if (distBetweenTiles < 0.0f)
		return;

	this->distBetweenTiles = distBetweenTiles;
}
