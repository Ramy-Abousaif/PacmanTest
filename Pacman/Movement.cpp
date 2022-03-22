#include "Movement.h"
#include "PathmapTile.h"
#include "MyGame.h"
#include "GameManager.h"
#include "GameObject.h"
#include "PathPosition.h"

Movement::Movement()
{
	this->pathPosition = nullptr;

	this->originSpeed = 1.0f;
	this->speed = 1.0f;
	this->desiredPosX = 0;
	this->desiredPosY = 0;
	this->currentPosX = 0;
	this->currentPosY = 0;
}


Movement::~Movement()
{
}

void Movement::Awake()
{
	this->pathPosition = GetGameObject()->GetComponent<PathPosition>();
	if (pathPosition == nullptr)
		pathPosition = GetGameObject()->AddComponent<PathPosition>();
}

void Movement::Start()
{
	this->desiredPosX = this->pathPosition->GetTilePosX();
	this->desiredPosY = this->pathPosition->GetTilePosY();
	this->currentPosX = this->pathPosition->GetTilePosX();
	this->currentPosY = this->pathPosition->GetTilePosY();
}

void Movement::_Update(const float& dt)
{
	const unsigned int prevPosX = GetDesiredPosX();
	const unsigned int prevPosY = GetDesiredPosY();
	Vector2f finalPos = this->pathPosition->GetMap()->GetTileWorldPos(prevPosX, prevPosY);
	Vector2f distance = finalPos - GetGameObject()->pos;

	const float moveSpeed = dt * speed;
	if (moveSpeed > distance.Length())
		SetCurrentPos(prevPosX, prevPosY);
	else
	{
		distance.Normalize();
		GetGameObject()->pos += distance * moveSpeed;
	}
}

bool Movement::SetDesiredPos(const unsigned int x, const unsigned int y)
{
	if (!this->pathPosition->GetMap()->IsPosValid(x, y))
		return false;

	this->desiredPosX = x;
	this->desiredPosY = y;
	return true;
}

unsigned int Movement::GetDesiredPosX() const
{
	return this->desiredPosX;
}

unsigned int Movement::GetDesiredPosY() const
{
	return this->desiredPosY;
}

int Movement::GetDirX() const
{
	return (int)GetDesiredPosX() - (int)GetCurrentPosX();
}

int Movement::GetDirY() const
{
	return (int)GetDesiredPosY() - (int)GetCurrentPosY();
}

void Movement::SetCurrentPos(const unsigned int x, const unsigned int y)
{
	if (!this->pathPosition->GetMap()->IsPosValid(x, y))
		return;

	this->currentPosX = x;
	this->currentPosY = y;
	this->desiredPosX = x;
	this->desiredPosY = y;
	this->pathPosition->SetPos(x, y);
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
	return (GetCurrentPosY() == GetDesiredPosY()
		&& GetCurrentPosX() == GetDesiredPosX());
}

void Movement::SetSpeed(const float& _speed)
{
	this->speed = _speed;
}

void Movement::SetOriginSpeed(const float& _originSpeed)
{
	this->originSpeed = _originSpeed;
}

float Movement::GetOriginSpeed()
{
	return this->originSpeed;
}
