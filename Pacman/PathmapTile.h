#ifndef PATHMAPTILE_H
#define PATHMAPTILE_H

enum class TileType : short
{
	Wall,
	Dot,
	BigDot,
	Cherry,
	Teleport,
	Empty
};

struct Tile
{
	TileType type = TileType::Empty;
	bool isWalkable = false;
};

class PathmapTile
{
private:
	Tile* map = nullptr;
	float distBetweenTiles = 1.0f;
	int rows = 0;
	int columns = 0;

public:
	PathmapTile(unsigned int sizeX, unsigned int sizeY, float distBetweenTiles = 1.0f);
	~PathmapTile();

	unsigned int GetSizeX() const;
	unsigned int GetSizeY() const;
	float GetDistBetweenTiles() const;
	void SetDistBetweenTiles(const float distBetweenTiles);
	Tile GetTile(unsigned int x, unsigned int y) const;
	void SetTile(unsigned int x, unsigned int y, const Tile& tile);
};
#endif