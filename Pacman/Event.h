#ifndef EVENT_H
#define EVENT_H

#include "EventHandler.h"

class GameObject;

struct LivesUpdateEvent
{
	int lives;
};
typedef EventDispatcher<LivesUpdateEvent> LivesUpdateEventDispatcher;
typedef EventDispatcher<LivesUpdateEvent>::Listener LivesUpdateEventListener;

struct PlayerHitEvent
{

};
typedef EventDispatcher<PlayerHitEvent> PlayerHitEventDispatcher;
typedef EventDispatcher<PlayerHitEvent>::Listener PlayerHitEventListener;

struct GhostKilledEvent
{

};
typedef EventDispatcher<GhostKilledEvent> GhostKilledEventDispatcher;
typedef EventDispatcher<GhostKilledEvent>::Listener GhostKilledEventListener;

struct PelletCollectedEvent
{

};
typedef EventDispatcher<PelletCollectedEvent> PelletCollectedEventDispatcher;
typedef EventDispatcher<PelletCollectedEvent>::Listener PelletCollectedEventListener;

struct BigPelletCollectedEvent
{

};
typedef EventDispatcher<BigPelletCollectedEvent> BigPelletCollectedEventDispatcher;
typedef EventDispatcher<BigPelletCollectedEvent>::Listener BigPelletCollectedEventListener;

struct PointsCollectedEvent
{
	int points;
};

typedef EventDispatcher<PointsCollectedEvent> PointsCollectedEventDispatcher;
typedef EventDispatcher<PointsCollectedEvent>::Listener PointsCollectedEventListener;

enum class CollisionType : short
{
	OnEnter,
	OnStay,
	OnExit
};

struct CollisionEvent
{
	CollisionType type;
	GameObject* thisGO;
	GameObject* other;
};

typedef EventDispatcher<CollisionEvent> CollisionEventDispatcher;
typedef EventDispatcher<CollisionEvent>::Listener CollisionEventListener;
#endif