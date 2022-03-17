#ifndef COLLISION_H
#define COLLISION_H

#include <map>
#include <vector>
#include "BaseComponent.h"
#include "Event.h"

class Collision : public BaseComponent, CollisionEventDispatcher
{
private:
	std::map<GameObject*, CollisionType> colType;
	std::vector<GameObject*> others;

public:
	Collision();
	~Collision() override;
	void Assign(CollisionEventListener* listener);
	void Unassign(CollisionEventListener* listener);
	void Start() override;
	void Update(const float dt) override;
	void AddOther(GameObject* other);
};
#endif
