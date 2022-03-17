#include "Teleporter.h"
#include "MyGame.h"
#include <vector>

Teleporter::Teleporter()
{
	this->other = nullptr;
}

Teleporter::~Teleporter()
{
}

void Teleporter::Start()
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

void Teleporter::Update(const float dt)
{
}
