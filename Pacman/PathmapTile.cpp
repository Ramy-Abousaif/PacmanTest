#include "PathmapTile.h"

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

void PathmapTile::SetTile(unsigned int x, unsigned int y, const Tile& tile)
{
	if (y >= rows || y < 0)
		return;

	if (x >= columns || x < 0)
		return;

	map[x + columns * y] = tile;
}

Tile PathmapTile::GetTile(unsigned int x, unsigned int y) const
{
	if (x >= columns || x < 0)
		return Tile();

	if (y >= rows || y < 0)
		return Tile();

	return map[x + columns * y];
}

unsigned int PathmapTile::GetSizeX() const
{
	return columns;
}

unsigned int PathmapTile::GetSizeY() const
{
	return rows;
}

float PathmapTile::GetDistBetweenTiles() const
{
	return this->distBetweenTiles;
}

void PathmapTile::SetDistBetweenTiles(const float distBetweenTiles)
{
	if (distBetweenTiles < 0.f)
		return;

	this->distBetweenTiles = distBetweenTiles;
}
