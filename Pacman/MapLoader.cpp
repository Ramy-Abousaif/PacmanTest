#include "PathmapTile.h"
#include "MapLoader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

PathmapTile* MapLoader::Read(const char* path)
{
	std::vector<std::string> lines;

	std::ifstream myfile(path);
	if (!myfile.is_open())
		return nullptr;

	unsigned int rows = 0;
	unsigned int columns = 0;

	std::string line;
	while (!myfile.eof())
	{
		std::getline(myfile, line);
		lines.push_back(line);

		if (line.length() > columns)
			columns = line.length();
		else
			columns = columns;

		++rows;
	}
	myfile.close();

	PathmapTile* map = new PathmapTile(columns, rows);

	for (unsigned int i = 0; i < lines.size(); ++i)
	{
		unsigned int Y = lines.size() - 1 - i;
		for (unsigned int j = 0; j < lines[i].length(); j++)
		{
			Tile tile;
			switch (lines[i][j])
			{
			case 'x':
				tile.type = TileType::Wall;
				tile.isWalkable = false;
				break;
			case 'o':
				tile.type = TileType::BigDot;
				tile.isWalkable = true;
				break;
			case '.':
				tile.type = TileType::Dot;
				tile.isWalkable = true;
				break;
			case 'c':
				tile.type = TileType::Cherry;
				tile.isWalkable = true;
				break;
			case ' ':
				tile.type = TileType::Empty;
				tile.isWalkable = true;
				break;
			default:
				tile.type = TileType::Empty;
				tile.isWalkable = true;
				break;
			}
			map->SetTile(j, Y, tile);
		}
	}

	return map;
}
