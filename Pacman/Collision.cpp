#include "Collision.h"
#include "MyGame.h"

Collision::Collision()
{
}

Collision::~Collision()
{
}

void Collision::Assign(CollisionEventListener* listener)
{
	CollisionEventDispatcher::Assign(listener);
}

void Collision::Unassign(CollisionEventListener* listener)
{
	CollisionEventDispatcher::Unassign(listener);
}

void Collision::SetSize(const float _radius)
{
	this->radius = _radius;
}

void Collision::_Update(const float& dt)
{
	Vector2f dist;
	for (unsigned int i = 0; i < others.size(); ++i)
	{
		if (others[i] == nullptr)
			continue;

		dist = this->GetGameObject()->pos - others[i]->pos;
		if (dist.Length() < radius)
		{
			CollisionType type = CollisionType::OnEnter;
			if (colType.count(others[i]) == 0)
				colType.insert({ others[i], type });
			else
			{
				type = CollisionType::OnStay;
				colType[others[i]] = type;
			}

			CollisionEvent event;
			event.type = type;
			event.other = others[i];
			event.thisGO = this->GetGameObject();
			Invoke(event);
		}
		else
		{
			if (colType.count(others[i]) > 0)
			{
				CollisionEvent event;
				event.type = CollisionType::OnExit;
				event.other = others[i];
				event.thisGO = this->GetGameObject();
				Invoke(event);
				colType.erase(others[i]);
			}
		}
	}
}

void Collision::AddOther(GameObject* other)
{
	if (other == nullptr)
		return;

	others.push_back(other);
}
