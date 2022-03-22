#include "EnemyPathFinder.h"
#include "GameObject.h"
#include "PathPosition.h"
#include "Movement.h"
#include "PathmapTile.h"

EnemyPathFinder::EnemyPathFinder()
{
	this->target = nullptr;
	this->pathPosition = nullptr;
	this->movement = nullptr;

	this->includePlayerTiles = false;

	this->lookDirX = 0;
	this->lookDirY = 0;
}

EnemyPathFinder::~EnemyPathFinder()
{
}

bool EnemyPathFinder::WalkableTile(Tile* tile) const
{
	if (this->includePlayerTiles)
		return (tile->canPlayerWalk && tile->canEnemyWalk);
	else
		return tile->canEnemyWalk;
}

void EnemyPathFinder::SetPlayerTileInclusion(const bool _includeTile)
{
	this->includePlayerTiles = _includeTile;
}

bool EnemyPathFinder::ReachedDesiredPos() const
{
	return (this->movement->GetCurrentPosX() == this->target->x && 
		this->movement->GetCurrentPosY() == this->target->y);
}

int EnemyPathFinder::SqrDist(Tile* tile1, Tile* tile2) const
{
	return (((int)tile1->x - (int)tile2->x) * ((int)tile1->x - (int)tile2->x)) +
		(((int)tile1->y - (int)tile2->y) * ((int)tile1->y - (int)tile2->y));
}

void EnemyPathFinder::Awake()
{
	this->movement = GetGameObject()->GetComponent<Movement>();
	this->pathPosition = GetGameObject()->GetComponent<PathPosition>();
}

void EnemyPathFinder::_Update(const float& dt)
{
	if (this->target == nullptr)
		return;

	if (ReachedDesiredPos())
		return;

	if (this->movement->ReachedDesiredPos())
		NextDesiredPos();
}

void EnemyPathFinder::NextDesiredPos()
{
	PathmapTile* map = this->pathPosition->GetMap();

	const int mapSizeX = (int)map->GetSizeX();
	const int mapSizeY = (int)map->GetSizeY();

	const int currentPosX = (int)this->movement->GetCurrentPosX();
	const int currentPosY = (int)this->movement->GetCurrentPosY();

	const int prevDirX = this->lookDirX;
	const int prevDirY = this->lookDirY;

	bool isDesiredPos = false;
	int minSqrDistance = (mapSizeX * mapSizeX) + (mapSizeY * mapSizeY) + 1;

	//Get tile above ghost
	Tile* relTileUp = map->GetTile(currentPosX, (currentPosY + 1) % mapSizeY);
	if (prevDirY != -1 && WalkableTile(relTileUp))
	{
		int sqrDistUp = SqrDist(target, relTileUp);
		if (sqrDistUp < minSqrDistance)
		{
			this->lookDirX = 0;
			this->lookDirY = 1;
			this->movement->SetDesiredPos(relTileUp->x, relTileUp->y);
			isDesiredPos = true;
			minSqrDistance = sqrDistUp;
		}
	}

	//Get tile below the ghost
	Tile* relTileDown = map->GetTile(currentPosX, (currentPosY + mapSizeY - 1) % mapSizeY);
	if (prevDirY != 1 && WalkableTile(relTileDown))
	{
		int sqrDistDown = SqrDist(target, relTileDown);
		if (sqrDistDown < minSqrDistance)
		{
			this->lookDirX = 0;
			this->lookDirY = -1;
			this->movement->SetDesiredPos(relTileDown->x, relTileDown->y);
			isDesiredPos = true;
			minSqrDistance = sqrDistDown;
		}
	}

	//Get tile to the left of the ghost
	Tile* relTileLeft = map->GetTile((currentPosX + mapSizeX - 1) % mapSizeX, currentPosY);
	if (prevDirX != 1 && WalkableTile(relTileLeft))
	{
		int sqrDistLeft = SqrDist(target, relTileLeft);
		if (sqrDistLeft < minSqrDistance)
		{
			this->lookDirX = -1;
			this->lookDirY = 0;
			this->movement->SetDesiredPos(relTileLeft->x, relTileLeft->y);
			isDesiredPos = true;
			minSqrDistance = sqrDistLeft;
		}
	}

	//Get tile to the right of the ghost
	Tile* relTileRight = map->GetTile((currentPosX + 1) % mapSizeX, currentPosY);
	if (prevDirX != -1 && WalkableTile(relTileRight))
	{
		int sqrDistRight = SqrDist(target, relTileRight);
		if (sqrDistRight < minSqrDistance)
		{
			this->lookDirX = 1;
			this->lookDirY = 0;
			this->movement->SetDesiredPos(relTileRight->x, relTileRight->y);
			isDesiredPos = true;
			minSqrDistance = sqrDistRight;
		}
	}

	if (!isDesiredPos)
		this->target = map->GetTile(currentPosX, currentPosY);
}

void EnemyPathFinder::SetDesiredPos(const unsigned int x, const unsigned int y, const bool los)
{
	if (!this->pathPosition->GetMap()->IsPosValid(x, y))
		return;

	if (los)
	{
		this->lookDirX = 0;
		this->lookDirY = 0;
	}

	this->target = this->pathPosition->GetMap()->GetTile(x, y);
	NextDesiredPos();
}