#include "GameObject.h"
#include "BaseComponent.h"

GameObject::GameObject(const Vector2f& pos)
{
	this->active = true;
	this->pos = pos;
	this->tag = TagManager::Default;
}

GameObject::~GameObject()
{
	for (BaseComponent* component : components)
		delete component;
}

void GameObject::StartComponents()
{
	for (BaseComponent* initialComponent : initialComponents)
		initialComponent->Start();

	initialComponents.clear();
}

void GameObject::UpdateComponents(const float dt)
{
	for (BaseComponent* component : components)
		component->Update(dt);
}

void GameObject::DrawComponents() const
{
	for (BaseComponent* component : components)
		component->Draw();
}
void GameObject::Update(const float dt)
{
	if (!active)
		return;

	StartComponents();
	UpdateComponents(dt);
}

void GameObject::Draw() const
{
	if (!active)
		return;

	DrawComponents();
}

void GameObject::SetActive(const bool _active)
{
	this->active = _active;
}

