#ifndef ENEMY_H
#define ENEMY_H

#include "BaseComponent.h"
#include "Event.h"

struct Tile;
class Movement;
class Teleporter;
class Animator;
class PathPosition;
class EnemyPathFinder;

enum class EnemyState : short
{
	LeavingPen,
	Roam,
	Chase,
	Flee,
	Still,
	Dead
};

class Enemy : public BaseComponent, BigPelletCollectedEventListener
{
protected:
	void _Update(const float& dt) override;
	virtual void SetUpAnims() = 0;
	virtual Tile* GetGhostTile() const = 0;
	virtual Tile* GetRoamTile() const = 0;
	virtual Tile* GetChaseTile() const = 0;

	Animator* anim = nullptr;
	PathPosition* pathPosition = nullptr;
	Movement* movement = nullptr;
	EnemyPathFinder* pathFinder = nullptr;

private:
	Tile* GetRandomTile() const;

	void SetLeavingPenState();
	void SetRoamState();
	void SetChaseState();
	void SetFleeState();
	void SetStillState();
	void GoToState();

	EnemyState state = EnemyState::Still;
	int stateIndex = 0;
	float timer = 0.0f;
	float duration = 1.0f;

public:
	Enemy();
	~Enemy() override;

	EnemyState GetState() const;
	void Awake() override;
	void Start() override;
	void OnEvent(const BigPelletCollectedEvent& event, const BigPelletCollectedEventDispatcher& sender) override;
	void SetDeadState();
	void SetNewDuration(const float seconds);
};


//////////////////////////
/*DIFFERENT GHOST TYPES*/
//////////////////////////


class PinkGhost : public Enemy
{
protected:
	void SetUpAnims() override;

	Tile* GetGhostTile() const override;
	Tile* GetRoamTile() const override;
	Tile* GetChaseTile() const override;
};

class OrangeGhost : public Enemy
{
protected:
	void SetUpAnims() override;

	Tile* GetGhostTile() const override;
	Tile* GetRoamTile() const override;
	Tile* GetChaseTile() const override;
};

class BlueGhost : public Enemy
{
protected:
	void SetUpAnims() override;

	Tile* GetGhostTile() const override;
	Tile* GetRoamTile() const override;
	Tile* GetChaseTile() const override;
};

class RedGhost : public Enemy
{
protected:
	void SetUpAnims() override;

	Tile* GetGhostTile() const override;
	Tile* GetRoamTile() const override;
	Tile* GetChaseTile() const override;
};
#endif

