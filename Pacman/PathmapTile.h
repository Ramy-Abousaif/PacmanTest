#ifndef PATHMAPTILE_H
#define PATHMAPTILE_H

class Vector2f;

enum class TileType : short
{
	Wall,
	Pellet,
	BigPellet,
	Cherry,
	GhostTile,
	TeleportTile,
	Empty
};

struct Tile
{
	TileType type = TileType::Empty;
	bool canPlayerWalk = false;
	bool canEnemyWalk = false;
	unsigned int x;
	unsigned int y;
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

	Vector2f GetTileWorldPos(const unsigned int x, const unsigned int y) const;
	unsigned int GetSizeX() const;
	unsigned int GetSizeY() const;
	unsigned int WorldPosToTilePosX(const float x);
	unsigned int WorldPosToTilePosY(const float y);
	bool IsPosValid(const unsigned int x, const unsigned int y) const;
	float GetDistBetweenTiles() const;
	void SetDistBetweenTiles(const float distBetweenTiles);
	Tile* GetTile(unsigned int x, unsigned int y) const;
	void SetTile(unsigned int x, unsigned int y, Tile& tile);
};
#endif