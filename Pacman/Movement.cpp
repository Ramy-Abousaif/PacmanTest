#include "Movement.h"
#include "PathmapTile.h"
#include "MyGame.h"
#include "PathPosition.h"

Movement::Movement()
{
	this->map = nullptr;
	this->pathPosition = nullptr;
	this->desiredPosX = 0;
	this->desiredPosY = 0;
	this->currentPosX = 0;
	this->currentPosY = 0;
}


Movement::~Movement()
{
}

void Movement::Update(const float dt)
{
}

void Movement::Start()
{
	this->map = MyGame::Instance->GetMap();
	this->pathPosition = gameObject->GetComponent<PathPosition>();
	this->desiredPosX = this->pathPosition->GetTilePosX();
	this->desiredPosY = this->pathPosition->GetTilePosY();
	this->currentPosX = this->pathPosition->GetTilePosX();
	this->currentPosY = this->pathPosition->GetTilePosY();
}

bool Movement::IsWalkable(const unsigned int x, const unsigned int y) const
{
	if (x >= this->map->GetSizeX())
		return false;

	if (y >= this->map->GetSizeY())
		return false;

	const Tile& tile = map->GetTile(x, y);
	return tile.isWalkable;
}

bool Movement::SetDesiredPos(const unsigned int x, const unsigned int y)
{
	if (IsWalkable(x, y))
	{
		this->desiredPosX = x;
		this->desiredPosY = y;
		return true;
	}
	return false;
}

unsigned int Movement::GetDesiredPosX() const
{
	return this->desiredPosX;
}

unsigned int Movement::GetDesiredPosY() const
{
	return this->desiredPosY;
}

void Movement::SetCurrentPos(const unsigned int x, const unsigned int y)
{
	if (IsWalkable(x, y))
	{
		this->currentPosX = x;
		this->currentPosY = y;
	}
}

unsigned int Movement::GetCurrentPosX() const
{
	return this->currentPosX;
}

unsigned int Movement::GetCurrentPosY() const
{
	return this->currentPosY;
}

bool Movement::ReachedDesiredPos() const
{
	return this->currentPosY == this->desiredPosY
		&& this->currentPosX == this->desiredPosX;
}
