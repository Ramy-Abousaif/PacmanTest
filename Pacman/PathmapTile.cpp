#include "PathmapTile.h"

PathmapTile::PathmapTile(int sizeX, int sizeY)
{
	if (sizeX < 1 || sizeY < 1)
		return;

	columns = sizeX;
	rows = sizeY;

	map = new Tile[rows * columns];
}

PathmapTile::~PathmapTile()
{
	delete[] map;
}

void PathmapTile::SetTile(int x, int y, const Tile& tile)
{
	if (y >= rows || y < 0)
		return;

	if (x >= columns || x < 0)
		return;

	map[x + columns * y] = tile;
	map[x + columns * y].x = x;
	map[x + columns * y].y = y;
}

Tile PathmapTile::GetTile(int x, int y) const
{
	if (y >= rows || y < 0)
		return Tile();

	if (x >= columns || x < 0)
		return Tile();

	return map[x + columns * y];
}

int PathmapTile::GetSizeX() const
{
	return columns;
}

int PathmapTile::GetSizeY() const
{
	return rows;
}
