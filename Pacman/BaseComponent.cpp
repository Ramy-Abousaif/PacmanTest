#include "BaseComponent.h"
#include "MyGame.h"

BaseComponent::BaseComponent()
{
	this->active = true;
}

void BaseComponent::Awake()
{
}

void BaseComponent::Start()
{
}

GameObject* BaseComponent::GetGameObject() const
{
	return this->gameObject;
}

void BaseComponent::SetActive(const bool _active)
{
	this->active = _active;
}

bool BaseComponent::GetActive() const
{
	return this->active;
}

void BaseComponent::Draw() const
{
	if (active)
		_Draw();
}

void BaseComponent::Update(const float dt)
{
	if (active)
		_Update(dt);
}

void BaseComponent::SetGO(GameObject* go)
{
	this->gameObject = go;
}
