#include "PlayerController.h"
#include "PathPosition.h"
#include "Movement.h"
#include "Collision.h"
#include "MyGame.h"
#include "Animator.h"
#include "Teleporter.h"
#include "Dot.h"

PlayerController::PlayerController()
{
	this->anim = nullptr;
	this->pathPosition = nullptr;
	this->movement = nullptr;
	this->prevInput = Vector2f(-1.0f, 0.0f);
	this->speed = 1.0f;
	this->tpLoc = nullptr;
	this->points = 0;
}

PlayerController::~PlayerController()
{
}

void PlayerController::OnEvent(const CollisionEvent& event, const CollisionEventDispatcher& other)
{
	switch (event.other->tag)
	{
		case TagManager::Ghost:
		{

		}
		break;
		case TagManager::Teleport:
		{
			if (event.type == CollisionType::OnEnter && tpLoc == nullptr)
			{
				Teleporter* teleporter = event.other->GetComponent<Teleporter>();
				Teleporter* otherTeleporter = teleporter->GetOtherTP();
				tpLoc = otherTeleporter;
				this->gameObject->pos = otherTeleporter->gameObject->pos;
				const unsigned int kCurrX = pathPosition->GetTilePosX();
				const unsigned int kCurrY = pathPosition->GetTilePosY();
				const unsigned int kNextDestinationX = (unsigned int)((int)kCurrX + (int)prevInput.X);
				const unsigned int kNextDestinationY = (unsigned int)((int)kCurrY + (int)prevInput.Y);
				movement->SetDesiredPos(kNextDestinationX, kNextDestinationY);
			}
			else if (event.type == CollisionType::OnExit && event.other == tpLoc->gameObject)
				tpLoc = nullptr;
		}
		break;
		case TagManager::Dot:
		{
			Dot* dot = event.other->GetComponent<Dot>();
			this->points += dot->GetAddedPoints();
			PointsCollectedEvent pointsCollectedEvent;
			pointsCollectedEvent.points = this->points;
			Invoke(pointsCollectedEvent);
			MyGame::Instance->DestroyGameObject(event.other);
		}
		break;
		case TagManager::BigDot:
		{
			Dot* dot = event.other->GetComponent<Dot>();
			this->points += dot->GetAddedPoints();
			PointsCollectedEvent pointsCollectedEvent;
			pointsCollectedEvent.points = this->points;
			Invoke(pointsCollectedEvent);
			MyGame::Instance->DestroyGameObject(event.other);
		}
		break;
	}
}	

void PlayerController::Start()
{
	this->movement = gameObject->GetComponent<Movement>();
	this->pathPosition = gameObject->GetComponent<PathPosition>();
	this->anim = gameObject->GetComponent<Animator>();
}

void PlayerController::SetPlayerSpeed(const float speed)
{
	this->speed = speed;
}

void PlayerController::Update(const float dt)
{
	if (movement->ReachedDesiredPos())
	{
		const Vector2f playerInput = MyGame::Instance->TakeInput();

		const unsigned int currentPosX = movement->GetCurrentPosX();
		const unsigned int currentPosY = movement->GetCurrentPosY();
		unsigned int expectedPosX = (unsigned int)((int)currentPosX + (int)playerInput.X);
		unsigned int expectedPosY = (unsigned int)((int)currentPosY + (int)playerInput.Y);

		if (!movement->SetDesiredPos(expectedPosX, expectedPosY) || playerInput.Length() == 0.f)
		{
			expectedPosX = (unsigned int)((int)currentPosX + (int)prevInput.X);
			expectedPosY = (unsigned int)((int)currentPosY + (int)prevInput.Y);
			movement->SetDesiredPos(expectedPosX, expectedPosY);
		}
		else
			prevInput = playerInput;
	}

	unsigned int desiredPosX = movement->GetDesiredPosX();
	unsigned int desiredPosY = movement->GetDesiredPosY();
	Vector2f finalPos = pathPosition->GetTileWorldPos(desiredPosX, desiredPosY);
	Vector2f dir = finalPos - gameObject->pos;

	const float moveSpeed = dt * speed;
	if (dir.Length() < moveSpeed)
	{
		unsigned int goToX = movement->GetDesiredPosX();
		unsigned int goToY = movement->GetDesiredPosY();

		movement->SetCurrentPos(goToX, goToY);
		gameObject->pos = finalPos;
	}
	else
	{
		dir.Normalize();
		gameObject->pos += dir * moveSpeed;
	}

	float rot = 0.f;
	if (prevInput.Y < 0.f)
		rot = 90.f;

	else if (prevInput.Y > 0.f)
		rot = -90.f;

	this->anim->SetRotation(rot);

	bool flipX = (prevInput.X < 0.f);
	if (!flipX)
		rot *= -1;

	this->anim->SetFlip(flipX, false);
}
