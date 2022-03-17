#ifndef MAPLOADER_H
#define MAPLOADER_H

class PathmapTile;

class MapLoader
{
public:
	MapLoader() = default;
	~MapLoader() = default;

	PathmapTile* Read(const char* filePath);
};
#endif