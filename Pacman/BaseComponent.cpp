#include "BaseComponent.h"

void BaseComponent::Start()
{
}

void BaseComponent::Draw() const
{
}

void BaseComponent::Update(const float dt)
{
}

void BaseComponent::SetGO(GameObject* go)
{
	this->gameObject = go;
}
