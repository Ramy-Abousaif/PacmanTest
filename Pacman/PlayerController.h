#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "BaseComponent.h"
#include "Collision.h"

class Animator;
class PathPosition;
class Movement;
class Teleporter;

class PlayerController : public BaseComponent, CollisionEventListener, PointsCollectedEventDispatcher
{
private:
	Animator* anim = nullptr;
	float speed = 1.0f;
	PathPosition* pathPosition = nullptr;
	Movement* movement = nullptr;
	Vector2f prevInput = Vector2f(0.0f, 0.0f);
	Teleporter* tpLoc = nullptr;
	unsigned int points = 0;

public:
	PlayerController();
	~PlayerController() override;
	void SetPlayerSpeed(const float speed);
	void Start() override;
	void Update(const float dt) override;

	void OnEvent(const CollisionEvent& event, const CollisionEventDispatcher& sender) override;
	void Assign(PointsCollectedEventListener* listener) { PointsCollectedEventDispatcher::Assign(listener); }
	void Unassign(PointsCollectedEventListener* listener) { PointsCollectedEventDispatcher::Unassign(listener); }
};
#endif