#include "GameObject.h"
#include "BaseComponent.h"

GameObject::GameObject(const Vector2f& pos)
{
	this->active = true;
	this->pos = pos;
}

GameObject::~GameObject()
{
	for (unsigned int i = 0; i < components.size(); ++i)
		delete components[i];
}

void GameObject::UpdateComponents(const float dt)
{
	for (BaseComponent* component : components)
		component->Update(dt);
}

void GameObject::Update(const float dt)
{
	if (!active)
		return;

	UpdateComponents(dt);
}

void GameObject::Draw() const
{
	if (!active)
		return;

	for (BaseComponent* component : components)
		component->Draw();
}

void GameObject::SetActive(const bool _active)
{
	this->active = _active;
}

