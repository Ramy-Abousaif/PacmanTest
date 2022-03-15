#include "GameObject.h"
#include "BaseComponent.h"


GameObject::GameObject() : GameObject(Vector2f(0, 0))
{
}

GameObject::GameObject(const Vector2f& pos) : Active(true), Pos(pos)
{
}

void GameObject::Draw() const
{
	if (!Active)
		return;

	for (BaseComponent* component : components)
	{
		component->Draw();
	}
}

void GameObject::Update(const float dt)
{
	if (!Active)
		return;

	UpdateComponents(dt);
}

void GameObject::UpdateComponents(const float dt)
{
	for (BaseComponent* component : components)
	{
		component->Update(dt);
	}
}

void GameObject::SetActive(const bool active)
{
	Active = active;
}

