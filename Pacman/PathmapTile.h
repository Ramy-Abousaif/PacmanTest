class PathmapTile
{
private:
	int rows = 0;
	int columns = 0;
	Tile* map;
public:
	PathmapTile(int sizeX, int sizeY);
	~PathmapTile();

	Tile GetTile(int x, int y) const;
	void SetTile(int x, int y, const Tile& tile);
	int GetSizeX() const;
	int GetSizeY() const;
};

enum TileType
{
	Wall,
	Dot,
	BigDot,
	Cherry,
	Empty
};

struct Tile
{
	int x = 0;
	int y = 0;
	TileType type = TileType::Empty;
	bool isWalkable = false;
};