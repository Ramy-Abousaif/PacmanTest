#include "Dot.h"

Dot::Dot()
{
	this->pointsToAdd = 0;
}

Dot::~Dot()
{
}

void Dot::Start()
{
}

void Dot::Update(const float dt)
{
}

void Dot::SetAddedPoints(const int points)
{
	this->pointsToAdd = points;
}

int Dot::GetAddedPoints() const
{
	return this->pointsToAdd;
}