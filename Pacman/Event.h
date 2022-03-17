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

enum class CollisionType : short
{
	OnEnter,
	OnStay,
	OnExit
};

struct CollisionEvent
{
	CollisionType type;
	GameObject* sender;
	GameObject* other;
};

typedef EventDispatcher<CollisionEvent> CollisionEventDispatcher;
typedef EventDispatcher<CollisionEvent>::Listener CollisionEventListener;

struct PointsCollectedEvent
{
	int points;
};

typedef EventDispatcher<PointsCollectedEvent> PointsCollectedEventDispatcher;
typedef EventDispatcher<PointsCollectedEvent>::Listener PointsCollectedEventListener;
#endif