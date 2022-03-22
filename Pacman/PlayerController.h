#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "BaseComponent.h"
#include "Event.h"

class Animator;
class PathPosition;
class Movement;
class Teleporter;

class PlayerController : public BaseComponent, CollisionEventListener, PelletCollectedEventDispatcher, BigPelletCollectedEventDispatcher, PlayerHitEventDispatcher, GhostKilledEventDispatcher
{
protected:
	void _Update(const float& dt) override;

private:
	void Pellet();
	void BigPellet();
	void GhostKill();
	void Hit();
	bool IsWalkable(const unsigned int x, const unsigned int y) const;

	Animator* anim = nullptr;
	PathPosition* pathPosition = nullptr;
	Movement* movement = nullptr;
	Teleporter* tpLoc = nullptr;
	int prevInputX = -1;
	int prevInputY = 0;

public:
	PlayerController();
	~PlayerController() override;

	void Awake() override;
	void Start() override;

	void OnEvent(const CollisionEvent& event, const CollisionEventDispatcher& sender) override;
	void Assign(PelletCollectedEventListener* listener);
	void Unassign(PelletCollectedEventListener* listener);
	void Assign(BigPelletCollectedEventListener* listener);
	void Unassign(BigPelletCollectedEventListener* listener);
	void Assign(PlayerHitEventListener* listener);
	void Unassign(PlayerHitEventListener* listener);
	void Assign(GhostKilledEventListener* listener);
	void Unassign(GhostKilledEventListener* listener);
};
#endif