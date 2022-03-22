#include "PathPosition.h"
#include "MyGame.h"
#include "GameManager.h"
#include "PathmapTile.h"
#include "GameObject.h"

PathPosition::PathPosition()
{
	this->map = nullptr;
}

PathPosition::~PathPosition()
{
}

void PathPosition::Awake()
{
	GameManager* gameManager = MyGame::Instance->GetComponent<GameManager>();
	this->map = gameManager->GetMap();
}

PathmapTile* PathPosition::GetMap() const
{
	return this->map;
}

unsigned int PathPosition::GetTilePosX() const
{
	return map->WorldPosToTilePosX(GetGameObject()->pos.X);
}

unsigned int PathPosition::GetTilePosY() const
{
	return map->WorldPosToTilePosY(GetGameObject()->pos.Y);
}

void PathPosition::SetPos(const unsigned int x, const unsigned int y)
{
	GetGameObject()->pos = map->GetTileWorldPos(x, y);
}
