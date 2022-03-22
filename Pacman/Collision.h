#ifndef COLLISION_H
#define COLLISION_H

#include "BaseComponent.h"
#include <map>
#include "Event.h"
#include <vector>

class Collision : public BaseComponent, CollisionEventDispatcher
{
protected:
	void _Update(const float& dt) override;

private:
	std::map<GameObject*, CollisionType> colType;
	std::vector<GameObject*> others;
	float radius = 0.3f;

public:
	Collision();
	~Collision() override;

	void SetSize(const float _radius);
	void Assign(CollisionEventListener* listener);
	void Unassign(CollisionEventListener* listener);
	void AddOther(GameObject* other);
};
#endif
