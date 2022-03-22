#include "Pellet.h"

Pellet::Pellet()
{
	this->pointsToAdd = 0;
}

Pellet::~Pellet()
{
}

void Pellet::SetAddedPoints(const int points)
{
	this->pointsToAdd = points;
}

int Pellet::GetAddedPoints() const
{
	return this->pointsToAdd;
}