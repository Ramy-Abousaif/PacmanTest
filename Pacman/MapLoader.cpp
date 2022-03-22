#include "MapLoader.h"
#include "PathmapTile.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

PathmapTile* MapLoader::Read(const char* filePath)
{
	std::vector<std::string> lines;

	std::ifstream myfile(filePath);
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

	for (unsigned int columns = 0; columns < lines.size(); ++columns)
	{
		unsigned int y = lines.size() - 1 - columns;
		for (unsigned int x = 0; x < lines[columns].length(); x++)
		{
			Tile tile;
			switch (lines[columns][x])
			{
			case 'c':
				tile.type = TileType::Cherry;
				tile.canPlayerWalk = true;
				tile.canEnemyWalk = true;
				break;
			case 'o':
				tile.type = TileType::BigPellet;
				tile.canPlayerWalk = true;
				tile.canEnemyWalk = true;
				break;
			case '.':
				tile.type = TileType::Pellet;
				tile.canPlayerWalk = true;
				tile.canEnemyWalk = true;
				break;
			case 'x':
				tile.type = TileType::Wall;
				tile.canPlayerWalk = false;
				tile.canEnemyWalk = false;
				break;
			case 'g':
				tile.type = TileType::GhostTile;
				tile.canPlayerWalk = false;
				tile.canEnemyWalk = true;
				break;
			case 't':
				tile.type = TileType::TeleportTile;
				tile.canPlayerWalk = true;
				tile.canEnemyWalk = true;
				break;
			case ' ':
				tile.type = TileType::Empty;
				tile.canPlayerWalk = true;
				tile.canEnemyWalk = true;
				break;
			default:
				tile.type = TileType::Empty;
				tile.canPlayerWalk = true;
				tile.canEnemyWalk = true;
				break;
			}
			map->SetTile(x, y, tile);
		}
	}

	return map;
}
