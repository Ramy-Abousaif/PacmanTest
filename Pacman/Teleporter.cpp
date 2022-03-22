#include "Teleporter.h"

Teleporter::Teleporter()
{
	this->other = nullptr;
}

Teleporter::~Teleporter()
{
}

Teleporter* Teleporter::GetOtherTP()
{
	return this->other;
}

void Teleporter::SetOtherTP(Teleporter* otherTP)
{
	if (otherTP == nullptr)
		return;

	this->other = otherTP;
}
